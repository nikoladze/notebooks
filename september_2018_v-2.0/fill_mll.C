#include <iostream>
#include "TTree.h"
#include "TH1.h"
#include "TLorentzVector.h"

void fill_mll(TTree* tree, TH1F* hist) {

    UInt_t  lep_n;      //number of preselected leptons
    Float_t lep_pt[5],      //transverse momentum of the lepton
            lep_charge[5],  //charge of the lep
            lep_eta[5],     //pseudorapidity of the lepton
            lep_phi[5],     //azimuthal angle of the lepton
            lep_E[5];       //energy of the lepton

    // Just read nescessary branches
    tree->SetBranchAddress("lep_pt", &lep_pt);
    tree->SetBranchAddress("lep_eta", &lep_eta);
    tree->SetBranchAddress("lep_phi", &lep_phi);
    tree->SetBranchAddress("lep_E", &lep_E);
    tree->SetBranchAddress("lep_n", &lep_n);

    tree->SetBranchStatus("*", 0);
    tree->SetBranchStatus("lep_n", 1);
    tree->SetBranchStatus("lep_pt", 1);
    tree->SetBranchStatus("lep_eta", 1);
    tree->SetBranchStatus("lep_phi", 1);
    tree->SetBranchStatus("lep_E", 1);

    TLorentzVector leadinglep, secondlep;

    for (int i=0; i<tree->GetEntriesFast(); i++) {
        tree->GetEntry(i);
        if (!(i%1000000)) {
            std::cout << "Processing event " << i << std::endl;
        }
        leadinglep.SetPtEtaPhiE(lep_pt[0], lep_eta[0], lep_phi[0], lep_E[0]);
        secondlep.SetPtEtaPhiE(lep_pt[1], lep_eta[1], lep_phi[1], lep_E[1]);
        hist->Fill((leadinglep+secondlep).M()/1000.);
    }
}
