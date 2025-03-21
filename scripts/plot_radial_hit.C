// build/reroot
// .L Tasneem_script.C
// main()

#include <TF1.h>

void plot_radial_hit()
{
  TChain* T = new TChain("T");
T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_1.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_2.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_3.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_4.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_5.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_6.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_7.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_8.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_9.root");
T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_10.root");

  Double_t rate = 0;
  std::vector<remollEventParticle_t>* parts = 0;
  std::vector<remollGenericDetectorHit_t>* hits = 0;

  T->SetBranchAddress("rate", &rate);
  T->SetBranchAddress("hit", &hits);
  T->SetBranchAddress("part", &parts);

  TH2F* xy_main = new TH2F("xy_main", "x and y ", 40, -2000, 2000, 40, -2000, 2000);
  xy_main->GetXaxis()->SetTitle("x [mm]");
  xy_main->GetYaxis()->SetTitle("y [mm]");

  //Loop over the entries
  for (size_t iev = 0; iev < T->GetEntries(); iev++)
  {
    T->GetEntry(iev);

    //Loop over hits
    for (size_t ihit = 0; ihit < hits->size(); ihit++)
    {
      remollGenericDetectorHit_t hit = hits->at(ihit);

      //fill if hit on main det
      if(hit.det==8000 && hit.pid == -22)
      {
        xy_main->Fill(-hit.x,hit.y);
      }

    }//hit loop
  }//entry loop

  TCanvas *c1 = new TCanvas("c1","hits on 8000",100,100,500,500);
  xy_main -> Draw();

  c1->SaveAs("images/test.png"); // open with "eog images/te
}//end script

