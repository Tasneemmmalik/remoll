void pe_yield () {

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

Double_t rate;

std::vector<remollEventParticle_t>* parts = 0;
std::vector<remollGenericDetectorHit_t>* hits = 0;

T->SetBranchAddress("hit", &hits);
T->SetBranchAddress("part", &parts);

TH1F* pe_yield = new TH1F("pe_yield","photoelectron yield;photoelectrons;counts", 100, 0, 1000);
for(size_t iev =0 ; iev < T->GetEntries(); iev++){
  T->GetEntry(iev);
 int npe = 0;
  for (size_t ihit = 0; ihit < hits->size(); ihit++){
   remollGenericDetectorHit_t hit = hits->at(ihit);

 
    if(hit.det == 8000 && hit.pid == -22){
    
     npe++;
    }//end of if loop

    }//end of hit loop  
   if (npe > 0){
   pe_yield->Fill(npe);
}
  }//end of event loop

TCanvas* c1 = new TCanvas("c1", "pe yield",1200, 800);

pe_yield-> Draw();

}
