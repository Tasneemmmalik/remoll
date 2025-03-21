#include <TChain.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <vector>
#include <iostream>

void plot_phi_vs_z() {
    TChain* T = new TChain("T");
    
    // Add the necessary ROOT files (adjust paths as needed)
    T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_1.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_2.root");
    T->Add("/volatile/halla/moller12gev/tasneemm/pionTest_10222024_3.root");
    // Add more files if needed...

    // Define the variables to hold hit data
    std::vector<remollGenericDetectorHit_t>* hits = nullptr;

    // Set branch address for hit data
    T->SetBranchAddress("hit", &hits);

    // Create a 2D histogram with phi on x-axis (in degrees) and z on y-axis
    TH2F *hPhiVsZ = new TH2F("hPhiVsZ", "Hit Phi vs. Z;Phi (degrees);Z (mm)", 100, -180, 180, 100, -3000, 3000); // Adjust Z range if needed

    // Loop over all entries
    for (size_t iev = 0; iev < T->GetEntries(); iev++) {
        T->GetEntry(iev);

        // Loop over all hits
        for (size_t ihit = 0; ihit < hits->size(); ihit++) {
            remollGenericDetectorHit_t hit = hits->at(ihit);

            // Convert phi from radians to degrees
               double phi_deg = hit.ph * (180.0 / 3.141592653589793);
            if (hit.det == 8000){
            // Fill the histogram with phi (degrees) and z values of each hit
            hPhiVsZ->Fill(phi_deg, hit.z);
        }
       }
    }

    // Draw the histogram
    TCanvas *c1 = new TCanvas("c1", "Phi vs Z", 800, 600);
    hPhiVsZ->Draw("COLZ");  // Use color to represent density

    // Optional: Save the canvas as an image
    // c1->SaveAs("phi_vs_z.png");
}
