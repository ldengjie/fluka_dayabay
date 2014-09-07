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
Double_t MuInitKineE,MuInitTime,MuInitLocalX,MuInitLocalY,MuInitLocalZ,MuInitLocalXCos,MuInitLocalYCos,MuInitLocalZCos,MuOwsTrackLength,MuIwsTrackLength,MuMoTrackLength,MuLsTrackLength,MuGdLsTrackLength=0.;
Int_t    MuEventID,MuNumOfNeutron,MuNumOfIsotope,MuMuonCharge=0;

static TTree *IsoTree = 0;
Double_t IsoDecayLoaclX,IsoDecayLoaclY,IsoDecayLoaclZ=0;
Int_t    IsoEventID,IsoZ,IsoA,IsoDecayVolume=0;

static TTree *MichelTree = 0;
Double_t MiLocalX,MiLocalY,MiLocalZ,MiKineE,MiMichelLocalTime=0;
Int_t    MiEventID,MiVolName=0; 

static TTree *SpaTree = 0;
Double_t Spax,Spay,Spaz,SpadE,Spatime,SpaquenchedDepE=0;
Int_t    SpaEventID,SpaFlukaNumber,SpaEnergyDepositedType,SpaMotherFlukaNumber,SpaMotherInteractionType,SpaVolume,SpaInitVolume=0;

static TTree *NeuTree = 0;
Double_t NeuInitKineE,NeuInitTime,NeuInitLocalX,NeuInitLocalY,NeuInitLocalZ,NeuCapLocalX,NeuCapLocalY,NeuCapLocalZ,NeuCapTime,NeuCapGammaESum=0;
Int_t    NeuEventID,NeuCapGammaNum,NeuMotherFlukaNumber,NeuMotherInteractionType,NeuCapVolumeName,NeuCapTargetName=0;

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
	IsoTree->Branch("DecayVolume",&IsoDecayVolume,"DecayVolume/I");
	
	MichelTree=new TTree("MichelElectron","MichelElectron");
	MichelTree->Branch("LocalX",&MiLocalX,"LocalX/D");
	MichelTree->Branch("LocalY",&MiLocalY,"LocalY/D");
	MichelTree->Branch("LocalZ",&MiLocalZ,"LocalZ/D");
	MichelTree->Branch("KineE",&MiKineE,"KineE/D");
	MichelTree->Branch("MichelLocalTime",&MiMichelLocalTime,"MichelLocalTime/D");
	MichelTree->Branch("EventID",&MiEventID,"EventID/I");
	MichelTree->Branch("VolName",&MiVolName,"VolName/I");
	
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
	SpaTree->Branch("Volume",&SpaVolume,"Volume/I");
	SpaTree->Branch("InitVolume",&SpaInitVolume,"InitVolume/I");

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
	NeuTree->Branch("CapVolumeName",&NeuCapVolumeName,"CapVolumeName/I");
	NeuTree->Branch("CapTargetName",&NeuCapTargetName,"CapTargetName/I");

    printf("%f\n", pluto);

  }
}
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
  void fillmuon( Int_t &m_MuEventID,Int_t &m_MuMuonCharge,Double_t &m_MuInitKineE,Double_t &m_MuInitTime,Double_t &m_MuInitLocalX,Double_t &m_MuInitLocalY,Double_t &m_MuInitLocalZ,Double_t &m_MuInitLocalXCos,Double_t &m_MuInitLocalYCos,Double_t &m_MuInitLocalZCos,Double_t &m_MuOwsTrackLength,Double_t &m_MuIwsTrackLength,Double_t &m_MuMoTrackLength,Double_t &m_MuLsTrackLength,Double_t &m_MuGdLsTrackLength,Int_t &m_MuNumOfNeutron,Int_t &m_MuNumOfIsotope)
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
    //printf("MuEventID   %d \n",MuEventID);
    MuonTree->Fill();
  }
}

#ifndef WIN32
#define filliso filliso_
#else
#define filliso FILLISO
#endif
extern "C" {
    void filliso(Int_t &m_IsoEventID,Int_t &m_IsoZ,Int_t &m_IsoA,Double_t &m_IsoDecayLoaclX,Double_t &m_IsoDecayLoaclY,Double_t &m_IsoDecayLoaclZ,Int_t &m_IsoDecayVolume)
  {
	IsoDecayLoaclX = m_IsoDecayLoaclX;
	IsoDecayLoaclY = m_IsoDecayLoaclY;
	IsoDecayLoaclZ = m_IsoDecayLoaclZ;
	IsoEventID     = m_IsoEventID;
	IsoZ           = m_IsoZ;
	IsoA           = m_IsoA;
    IsoDecayVolume = m_IsoDecayVolume;
    IsoTree->Fill();
  }
}

#ifndef WIN32
#define fillmi     fillmi_
#else
#define fillmi     FILLMI    
#endif
extern "C" {
    void fillmi(Int_t &m_MiEventID,Double_t &m_MiKineE,Double_t &m_MiMichelLocalTime,Double_t &m_MiLocalX,Double_t &m_MiLocalY,Double_t &m_MiLocalZ,Int_t &m_MiVolName)
  {
	MiLocalX          = m_MiLocalX;          
	MiLocalY          = m_MiLocalY;
	MiLocalZ          = m_MiLocalZ;
	MiKineE           = m_MiKineE;
	MiMichelLocalTime = m_MiMichelLocalTime;
	MiEventID         = m_MiEventID; 
    MiVolName         = m_MiVolName;
    MichelTree->Fill();
  }
}

#ifndef WIN32
#define fillspa fillspa_
#else
#define fillspa FILLSPA
#endif
extern "C" {
    void fillspa( Int_t    &m_SpaEventID,Double_t &m_Spax,Double_t &m_Spay,Double_t &m_Spaz,Double_t &m_SpadE,Double_t &m_Spatime,Double_t &m_SpaquenchedDepE,Int_t &m_SpaFlukaNumber,Int_t &m_SpaEnergyDepositedType,Int_t &m_SpaMotherFlukaNumber,Int_t &m_SpaMotherInteractionType,Int_t &m_SpaVolume,Int_t &m_SpaInitVolume)
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
    SpaVolume                = m_SpaVolume;
    SpaInitVolume                = m_SpaInitVolume;
    SpaTree->Fill();
  }
}

#ifndef WIN32
#define fillneu fillneu_
#else
#define fillneu FILLNEU
#endif
extern "C" {
    void fillneu(Int_t    &m_NeuEventID,Double_t &m_NeuInitKineE,Double_t &m_NeuInitTime,Double_t &m_NeuInitLocalX,Double_t &m_NeuInitLocalY,Double_t &m_NeuInitLocalZ,Double_t &m_NeuCapLocalX,Double_t &m_NeuCapLocalY,Double_t &m_NeuCapLocalZ,Double_t &m_NeuCapTime,Double_t &m_NeuCapGammaESum,Int_t &m_NeuCapGammaNum,Int_t &m_NeuMotherFlukaNumber,Int_t &m_NeuMotherInteractionType,Int_t &m_NeuCapVolumeName,Int_t &m_NeuCapTargetName)
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
    NeuCapVolumeName          = m_NeuCapVolumeName;
    NeuCapTargetName          = m_NeuCapTargetName;
    NeuTree->Fill();
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

