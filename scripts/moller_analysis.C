void moller_analysis() {
    TChain* T_moller = new TChain("T");

    // Add Møller simulation files
    T_moller->Add("/volatile/halla/moller12gev/tasneemm/mollergen_1.root");
    T_moller->Add("/volatile/halla/moller12gev/tasneemm/mollergen_2.root");
    T_moller->Add("/volatile/halla/moller12gev/tasneemm/mollergen_3.root");
    T_moller->Add("/volatile/halla/moller12gev/tasneemm/mollergen_4.root");
    T_moller->Add("/volatile/halla/moller12gev/tasneemm/mollergen_5.root");
    T_moller->Add("/volatile/halla/moller12gev/tasneemm/mollergen_6.root");
    T_moller->Add("/volatile/halla/moller12gev/tasneemm/mollergen_7.root");
    T_moller->Add("/volatile/halla/moller12gev/tasneemm/mollergen_8.root");
    T_moller->Add("/volatile/halla/moller12gev/tasneemm/mollergen_9.root");
    T_moller->Add("/volatile/halla/moller12gev/tasneemm/mollergen_10.root");


    Double_t rate;
    std::vector<remollEventParticle_t>* parts = 0;
    std::vector<remollGenericDetectorHit_t>* hits = 0;

    // Set branch addresses
    T_moller->SetBranchAddress("rate", &rate);
    T_moller->SetBranchAddress("hit", &hits);
    T_moller->SetBranchAddress("part", &parts);

    // Create histograms
    TH2F* h_energy_angle_moller = new TH2F("h_energy_angle_moller", "Energy-Angle Correlation (Moller);Angle [degree];Energy [GeV]", 200, 0, 10, 200, 0, 11);
    TH1F* pe_yield = new TH1F("pe_yield","photoelectron yield;photoelectrons;events", 100, 0, 300);
    // Process Møller events
    for (size_t iev = 0; iev < T_moller->GetEntries(); ++iev) {
        T_moller->GetEntry(iev);
        remollEventParticle_t part = parts->at(1);
        Double_t angle = 0;
        Double_t energy = 0; 
        angle = part.th;
       energy = part.p;
        int npe = 0;
        for (size_t ihit = 0; ihit < hits->size(); ihit++) {
            remollGenericDetectorHit_t hit = hits->at(ihit);

            if (hit.det == 28 && (hit.trid == 1 || hit.trid == 2)) {
                h_energy_angle_moller->Fill(angle* (180.0 / TMath::Pi()), energy/ 1000);

            } else if (hit.det == 8000 && hit.pid == -22) {
                npe++;
            }//end of if loop

        }//end of hit loop      

      if (npe > 0){
       pe_yield ->Fill(npe);
     }

    }//end of event loop

    // Draw histograms
    TCanvas* c1 = new TCanvas("c1", "Moller Analysis", 1200, 800);
    c1->Divide(2, 1);
    c1->cd(1);
    h_energy_angle_moller->Draw("COLZ");
    c1->cd(2);
    pe_yield->Draw();
}

