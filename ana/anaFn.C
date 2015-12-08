//#include  <iostream>
//#include  "TH1F.h"
//#include  "TFile.h"
//#include  "TTree.h"
//#include  "math.h"
//#include  <vector>
//using namespace std;
//int ana()
{
    string nameStr;
    for( int fi=3001 ; fi<=8000 ; fi++ )
    {
        struct timeval allStartTime,allFinishTime;
        double timeInterval=0.;
        gettimeofday( &allStartTime, NULL );
        nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/data/PART10/rootFile/fluSim_%06d_sort.root",fi);
        //cout<<"nameStr  : "<<nameStr<<endl;
        TFile* f= new TFile(nameStr.c_str());
        if( f->IsZombie() )
        {
            f->Close();
            delete f;
            continue;
        }
        //if( fi%50==0 )
        //{
        //cout<<"nameStr  : "<<nameStr<<endl;
        //}

        TTree* mt= (TTree*)f->Get("Muon");
        int mtnum=mt->GetEntries();
        Int_t muEventID;
        double muInitKineE;
        double muInitLocalX;
        double muInitLocalY;
        double muInitLocalZ;
        double muInitLocalXCos;
        double muInitLocalYCos;
        double muInitLocalZCos;
        double muAirTrackLength;
        double muOwsTrackLength;
        double muStoneTrackLength;
        double muIwsTrackLength;
        double muSstTrackLength[4];
        double muOatTrackLength[4];
        double muIatTrackLength[4];
        double muMoTrackLength[4];
        double muLsTrackLength[4];
        double muGdLsTrackLength[4];
        mt->SetBranchAddress("EventID",&muEventID);
        mt->SetBranchAddress("InitKineE",&muInitKineE);
        mt->SetBranchAddress("InitLocalX",&muInitLocalX);
        mt->SetBranchAddress("InitLocalY",&muInitLocalY);
        mt->SetBranchAddress("InitLocalZ",&muInitLocalZ);
        mt->SetBranchAddress("InitLocalXCos",&muInitLocalXCos);
        mt->SetBranchAddress("InitLocalYCos",&muInitLocalYCos);
        mt->SetBranchAddress("InitLocalZCos",&muInitLocalZCos);
        mt->SetBranchAddress("AirTrackLength",&muAirTrackLength);
        mt->SetBranchAddress("StoneTrackLength",&muStoneTrackLength);
        mt->SetBranchAddress("OwsTrackLength",&muOwsTrackLength);
        mt->SetBranchAddress("IwsTrackLength",&muIwsTrackLength);
        mt->SetBranchAddress("SstTrackLength",muSstTrackLength);
        mt->SetBranchAddress("OatTrackLength",muOatTrackLength);
        mt->SetBranchAddress("IatTrackLength",muIatTrackLength);
        mt->SetBranchAddress("MoTrackLength",muMoTrackLength);
        mt->SetBranchAddress("LsTrackLength",muLsTrackLength);
        mt->SetBranchAddress("GdLsTrackLength",muGdLsTrackLength);
        //map<int,int> muonIndex;
        for( int i=0 ; i<mtnum ; i++ )
        {
            mt->GetEntry(i);
        }

        TTree* st=(TTree*)f->Get("Spallation");
        int stnum=st->GetEntries();
        int sEventID;
        double sx;
        double sy;
        double sz;
        double sdE;
        double spaTime;
        double squenchedDepE;
        int svolume;
        int sInitvolume;
        int sFlukaNumber;
        int sEnergyDepositedType;
        int sMotherFlukaNumber;
        int sMotherInteractionType;
        st->SetBranchAddress("EventID",&sEventID);
        st->SetBranchAddress("x",&sx);
        st->SetBranchAddress("Volume",&svolume);
        st->SetBranchAddress("InitVolume",&sInitvolume);
        st->SetBranchAddress("y",&sy);
        st->SetBranchAddress("z",&sz);
        st->SetBranchAddress("dE",&sdE);
        st->SetBranchAddress("time",&spaTime);
        st->SetBranchAddress("quenchedDepE",&squenchedDepE);
        st->SetBranchAddress("FlukaNumber",&sFlukaNumber);
        st->SetBranchAddress("EnergyDepositedType",&sEnergyDepositedType);
        st->SetBranchAddress("MotherFlukaNumber",&sMotherFlukaNumber);
        st->SetBranchAddress("MotherInteractionType",&sMotherInteractionType);
        //cout<<"stnum  : "<<stnum<<endl;

        //cout<<"begin loop over spallation tree "<<endl;
        for (int sti = 0; sti<stnum; sti++)
        {
            st->GetEntry(sti);
        }


        f->Close();
        delete f;
    }
