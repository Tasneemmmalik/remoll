#include "/work/halla/moller12gev/tasneemm/remoll/include/remollToQsim.hh"
#include "/work/halla/moller12gev/tasneemm/remoll/include/shower-max_resposne_lookup.hh"

void showermax_hit_position_vs_pe() {
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
 // Define a 2D histogram for PE yield vs. detector position
  TH2D* h_pe_vs_position = new TH2D("h_pe_vs_position", "PE Yield vs. Detector Position; X (mm); Y (mm); PE", 100, -2000, 2000, 100, -2000, 2000);
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
                if (pid == 11 && (hit.trid == 1 || hit.trid == 2)) {
              h_pe_vs_position->Fill(hitx, hity, pe);
              }
              else if(pid == 22 || pid == 13 || pid == 211 || pid == 2112){
             h_pe_vs_position->Fill(hitx, hity, pe);
           }
          }
        }

      }
// Create a canvas for the 2D histogram
TCanvas* c4 = new TCanvas("c4", "PE Yield vs. Detector Position", 800, 600);

// Set z-axis (color scale) to logarithmic
///c4->SetLogz();

// Draw the 2D histogram
h_pe_vs_position->Draw("COLZ");

 }

