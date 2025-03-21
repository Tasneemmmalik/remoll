void lucite_for_mollergen () {
TChain* T = new TChain("T");
 // Add Møller simulation files
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_1.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_2.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_3.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_4.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_5.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_6.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_7.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_8.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_9.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_10.root");


    std::vector<remollGenericDetectorHit_t>* hits = 0;

T->SetBranchAddress("hit", &hits);
TH2F* pion_xy = new TH2F("pion_xy","xy plot for lucite for mollergen;hit.x;hit.y", 40, -2000, 2000, 40, -2000, 2000);
TCanvas* c1 =  new TCanvas("c1", "xy plot for lucite for mollergen", 1200, 1200);
// Event loop
  for (size_t iev = 0; iev < T->GetEntries(); iev++){

   T->GetEntry(iev);

//hit loop
for (size_t ihit = 0;ihit < hits->size(); ihit++) {
   remollGenericDetectorHit_t hit = hits->at(ihit);

    if(hit.det == 8001 && hit.pid == 22) {
     
      pion_xy->Fill(hit.x, hit.y); 


     }//if loop
  }//hit loop
}//event loop
pion_xy->Draw();

}
