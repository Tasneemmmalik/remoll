void lucite_for_piongen () {

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

T->SetBranchAddress("hit", &hits);
TH2F* pion_xy = new TH2F("pion_xy","xy plot for lucite;hit.x;hit.y", 40, -2000, 2000, 40, -2000, 2000);
TCanvas* c1 =  new TCanvas("c1", "xy plot for lucite", 1200, 1200);
// Event loop
  for (size_t iev = 0; iev < T->GetEntries(); iev++){

   T->GetEntry(iev);

//hit loop
for (size_t ihit = 0;ihit < hits->size(); ihit++) {
   remollGenericDetectorHit_t hit = hits->at(ihit);

    if(hit.det == 8001) {
     
      pion_xy->Fill(hit.x, hit.y); 


     }//if loop
  }//hit loop
}//event loop
pion_xy->Draw();

}
