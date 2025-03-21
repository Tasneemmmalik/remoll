void pion_analysis(){

    TChain* T_pion = new TChain("T");

    // Add Pion simulation files
    T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_1.root");
    T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_2.root");
    T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_3.root");
    T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_4.root");
    T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_5.root");

    Double_t rate;
    std::vector<remollEventParticle_t>* parts = 0;
    std::vector<remollGenericDetectorHit_t>* hits = 0;

    // Set branch addresses
    T_pion->SetBranchAddress("rate", &rate);
    T_pion->SetBranchAddress("hit", &hits);
    T_pion->SetBranchAddress("part", &parts);

    // Create histograms
    TH2F* h_energy_angle_pion = new TH2F("h_energy_angle_pion", "Energy-Angle Correlation (Pion);Angle [mrad];Energy [GeV]", 200, 0, 20, 200, 0, 11);
    TH1F* h_radial_pion = new TH1F("h_radial_pion", "Radial Distribution (Pion);Radius [mm];Counts", 200, 0, 2000);
    TH1F* h_azimuthal_pion = new TH1F("h_azimuthal_pion", "Azimuthal Distribution (Pion);Phi [rad];Counts", 200, -TMath::Pi(), TMath::Pi());
    TH1F* h_energy_pion_det_pion = new TH1F("h_energy_pion_det_pion", "Energy Deposition in Pion Detector (Pion);Energy [MeV];Counts", 200, 0, 1000);
    TH1F* h_photoelectron_yield_pion = new TH1F("h_photoelectron_moller", "Photoelectron Distribution (Moller);Photoelectrons;Counts", 100, 0, 1000);
    // Process Pion events
    for (size_t iev = 0; iev < T_pion->GetEntries(); ++iev) {
        T_pion->GetEntry(iev);
        for (size_t ihit = 0; ihit < hits->size(); ihit++) {
            remollGenericDetectorHit_t hit = hits->at(ihit);
            if (hit.det == 28) {
                double angle = TMath::ATan2(TMath::Sqrt(hit.x * hit.x + hit.y * hit.y), hit.z) * 1000; // Convert to mrad
                h_energy_angle_pion->Fill(angle, hit.e);
                h_radial_pion->Fill(TMath::Sqrt(hit.x * hit.x + hit.y * hit.y));
                h_azimuthal_pion->Fill(TMath::ATan2(hit.y, hit.x));
            } else if (hit.det == 8000) {
                h_energy_pion_det_pion->Fill(hit.e * 1000); // Convert GeV to MeV
            } else if (hit.det == 8001) {
                h_photoelectron_yield_pion->Fill(hit.e); // Assuming energy deposit is proportional to PE yield
            }

        }
    }

    // Draw histograms
    TCanvas* c2 = new TCanvas("c2", "Pion Analysis", 1200, 800);
    c2->Divide(3, 2);
    c2->cd(1); h_energy_angle_pion->Draw("COLZ");
    c2->cd(2); h_radial_pion->Draw();
    c2->cd(3); h_azimuthal_pion->Draw();
    c2->cd(4); h_energy_pion_det_pion->SetLineColor(kBlue); h_energy_pion_det_pion->Draw();
    c2->cd(5); h_photoelectron_yield_pion->SetLineColor(kGreen); h_photoelectron_yield_pion->Draw();
}
