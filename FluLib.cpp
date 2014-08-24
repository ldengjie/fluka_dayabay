#ifndef __CFORTRAN_LOADED
#include "cfortran.h"
#endif

#include <stdio.h>

#include <TROOT.h>
//#include "Results.h"
#include <TTree.h>
#include <TFile.h>

#ifndef WIN32
#define myusrini myusrini_
#else
#define myusrini MYUSRINI
#endif

static TFile *RootFile = 0;
//static TTree *RootTree = 0;
//
static TTree *MuonTree = 0;
double MuInitKineE,MuInitTime,MuInitLocalX,MuInitLocalY,MuInitLocalZ,MuInitLocalXCos,MuInitLocalYCos,MuInitLocalZCos,MuOwsTrackLength,MuIwsTrackLength,MuMoTrackLength,MuLsTrackLength,MuGdLsTrackLength;
int    MuEventID,MuNumOfNeutron,MuNumOfIsotope,MuMuonCharge;

static TTree *IsoTree = 0;
double IsoDecayLoaclX,IsoDecayLoaclY,IsoDecayLoaclZ;
int    IsoEventID,IsoZ,IsoA;

static TTree *MichelTree = 0;
double MiLocalX,MiLocalY,MiLocalZ,MiKineE,MiMichelLocalTime;
int    MiEventID; 

static TTree *SpaTree = 0;
double Spax,Spay,Spaz,SpadE,Spatime,SpaquenchedDepE;
int    SpaEventID,SpaFlukaNumber,SpaEnergyDepositedType,SpaMotherFlukaNumber,SpaMotherInteractionType;

static TTree *NeuTree = 0;
double NeuInitKineE,NeuInitTime,NeuInitLocalX,NeuInitLocalY,NeuInitLocalZ,NeuCapLocalX,NeuCapLocalY,NeuCapLocalZ,NeuCapTime,NeuCapGammaESum;
int    NeuEventID,NeuCapGammaNum,NeuMotherFlukaNumber,NeuMotherInteractionType;

//static Results *TheResults = 0;

extern "C" {
  void myusrini (Double_t &pluto)
  {
    printf("Executing MYUSRINI\n");
    RootFile = new TFile("sim.root","recreate");
    MuonTree = new TTree("Muon","Muon");
	MuonTree->Branch("EventID",&MuEventID,"EventID/I");
	MuonTree->Branch("InitKineE",&MuInitKineE,"InitKineE/D");
	MuonTree->Branch("InitTime",&MuInitTime,"InitTime/D");
	MuonTree->Branch("InitLocalX",&MuInitLocalX,"InitLocalX/D");
	MuonTree->Branch("InitLocalY",&MuInitLocalY,"InitLocalY/D");
	MuonTree->Branch("InitLocalZ",&MuInitLocalZ,"InitLocalZ/D");
	MuonTree->Branch("InitLocalXCos",&MuInitLocalXCos,"InitLocalXCos/D");
	MuonTree->Branch("InitLocalYCos",&MuInitLocalYCos,"InitLocalYCos/D");
	MuonTree->Branch("InitLocalZCos",&MuInitLocalZCos,"InitLocalZCos/D");
	MuonTree->Branch("OwsTrackLength",&MuOwsTrackLength,"OwsTrackLength/D");
	MuonTree->Branch("IwsTrackLength",&MuIwsTrackLength,"IwsTrackLength/D");
	MuonTree->Branch("MoTrackLength",&MuMoTrackLength,"MoTrackLength/D");
	MuonTree->Branch("LsTrackLength",&MuLsTrackLength,"LsTrackLength/D");
	MuonTree->Branch("GdLsTrackLength",&MuGdLsTrackLength,"GdLsTrackLength/D");
	MuonTree->Branch("NumOfNeutron",&MuNumOfNeutron,"NumOfNeutron/I");
	MuonTree->Branch("NumOfIsotope",&MuNumOfIsotope,"NumOfIsotope/I");
	MuonTree->Branch("MuonCharge",&MuMuonCharge,"MuonCharge/I");
	
	IsoTree=new TTree("Isotope","Isotope");
	IsoTree->Branch("DecayLoaclX",&IsoDecayLoaclX,"DecayLoaclX/D");
	IsoTree->Branch("DecayLoaclY",&IsoDecayLoaclY,"DecayLoaclY/D");
	IsoTree->Branch("DecayLoaclZ",&IsoDecayLoaclZ,"DecayLoaclZ/D");
	IsoTree->Branch("EventID",&IsoEventID,"EventID/I");
	IsoTree->Branch("Z",&IsoZ,"Z/I");
	IsoTree->Branch("A",&IsoA,"A/I");
	
	MichelTree=new TTree("MichelElectron","MichelElectron");
	MichelTree->Branch("LocalX",&MiLocalX,"LocalX/D");
	MichelTree->Branch("LocalY",&MiLocalY,"LocalY/D");
	MichelTree->Branch("LocalZ",&MiLocalZ,"LocalZ/D");
	MichelTree->Branch("KineE",&MiKineE,"KineE/D");
	MichelTree->Branch("MichelLocalTime",&MiMichelLocalTime,"MichelLocalTime/D");
	MichelTree->Branch("EventID",&MiEventID,"EventID/I");
	
	SpaTree=new TTree("Spallation","Spallation");
	SpaTree->Branch("x",&Spax,"x/D");
	SpaTree->Branch("y",&Spay,"y/D");
	SpaTree->Branch("z",&Spaz,"z/D");
	SpaTree->Branch("dE",&SpadE,"dE/D");
	SpaTree->Branch("time",&Spatime,"time/D");
	SpaTree->Branch("quenchedDepE",&SpaquenchedDepE,"quenchedDepE/D");
	SpaTree->Branch("EventID",&SpaEventID,"EventID/I");
	SpaTree->Branch("FlukaNumber",&SpaFlukaNumber,"FlukaNumber/I");
	SpaTree->Branch("EnergyDepositedType",&SpaEnergyDepositedType,"EnergyDepositedType/I");
	SpaTree->Branch("MotherFlukaNumber",&SpaMotherFlukaNumber,"MotherFlukaNumber/I");
	SpaTree->Branch("MotherInteractionType",&SpaMotherInteractionType,"MotherInteractionType/I");

    //RootTree->Branch("Results", "Results", &TheResults, 64000, 1);
    NeuTree = new TTree("Neutron","Neutron");
	NeuTree->Branch("InitKineE",&NeuInitKineE,"InitKineE/D");
	NeuTree->Branch("InitTime",&NeuInitTime,"InitTime/D");
	NeuTree->Branch("InitLocalX",&NeuInitLocalX,"InitLocalX/D");
	NeuTree->Branch("InitLocalY",&NeuInitLocalY,"InitLocalY/D");
	NeuTree->Branch("InitLocalZ",&NeuInitLocalZ,"InitLocalZ/D");
	NeuTree->Branch("CapLocalX",&NeuCapLocalX,"CapLocalX/D");
	NeuTree->Branch("CapLocalY",&NeuCapLocalY,"CapLocalY/D");
	NeuTree->Branch("CapLocalZ",&NeuCapLocalZ,"CapLocalZ/D");
	NeuTree->Branch("CapTime",&NeuCapTime,"CapTime/D");
	NeuTree->Branch("CapGammaESum",&NeuCapGammaESum,"CapGammaESum/D");
	NeuTree->Branch("EventID",&NeuEventID,"EventID/I");
	NeuTree->Branch("CapGammaNum",&NeuCapGammaNum,"CapGammaNum/I");
	NeuTree->Branch("MotherFlukaNumber",&NeuMotherFlukaNumber,"MotherFlukaNumber/I");
	NeuTree->Branch("MotherInteractionType",&NeuMotherInteractionType,"MotherInteractionType/I");

    printf("%f\n", pluto);

  }
}
//
//#ifndef WIN32
//#define treefill treefill_
//#else
//#define treefill TREEFILL
//#endif
//
//extern "C" {
//void treefill(Int_t &ij, Double_t &econtr, Double_t &xa, Double_t &ya, Double_t &za,
//Double_t &txx, Double_t &tyy, Double_t &tzz)
//{
////if (TheResults) {
////delete TheResults;
////TheResults = 0;
////}
//
////TheResults = new Results(ij, econtr, xa, ya, za,
////txx, tyy, tzz);
//RootTree->Fill();
//}
//}
#ifndef WIN32
#define fillmuon fillmuon_
#else
#define fillmuon FILLMUON
#endif
extern "C" {
  void fillmuon( int m_MuEventID,int m_MuMuonCharge,double m_MuInitKineE,double m_MuInitTime,double m_MuInitLocalX,double m_MuInitLocalY,double m_MuInitLocalZ,double m_MuInitLocalXCos,double m_MuInitLocalYCos,double m_MuInitLocalZCos,double m_MuOwsTrackLength,double m_MuIwsTrackLength,double m_MuMoTrackLength,double m_MuLsTrackLength,double m_MuGdLsTrackLength,int m_MuNumOfNeutron,int m_MuNumOfIsotope)
  {
	MuEventID         = m_MuEventID;
	MuInitKineE       = m_MuInitKineE;
	MuInitTime        = m_MuInitTime;
	MuInitLocalX      = m_MuInitLocalX;
	MuInitLocalY      = m_MuInitLocalY;
	MuInitLocalZ      = m_MuInitLocalZ;
	MuInitLocalXCos   = m_MuInitLocalXCos;
	MuInitLocalYCos   = m_MuInitLocalYCos;
	MuInitLocalZCos   = m_MuInitLocalZCos;
	MuOwsTrackLength  = m_MuOwsTrackLength;
	MuIwsTrackLength  = m_MuIwsTrackLength;
	MuMoTrackLength   = m_MuMoTrackLength;
	MuLsTrackLength   = m_MuLsTrackLength;
	MuGdLsTrackLength = m_MuGdLsTrackLength;
	MuNumOfNeutron    = m_MuNumOfNeutron;
	MuNumOfIsotope    = m_MuNumOfIsotope;
	MuMuonCharge      = m_MuMuonCharge     ;
    MuonTree->Fill();
  }
}

#ifndef WIN32
#define filliso filliso_
#else
#define filliso FILLISO
#endif
extern "C" {
  void filliso(int m_IsoEventID,int m_IsoZ,int m_IsoA,double m_IsoDecayLoaclX,double m_IsoDecayLoaclY,double m_IsoDecayLoaclZ)
  {
	IsoDecayLoaclX = m_IsoDecayLoaclX;
	IsoDecayLoaclY = m_IsoDecayLoaclY;
	IsoDecayLoaclZ = m_IsoDecayLoaclZ;
	IsoEventID     = m_IsoEventID;
	IsoZ           = m_IsoZ;
	IsoA           = m_IsoA;
    IsoTree->Fill();
  }
}

#ifndef WIN32
#define fillmi     fillmi_
#else
#define fillmi     FILLMI    
#endif
extern "C" {
  void fillmi(int m_MiEventID,double m_MiKineE,double m_MiMichelLocalTime,double m_MiLocalX,double m_MiLocalY,double m_MiLocalZ)
  {
	MiLocalX          = m_MiLocalX;          
	MiLocalY          = m_MiLocalY;
	MiLocalZ          = m_MiLocalZ;
	MiKineE           = m_MiKineE;
	MiMichelLocalTime = m_MiMichelLocalTime;
	MiEventID         = m_MiEventID; 
    MichelTree->Fill();
  }
}

#ifndef WIN32
#define fillspa fillspa_
#else
#define fillspa FILLSPA
#endif
extern "C" {
  void fillspa(double m_Spax,double m_Spay,double m_Spaz,double m_SpadE,double m_Spatime,double m_SpaquenchedDepE, int    m_SpaEventID,int m_SpaFlukaNumber,int m_SpaEnergyDepositedType,int m_SpaMotherFlukaNumber,int m_SpaMotherInteractionType)
  {
	Spax                     = m_Spax;
	Spay                     = m_Spay;
	Spaz                     = m_Spaz;
	SpadE                    = m_SpadE;
	Spatime                  = m_Spatime;
	SpaquenchedDepE          = m_SpaquenchedDepE;
	SpaEventID               = m_SpaEventID;
	SpaFlukaNumber           = m_SpaFlukaNumber;
	SpaEnergyDepositedType   = m_SpaEnergyDepositedType;
	SpaMotherFlukaNumber     = m_SpaMotherFlukaNumber;
	SpaMotherInteractionType = m_SpaMotherInteractionType;
    SpaTree->Fill();
  }
}

#ifndef WIN32
#define fillneu fillneu_
#else
#define fillneu FILLNEU
#endif
extern "C" {
  void fillneu(int    m_NeuEventID,double m_NeuInitKineE,double m_NeuInitTime,double m_NeuInitLocalX,double m_NeuInitLocalY,double m_NeuInitLocalZ,double m_NeuCapLocalX,double m_NeuCapLocalY,double m_NeuCapLocalZ,double m_NeuCapTime,double m_NeuCapGammaESum,int m_NeuCapGammaNum,int m_NeuMotherFlukaNumber,int m_NeuMotherInteractionType)
  {
	NeuInitKineE              = m_NeuInitKineE;
	NeuInitTime               = m_NeuInitTime;
	NeuInitLocalX             = m_NeuInitLocalX;
	NeuInitLocalY             = m_NeuInitLocalY;
	NeuInitLocalZ             = m_NeuInitLocalZ;
	NeuCapLocalX              = m_NeuCapLocalX;
	NeuCapLocalY              = m_NeuCapLocalY;
	NeuCapLocalZ              = m_NeuCapLocalZ;
	NeuCapTime                = m_NeuCapTime;
	NeuCapGammaESum           = m_NeuCapGammaESum;
	NeuEventID                = m_NeuEventID;
	NeuCapGammaNum            = m_NeuCapGammaNum;
	NeuMotherFlukaNumber      = m_NeuMotherFlukaNumber;
	NeuMotherInteractionType  = m_NeuMotherInteractionType ;
    MuonTree->Fill();
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
      //if (TheResults) {
      //delete TheResults;
      //TheResults = 0;
      //}
    MuonTree->Write();
    NeuTree->Write();
    IsoTree->Write();
    SpaTree->Write();
    MichelTree->Write();
    RootFile->Close();
  }
}

