#include "/work/halla/moller12gev/tasneemm/remoll/include/remollToQsim.hh"
#include "/work/halla/moller12gev/tasneemm/remoll/include/shower-max_resposne_lookup.hh"

void showermax_response_for_mollergen() {
    std::vector<remollGenericDetectorHit_t>* hits = 0;
    Double_t rates = 0; 

    // Get the fit parameters
    vector<vector<Double_t>> fit_data_electron = retrieve_fit_data("e-");
    vector<vector<Double_t>> fit_data_gamma = retrieve_fit_data("gamma");
    vector<vector<Double_t>> fit_data_mu = retrieve_fit_data("mu-");
    vector<vector<Double_t>> fit_data_pi = retrieve_fit_data("pi-");
    vector<vector<Double_t>> fit_data_neutron = retrieve_fit_data("neutron");

    // Make a map of pid and fit_data
    map<int, vector<vector<Double_t>>> map_fit_data;
    map_fit_data[11] = fit_data_electron;
    map_fit_data[-11] = fit_data_electron;
    map_fit_data[22] = fit_data_gamma;
    map_fit_data[13] = fit_data_mu;
    map_fit_data[-13] = fit_data_mu;
    map_fit_data[211] = fit_data_pi;
    map_fit_data[-211] = fit_data_pi;
    map_fit_data[2112] = fit_data_neutron;

    // Test pe response
    cout << "PE: " << get_PE_response(map_fit_data[11], 8234, 0, 0) << endl;
    cout << "PE: " << get_PE_response(map_fit_data[-11], 8234, 0, 0) << endl;
    cout << "PE: " << get_PE_response(map_fit_data[22], 8234, 0, 0) << endl;
    cout << "PE: " << get_PE_response(map_fit_data[13], 8234, 0, 0) << endl;
    cout << "PE: " << get_PE_response(map_fit_data[-13], 8234, 0, 0) << endl;
    cout << "PE: " << get_PE_response(map_fit_data[211], 8234, 0, 0) << endl;  

    // root files
    TChain* T = new TChain("T");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_10.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_9.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_8.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_7.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_6.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_5.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_4.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_3.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_2.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_1.root");

    // Set branch addresses
    T->SetBranchAddress("hit", &hits);
    T->SetBranchAddress("rate", &rates);

    // Define histograms for each particle type
    TH1D* h_pe_electron = new TH1D("h_pe_electron", "Photoelectron Yield (Electrons); PE; Counts", 100, 0, 1000);
    TH1D* h_pe_gamma = new TH1D("h_pe_gamma", "Photoelectron Yield (Gammas); PE; Counts", 100, 0, 1000);
    TH1D* h_pe_muon = new TH1D("h_pe_muon", "Photoelectron Yield (Muons); PE; Counts", 100, 0, 500);
    TH1D* h_pe_pion = new TH1D("h_pe_pion", "Photoelectron Yield (Pions); PE; Counts", 100, 0, 500);
    TH1D* h_pe_neutron = new TH1D("h_pe_neutron", "Photoelectron Yield (Neutrons); PE; Counts", 100, 0, 500);

    // Loop over all events
    for (size_t iev = 0; iev < T->GetEntries(); iev++) {
        T->GetEntry(iev);

        // Loop over all hits
        for (size_t ihit = 0; ihit < hits->size(); ihit++) {
            remollGenericDetectorHit_t hit = hits->at(ihit); 

            // Apply detector and z-position cuts
            if ((hit.det == 7001 || hit.det == 7011 || hit.det == 7021 || hit.det == 7031 || hit.det == 7041 ||
                 hit.det == 7051 || hit.det == 7061 || hit.det == 7071 || hit.det == 7081 || hit.det == 7091 ||
                 hit.det == 7101 || hit.det == 7111 || hit.det == 7121 || hit.det == 7131 || hit.det == 7141 ||
                 hit.det == 7151 || hit.det == 7161 || hit.det == 7171 || hit.det == 7181 || hit.det == 7191 ||
                 hit.det == 7201 || hit.det == 7211 || hit.det == 7221 || hit.det == 7231 || hit.det == 7241 ||
                 hit.det == 7251 || hit.det == 7261 || hit.det == 7271) && hit.z > 23000) {

                // Extract hit properties
                int pid = hit.pid;
                double energy = hit.e;
                double hitx = hit.x;
                double hity = hit.y;

                // Calculate photoelectron yield
                std::pair<double, double> qsimxy = ConvertRemollToQsim(hitx, hity);
                Double_t pe = get_PE_response(map_fit_data[pid], energy, qsimxy.first, qsimxy.second);

                // Fill histograms based on particle type
                if ((pid == 11 || pid == -11) && (hit.trid == 1 || hit.trid == 2)) {
                    h_pe_electron->Fill(pe);
                } else if (pid == 22 && energy > 10) {
                    h_pe_gamma->Fill(pe);
                } else if (pid == 13 || pid == -13) {
                    h_pe_muon->Fill(pe);
                } else if (pid == 211 || pid == -211) {
                    h_pe_pion->Fill(pe);
                } else if (pid == 2112) {
                     h_pe_neutron->Fill(pe);


              }
            }
        }
    }

    // Create canvases and draw histograms

 // Draw histograms
    TCanvas* c1 = new TCanvas("c1", "Particle Counts", 1200, 800);
    c1->Divide(3, 2);


    c1->cd(1);
    gPad->SetLogy();
    h_pe_neutron->Draw();
    c1->cd(2);
    gPad->SetLogy();
   h_pe_pion->Draw();
    c1->cd(3);
   gPad->SetLogy();
  h_pe_muon->Draw();  
   c1->cd(4);
   gPad->SetLogy();
  h_pe_gamma->Draw();
   c1->cd(5);
   gPad->SetLogy();
  h_pe_electron->Draw();
}

