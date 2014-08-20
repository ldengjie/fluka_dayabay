
using namespace std;

#include "Results.h"
#include "iostream"

ClassImp(Results)

Results::Results(Int_t ijj, Double_t econtrr, Double_t xaa,
		 Double_t yaa, Double_t zaa,
		 Double_t txxx, Double_t tyyy, Double_t tzzz)
{
  ij = ijj;
  econtr = econtrr;
  xa = xaa;
  ya = yaa;
  za = zaa;
  txx = txxx;
  tyy = tyyy;
  tzz = tzzz;

  cout << ij << " " << econtr << endl;

}

Results::~Results()
{
}


