void showermax_rz_distribution_for_mollergen()
{
  TChain* T = new TChain("T");
 
  T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_1.root");
  T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_2.root");
  T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_3.root");
  T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_4.root");
  T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_5.root");
  T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_6.root");
  T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_7.root");
  T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_8.root");
  T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_9.root");
  T->Add("/volatile/halla/moller12gev/tasneemm/showermax_events_for_mollergen_10.root");
 
 
  Double_t rate = 0;
  std::vector<remollEventParticle_t>* parts = 0;
  std::vector<remollGenericDetectorHit_t>* hits = 0;
 
  T->SetBranchAddress("rate", &rate);
  T->SetBranchAddress("hit", &hits);
  T->SetBranchAddress("part", &parts);
 
 
  // Histogram for R vs Z
  TH2F* rz_main = new TH2F("rz_main", "R vs Z hits on showermax", 100, 10000, 25000, 100, 0, 5000);
 
  // Loop over the entries
  for (size_t iev = 0; iev < T->GetEntries(); iev++)
  {
    T->GetEntry(iev);
 
    // Loop over hits
    for (size_t ihit = 0; ihit < hits->size(); ihit++)
    {
      remollGenericDetectorHit_t hit = hits->at(ihit);
      // Fill if hit on Showermax tungsten and quartz
      if (
        hit.det == 7001 || hit.det == 7011 || hit.det == 7021 || hit.det == 7031 || hit.det == 7041 ||
        hit.det == 7051 || hit.det == 7061 || hit.det == 7071 || hit.det == 7081 || hit.det == 7091 ||
        hit.det == 7101 || hit.det == 7111 || hit.det == 7121 || hit.det == 7131 || hit.det == 7141 ||
        hit.det == 7151 || hit.det == 7161 || hit.det == 7171 || hit.det == 7181 || hit.det == 7191 ||
        hit.det == 7201 || hit.det == 7211 || hit.det == 7221 || hit.det == 7231 || hit.det == 7241 ||
        hit.det == 7251 || hit.det == 7261 || hit.det == 7271)
      {
 
        // Calculate R and fill R vs Z histogram
        Double_t R = TMath::Sqrt(hit.x * hit.x + hit.y * hit.y);

        rz_main->Fill( hit.z, R);
      }
    } // End of hit loop
  } // End of entry loop
 
  // Create canvas and draw histograms
  TCanvas *c1 = new TCanvas("c1", "hits on showermax", 100, 100, 1000, 500);

  rz_main->Draw();
}
