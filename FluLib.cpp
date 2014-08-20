#ifndef __CFORTRAN_LOADED
#include "cfortran.h"
#endif

#include <stdio.h>

#include <TROOT.h>
#include "Results.h"
#include <TTree.h>
#include <TFile.h>

#ifndef WIN32
#define myusrini myusrini_
#else
#define myusrini MYUSRINI
#endif

static TFile *RootFile = 0;
static TTree *RootTree = 0;
static Results *TheResults = 0;

extern "C" {
  void myusrini (Double_t &pluto)
  {
    printf("Executing MYUSRINI\n");
    RootFile = new TFile("Out.root","recreate");
    RootTree = new TTree("ResultsTree","Protons");
    RootTree->Branch("Results", "Results", &TheResults, 64000, 1);

    printf("%f\n", pluto);

  }
}

#ifndef WIN32
#define treefill treefill_
#else
#define treefill TREEFILL
#endif

extern "C" {
  void treefill(Int_t &ij, Double_t &econtr, Double_t &xa, Double_t &ya, Double_t &za,
		Double_t &txx, Double_t &tyy, Double_t &tzz)
  {
    if (TheResults) {
      delete TheResults;
      TheResults = 0;
    }

    TheResults = new Results(ij, econtr, xa, ya, za,
			     txx, tyy, tzz);
    RootTree->Fill();
  }
}

#ifndef WIN32
#define fileclose fileclose_
#else
#define fileclose FILECLOSE
#endif

extern "C" {
  void fileclose()
  {
    if (TheResults) {
      delete TheResults;
      TheResults = 0;
    }
    RootTree->Write();
    RootFile->Close();
  }
}

