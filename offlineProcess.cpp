#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>

#include "TGraph.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TLegend.h"
#include "TFile.h"
#include "TTree.h"

TTree * theTree = new TTree("theTree", "theTree");
TFile * theFile = new TFile("chi2dist.root", "RECREATE");
TH1D * theHistogram = new TH1D("theHistogram", "Delta-Chisquare Distribution", 50, 0, 10);
void makeRoot();
void makeHistogram();

void makeRoot() {
  for (int i = 9; i < 10; i++) {
    theTree->ReadFile(Form("chi2dist_%i", i), "chi2");
  }

  theTree->Write();
  theFile->Write();

  return;
}

void makeHistogram() {
  int nentry = theTree->GetEntries();
  double dchi2;
  theTree->SetBranchAddress("chi2", &dchi2);
  for (int i = 0; i < nentry; i++) {
    theTree->GetEntry(i);
    theHistogram->Fill(dchi2);
  }

  return;
}

void drawHistogram() {
  TCanvas * theCanvas = new TCanvas();
  theHistogram->Draw();
  theCanvas->SaveAs("dchi2.eps");

  return;
}

int main() {
  makeRoot();
  makeHistogram();
  drawHistogram();

  return 0;
}
