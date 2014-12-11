{
    int rootNum=4000;
    string dataVer[4]={"PART10"};
    string nameStr;
    //double density=0.8602;
    double GdMuonRate=15.*0.6;
    double density=0.8550;
    string isoName[7]={"H","He","Li","Be","B","C","N"};
    for( int anaDet=12 ; anaDet<13 ; anaDet+=2 )
    {
        int GdMuonNum=0;
        double adMuonLength=0.;
        int neuNum=0;
        int neuGdCapNum=0;
        int neuGdCapNumAfter=0;
        int neuNum2=0;
        int neuNumInit=0;
        int neuNumOut=0;
        int neuNumIn=0;
        int neuNumD[15]={0};
        int isoNum[150][300]={0};
        int isoNumOut[150][300]={0};
        int isoNumIn[150][300]={0};
        int neuVolume[15][15][15]={0};
        int In1,In2,In3,Out4,Out5,Cap6,Oth7,Oth8=0;
        TH1D* dis=new TH1D("dis","distance between neutron and muon track",100,0,1000);
        TH1D* eng=new TH1D("eng","energy of neutron",1000,0,1);
        TH1D* eng2=new TH1D("eng2","energy of neutron",2000,0,20);
        TH2D* xy=new TH2D("xy","xy of neutron",300,-600,600,800,-400,400);
        TH2D* rz=new TH2D("rz","rz of neutron",250,0,250,500,-250,250);
        TH2D* rzNoW=new TH2D("rzNoW","rzNoW of neutron",250,0,250,500,-250,250);
        TH1D* hr=new TH1D("hr","r of neutron",250,0,250);
        TH1D* hz=new TH1D("hz","z of neutron",50,-250,250);
        TH1D* inVol=new TH1D("inVol","volume of spill-in neutron",12,0,12);
        TH2D* inVolvsClass=new TH2D("inVolvsClass","volume of spill-in neutron",12,0,12,5,0,5);
        TH1D* inVolforCap=new TH1D("inVolforCap","volume of spill-in neutron",12,0,12);
        TH2D* inVolvsClassforCap=new TH2D("inVolvsClassforCap","volume of spill-in neutron",12,0,12,5,0,5);
        TH2D* RvsCom=new TH2D("RvsCom","RvsCom of neutron",50,-250,250,12,1,13);
        TH1D* RvsComX[12];
        TH2D* rzAll=new TH2D("rzAll","rz of all neutron",300,0,300,4100,-800,3300);
        TH1D* hrAll=new TH1D("hrAll","rAll of neutron",300,0,300);
        TH1D* hzAll=new TH1D("hzAll","zAll of neutron",410,-800,3300);
        TH1D* NeuMultiplicity=new TH1D("NeuMultiplicity","neutron multiplicity for each ad muon",500,0,500);
        TH1D* NeuT2Admuon=new TH1D("NeuT2Admuon","time interval between neutron and previous admuon",500,0,500.e3);
        TCanvas* c=new TCanvas("c","c",1200,900);
        c->Divide(3,3);


        //loop for counting
        for( int i=1; i<rootNum+1; i++ )
        {
            nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/data/%s/rootFile/fluSim_%06d.root",dataVer[j].c_str(),i);
            //if( i%100==0 )
            //{
            std::cout<<"filename : "<<nameStr<<endl;
            //} 
            TFile* f= new TFile(nameStr.c_str());
            if( f->IsZombie() )
            {
                f->Close();
            }else
            {

                TTree* mt= (TTree*)f->Get("Muon");
                int mtnum=mt->GetEntries();
                Int_t muEventID;
                double muInitLocalX;
                double muInitLocalY;
                double muInitLocalZ;
                double muInitLocalXCos;
                double muInitLocalYCos;
                double muInitLocalZCos;
                double muAirTrackLength;
                double muStoneTrackLength;
                double muOwsTrackLength;
                double muIwsTrackLength;
                double muSstTrackLength[4];
                double muOatTrackLength[4];
                double muIatTrackLength[4];
                double muMoTrackLength[4];
                double muLsTrackLength[4];
                double muGdLsTrackLength[4];
                double muTrackLength[15][4]={0.};
                mt->SetBranchAddress("EventID",&muEventID);
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

                TTree* neut= (TTree*)f->Get("Neutron");
                int neutnum=neut->GetEntries();
                Int_t neuEventID;
                double neuInitTime;
                double neuInitKineE;
                double neuInitLocalX;
                double neuInitLocalY;
                double neuInitLocalZ;
                double neuCapLocalX;
                double neuCapLocalY;
                double neuCapLocalZ;
                int neuInitVolumeName;
                int neuCapVolumeName;
                double neuCapGammaESum;
                double neuCapTime;
                int neuCapTargetName;
                int neuOriginVolumeNumber;
                int neuMotherInteractionType;
                int    neuMotherFlukaNumber;
                neut->SetBranchAddress("EventID",&neuEventID);
                neut->SetBranchAddress("InitTime",&neuInitTime);
                neut->SetBranchAddress("InitKineE",&neuInitKineE);
                neut->SetBranchAddress("InitLocalX",&neuInitLocalX);
                neut->SetBranchAddress("InitLocalY",&neuInitLocalY);
                neut->SetBranchAddress("InitLocalZ",&neuInitLocalZ);
                neut->SetBranchAddress("CapLocalX",&neuCapLocalX);
                neut->SetBranchAddress("CapLocalY",&neuCapLocalY);
                neut->SetBranchAddress("CapLocalZ",&neuCapLocalZ);
                neut->SetBranchAddress("InitVolumeName",&neuInitVolumeName);
                neut->SetBranchAddress("CapVolumeName",&neuCapVolumeName);
                neut->SetBranchAddress("CapGammaESum",&neuCapGammaESum);
                neut->SetBranchAddress("CapTime",&neuCapTime);
                neut->SetBranchAddress("CapTargetName",&neuCapTargetName);
                neut->SetBranchAddress("OriginVolumeNumber",&neuOriginVolumeNumber);
                neut->SetBranchAddress("MotherInteractionType",&neuMotherInteractionType);
                neut->SetBranchAddress("MotherFlukaNumber",&neuMotherFlukaNumber);

                TTree* isot=(TTree*)f->Get("Isotope");
                int isotnum=isot->GetEntries();
                int isoEventID;
                double isoDecayLocalX;
                double isoDecayLocalY;
                double isoDecayLocalZ;
                int isoZ;
                int isoA;
                int isoInitVolume;
                int isoDecayVolume;
                int isoOriginVolumeNumber;
                isot->SetBranchAddress("EventID",&isoEventID);
                isot->SetBranchAddress("DecayLocalX",&isoDecayLocalX);
                isot->SetBranchAddress("DecayLocalY",&isoDecayLocalY);
                isot->SetBranchAddress("DecayLocalZ",&isoDecayLocalZ);
                isot->SetBranchAddress("Z",&isoZ);
                isot->SetBranchAddress("A",&isoA);
                isot->SetBranchAddress("InitVolume",&isoInitVolume);
                isot->SetBranchAddress("DecayVolume",&isoDecayVolume);
                isot->SetBranchAddress("OriginVolumeNumber",&isoOriginVolumeNumber);


                map<int,int> muIndex;
                map<int,int> muNeuMul;
                for( int u=0 ; u<mtnum ; u++ )
                //for( int u=90894-1 ; u<=90894-1; u++ )
                {
                    mt->GetEntry(u);
                    //cout<<"muAirTrackLength  : "<<muAirTrackLength<<endl;
                    //cout<<"muStoneTrackLength  : "<<muStoneTrackLength<<endl;
                    //cout<<"muOwsTrackLength  : "<<muOwsTrackLength<<endl;
                    //cout<<"muIwsTrackLength  : "<<muIwsTrackLength<<endl;
                    for( int mi=0 ; mi<4 ; mi++ )
                    {
                        muTrackLength[7][mi] =muSstTrackLength[mi] ;
                        muTrackLength[8][mi] =muMoTrackLength[mi]  ;
                        muTrackLength[9][mi] =muOatTrackLength[mi] ;
                        muTrackLength[10][mi]=muLsTrackLength[mi]  ;
                        muTrackLength[11][mi]=muIatTrackLength[mi] ;
                        muTrackLength[12][mi]=muGdLsTrackLength[mi];
                        //cout<<" muSstTrackLength["<<mi<<"]  : "<<muSstTrackLength[mi]  <<endl;
                        //cout<<" muMoTrackLength["<<mi<<"]   : "<<muMoTrackLength[mi]   <<endl;
                        //cout<<" muOatTrackLength["<<mi<<"]  : "<<muOatTrackLength[mi]  <<endl;
                        //cout<<" muLsTrackLength["<<mi<<"]   : "<<muLsTrackLength[mi]   <<endl;
                        //cout<<" muIatTrackLength["<<mi<<"]  : "<<muIatTrackLength[mi]  <<endl;
                        //cout<<" muGdLsTrackLength["<<mi<<"] : "<<muGdLsTrackLength[mi] <<endl;

                    }

                    bool passLs=0;
                    for( int ai=0 ; ai<4 ; ai++ )
                    {
                        if(muTrackLength[anaDet][ai]==0) continue;
                        GdMuonNum++;
                        for( int di=anaDet ; di<=12;di++ )
                        {
                            adMuonLength+=muTrackLength[di][ai];
                        }
                        
                    }
                    for( int ai=0 ; ai<4 ; ai++ )
                    {
                        if(muTrackLength[10][ai]==0) continue;
                        passLs=1;
                        muNeuMul.insert(std::pair<int,int>(muEventID*10+ai+1,0));
                    }
                    if( passLs )
                    {
                        muIndex.insert(std::pair<int,int>(muEventID,u));
                    }

                }

                //cout<<"neutnum  : "<<neutnum<<endl;
                for( int r=0 ; r<neutnum ; r++ )
                {
                    neut->GetEntry(r);
                    //if( neuEventID==90894 )
                    //{
                    //cout<<"===== "<<endl;
                    //cout<<"neuEventID                 : "<<neuEventID                <<endl;
                    //cout<<"neuInitTime                : "<<neuInitTime               <<endl;
                    //cout<<"neuInitKineE               : "<<neuInitKineE              <<endl;
                    //cout<<"neuInitLocalX              : "<<neuInitLocalX             <<endl;
                    //cout<<"neuInitLocalY              : "<<neuInitLocalY             <<endl;
                    //cout<<"neuInitLocalZ              : "<<neuInitLocalZ             <<endl;
                    //cout<<"neuCapLocalX               : "<<neuCapLocalX              <<endl;
                    //cout<<"neuCapLocalY               : "<<neuCapLocalY              <<endl;
                    //cout<<"neuCapLocalZ               : "<<neuCapLocalZ              <<endl;
                    //cout<<"neuInitVolumeName          : "<<neuInitVolumeName         <<endl;
                    //cout<<"neuCapVolumeName           : "<<neuCapVolumeName          <<endl;
                    //cout<<"neuCapGammaESum            : "<<neuCapGammaESum           <<endl;
                    //cout<<"neuCapTime                 : "<<neuCapTime                <<endl;
                    //cout<<"neuCapTargetName           : "<<neuCapTargetName          <<endl;
                    //cout<<"neuOriginVolumeNumber      : "<<neuOriginVolumeNumber     <<endl;
                    //cout<<"neuMotherFlukaNumber       : "<<neuMotherFlukaNumber      <<endl;
                    //cout<<"neuMotherInteractionType   : "<<neuMotherInteractionType  <<endl;
                    //}
                    int a_initDet=neuInitLocalX>0?2:1;
                    if( neuInitLocalY>300 )
                    {
                        a_initDet+=2;
                    }
                    double a_centerX=300*pow(-1,a_initDet%2);
                    double a_centerY=a_initDet>2?-600:0;
                    double a_lengthX=neuInitLocalX-a_centerX;
                    double a_lengthY=neuInitLocalY-a_centerY;
                    double a_radius=sqrt(a_lengthX*a_lengthX+a_lengthY*a_lengthY);
                    double a_weight=1/a_radius;
                    if( a_radius<=300 )
                    {
                        rzAll->Fill(a_radius,neuInitLocalZ,a_weight);
                        hrAll->Fill(a_radius,a_weight);
                        hzAll->Fill(neuInitLocalZ);
                    }
                    //if( neuMotherFlukaNumber==8 )
                    if(1)
                    {
                        if(muIndex.find(neuEventID)==muIndex.end()) continue;
                    //if(muIndex.find(neuEventID)==muIndex.end()) 
                    //{
                    //mt->GetEntry(neuEventID-1);
                    //cout<<"muon didn't pass through AD "<<endl;
                    //cout<<"muAirTrackLength  : "<<muAirTrackLength<<endl;
                    //}
                    neuNumD[14]++;
                    neuNumD[neuInitVolumeName]++;

                    //if( neuCapVolumeName== 12  )
                    //{
                    //neuNum++;
                    //if(neuOriginVolumeNumber!= 12 ) neuNumIn++;
                    //if(neuOriginVolumeNumber== 12 &&neuInitVolumeName!= 12 ) neuNumIn++;
                    //}
                    //if(neuOriginVolumeNumber== 12  && neuCapVolumeName!= 12  && neuInitVolumeName== 12 ) neuNumOut++;

                    neuVolume[neuOriginVolumeNumber][neuInitVolumeName][neuCapVolumeName]++;


                    int initDet;
                    if( neuInitVolumeName>= anaDet )
                    {
                        initDet=neuInitLocalX>0?2:1;
                        if( neuInitLocalY>300 )
                        {
                            initDet+=2;
                        }
                    }
                    int capDet;
                    if( neuCapVolumeName>= anaDet )
                    {
                        capDet=neuInitLocalX>0?2:1;
                        if( neuInitLocalY>300 )
                        {
                            capDet+=2;
                        }
                    }
                    mt->GetEntry(neuEventID-1);
                    for( int mi=0 ; mi<4 ; mi++ )
                    {
                        muTrackLength[7][mi]=muSstTrackLength[mi];
                        muTrackLength[8][mi]=muMoTrackLength[mi];
                        muTrackLength[9][mi]=muOatTrackLength[mi];
                        muTrackLength[10][mi]=muLsTrackLength[mi];
                        muTrackLength[11][mi]=muIatTrackLength[mi];
                        muTrackLength[12][mi]=muGdLsTrackLength[mi];

                    }
                    if( muTrackLength[10][0]>0||  muTrackLength[10][1]>0|| muTrackLength[10][2]>0|| muTrackLength[10][3]>0)
                        //if(1)
                    {
                        if( neuCapVolumeName>= anaDet  && muTrackLength[10][capDet-1]>0 )
                        {
                            if( muNeuMul.find(neuEventID*10+initDet)!=muNeuMul.end() )
                            {
                                muNeuMul[neuEventID*10+initDet]++;
                            }
                            if( neuCapGammaESum>0.006 && neuCapGammaESum<0.012 && neuCapTime>10.e3 &&neuCapTime<200.e3)
                            {
                                neuGdCapNumAfter++;
                                //cout<<"neuGdCapNumAfter "<<endl;
                            }
                            if( neuCapTargetName== 26)
                            {
                                neuGdCapNum++;
                                //cout<<neuEventID<<"  : "<<neuCapGammaESum<<" "<<neuCapTime<<" "<<neuCapLocalX<<","<<neuCapLocalY<<","<<neuCapLocalZ <<endl;
                            }
                        }
                        if( neuInitVolumeName>= anaDet  && muTrackLength[10][initDet-1]>0)
                            //if( neuInitVolumeName>= anaDet  )
                        { 

                            neuNum++;
                            if( neuMotherInteractionType==300 )
                            {
                                cout<<"MotherInteractionType  : "<<neuMotherInteractionType<<endl;
                                neuNum2++;
                            }
                            double disV=sqrt(
                                    (muInitLocalYCos*(neuInitLocalZ-muInitLocalZ)-muInitLocalZCos*(neuInitLocalY-muInitLocalY))*(muInitLocalYCos*(neuInitLocalZ-muInitLocalZ)-muInitLocalZCos*(neuInitLocalY-muInitLocalY))+
                                    (muInitLocalXCos*(neuInitLocalZ-muInitLocalZ)-muInitLocalZCos*(neuInitLocalX-muInitLocalX))*(muInitLocalXCos*(neuInitLocalZ-muInitLocalZ)-muInitLocalZCos*(neuInitLocalX-muInitLocalX))+
                                    (muInitLocalXCos*(neuInitLocalY-muInitLocalY)-muInitLocalYCos*(neuInitLocalX-muInitLocalX))*(muInitLocalXCos*(neuInitLocalY-muInitLocalY)-muInitLocalYCos*(neuInitLocalX-muInitLocalX)));
                            dis->Fill(disV);
                            eng->Fill(neuInitKineE);
                            eng2->Fill(neuInitKineE*1000);
                            xy->Fill(neuInitLocalX,neuInitLocalY);
                            double centerX=300*pow(-1,initDet%2);
                            double centerY=initDet>2?-600:0;
                            double lengthX=neuInitLocalX-centerX;
                            double lengthY=neuInitLocalY-centerY;
                            double radius=sqrt(lengthX*lengthX+lengthY*lengthY);
                            double weight=1.;
                            if( radius>0 )
                            {
                                weight=1/radius;
                            }
                            //cout<<"initDet,neuInitLocalX,neuInitLocalY,centerX,centerY,radius  : "<<initDet<<","<<neuInitLocalX<<","<<neuInitLocalY<<","<<centerX<<","<<centerY<<","<<radius<<endl;

                            rz->Fill(radius,neuInitLocalZ,weight);
                            rzNoW->Fill(radius,neuInitLocalZ);
                            hz->Fill(neuInitLocalZ);
                            //hr->Fill(radius,radius); 
                            hr->Fill(radius,weight); 
                            RvsCom->Fill(neuInitLocalZ,neuOriginVolumeNumber);
                        }
                        if((neuCapVolumeName>= anaDet&&muTrackLength[10][capDet-1]>0)  && !(neuInitVolumeName>= anaDet &&muTrackLength[10][initDet-1]>0))
                            //if((neuCapVolumeName>= anaDet)  && !(neuInitVolumeName>= anaDet ))
                        {
                          neuNumIn++;   
                          int muClass=4;
                          if( muStoneTrackLength>0. && !(muOwsTrackLength>0. || muIwsTrackLength>0.) )
                          {
                              muClass=3;
                          }
                          if( (muOwsTrackLength>0. || muIwsTrackLength>0.) && !( muSstTrackLength[0]>0. ||  muSstTrackLength[1]>0. || muSstTrackLength[2]>0. || muSstTrackLength[3]>0.))
                          {
                              muClass=2;
                          }
                          if( muSstTrackLength[0]>0. ||  muSstTrackLength[1]>0. || muSstTrackLength[2]>0. || muSstTrackLength[3]>0.)
                          {
                              muClass=1;
                          }
                          inVol->Fill(neuInitVolumeName);
                          inVolvsClass->Fill(neuInitVolumeName,muClass);
                        }
                        if((neuCapVolumeName>= anaDet)  && !(neuInitVolumeName>= anaDet))
                        {
                          int muClass=4;
                          if( muStoneTrackLength>0. && !(muOwsTrackLength>0. || muIwsTrackLength>0.) )
                          {
                              muClass=3;
                          }
                          if( (muOwsTrackLength>0. || muIwsTrackLength>0.) && !( muSstTrackLength[0]>0. ||  muSstTrackLength[1]>0. || muSstTrackLength[2]>0. || muSstTrackLength[3]>0.))
                          {
                              muClass=2;
                          }
                          if( muSstTrackLength[0]>0. ||  muSstTrackLength[1]>0. || muSstTrackLength[2]>0. || muSstTrackLength[3]>0.)
                          {
                              muClass=1;
                          }
                          inVolforCap->Fill(neuInitVolumeName);
                          inVolvsClassforCap->Fill(neuInitVolumeName,muClass);
                        }
                        if(!(neuCapVolumeName>= anaDet &&muTrackLength[10][capDet-1]>0) && (neuInitVolumeName>= anaDet &&muTrackLength[10][initDet-1]>0)) neuNumOut++;
                        //if(!(neuCapVolumeName>= anaDet ) && (neuInitVolumeName>= anaDet )) neuNumOut++;
                    }

                    //if( neuCapVolumeName== 12  )
                    //{
                    //neuNum++;
                    //if(neuInitVolumeName!= 12 ) neuNumIn++;
                    //}
                    //if(neuCapVolumeName!= 12  && neuInitVolumeName== 12 ) neuNumOut++;

                    //if( neuCapVolumeName== 12  || neuCapVolumeName==10)
                    //{
                    //neuNum++;
                    //if(neuOriginVolumeNumber!= 12  && neuOriginVolumeNumber!=10) neuNumIn++;
                    //}
                    //if((neuOriginVolumeNumber== 12  || neuOriginVolumeNumber==10)&& (neuCapVolumeName!= 12  && neuCapVolumeName!=10)) neuNumOut++;
                    //if(neuOriginVolumeNumber== 12  && neuInitVolumeName== 12 ) neuNumInit++;
                    //if(neuOriginVolumeNumber== 12  && neuInitVolumeName== 12 )
                    //{
                    //if(muIndex.find(neuEventID)==muIndex.end()) 
                    //{
                    //cout<<"muon didn't pass through GDLS "<<endl;
                    //cout<<"muGdLsTrackLength  : "<<muGdLsTrackLength<<endl;
                    //}
                    // 
                    //}
                    }

                }

                for( int is=0 ; is<isotnum ; is++ )
                {
                    isot->GetEntry(is);
                    if(muIndex.find(isoEventID)==muIndex.end()) continue;
                    //if( isoDecayVolume== 12  )
                    //{
                    //isoNum[isoZ][isoA]++;
                    ////if(isoOriginVolumeNumber!= 12 ) isoNumIn[isoZ][isoA]++;
                    ////if(isoOriginVolumeNumber== 12 &&isoInitVolume!= 12 ) isoNumIn[isoZ][isoA]++;//==zero
                    //}
                    ////if(isoOriginVolumeNumber== 12  && isoDecayVolume!= 12 &&isoInitVolume== 12 ) isoNumOut[isoZ][isoA]++;
                    //if(isoDecayVolume== 12 &&isoInitVolume!= 12 )isoNumIn[isoZ][isoA]++;
                    //if(isoDecayVolume!= 12 &&isoInitVolume== 12 ) isoNumOut[isoZ][isoA]++;
                    int initDet;
                    if( isoDecayVolume>= anaDet )
                    {
                        initDet=neuInitLocalX>0?2:1;
                        if( neuInitLocalY>300 )
                        {
                            initDet+=2;
                        }
                    }
                    int capDet;
                    if( isoDecayVolume>= anaDet )
                    {
                        capDet=neuInitLocalX>0?2:1;
                        if( neuInitLocalY>300 )
                        {
                            capDet+=2;
                        }
                    }
                    mt->GetEntry(neuEventID-1);
                    for( int mi=0 ; mi<4 ; mi++ )
                    {
                        muTrackLength[7][mi]=muSstTrackLength[mi];
                        muTrackLength[8][mi]=muMoTrackLength[mi];
                        muTrackLength[9][mi]=muOatTrackLength[mi];
                        muTrackLength[10][mi]=muLsTrackLength[mi];
                        muTrackLength[11][mi]=muIatTrackLength[mi];
                        muTrackLength[12][mi]=muGdLsTrackLength[mi];

                    }
                    if( muTrackLength[10][0]>0||  muTrackLength[10][1]>0|| muTrackLength[10][2]>0|| muTrackLength[10][3]>0)
                    {
                        if( isoDecayVolume>= anaDet  && muTrackLength[10][initDet-1]>0)
                        { 
                            isoNum[isoZ][isoA]++;
                        }
                        if((isoDecayVolume>= anaDet&&muTrackLength[10][capDet-1]>0)  && !(isoDecayVolume>= anaDet &&muTrackLength[10][initDet-1]>0)) isoNumIn[isoZ][isoA]++; 
                        if(!(isoDecayVolume>= anaDet &&muTrackLength[10][capDet-1]>0) && (isoDecayVolume>= anaDet &&muTrackLength[10][initDet-1]>0)) isoNumOut[isoZ][isoA]++;
                    }
                }

                f->Close();
            }
                /*
            for( map<int,int>::iterator it=muNeuMul.begin() ; it!=muNeuMul.end() ; it++ )
            {
                if( it->second !=0 )
                {
                    NeuMultiplicity->Fill(it->second);
                }
            }
                */
            

        }
        //in

        //c->cd(1);
        //dis->GetXaxis()->SetTitle(" /cm");
        //dis->Draw();
        //gPad->SetLogy();
        c->cd(1);
        //eng->GetXaxis()->SetTitle(" /GeV");
        //eng->Draw();
        //gPad->SetLogy();
        hz->Draw();
        c->cd(2);
        //eng2->GetXaxis()->SetTitle(" /MeV");
        //eng2->Draw();
        hr->Draw();
        c->cd(3);
        rz->Draw("COLZ");
        c->cd(4);
        hzAll->Draw();
        c->cd(5);
        hrAll->Draw();
        //rzNoW->Draw("COLZ");
        //inVolforCap->Draw();
        inVolvsClass->Draw("TEXT");
        c->cd(6);
        rzAll->Draw("COLZ");

        c->cd(7);
        xy->Draw("COLZ");
        c->cd(8);
        c->cd(9);
        int colorList[12]={kBlack+1,kAzure+10,3,4,6,7,kGreen+4,kOrange+2,kRed+2,kBlue-3,1,2};
        double maxValue=0.;
        for( int yi=1 ; yi<=12 ; yi++ )
        {
            nameStr=Form("RvsComX%d",yi);
            RvsComX[yi-1]=new TH1D(nameStr.c_str(),nameStr.c_str(),50,-250,250);
            for( int xi=1 ; xi<=50 ; xi++ )
            {
                RvsComX[yi-1]->SetBinContent(xi,RvsCom->GetBinContent(xi,yi));
            }

            maxValue=maxValue<RvsComX[yi-1]->GetMaximum()?RvsComX[yi-1]->GetMaximum():maxValue;
        }
        TLegend *legend=new TLegend(.6,.65,.79,.89);
        RvsComX[2]->SetMaximum(maxValue+10);
        RvsComX[2]->SetLineColor(colorList[2]);
        RvsComX[2]->Draw("C");
        nameStr=Form("Det %d",3);
        legend->AddEntry(RvsComX[2],nameStr.c_str(),"lp");
        for( int yi=4 ; yi<=12 ; yi++ )
        {
            RvsComX[yi-1]->SetLineColor(colorList[yi-1]);
            RvsComX[yi-1]->Draw("sameC");
            nameStr=Form("Det %d",yi);
            legend->AddEntry(RvsComX[yi-1],nameStr.c_str(),"lp");
        }
        legend->Draw("same");
        
        //inVolvsClassforCap->Draw("TEXT");
        nameStr=Form("c_%s_Det%d.eps",dataVer[0].c_str(),anaDet);
        c->SaveAs(nameStr.c_str());
        delete dis;
        delete eng;
        delete eng2;
        delete xy;
        delete rz;
        delete rzNoW;
        delete hr;
        delete hz;
        delete inVol;
        delete inVolvsClass;
        delete inVolforCap;
        delete inVolvsClassforCap;
        delete c;

        nameStr=Form("result_%s_Det%d.txt",dataVer[0].c_str(),anaDet);
        cout<<"nameStr "<<nameStr<<endl;
        cout<<"anaDet  : "<<anaDet<<endl;
        //print 
        double liveTime=GdMuonNum/(GdMuonRate*86400);
        cout<<"GdMuonNum : "<<GdMuonNum<<" liveTime : "<<liveTime<< " days"<<endl;
        cout<<"adMuonLength : "<<adMuonLength<<"   "<<adMuonLength/GdMuonNum<<" per muon"<<endl;
        //int neuNumCap=neuNum+neuNumOut-neuNumIn;
        //cout<<"neuNumInit  : "<<neuNumInit<<endl;
        cout<<"neuNum2  : "<<neuNum2<<endl;
        cout<<"neuGdCapNum: "<<neuGdCapNum<<endl;
        cout<<"neuGdCapNumAfter: "<<neuGdCapNumAfter<<endl;
        cout<<"capNeuNum  : "<<neuNum-neuNumOut+neuNumIn<<"="<<neuNum<<"-"<<neuNumOut<<"("<<(double)neuNumOut/neuNum*100 <<"%)+"<<neuNumIn<<"("<<(double)neuNumIn/neuNum*100 <<"%)"<<endl;
        cout<<"InitNeuNum : "<<neuNum<<"+-"<<sqrt(neuNum)<<"   "<<(double)neuNum/GdMuonNum <<" per muon" <<"   neuYield : "<<neuNum/adMuonLength/density*1.e5<<"e-05"<<" neuRate: "<<neuNum/liveTime<<" /day = "<<neuNum/liveTime/86400<<" Hz"<<endl;
        cout<<"Neutrons in initial volume : "<<endl;
        for( int i=0 ; i<15 ; i++ )
        {
            if(neuNumD[i]!=0) cout<<"    "<<i<<" : "<<neuNumD[i]<<endl;
        }

        cout<<"isoNum : "<<endl;
        for( int z=1 ; z<=7 ; z++ )
        {
            for( int a=1 ; a<300 ; a++ )
            {
                int isoNumFinal=isoNum[z][a];
                if(isoNumFinal==0) continue;
                if( isoNum[z][a]!=0 )
                {
                    cout<<"    "<<isoName[z-1]<<a<<" : "<<isoNumFinal <<" spill-out:"<<isoNumOut[z][a]<<"("<<(double)isoNumOut[z][a]/isoNum[z][a]*100 <<"%) spill-in:"<<isoNumIn[z][a]<<"("<<(double)isoNumIn[z][a]/isoNum[z][a]*100 <<"%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<" isoRate: "<<isoNum[z][a]/liveTime<<" /day = "<<isoNum[z][a]/liveTime/86400<<" Hz"<<endl;
                } else
                {
                    cout<<"    "<<isoName[z-1]<<a<<" : "<<isoNumFinal <<" spill-out:"<<isoNumOut[z][a]<<"(100%) spill-in:"<<isoNumIn[z][a]<<"(0%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<" isoRate: "<<isoNum[z][a]/liveTime<< " /day = "<<isoNum[z][a]/liveTime/86400<<" Hz"<<endl;
                }
            }
        }
        cout<<" "<<endl;

        ofstream outfile;

        outfile.open(nameStr.c_str());

        /*
        for( int n1=0 ; n1<15 ; n1++ )
        {
            for( int n2=0 ; n2<15 ; n2++ )
            {
                for( int n3=0 ; n3<15 ; n3++ )
                {
                    if( neuVolume[n1][n2][n3]!=0 )
                    {
                        outfile<<"Zall "<<n1<<"->"<<n2<<"->"<<n3<<" : "<<neuVolume[n1][n2][n3]<<endl;
                        if( n3== 5  && n2== 5  &&n1!= 5 )
                        {
                            outfile<<"In1  "<<n1<<"->"<<n2<<"->"<<n3<<" : "<<neuVolume[n1][n2][n3]<<endl;
                            In1+=neuVolume[n1][n2][n3];
                        }
                        if( n3== 5  && n2!= 5  &&n1!= 5 )
                        {
                            outfile<<"In2  "<<n1<<"->"<<n2<<"->"<<n3<<" : "<<neuVolume[n1][n2][n3]<<endl;
                            In2+=neuVolume[n1][n2][n3];
                        }
                        if( n3== 5  && n2!= 5  &&n1== 5 )
                        {
                            outfile<<"In3  "<<n1<<"->"<<n2<<"->"<<n3<<" : "<<neuVolume[n1][n2][n3]<<endl;
                            In3+=neuVolume[n1][n2][n3];
                        }
                        if( n3!= 5  && n2== 5  &&n1== 5 )
                        {
                            outfile<<"Out4 "<<n1<<"->"<<n2<<"->"<<n3<<" : "<<neuVolume[n1][n2][n3]<<endl;
                            Out4+=neuVolume[n1][n2][n3];
                        }
                        if( n3!= 5  && n2!= 5  &&n1== 5 )
                        {
                            outfile<<"Out5 "<<n1<<"->"<<n2<<"->"<<n3<<" : "<<neuVolume[n1][n2][n3]<<endl;
                            Out5+=neuVolume[n1][n2][n3];
                        }
                        if( n3== 5  && n2== 5  &&n1== 5 )
                        {
                            outfile<<"Cap6 "<<n1<<"->"<<n2<<"->"<<n3<<" : "<<neuVolume[n1][n2][n3]<<endl;
                            Cap6+=neuVolume[n1][n2][n3];
                        }
                        if( n3!= 5  && n2!= 5  &&n1!= 5 )
                        {
                            outfile<<"Oth7 "<<n1<<"->"<<n2<<"->"<<n3<<" : "<<neuVolume[n1][n2][n3]<<endl;
                            Oth7+=neuVolume[n1][n2][n3];
                        }
                        if( n3!= 5  && n2== 5  &&n1!= 5 )
                        {
                            outfile<<"Oth8 "<<n1<<"->"<<n2<<"->"<<n3<<" : "<<neuVolume[n1][n2][n3]<<endl;
                            Oth8+=neuVolume[n1][n2][n3];
                        }

                    }
                }

            }

        }
        */
        outfile<<"In1  : "<<In1<<endl;
        outfile<<"In2  : "<<In2<<endl;
        outfile<<"In3  : "<<In3<<endl;
        outfile<<"Out4 : "<<Out4<<endl;
        outfile<<"Out5 : "<<Out5<<endl;
        outfile<<"Cap6 : "<<Cap6<<endl;
        outfile<<"Oth7 : "<<Oth7<<endl;
        outfile<<"Oth8 : "<<Oth8<<endl;
        outfile<<"***********(1)***********"<<endl;
        outfile<<"neuNumIn : "<<neuNumIn<<" <==> In1("<<In1<<"/"<<(double)In1/(In1+In2+In3)*100<<"%)+In2("<<In2<<"/"<<(double)In2/(In1+In2+In3)*100<<"%)+In3("<<In3<<"/"<<(double)In3/(In1+In2+In3)*100<<"%)="<<In1+In2+In3<<endl;
        outfile<<"neuNumOut : "<<neuNumOut<<" <==> Out4 "<<Out4<<endl;
        outfile<<"neuNum : "<<neuNum<<" <==> Cap6("<<Cap6<<"/"<<(double)Cap6/(Cap6+Out4)<<")+Out4("<<Out4<<"/"<<(double)Out4/(Cap6+Out4)<<")="<<Cap6+Out4<<endl; 

        outfile<<"***********(2)***********"<<endl;
        outfile<<"neuNumIn : "<<neuNumIn<<" <==> In2("<<In2<<"/"<<(double)In2/(In2+In3)*100<<"%)+In3("<<In3<<"/"<<(double)In3/(In2+In3)*100<<"%)="<<In2+In3<<endl;
        outfile<<"neuNumOut : "<<neuNumOut<<" <==> Out4("<<Out4<<"/"<<(double)Out4/(Out4+Oth8)*100<<"%)+Oth8("<<Oth8 <<"/"<<(double)Oth8/(Out4+Oth8)*100 <<"%)="<<Out4+Oth8<<endl;
        outfile<<"neuNum : "<<neuNum<<" <==> Cap6+In1+Oth8+Out4="<<Cap6+In1+Oth8+Out4<<endl; 

        outfile<<"GdMuonNum : "<<GdMuonNum<<" liveTime : "<<liveTime<< " days"<<endl;
        outfile<<"adMuonLength : "<<adMuonLength<<"   "<<adMuonLength/GdMuonNum<<" per muon"<<endl;
        //outfile<<"neuNumInit  : "<<neuNumInit<<endl;
        outfile<<"neuNum  : "<<neuNum<<"="<<neuNum<<"+"<<neuNumOut<<"("<<(double)neuNumOut/neuNum*100 <<"%)-"<<neuNumIn<<"("<<(double)neuNumIn/neuNum*100 <<"%)"<<endl;
        outfile<<"neuNum : "<<neuNum<<"+-"<<sqrt(neuNum)<<"   "<<(double)neuNum/GdMuonNum <<" per muon" <<"   neuYield : "<<neuNum/adMuonLength/density*1.e5<<"e-05"<<" neuRate: "<<neuNum/liveTime<<" /day = "<<neuNum/liveTime/86400<<" Hz"<<endl;
        outfile<<"Neutrons in initial volume : "<<endl;
        for( int i=0 ; i<15 ; i++ )
        {
            if(neuNumD[i]!=0) outfile<<"    "<<i<<" : "<<neuNumD[i]<<endl;
        }

        outfile<<"isoNum : "<<endl;
        for( int z=1 ; z<=7 ; z++ )
        {
            for( int a=1 ; a<300 ; a++ )
            {
                int isoNumFinal=isoNum[z][a];
                if(isoNumFinal==0) continue;
                if( isoNum[z][a]!=0 )
                {
                    outfile<<"    "<<isoName[z-1]<<a<<" : "<<isoNumFinal <<" spill-out:"<<isoNumOut[z][a]<<"("<<(double)isoNumOut[z][a]/isoNum[z][a]*100 <<"%) spill-in:"<<isoNumIn[z][a]<<"("<<(double)isoNumIn[z][a]/isoNum[z][a]*100 <<"%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<" isoRate: "<<isoNum[z][a]/liveTime<<" /day = "<<isoNum[z][a]/liveTime/86400<<" Hz"<<endl;
                } else
                {
                    outfile<<"    "<<isoName[z-1]<<a<<" : "<<isoNumFinal <<" spill-out:"<<isoNumOut[z][a]<<"(100%) spill-in:"<<isoNumIn[z][a]<<"(0%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<" isoRate: "<<isoNum[z][a]/liveTime<< " /day = "<<isoNum[z][a]/liveTime/86400<<" Hz"<<endl;
                }
            }
        }

        outfile<<" "<<endl;
        outfile.close();
    }
}
