//  Need to use reroot (CERN's root compiled with special remoll libraries, or root when you have linked to ibremoll.so, i.e. by a command like setenv LD_PRELOAD build/libremoll.so needs to have a subdirectory "images/" defined for the images to go to
//
//  Run using:
//   build/reroot
//   .L scripts/PowerDep.C
//   PowerDep()
//
//  Alternatively, you can type the following command directly in the terminal while in your remoll directory:
//  echo 'gROOT->LoadMacro("scripts/PowerDep.C"); PowerDep(); gSystem->Exit(0);' | build/reroot -b -l
//
//  Can put multiple root files in the script, and they will be chained together.
//
//  This script will plot the energy deposition (in MeV) of all particles hitting detector 1000, the detector for the blocker. It will weight the histogram such that the bins include how much energy is deposited. This way, when the integral of our histogram is taken, it will yield the power in W deposited onto the detector. Finally, the script will print the power value onto the histogram and save it as an image to the folder "remoll/images".

#include <TF1.h>
void PowerDep()
{
  //Allow Tree to use the root files that you call
  TChain* T = new TChain("T");

  //Add root files.
  T->Add("/volatile/halla/moller12gev/ktevans1/rootfiles2024/Pass4_Optics2_beam_2M.root");


  //Define variables that we will loop over later
  Double_t rate = 0;
  std::vector<remollEventParticle_t>* parts = 0;
  std::vector<remollGenericDetectorHit_t>* hits = 0;

  //Define some branches of the Tree (which is "T")
  T->SetBranchAddress("rate", &rate);
  T->SetBranchAddress("hit", &hits);
  T->SetBranchAddress("part", &parts);

  gROOT -> SetBatch(kTRUE);

  //Define variable for power
  double power = 0.0;

  double curr = 1e-6; //Beam current in A
  double nelec_s = curr/1.6e-19; //Number of electrons per second, electron rate
  Double_t scale = nelec_s/T->GetEntries(); //Electron rate divided by number of events in tree

//----------------------------------------------------------------------------

  //Define Histograms that we will fill later

  //This is a 1D histogram for the energy deposited on the blocker, detector 1000, for all particles
  TH1F *edep_blocker = new TH1F("edep_blocker","Sum of Energy Deposition on the Sieve", 100, 0, 11000);
  edep_blocker -> GetXaxis() -> SetTitle("Energy Deposited on Detector [MeV]");

//----------------------------------------------------------------------------

  //Here we are filling the histogram. The Form command is a variation on the C++ printf string operation, and here is allows us to change the name of the histograms and the cuts of the projections. The Project command is being used to fill the histogram instead of looping through events and using Fill. Project loops over the TTree T, filling that named histogram (first argument) with the contents of the sum.edep branch (second argument), with a cut so only the events passing the cut (3rd argument) are added into the histogram.

  T -> Project("edep_blocker", "sum.edep", Form("%g*sum.edep*(sum.det==1008 && sum.edep>1e-20)", scale)); //This specific histogram is "weighted" by multiplying the cut by sum.edep so that when it passes the cut the histogram is filled sum.edep times (instead of +1 logical increment). The energy value is added into the bins (incrementing +Edep rather than +1 count) so that the integral we take later is the total energy deposited.

//--------------------------------------------------------------------------------
//Draw and save the histograms

  //Create a canvas on which to draw the histograms
  TCanvas *blocker = new TCanvas("sieve","Particles Hitting the Sieve Detector", 1000, 1000, 1000, 1000);

  edep_blocker -> Draw();

  //Integrate over this histogram to get the power in W. J per MeV is 1.6e-13.
  power = edep_blocker -> Integral()*1.6e-13;
  //Print this value from the Integral and place it on the histogram
  printf("Power = %f W\n", power);
  TPaveLabel *Plab0 = new TPaveLabel(0.27, 0.76, 0.75, 0.87, Form("%5.4f W at %1.0f #muA", power, curr*1e6), "NDC");
  Plab0 -> Draw();

  //Save the canvas as an image in the director "remoll/images/"
  blocker -> SaveAs("images/PowerDep_Det1008_Pass4_Optics2_beam_2M.png");

}//end PowerDep()
