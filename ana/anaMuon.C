{
    int spaAdMuonNum=0;
    int signalNum=0;
    int signalNumNo12=0;
    int showNum=0;
    int evtNum=0;
    int bkgNum=0;
    int mimicSignalNum=0;
    int doubleAdMuon=0;
    int mimicAdMuon=0;
    int errorNum=0;
    map<string,int> mimicMuonNum;
    map<string,int> adMuonNum;
    string nameStr;
    double muonEnergyEdge[8]={0.,20,500,1500,2500,3500,4500,1000000};

    for( int fi=3001 ; fi<=3200 ; fi++ )
    {
        struct timeval allStartTime,allFinishTime;
        double timeInterval=0.;
        struct timeval allStartTime,allFinishTime;
        double timeInterval=0.;
        gettimeofday( &allStartTime, NULL );
        nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/data/PART10/rootFile/fluSim_%06d_sort.root",fi);
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

        //event constructor
        int _eventID[4]={0};
        int _InitVolume[4]={0};
        double _x[4]={0.};
        double _y[4]={0.};
        double _z[4]={0.};
        double _time[4]={0.};
        int _flukaNum[4]={0};
        int _spaNum[4]={0};
        double lastTime[4]={0.};
        double _dE[4]={0.};
        double _quenchedDepE[4]={0.};
        double _deltaECom[4][500]={0.};
        double _deltaQuenECom[4][500]={0.};
        int _det=999;

        //cout<<"begin loop over spallation tree "<<endl;
        int muonNum=0;
        bool dontLoopThisEventID=0;
        map<int,double> spaAdMuonMap[4];
        map<int,double> spaAdMuonDetMap[4];

        for (int sti = 0; sti<stnum; sti++)
        {
            st->GetEntry(sti);
            int detTmp=sx>0?2:1;
            if( sy<-300 )
            {
                detTmp+=2;
            }
            if( sEventID<_eventID[detTmp-1])
            {
                errorNum++;
            }
            if( sEventID!=_eventID[detTmp-1] )
            {
                muonNum++;
                dontLoopThisEventID=0;
            }
            if(dontLoopThisEventID) continue;

            
            // construct event 
            if( _eventID[detTmp-1]!=0&&((sEventID!=_eventID[detTmp-1]&&_flukaNum[detTmp-1]!=0)|| (spaTime-lastTime[detTmp-1])>100. ||((spaTime-lastTime[detTmp-1])<0 && abs(spaTime-lastTime[detTmp-1])>1. && lastTime[detTmp-1]>pow(2,64))))//18446744=pow(2,64)/1.e12
            {
                //identify admuon
                if( _quenchedDepE[detTmp-1]>=20.e-3 && _time[detTmp-1]<2e3 )
                {
                    spaAdMuonNum++;
                    if( muLsTrackLength[_det-1]==0. )
                    {
                        mimicAdMuon++;
                    }
                    if( spaAdMuonMap[_det-1].find(_eventID[detTmp-1])==spaAdMuonMap[_det-1].end() )
                    {
                        spaAdMuonMap[_det-1].insert(std::pair<int,double>(_eventID[detTmp-1],_time[detTmp-1]));
                        spaAdMuonDetMap[_det-1].insert(std::pair<int,double>(_eventID[detTmp-1],_det));
                    }else
                    {
                        doubleAdMuon++;
                        spaAdMuonMap[_det-1][_eventID[detTmp-1]]=_time[detTmp-1];
                    }
                    //TODO:
                    int sliceNum=999;
                    for( int slicei=0 ; slicei<7 ; slicei++ )
                    {
                        if( _dE[detTmp-1]*1000>=muonEnergyEdge[slicei] && _dE[detTmp-1]*1000<muonEnergyEdge[slicei+1] )
                        {
                            sliceNum=slicei;
                        }
                    }
                    
                    for( int flukaNumi=0 ; flukaNumi<500 ; flukaNumi++ )
                    {
                        if( _deltaECom[detTmp-1][flukaNumi]>0. )
                        {
                            cout<<"  "<<detTmp<<" "<<sliceNum<<"~"<<(flukaNumi+100)%500-100 <<"  : "<<_deltaECom[detTmp-1][flukaNumi]*1000<< "  ->  "<<_deltaQuenECom[detTmp-1][flukaNumi]*1000<<endl;
                        }
                    }
                    cout<<"    "<<_dE[detTmp-1]*1000<< " -> "<<_quenchedDepE[detTmp-1]*1000<<endl;
                    cout<<" "<<endl;
                    

                }
                if( _time[detTmp-1]>2e3 )//2us
                {
                    dontLoopThisEventID=1;
                }
                _dE[detTmp-1]=0.;
                _flukaNum[detTmp-1]=0;
                _spaNum[detTmp-1]=0;
                _quenchedDepE[detTmp-1]=0.;
                memset(_deltaECom[detTmp-1],0,sizeof(double)*500);
                memset(_deltaQuenECom[detTmp-1],0,sizeof(double)*500);
                if( sEventID!=_eventID[detTmp-1]&&_flukaNum[detTmp-1]!=0)
                {
                    lastTime[detTmp-1]=0.;
                }
            }
            //construct event
            if( _dE[detTmp-1]==0. )
            {
                _time[detTmp-1]=spaTime; 
                _flukaNum[detTmp-1]=sFlukaNumber;
                _x[detTmp-1]=sx;
                _InitVolume[detTmp-1]=sInitvolume;
                _y[detTmp-1]=sy;
                _z[detTmp-1]=sz;
            }
            _det=detTmp;
            _eventID[detTmp-1]=sEventID;
            _spaNum[detTmp-1]++;
            _dE[detTmp-1]+=sdE;
            _quenchedDepE[detTmp-1]+=squenchedDepE;
            _deltaECom[detTmp-1][(sFlukaNumber+500)%500]+=sdE;
            _deltaQuenECom[detTmp-1][(sFlukaNumber+500)%500]+=squenchedDepE;
            //
            lastTime[detTmp-1]=spaTime;
        }
        cout<<"stnum  : "<<stnum<<endl;
        cout<<"muonNum  : "<<muonNum<<endl;
        /* loop event buffer
        int bufSize=eventBuf.size();
        for( int i=0 ; i<eventBuf.size() ; i++ )
        {
            mt->GetEntry(eventBuf[i].EventID-1);
            if( muOwsTrackLength>0 || muIwsTrackLength>0)
            {
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
                        if( time2muon>=20.e3 && time2muon<=500.e3 )
                        {
                            signalNum++;
                            if( eventBuf[i].InitVolume!=12 )
                            {
                                signalNumNo12++;
                            }
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
                                int muonClass=0;
                                if(muAirTrackLength                      !=0.) muonClass=3; 
                                if(muStoneTrackLength                    !=0.) muonClass=4; 
                                if(muOwsTrackLength                      !=0.) muonClass=5; 
                                if(muIwsTrackLength                      !=0.) muonClass=6; 
                                if(muSstTrackLength[eventBuf[i].det-1]   !=0.) muonClass=7; 
                                if(muMoTrackLength[eventBuf[i].det-1]    !=0.) muonClass=8; 
                                if(muOatTrackLength[eventBuf[i].det-1]   !=0.) muonClass=9; 
                                if(muLsTrackLength[eventBuf[i].det-1]    !=0.) muonClass=10; 
                                if(muIatTrackLength[eventBuf[i].det-1]   !=0.) muonClass=11; 
                                if(muGdLsTrackLength[eventBuf[i].det-1]  !=0.) muonClass=12; 
                                nameStr=Form("%d-%d",fi,eventBuf[i].EventID);
                            if( muLsTrackLength[eventBuf[i].det-1]==0. )
                            {
                                mimicSignalNum++;
                                if( mimicMuonNum.find(nameStr)!= mimicMuonNum.end() )
                                {
                                     mimicMuonNum[nameStr]++;
                                }else
                                {
                                     mimicMuonNum.insert(std::pair<string,int>(nameStr,1));
                                }

                                //cout<<"mimicSignal "<<endl;
                            }else
                            {
                                if( adMuonNum.find(nameStr)!= adMuonNum.end() )
                                {
                                     adMuonNum[nameStr]++;
                                }else
                                {
                                     adMuonNum.insert(std::pair<string,int>(nameStr,1));
                                }
                                
                            }

                            if( eventBuf[i].InitVolume!=12 )
                            {
                                cout<<" "<<endl;
                                cout<<eventBuf[i].EventID<<" : FlukaNum~"<<eventBuf[i].flukaNum <<" InitVolume~"<<eventBuf[i].InitVolume<<" "<<eventBuf[i].quenchedDepE*1000<<"MeV "<<eventBuf[i].time/1000.<<"us "<<eventBuf[i].x<<","<<eventBuf[i].y<<","<<eventBuf[i].z <<" ("<<eventBuf[i].spaNum <<")"<<endl;
                                for( map<string,double>::iterator it=eventBuf[i].com.begin() ; it!=eventBuf[i].com.end() ; it++ )
                                {
                                    if( it->first!="3-0-8-300" && it->first!="3-22-8-300"&& it->first!="7-22-8-300"&&it->first!="4-0-8-300" && it->first!="4-22-8-300" )
                                    {
                                        //FlukaNumber-EnergyDepositedType-MotherFlukaNumber-InteractionType
                                        //cout<<eventBuf[i].EventID<<" : "<<it->first<<" ("<<it->second<<" "<<it->second/eventBuf[i].quenchedDepE<<") "<<eventBuf[i].time<<" "<<eventBuf[i].x<<","<<eventBuf[i].y<<","<<eventBuf[i].z <<endl;
                                        cout<<"FlukaNumber-EnergyDepositedType-MotherFlukaNumber-InteractionType  : "<< it->second/eventBuf[i].quenchedDepE*100<<"% "<<it->first<<endl;
                                    }
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
        for( int j=0 ; j<4 ; j++ )
        {
            spaAdMuonMap[j].clear();
            spaAdMuonDetMap[j].clear();
        }
        */

            //eventBuf.clear();

        f->Close();
        delete f;

        gettimeofday( &allFinishTime, NULL );
        timeInterval=allFinishTime.tv_sec-allStartTime.tv_sec+(allFinishTime.tv_usec-allStartTime.tv_usec)/1000000.;
        cout<<"errorNum  : "<<errorNum<<endl;
        //cout<<"   "<<fi<<"   eventBuf/stnum  : "<<bufSize<<"/"<<stnum<<" "<<(double)bufSize/stnum<<" signalNumNo12/signalNum:"<<signalNumNo12<<"/"<<signalNum<<" (Used time : "<<timeInterval<<" s = "<<(int)timeInterval/3600<<"h"<<(int)timeInterval%3600/60 <<"min"<<(int)timeInterval%3600%60 <<"s) ..."<<endl;
        cout<<"   "<<fi<<" (Used time : "<<timeInterval<<" s = "<<(int)timeInterval/3600<<"h"<<(int)timeInterval%3600/60 <<"min"<<(int)timeInterval%3600%60 <<"s) ..."<<endl;
    }
}
