#include <TF1.h>

//#include "remollGenericDetectorHit.hh"
void hit_script() {
  //TFile *file = new TFile("/volatile/halla/moller12gev/tasneemm/showermax_piondetector_optical_response_moller_10062024_1.root");
    //TTree *tree = (TTree*)file->Get("T");

    TChain* T = new TChain("T");
    T->Add("/volatile/halla/moller12gev/tasneemm/showermax_piondetector_optical_response_moller_10062024_1.root");
    
    std::vector<remollGenericDetectorHit_t>* hits = 0;
    T->SetBranchAddress("hit", &hits);

    //T->print();

    
    TH2F *hist = new TH2F("hist", "Histogram of hit.x vs hit.y", 100, -2000, 2000, 100, -2000, 2000);

    for (size_t iev = 0; iev < T->GetEntries(); iev++) {
        T->GetEntry(iev);

        for (size_t ihit = 0; ihit < hits->size(); ihit++) {

	  remollGenericDetectorHit_t hit  = hits->at(ihit);
            //Double_t hit_x = hits->at(ihit).x;
            //Double_t hit_y = hits->at(ihit).y;
            //Int_t hit_det = hits->at(ihit).det;
            //Int_t hit_trid = hits->at(ihit).trid;

            //if ((hit.det == 28 && hit.trid == 1) || (hit.det == 28 && hit.trid == 2)) {
	  //  hist->Fill(hit.x, hit.y);
	  //}

	  if(hit.det == 28)
	    {
	      hist -> Fill(-hit.x,hit.y);
	    }
        }//end hit loop
    }//end entry loop

    hist->Draw();
}
