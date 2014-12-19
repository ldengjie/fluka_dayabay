//#include  <iostream>
//#include  "TH1F.h"
//#include  "TFile.h"
//#include  "TTree.h"
//#include  "math.h"
//#include  <vector>
//using namespace std;
//int ana()
{
    struct event
    {
        int EventID;
        double x;
        double y;
        double z;
        double dE;
        double quenchedDepE;
        double time;
        int det;
        double tag;
        double firstHitTime;
        //int capVol;
        //int genVol;
        map<string,double> com;
        event()
        {
            x=0.;
            y=0.;
            z=0.;
            dE=0.;
            quenchedDepE=0.;
            time=0.;
            firstHitTime=0.;
        }
    };

    int wpMuonNum=0;
    int muonNum_iwp_only=0;
    int muonNum_owp_only=0;
    int muonNum_owp_iwp=0;
    int moNum=0;
    int adNum=0;
    int gdlsNum=0;
    double gdlsLength=0.;
    int spaAdMuonNum=0;
    int signalNum=0;
    int showNum=0;
    int evtNum=0;
    int bkgNum=0;
    int mimicSignalNum=0;
    double muonE=0.;
    int doubleAdMuon=0;
    int mimicAdMuon=0;
    int errorNum=0;
    TH1F* NeuLikeT2Admuon=new TH1F("NeuLikeT2Admuon","time interval between neutron-like and previous admuon",500,0,500.e3);//s

    string nameStr;
    for( int fi=2001 ; fi<=2200 ; fi++ )
    {
        struct timeval allStartTime,allFinishTime;
        double timeInterval=0.;
        gettimeofday( &allStartTime, NULL );
        //nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/data/PART10/rootFile/fluSim_%06d.root",fi);
        nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/data/PART10/rootFile/fluSim_%06d_sort.root",fi);
        cout<<"nameStr  : "<<nameStr<<endl;
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
            if( muIwsTrackLength>0 )
            {
                if( muOwsTrackLength>0 )
                {
                    muonNum_owp_iwp++;
                }else
                {
                    muonNum_iwp_only++;
                }
            }
            if( muOwsTrackLength>0 && muIwsTrackLength==0 )
            {
                muonNum_owp_only++;
            }
            if( muOwsTrackLength>0 || muIwsTrackLength>0 )
            {
                wpMuonNum++;
            }
            for( int j=0 ; j<4 ; j++ )
            {
                if( muMoTrackLength[j]>0 )
                {
                    moNum++;
                    if( muLsTrackLength[j]>0 )
                    {
                        adNum++;
                        if( muGdLsTrackLength[j]>0 )
                        {
                            gdlsNum++;
                            gdlsLength+=muGdLsTrackLength[j];
                            muonE+=muInitKineE;
                        }
                    }
                }
            }

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
        int sFlukaNumber;
        int sEnergyDepositedType;
        int sMotherFlukaNumber;
        int sMotherInteractionType;
        st->SetBranchAddress("EventID",&sEventID);
        st->SetBranchAddress("x",&sx);
        st->SetBranchAddress("Volume",&svolume);
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

        //event constructor
        vector<event> eventBuf;
        int _eventID=0;
        double _x=0.;
        double _y=0.;
        double _z=0.;
        double _dE=0.;
        double _quenchedDepE=0.;
        double _time=0.;
        double lastTime[4]={0.};
        int _det=999;
        map<string,double> _com;

        //st->BuildIndex("EventID","time");//1.e12
        //TTreeIndex *branchIndex = (TTreeIndex*)st->GetTreeIndex();
        //Long64_t* i_index=branchIndex->GetIndex();

        //cout<<"begin loop over spallation tree "<<endl;
        for (int sti = 0; sti<stnum; sti++)
        {
            //st->GetEntry(i_index[sti]);
            st->GetEntry(sti);
            int detTmp=sx>0?2:1;
            if( sy>300 )
            {
                detTmp+=2;
            }
            if( sEventID==_eventID && (spaTime-lastTime[detTmp])<0 && abs(spaTime-lastTime[detTmp])>1. && lastTime[detTmp]<=pow(2,64))
            {
                errorNum++;
                //cout<<"lastTime[detTmp]  : "<<lastTime[detTmp]<<endl;
                //st->GetEntry(i_index[sti-1]);
                //cout<<"last  : "<<sEventID<<","<<spaTime<<" "<<branchIndex->GetIndexValues()[sti-1]<<" + "<<branchIndex->GetIndexValuesMinor()[sti-1]<<endl;
                //st->GetEntry(i_index[sti]);
                //cout<<"now   : "<<sEventID<<","<<spaTime<<" "<<branchIndex->GetIndexValues()[sti]<<" + "<<branchIndex->GetIndexValuesMinor()[sti]<<endl;
            }
            if( _eventID!=0&&(sEventID!=_eventID|| (spaTime-lastTime[detTmp])>100. ||((spaTime-lastTime[detTmp])<0 && abs(spaTime-lastTime[detTmp])>1. && lastTime[detTmp]>pow(2,64))))//18446744=pow(2,64)/1.e12
            //if( _eventID!=0&&(sEventID!=_eventID|| (spaTime-lastTime[detTmp])>100.e-9 ))//18446744=pow(2,64)/1.e12
            {
                event eventTmp;
                eventTmp.EventID=_eventID;
                eventTmp.x=_x;
                eventTmp.y=_y;
                eventTmp.z=_z;
                eventTmp.dE=_dE;
                eventTmp.quenchedDepE=_quenchedDepE;
                eventTmp.com=_com;
                eventTmp.time=_time;
                eventTmp.det=_det;
                eventBuf.push_back(eventTmp);
                _dE=0.;
                _quenchedDepE=0.;
                _com.clear();
                if( sEventID!=_eventID)
                {
                    for( int mui=0 ; mui<4;mui++ )
                    {
                        lastTime[mui]=0.;
                    }
                }
            }
            if( _dE==0. )
            {
                _time=spaTime; 
                _x=sx;
                _y=sy;
                _z=sz;
            }
            _det=detTmp;
            _eventID=sEventID;
            _dE+=sdE;
            _quenchedDepE+=squenchedDepE;
            nameStr=Form("%d-%d-%d-%d",sFlukaNumber,sEnergyDepositedType,sMotherFlukaNumber,sMotherInteractionType);
            if( _com.find(nameStr)!=_com.end() )
            {
                _com[nameStr]+=squenchedDepE;
            }else
            {
                _com.insert(std::pair<string,double>(nameStr,squenchedDepE));
            }
            if( nameStr=="3-0-8-300" || nameStr=="3-22-8-300"|| nameStr=="7-22-8-300"|| nameStr=="4-0-8-300" || nameStr=="4-22-8-300" )
            {
                if( _com.find("neuCap")!=_com.end() )
                {
                    _com["neuCap"]+=squenchedDepE;
                }else
                {
                    _com.insert(std::pair<string,double>("neuCap",squenchedDepE));
                }
            }
            lastTime[detTmp]=spaTime;
        }
        int bufSize=eventBuf.size();
        map<int,double> spaAdMuonMap[4];
        map<int,double> spaAdMuonDetMap[4];
        for( int i=0 ; i<eventBuf.size() ; i++ )
        {
            mt->GetEntry(eventBuf[i].EventID-1);
            if( muOwsTrackLength>0 || muIwsTrackLength>0)
            {
                //cout<<"===== "<<endl;
                //if( eventBuf[i].EventID==90894 )
                //{
                //cout<<"muEventID  : "<<muEventID<<endl;
                //cout<<"muOwsTrackLength  : "<<muOwsTrackLength<<endl;
                //cout<<"muIwsTrackLength  : "<<muIwsTrackLength<<endl;
                //}
                //if( muEventID==90894 )
                //{
                //cout<<"muOwsTrackLength  : "<<muOwsTrackLength<<endl;
                //cout<<"muIwsTrackLength  : "<<muIwsTrackLength<<endl;
                // 
                //}
                //cout<<"===== "<<endl;
                //find admuon
                if( eventBuf[i].quenchedDepE>=20.e-3 && eventBuf[i].time<2e3 )
                {
                    //cout<<"eventBuf[i].time  : "<<eventBuf[i].time<<" eventBuf[i].EventID : "<<eventBuf[i].EventID<<" "<<eventBuf[i].det<<endl;
                    spaAdMuonNum++;
                    if( muLsTrackLength[eventBuf[i].det-1]==0. )
                    {
                        mimicAdMuon++;
                    }
                    if( spaAdMuonMap[eventBuf[i].det-1].find(eventBuf[i].EventID)==spaAdMuonMap[eventBuf[i].det-1].end() )
                    {
                        spaAdMuonMap[eventBuf[i].det-1].insert(std::pair<int,double>(eventBuf[i].EventID,eventBuf[i].time));
                        spaAdMuonDetMap[eventBuf[i].det-1].insert(std::pair<int,double>(eventBuf[i].EventID,eventBuf[i].det));
                    }else
                    {
                        //cout<<"find double count admuon "<<endl;
                        //cout<<"first  : "<<spaAdMuonMap[eventBuf[i].det-1][eventBuf[i].EventID]<<" second:"<<eventBuf[i].time<<" Ls:"<<muLsTrackLength<<" det:"<<spaAdMuonDetMap[eventBuf[i].det-1][eventBuf[i].EventID]<<"vs"<<eventBuf[i].det<<" id:"<<spaAdMuonMap[eventBuf[i].det-1].find(eventBuf[i].EventID)->first<<"vs"<<eventBuf[i].EventID<<endl;
                        doubleAdMuon++;
                        spaAdMuonMap[eventBuf[i].det-1][eventBuf[i].EventID]=eventBuf[i].time;
                    }
                    continue;
                }
                //select neutron
                if( spaAdMuonMap[eventBuf[i].det-1].find(eventBuf[i].EventID)!=spaAdMuonMap[eventBuf[i].det-1].end()  )
                {
                    if( eventBuf[i].quenchedDepE>=0.7e-3 )
                    {
                        evtNum++;
                    }
                    if( eventBuf[i].quenchedDepE>=6.e-3 && eventBuf[i].quenchedDepE<=12.e-3 )
                    {
                        double time2muon=eventBuf[i].time-spaAdMuonMap[eventBuf[i].det-1][eventBuf[i].EventID];
                        NeuLikeT2Admuon->Fill(time2muon);
                        if( time2muon>=10.e3 && time2muon<=200.e3 )
                        {
                            signalNum++;
                            //cout<<" "<<endl;
                            //cout<<"quenchedDepE  : "<<eventBuf[i].quenchedDepE<<endl;
                            bool showDetials = true;
                            if( eventBuf[i].com.find("neuCap")!=eventBuf[i].com.end() )
                            {
                                if( eventBuf[i].com["neuCap"]/eventBuf[i].quenchedDepE>0.99 )
                                {
                                    showDetials=false;
                                }
                            }
                            if( showDetials )
                            {
                                showNum++;
                            }
                            //cout<<" "<<endl;
                            if( muLsTrackLength[eventBuf[i].det-1]==0. )
                            {
                                mimicSignalNum++;
                                //cout<<"mimicSignal "<<endl;
                            }
                            for( map<string,double>::iterator it=eventBuf[i].com.begin() ; it!=eventBuf[i].com.end() ; it++ )
                            {
                                if( it->first!="3-0-8-300" && it->first!="3-22-8-300"&& it->first!="7-22-8-300"&&it->first!="4-0-8-300" && it->first!="4-22-8-300" )
                                {
                                    //FlukaNumber-EnergyDepositedType-MotherFlukaNumber-InteractionType
                                    //cout<<eventBuf[i].EventID<<" : "<<it->first<<" ("<<it->second<<" "<<it->second/eventBuf[i].quenchedDepE<<") "<<eventBuf[i].time<<" "<<eventBuf[i].x<<","<<eventBuf[i].y<<","<<eventBuf[i].z <<endl;
                                }
                            }

                        }else if( time2muon>=1010.e3 && time2muon<=1200.e3 )
                        {
                            bkgNum++;
                        }
                    }
                }

            }

        }
        eventBuf.clear();
        for( int j=0 ; j<4 ; j++ )
        {
            spaAdMuonMap[j].clear();
            spaAdMuonDetMap[j].clear();
        }


        f->Close();
        delete f;

        gettimeofday( &allFinishTime, NULL );
        timeInterval=allFinishTime.tv_sec-allStartTime.tv_sec+(allFinishTime.tv_usec-allStartTime.tv_usec)/1000000.;
        cout<<"   "<<fi<<"   eventBuf/stnum  : "<<bufSize<<"/"<<stnum<<" "<<(double)bufSize/stnum<<" (Used time : "<<timeInterval<<" s = "<<(int)timeInterval/3600<<"h"<<(int)timeInterval%3600/60 <<"min"<<(int)timeInterval%3600%60 <<"s) ..."<<endl;
    }
    NeuLikeT2Admuon->Draw();

    cout<<" "<<endl;
    cout<<"moNum  : "<<moNum<<endl;
    cout<<"adNum  : "<<adNum<<endl;
    cout<<"gdlsNum  : "<<gdlsNum<<endl;
    cout<<"gdlsNum/moNum  : "<<(double)gdlsNum/moNum<<endl;
    cout<<"AverageMuonE  : "<<muonE/gdlsNum<<endl;
    cout<<"muonNum_owp_iwp  : "<<muonNum_owp_iwp<<endl;
    cout<<"muonNum_owp_only : "<<muonNum_owp_only<<endl;
    cout<<"muonNum_iwp_only : "<<muonNum_iwp_only<<endl;
    cout<<"wpMuonNum  : "<<wpMuonNum<<" = "<<muonNum_owp_iwp+muonNum_owp_only+muonNum_iwp_only<<endl;
    cout<<"owp_iwp/owp  : "<<(double)muonNum_owp_iwp/(muonNum_owp_only+muonNum_owp_iwp)<<endl;
    cout<<"owp_iwp/iwp  : "<<(double)muonNum_owp_iwp/(muonNum_iwp_only+muonNum_owp_iwp)<<endl;
    cout<<"owp/iwp  : "<<(double)(muonNum_owp_only+muonNum_owp_iwp)/(muonNum_iwp_only+muonNum_owp_iwp)<<endl;
    cout<<" "<<endl;
    cout<<"errorNum  : "<<errorNum<<endl;
    cout<<"mimicAdMuon  : "<<mimicAdMuon<<endl;
    cout<<"doubleAdMuon  : "<<doubleAdMuon<<endl;
    cout<<"spaAdMuonNum  : "<<spaAdMuonNum<<endl;
    cout<<"evtNum  : "<<evtNum<<endl;
    cout<<"signalNum  : "<<signalNum<<endl;
    cout<<"showNum  : "<<showNum<<endl;
    cout<<"mimicSignalNum  : "<<mimicSignalNum<<endl;
    cout<<"bkgNum  : "<<bkgNum<<endl;
    cout<<" "<<endl;
    cout<<">>>gdlsNum/adNum  : "<<(double)gdlsNum/adNum<<endl;
    cout<<">>>average trackLength  : "<<gdlsLength/gdlsNum<<endl;
    cout<<">>>(spaAdMuonNum-adNum)/spaAdMuonNum  : "<<(double)(spaAdMuonNum-adNum)/spaAdMuonNum<<endl;

    cout<<"==== xi === "<<endl;

    cout<<"xi_mimic : "<<(double)mimicSignalNum/signalNum<<endl;
    //cout<<"yield  : "<<(double)(signalNum-bkgNum)*(1-0.078)/0.862/(0.836*0.917*0.838)/(adNum*0.6*218)/0.855<<endl;
    //cout<<"spa yield  : "<<(double)(signalNum-bkgNum)*(1-(double)mimicSignalNum/signalNum)/(0.836*0.917*0.838)/(adNum*0.6*218)/0.855<<endl;

    //return 1;
}

