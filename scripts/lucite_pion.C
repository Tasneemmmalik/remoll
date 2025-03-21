void lucite_pion () {

TChain* T = new TChain("T");
T->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_1.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_2.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_3.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_4.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_5.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_6.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_7.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_8.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_9.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pion_06112024_10.root");

    std::vector<remollGenericDetectorHit_t>* hits = 0;
    std::vector<remollEventParticle_t>* parts = 0;

    T->SetBranchAddress("hit", &hits);
    T->SetBranchAddress("part", &parts);

    TH1F* h_npn = new TH1F("h_npn", " pe yield (pions); photoelectrons;events", 100, 0, 300);
    TH1F* h_nmn = new TH1F("h_nmn", "pe yield (muons);photoelectrons;events", 100, 0, 300);
    TH1F* h_npo = new TH1F("h_npo", "pe Yield (gamma rays);photoelectrons;events", 100, 0, 300);
    TH1F* h_nen = new TH1F("h_nen", "pe yield (electrons);photoelectrons;events", 100, 0, 300);
    TH1F* h_xpn = new TH1F("h_xpn", " pe yield (only pions); photoelectrons;events", 100, 0, 300);
    TH1F* h_xmn = new TH1F("h_xmn", " pe yield (only muons); photoelectrons;events", 100, 0, 300);
    TH1F* h_xpo = new TH1F("h_xpo", " pe yield (only gamma rays); photoelectrons;events", 100, 0, 300);
    TH1F* h_xen = new TH1F("h_xen", " pe yield (only electrons); photoelectrons;events", 100, 0, 300);
    // Event loop
    for (size_t iev = 0; iev < T->GetEntries(); iev++) {
        T->GetEntry(iev);

        bool npn = false; 
        bool nmn = false; 
        bool npo = false; 
        bool nen = false; 
        int npe = 0;
        // Hit loop
        for (size_t ihit = 0; ihit < hits->size(); ihit++) {
            remollGenericDetectorHit_t hit = hits->at(ihit);

            if (hit.det == 8001 && hit.pid == -211) { 
                npn = true;
            }

            if (hit.det == 8001 && hit.pid == 13) { 
                nmn = true;
            }


            if (hit.det == 8001 && hit.pid == 22) { 
                npo = true;
            }

            if (hit.det == 8001 && hit.pid == 11) {
                nen = true;
           }

          if(hit.det == 8000 && hit.pid == -22){
          npe ++;
          }

        }

        // Fill histograms
        if (npn > 0) h_npn->Fill(npe);
        if (nmn > 0) h_nmn->Fill(npe);
        if (npo > 0) h_npo->Fill(npe);
        if (nen > 0) h_nen->Fill(npe);
        if (npn > 0 && nmn == 0 && npo == 0 && nen == 0) h_xpn->Fill(npe);
        if (nmn > 0 && npn == 0 && npo == 0 && nen == 0) h_xmn->Fill(npe);
        if (npo > 0 && nmn == 0 && npn == 0 && nen == 0) h_xpo->Fill(npe);
        if (nen > 0 && nmn == 0 && npo == 0 && npn == 0) h_xen->Fill(npe);
    
}

    // Draw histograms
    TCanvas* c1 = new TCanvas("c1", "Particle Counts", 1200, 800);
    c1->Divide(4, 2);

    c1->cd(1);
    h_npn->Draw();

    c1->cd(2);
    h_nmn->Draw();

    c1->cd(3);
    h_npo->Draw();

    c1->cd(4);
    h_nen->Draw();

    c1->cd(5);
    h_xpn->Draw();

    c1->cd(6);
    h_xmn->Draw();
  
   c1->cd(7);
  h_xpo->Draw();

   c1->cd(8);
  h_xen->Draw();

}

