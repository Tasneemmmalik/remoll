void moller_pion_energy_correlation(){

TChain* T_moller = new TChain("T");
TChain* T_pion = new TChain("T");


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

    // Add pion simulation files
   T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_1.root");
   T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_2.root");
   T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_3.root");
   T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_4.root");
   T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_5.root");
   T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_6.root");
   T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_7.root");
   T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_8.root");
   T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_9.root");
   T_pion->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_10.root");

    Double_t rate;
    std::vector<remollEventParticle_t>* parts = 0;
    std::vector<remollGenericDetectorHit_t>* hits = 0;

    // Set branch addresses for both chains
    T_moller->SetBranchAddress("rate", &rate);
    T_moller->SetBranchAddress("hit", &hits);
    T_moller->SetBranchAddress("part", &parts);

    T_pion->SetBranchAddress("rate", &rate);
    T_pion->SetBranchAddress("hit", &hits);
    T_pion->SetBranchAddress("part", &parts);


  // Create histograms
    TH2F* h_energy_angle_moller = new TH2F("h_energy_angle_moller","Energy-Angle Correlation (Moller);Angle [mrad];Energy [GeV]", 200, 0, 20, 200, 0, 11);
    TH2F* h_energy_angle_pion = new TH2F("h_energy_angle_pion","Energy-Angle Correlation (Pion);Angle [mrad];Energy [GeV]", 200, 0, 20, 200, 0, 11);
    TH1F* h_azimuthal_moller = new TH1F("h_azimuthal_moller", "Azimuthal Distribution (Moller);Phi [rad];Counts", 200, -TMath::Pi(), TMath::Pi());
    TH1F* h_azimuthal_pion = new TH1F("h_azimuthal_pion", "Azimuthal Distribution (Pion);Phi [rad];Counts", 200, -TMath::Pi(), TMath::Pi());
    TH1F* h_radial_moller = new TH1F("h_radial_moller", "Radial Distribution (Moller);Radius [mm];Counts", 200, 0, 2000);
    TH1F* h_radial_pion = new TH1F("h_radial_pion", "Radial Distribution (Pion);Radius [mm];Counts", 200, 0, 2000);
    TH1F* h_energy_pion_det_moller = new TH1F("h_energy_pion_det_moller", "Energy Deposition in Pion Detector (Moller);Energy [MeV];Counts", 200, 0, 1000);
    TH1F* h_energy_pion_det_pion = new TH1F("h_energy_pion_det_pion", "Energy Deposition in Pion Detector (Pion);Energy [MeV];Counts", 200, 0, 1000);
    TH1F* h_pe_yield_moller = new TH1F("h_pe_yield_moller", "Photoelectron Yield (Moller);Photoelectrons;Counts", 200, 0, 1000);
    TH1F* h_pe_yield_pion = new TH1F("h_pe_yield_pion", "Photoelectron Yield (Pion);Photoelectrons;Counts", 200, 0, 1000);
 







// Process Møller events
    for (size_t iev = 0; iev < T_moller->GetEntries(); ++iev) {
        T_moller->GetEntry(iev);

        // Loop over all hits
        for (size_t ihit = 0; ihit < hits->size(); ihit++) {
            remollGenericDetectorHit_t hit = hits->at(ihit);

            if (hit.det >=70000 && hit.det == 90000) {
                double angle = TMath::ATan2(TMath::Sqrt(hit.x * hit.x + hit.y * hit.y), hit.z) * 1000; // Convert to mrad
                h_energy_angle_moller->Fill(angle, hit.e);
                h_radial_moller->Fill(TMath::Sqrt(hit.x * hit.x + hit.y * hit.y));
                h_azimuthal_moller->Fill(TMath::ATan2(hit.y, hit.x));
            } else if (hit.det == 8000) {
                h_energy_pion_det_moller->Fill(hit.e * 1000); // Convert GeV to MeV
            } else if (hit.det == 8001) {
                h_pe_yield_moller->Fill(hit.e); // Assuming energy deposit is proportional to PE yield
            }
        }
    }

    // Process Pion events
    for (size_t iev = 0; iev < T_pion->GetEntries(); ++iev) {
        T_pion->GetEntry(iev);

        // Loop over all hits
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
                h_pe_yield_pion->Fill(hit.e); // Assuming energy deposit is proportional to PE yield
            }
        }
    }






   TCanvas* c1 = new TCanvas("c1", "Main Detector Analysis", 1200, 800);
   TCanvas* c2 = new TCanvas("c2", "pion detector Analysis", 1200, 1000);
   c1->Divide(3, 2);
   c1->cd(1);
    h_energy_angle_moller->Draw();
    c1->cd(2);
    h_energy_angle_pion->Draw();
    c1->cd(3);
    h_radial_moller->Draw();
    c1->cd(4);
    h_radial_pion->Draw();  
   c1->cd(5);
    h_azimuthal_moller->Draw();
  c1->cd(6);
   h_azimuthal_pion->SetLineColor(kRed);

    h_azimuthal_pion->Draw();
    c2->Divide(2, 2);
    c2->cd(1);
   h_energy_pion_det_moller->SetLineColor(kRed);

    h_energy_pion_det_moller->Draw();
    c2->cd(2);
   h_energy_pion_det_pion->SetLineColor(kRed);
   h_energy_pion_det_pion->Draw();
   c2->cd(3);
  h_pe_yield_moller->SetLineColor(kRed);
  h_pe_yield_moller->Draw();
  c2->cd(4);
 h_pe_yield_pion->SetLineColor(kRed);
  h_pe_yield_pion->Draw();


}//main function
