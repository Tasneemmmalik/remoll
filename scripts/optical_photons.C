// build/reroot
// .L scripts/Tasneem_script.C
// main()

#include <TF1.h>

void optical_photons()
{

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
  Double_t rate = 0;
  std::vector<remollEventParticle_t>* parts = 0;
  std::vector<remollGenericDetectorHit_t>* hits = 0;

  T->SetBranchAddress("rate", &rate);
  T->SetBranchAddress("hit", &hits);
  T->SetBranchAddress("part", &parts);

  TH2F* xy_pion = new TH2F("xy_pion", "x and y hits on pion detector", 400, -2000, 2000, 400, -2000, 2000);
  xy_pion->GetXaxis()->SetTitle("x [mm]");
  xy_pion->GetYaxis()->SetTitle("y [mm]");

  TH2F* xy_lucite = new TH2F("xy_lucite", "x and y hits on pion detector lucite", 400, -2000, 2000, 400, -2000, 2000);
  xy_lucite->GetXaxis()->SetTitle("x [mm]");
  xy_lucite->GetYaxis()->SetTitle("y [mm]");

  //Loop over the entries
  for (size_t iev = 0; iev < T->GetEntries(); iev++)
  {
    T->GetEntry(iev);

    //Loop over hits
    for (size_t ihit = 0; ihit < hits->size(); ihit++)
    {
      remollGenericDetectorHit_t hit = hits->at(ihit);

      //fill if hit on main det
     if(hit.det >= 70000 && hit.det < 90000 && hit.pid == -22)
      {
        xy_pion->Fill(-hit.x,hit.y);
      }

      //fill if hit on main det
      if (hit.det==8001 && (hit.pid == -211 || hit.pid == 13))
      {
        xy_lucite->Fill(-hit.x,hit.y);
      }

    }//hit loop
  }//entry loop

  TCanvas *c1 = new TCanvas("c1","hits on main",1200,800);
  c1->Divide(2,1);
  c1->cd(1);
  xy_pion -> Draw();
  c1->cd(2);
  xy_lucite -> Draw();

  //c1->SaveAs("images/test.png"); // open with "eog images/test.png"

}//end script
