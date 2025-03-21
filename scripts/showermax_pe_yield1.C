#include <iostream>
#include <vector>
#include <map>

void showermax_pe_yield1() {
    TChain *T = new TChain("T");
    T->Add("/volatile/halla/moller12gev/tasneemm/mollergen_1.root");

    std::vector<remollGenericDetectorHit_t>* hits = 0;
    std::vector<remollEventParticle_t>* parts = 0;
    T->SetBranchAddress("hit", &hits);
    T->SetBranchAddress("part", &parts);

    TH1F* hist = new TH1F("hist", "PE Yield", 100, 0, 300);

    // Define a map for categorized energy bins
    std::map<std::string, std::vector<double>> edep_categories;

    // Define energy ranges
    std::vector<std::pair<double, double>> energy_ranges = {
        {0, 50}, {50, 100}, {100, 150}, {150, 200}, {200, 300}
    };

    // Initialize categories
    for (auto range : energy_ranges) {
        std::string label = std::to_string((int)range.first) + "-" + std::to_string((int)range.second);
        edep_categories[label] = std::vector<double>();
    }

    // Event loop
    for (size_t iev = 0; iev < T->GetEntries(); iev++) {
        T->GetEntry(iev);

        // Hit loop
        for (size_t ihit = 0; ihit < hits->size(); ihit++) {
            remollGenericDetectorHit_t hit = hits->at(ihit);

            // Filtering condition
            if (hit.det >= 70000 && hit.det < 90000 && hit.pid == 11) {
                hist->Fill(hit.edep);

                // Categorize into energy bins
                for (auto range : energy_ranges) {
                    if (hit.edep >= range.first && hit.edep < range.second) {
                        std::string label = std::to_string((int)range.first) + "-" + std::to_string((int)range.second);
                        edep_categories[label].push_back(hit.edep);
                        break;
                    }
                }
            }
        }
    }

    // Print categorized data
    std::cout << "Electron Energy Deposition Categories:\n";
    for (const auto& category : edep_categories) {
        std::cout << category.first << " GeV: " << category.second.size() << " hits\n";
    }

    // Draw histogram
    TCanvas *c1 = new TCanvas("c1", "PE Yield Histogram", 800, 600);
    hist->SetFillColor(kBlue);
    hist->Draw();
}
