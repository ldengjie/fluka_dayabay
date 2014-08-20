#ifndef ROOT_Results
#define ROOT_Results

#include "TObject.h"

class Results : public TObject {
  
 private:
  
  Int_t ij;
  Double_t econtr, xa, ya, za, txx, tyy, tzz;
  
 public:
  
  Results() : ij(0), econtr(0), xa(0), ya(0), 
    za(0), txx(0), tyy(0), tzz(0) {}
  Results(Int_t ijj, Double_t econtrr, Double_t xaa, 
	  Double_t yaa, Double_t zaa,
	  Double_t txxx, Double_t tyyy, Double_t tzzz);
  virtual ~Results();

  ClassDef(Results,1);

};

#endif
