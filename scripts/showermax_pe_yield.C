void showermax_pe_yield () {
TChain *T = new TChain("T");
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
   std::vector<remollEventParticle_t>* parts = 0;
   std::vector<double> edep_values;
   T->SetBranchAddress("hit", &hits);
   T->SetBranchAddress("part", &parts);
  
  TH1F* hist = new TH1F("hist", "pe yield", 100, 0, 300);
//event loop
  for(size_t iev = 0; iev < T->GetEntries(); iev++){
   T->GetEntry(iev);

//hit loop
      for(size_t ihit = 0; ihit < hits->size(); ihit++){
           remollGenericDetectorHit_t hit = hits->at(ihit);
// if loop
     if(hit.det >=70000 && hit.det < 90000 && hit.pid == 11) {

      edep_values.push_back(hit.edep);
       hist->Fill(hit.edep);


      }
     }
  
  }

std::cout <<"TOTAL HITS RECORDED" << edep_values.size()<< std::endl;
TCanvas *c1 = new TCanvas("c1", "pe yield histogram", 800, 600);
hist->SetFillColor(kBlue);
hist->Draw();


}
