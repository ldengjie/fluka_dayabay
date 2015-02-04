{
    int rootNum=8000;
    string dataVer[4]={"PART10"};
    string nameStr;
    double GdMuonRate=21.*0.6;
    double density=0.8550;
    string isoName[7]={"H","He","Li","Be","B","C","N"};
    int muSelList[4]={4,5,10,12};
    double neuYield[4]={0.};
    int anaDet=12;
    double re_adMuonLength=0.;
    int re_GdMuonNum=0;
    double xi_spill[4]={0.};
    double xi_Gd[4]={0.};
    TH1D* xi_th[4];
    double xi_time[4]={0.};
    double xi_mu[4]={0.};
    for( int im=0;im<4;im++  )
    {

        int muonSel=muSelList[im];
        int GdMuonNum=0;
        double adMuonLength=0.;
        int LsMuonNum=0;
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
                    int desMuInducedIsoNum[150][300]={0};
                    int desMuInducedNeuNum=0;
                    int desMuInducedNeuInitVol[15]={0};
        nameStr=Form("histo_%s_Det%d_Sel%d.root",dataVer[0].c_str(),anaDet,muonSel);
        TFile* fout=new TFile(nameStr.c_str(),"recreate");
        xi_th[im]=new TH1D("CapTimeMinusInitTime","CapTimeMinusInitTime",2000,0,2.e6);
        TH1D* dis=new TH1D("dis","distance between neutron and muon track",1000,0,1000);
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
        TH1D* NeuT2Admuon=new TH1D("NeuT2Admuon","time interval between neutron and previous admuon",500,0,500.e3);

        TH1F* capDis=new TH1F("capDis","distance between neutron captured positon and muon track",1000,0,1000);
        TH1D* capT2muon=new TH1D("capT2muon","time interval between neutron captured time and mother muon",500,0,500.e-6);
        TH1F* capEng2=new TH1F("capEng2","energy of neutron",24,6,12);
        TH1F* NeuMultiplicity=new TH1F("NeuMultiplicity","neutron multiplicity for each ad muon",500,0,500);
        TH1F* NeuMultiplicityAfterCut=new TH1F("NeuMultiplicityAfterCut","neutron multiplicity for each ad muon",500,0,500);
        TCanvas* c=new TCanvas("c","c",1200,900);
        c->Divide(3,3);


        //loop for counting
        for( int i=2001; i<=rootNum; i++ )
        {
            nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/data/%s/rootFile/fluSim_%06d_sort.root",dataVer[0].c_str(),i);
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
                int muNumOfNeutron;
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
                mt->SetBranchAddress("NumOfNeutron",&muNumOfNeutron);

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
                map<int,int> muNeuMulAfterCut;
                for( int u=0 ; u<mtnum ; u++ )
                {
                    mt->GetEntry(u);
                    for( int mi=0 ; mi<4 ; mi++ )
                    {
                        muTrackLength[3][mi] =muAirTrackLength;
                        muTrackLength[4][mi] =muStoneTrackLength;
                        muTrackLength[5][mi] =muIwsTrackLength+muOwsTrackLength;
                        muTrackLength[6][mi] =muOwsTrackLength;
                        muTrackLength[7][mi] =muSstTrackLength[mi] ;
                        muTrackLength[8][mi] =muMoTrackLength[mi]  ;
                        muTrackLength[9][mi] =muOatTrackLength[mi] ;
                        muTrackLength[10][mi]=muLsTrackLength[mi]  ;
                        muTrackLength[11][mi]=muIatTrackLength[mi] ;
                        muTrackLength[12][mi]=muGdLsTrackLength[mi];

                    }

                    bool passLs=0;
                    bool passWp=0;
                    for( int ai=0 ; ai<4 ; ai++ )
                    {
                        if( muTrackLength[10][ai]>0 )
                        {
                            LsMuonNum++;
                        }
                        if(muTrackLength[anaDet][ai]==0) continue;
                        GdMuonNum++;
                        for( int di=anaDet ; di<=12;di++ )
                        {
                            adMuonLength+=muTrackLength[di][ai];
                        }

                    }
                    if( muTrackLength[5][0]!=0 )
                    {
                        muNeuMul.insert(std::pair<int,int>(muEventID*10+0+1,0));
                        muNeuMulAfterCut.insert(std::pair<int,int>(muEventID*10+0+1,0));
                    }
                    for( int ai=0 ; ai<4 ; ai++ )
                    {
                        if(muTrackLength[muonSel][ai]==0) continue;
                        passLs=1;
                    }
                    if( passLs )
                    {
                        muIndex.insert(std::pair<int,int>(muEventID,u));
                    }

                }

                for( int r=0 ; r<neutnum ; r++ )
                {
                    neut->GetEntry(r);
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
                    if(muIndex.find(neuEventID)==muIndex.end()) continue;
                    neuNumD[14]++;
                    neuNumD[neuInitVolumeName]++;

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
                        muTrackLength[3][mi] =muAirTrackLength;
                        muTrackLength[4][mi] =muStoneTrackLength;
                        muTrackLength[5][mi] =muIwsTrackLength+muOwsTrackLength;
                        muTrackLength[6][mi] =muOwsTrackLength;
                        muTrackLength[7][mi]=muSstTrackLength[mi];
                        muTrackLength[8][mi]=muMoTrackLength[mi];
                        muTrackLength[9][mi]=muOatTrackLength[mi];
                        muTrackLength[10][mi]=muLsTrackLength[mi];
                        muTrackLength[11][mi]=muIatTrackLength[mi];
                        muTrackLength[12][mi]=muGdLsTrackLength[mi];

                    }
                    if( muTrackLength[muonSel][0]>0||  muTrackLength[muonSel][1]>0|| muTrackLength[muonSel][2]>0|| muTrackLength[muonSel][3]>0)
                    {
                        if( neuOriginVolumeNumber>=anaDet)
                        {
                            desMuInducedNeuNum++;
                            desMuInducedNeuInitVol[neuInitVolumeName]++;
                        }
                        //captured in GDLS
                        if( neuCapVolumeName>= anaDet  && muTrackLength[muonSel][capDet-1]>0 )
                        {
                            if( muNeuMul.find(neuEventID*10+1)!=muNeuMul.end() )
                            {
                                muNeuMul[neuEventID*10+1]++;
                                if( neuCapTime>=20.e3 && neuCapTime<=500.e3 )
                                {
                                    muNeuMulAfterCut[neuEventID*10+1]++;
                                }
                            }
                            if( neuCapGammaESum>0.006 && neuCapGammaESum<0.012 && neuCapTime>10.e3 &&neuCapTime<200.e3)
                            {
                                neuGdCapNumAfter++;
                            }
                            if( neuCapTargetName== 26)
                            {
                                neuGdCapNum++;
                                xi_th[im]->Fill(neuCapTime-neuInitTime);
                                double disV=sqrt(
                                        (muInitLocalYCos*(neuCapLocalZ-muInitLocalZ)-muInitLocalZCos*(neuCapLocalY-muInitLocalY))*(muInitLocalYCos*(neuCapLocalZ-muInitLocalZ)-muInitLocalZCos*(neuCapLocalY-muInitLocalY))+
                                        (muInitLocalXCos*(neuCapLocalZ-muInitLocalZ)-muInitLocalZCos*(neuCapLocalX-muInitLocalX))*(muInitLocalXCos*(neuCapLocalZ-muInitLocalZ)-muInitLocalZCos*(neuCapLocalX-muInitLocalX))+
                                        (muInitLocalXCos*(neuCapLocalY-muInitLocalY)-muInitLocalYCos*(neuCapLocalX-muInitLocalX))*(muInitLocalXCos*(neuCapLocalY-muInitLocalY)-muInitLocalYCos*(neuCapLocalX-muInitLocalX)));
                            capDis->Fill(disV);
                            capT2muon->Fill(neuCapTime/1.e9);
                            capEng2->Fill(neuCapGammaESum*1000);
                            }
                        }
                        //initialized in GDLS
                        if( neuInitVolumeName>= anaDet  && muTrackLength[muonSel][initDet-1]>0)
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

                            rz->Fill(radius,neuInitLocalZ,weight);
                            rzNoW->Fill(radius,neuInitLocalZ);
                            hz->Fill(neuInitLocalZ);
                            hr->Fill(radius,weight); 
                            RvsCom->Fill(neuInitLocalZ,neuOriginVolumeNumber);
                        }
                        //spill in
                        if((neuCapVolumeName>= anaDet&&muTrackLength[muonSel][capDet-1]>0)  && !(neuInitVolumeName>= anaDet &&muTrackLength[muonSel][initDet-1]>0))
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
                        //spill out
                        if(!(neuCapVolumeName>= anaDet &&muTrackLength[muonSel][capDet-1]>0) && (neuInitVolumeName>= anaDet &&muTrackLength[muonSel][initDet-1]>0)) neuNumOut++;
                    }else
                    {
                        if( neuOriginVolumeNumber>=anaDet)
                        {
                           cout<<"ERROR:~~~~~~~~~~~~~~~~neuOriginVolumeNumber>=anaDet~~~ "<<endl; 
                        }
                    }



                }

                for( map<int,int>::iterator it=muNeuMul.begin() ; it!=muNeuMul.end() ; it++ )
                {
                    if( it->second>0 )
                    {
                        NeuMultiplicity->Fill(it->second);
                    }
                }
                for( map<int,int>::iterator it=muNeuMulAfterCut.begin() ; it!=muNeuMulAfterCut.end() ; it++ )
                {
                    if( it->second>0 )
                    {
                        NeuMultiplicityAfterCut->Fill(it->second);
                    }
                }
                

                for( int is=0 ; is<isotnum ; is++ )
                {
                    isot->GetEntry(is);
                    if(muIndex.find(isoEventID)==muIndex.end()) continue;
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
                    mt->GetEntry(isoEventID-1);
                    for( int mi=0 ; mi<4 ; mi++ )
                    {
                        muTrackLength[3][mi] =muAirTrackLength;
                        muTrackLength[4][mi] =muStoneTrackLength;
                        muTrackLength[5][mi] =muIwsTrackLength+muOwsTrackLength;
                        muTrackLength[6][mi] =muOwsTrackLength;
                        muTrackLength[7][mi]=muSstTrackLength[mi];
                        muTrackLength[8][mi]=muMoTrackLength[mi];
                        muTrackLength[9][mi]=muOatTrackLength[mi];
                        muTrackLength[10][mi]=muLsTrackLength[mi];
                        muTrackLength[11][mi]=muIatTrackLength[mi];
                        muTrackLength[12][mi]=muGdLsTrackLength[mi];

                    }
                    if( muTrackLength[muonSel][0]>0||  muTrackLength[muonSel][1]>0|| muTrackLength[muonSel][2]>0|| muTrackLength[muonSel][3]>0)
                    {
                    if( isoOriginVolumeNumber>=anaDet )
                    {
                        desMuInducedIsoNum[isoZ][isoA]++;
                    }
                        if( isoDecayVolume>= anaDet  && muTrackLength[muonSel][capDet-1]>0)
                        { 
                            isoNum[isoZ][isoA]++;
                        }
                        if((isoDecayVolume>= anaDet&&muTrackLength[muonSel][capDet-1]>0)  && !(isoInitVolume>= anaDet &&muTrackLength[muonSel][initDet-1]>0)) isoNumIn[isoZ][isoA]++; 
                        if(!(isoDecayVolume>= anaDet &&muTrackLength[muonSel][capDet-1]>0) && (isoInitVolume>= anaDet &&muTrackLength[muonSel][initDet-1]>0)) isoNumOut[isoZ][isoA]++;
                    }else
                    {
                        if( isoOriginVolumeNumber>=anaDet)
                        {
                           cout<<"ERROR:~~~~~~~~~~~~~~~~isoOriginVolumeNumber>=anaDet~~~ "<<endl; 
                        }
                    }
                }

                f->Close();
            }

        }

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
        nameStr=Form("c_%s_Det%d_Sel%d.eps",dataVer[0].c_str(),anaDet,muonSel);
        c->SaveAs(nameStr.c_str());

        nameStr=Form("result_%s_Det%d_Sel%d.txt",dataVer[0].c_str(),anaDet,muonSel);
        xi_spill[im]=(double)(neuNum-neuNumOut+neuNumIn)/neuNum;
        xi_Gd[im]=(double)neuGdCapNum/(neuNum-neuNumOut+neuNumIn);
        int binMin=xi_th[im]->FindBin(20.e3);
        int binMax=xi_th[im]->FindBin(500.e3);
        xi_time[im]=(double)xi_th[im]->Integral(binMin,binMax)/xi_th[im]->GetEntries();
        xi_mu[im]=(double)GdMuonNum/LsMuonNum;
        cout<<"nameStr "<<nameStr<<endl;
        cout<<"anaDet  : "<<anaDet<<endl;
        cout<<"muonSel: "<<muonSel<<endl;
        //print 
        cout<<"xi_spill  : "<<xi_spill[im]<<endl;
        cout<<"xi_Gd: "<<xi_Gd[im]<<endl;
        cout<<"xi_time: "<<xi_time[im]<<endl;
        cout<<"xi_mu: "<<xi_mu[im]<<endl;
        double liveTime=GdMuonNum/(GdMuonRate*86400);
        cout<<"GdMuonNum : "<<GdMuonNum<<" liveTime : "<<liveTime<< " days"<<endl;
        cout<<"adMuonLength : "<<adMuonLength<<"   "<<adMuonLength/GdMuonNum<<" per muon"<<endl;
        cout<<"neuGdCapNum: "<<neuGdCapNum<<endl;
        cout<<"neuGdCapNumAfter: "<<neuGdCapNumAfter<<endl;
        cout<<"capNeuNum  : "<<neuNum-neuNumOut+neuNumIn<<"="<<neuNum<<"-"<<neuNumOut<<"("<<(double)neuNumOut/neuNum*100 <<"%)+"<<neuNumIn<<"("<<(double)neuNumIn/neuNum*100 <<"%)"<<endl;
        cout<<"InitNeuNum : "<<neuNum<<"+-"<<sqrt(neuNum)<<"   "<<(double)neuNum/GdMuonNum <<" per muon" <<"   neuYield : "<<neuNum/adMuonLength/density*1.e5<<"e-05"<<" neuRate: "<<neuNum/liveTime<<" /day = "<<neuNum/liveTime/86400<<" Hz"<<endl;
        cout<<"desMuInducedNeuNum from GDLS : "<<desMuInducedNeuNum<<"+-"<<sqrt(desMuInducedNeuNum)<<"   "<<(double)desMuInducedNeuNum/GdMuonNum <<" per muon" <<"   neuYield : "<<desMuInducedNeuNum/adMuonLength/density*1.e5<<"e-05"<<" neuRate: "<<desMuInducedNeuNum/liveTime<<" /day = "<<desMuInducedNeuNum/liveTime/86400<<" Hz"<<endl;
        for( int i=0 ; i<15 ; i++ )
        {
            if( desMuInducedNeuInitVol[i]!=0 )
            {
                cout<<" "<<i<<"  : "<<desMuInducedNeuInitVol[i]<<" "<<(double)desMuInducedNeuInitVol[i]/desMuInducedNeuNum<<"  "<<(double)desMuInducedNeuInitVol[i]/(0.0151706*GdMuonNum)<<endl;
            }
        }
        
        neuYield[im]=neuNum/adMuonLength/density;
        //cout<<"Neutrons in initial volume : "<<endl;
        //for( int i=0 ; i<15 ; i++ )
        //{
        //if(neuNumD[i]!=0) cout<<"    "<<i<<" : "<<neuNumD[i]<<endl;
        //}

        cout<<"isoNum : "<<endl;
        for( int z=1 ; z<=7 ; z++ )
        {
            for( int a=1 ; a<300 ; a++ )
            {
                int isoNumFinal=isoNum[z][a];
                if(isoNumFinal==0) continue;
                if( isoNum[z][a]!=0 )
                {
                    cout<<"    "<<isoName[z-1]<<a<<" : "<<isoNumFinal <<" spill-out:"<<isoNumOut[z][a]<<"("<<(double)isoNumOut[z][a]/isoNum[z][a]*100 <<"%) spill-in:"<<isoNumIn[z][a]<<"("<<(double)isoNumIn[z][a]/isoNum[z][a]*100 <<"%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<" isoRate: "<<isoNum[z][a]/liveTime<<" /day = "<<isoNum[z][a]/liveTime/86400<<" Hz | "<<desMuInducedIsoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<endl;
                } else
                {
                    cout<<"    "<<isoName[z-1]<<a<<" : "<<isoNumFinal <<" spill-out:"<<isoNumOut[z][a]<<"(100%) spill-in:"<<isoNumIn[z][a]<<"(0%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<" isoRate: "<<isoNum[z][a]/liveTime<< " /day = "<<isoNum[z][a]/liveTime/86400<<" Hz | "<<desMuInducedIsoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<endl;
                }
            }
        }
        cout<<" "<<endl;

        ofstream outfile;

        outfile.open(nameStr.c_str());

        outfile<<"nameStr "<<nameStr<<endl;
        outfile<<"anaDet  : "<<anaDet<<endl;
        outfile<<"muonSel: "<<muonSel<<endl;
        //print 
        outfile<<"xi_spill  : "<<xi_spill[im]<<endl;
        outfile<<"xi_Gd: "<<xi_Gd[im]<<endl;
        outfile<<"xi_time: "<<xi_time[im]<<endl;
        outfile<<"xi_mu: "<<xi_mu[im]<<endl;
        outfile<<"GdMuonNum : "<<GdMuonNum<<" liveTime : "<<liveTime<< " days"<<endl;
        outfile<<"adMuonLength : "<<adMuonLength<<"   "<<adMuonLength/GdMuonNum<<" per muon"<<endl;
        outfile<<"neuGdCapNum: "<<neuGdCapNum<<endl;
        outfile<<"neuGdCapNumAfter: "<<neuGdCapNumAfter<<endl;
        outfile<<"capNeuNum  : "<<neuNum-neuNumOut+neuNumIn<<"="<<neuNum<<"-"<<neuNumOut<<"("<<(double)neuNumOut/neuNum*100 <<"%)+"<<neuNumIn<<"("<<(double)neuNumIn/neuNum*100 <<"%)"<<endl;
        outfile<<"InitNeuNum : "<<neuNum<<"+-"<<sqrt(neuNum)<<"   "<<(double)neuNum/GdMuonNum <<" per muon" <<"   neuYield : "<<neuNum/adMuonLength/density*1.e5<<"e-05"<<" neuRate: "<<neuNum/liveTime<<" /day = "<<neuNum/liveTime/86400<<" Hz"<<endl;
        outfile<<"desMuInducedNeuNum from GDLS : "<<desMuInducedNeuNum<<"+-"<<sqrt(desMuInducedNeuNum)<<"   "<<(double)desMuInducedNeuNum/GdMuonNum <<" per muon" <<"   neuYield : "<<desMuInducedNeuNum/adMuonLength/density*1.e5<<"e-05"<<" neuRate: "<<desMuInducedNeuNum/liveTime<<" /day = "<<desMuInducedNeuNum/liveTime/86400<<" Hz"<<endl;

        outfile<<"isoNum : "<<endl;

        for( int z=1 ; z<=7 ; z++ )
        {
            for( int a=1 ; a<300 ; a++ )
            {
                int isoNumFinal=isoNum[z][a];
                if(isoNumFinal==0) continue;
                if( isoNum[z][a]!=0 )
                {
                    outfile<<"    "<<isoName[z-1]<<a<<" : "<<isoNumFinal <<" spill-out:"<<isoNumOut[z][a]<<"("<<(double)isoNumOut[z][a]/isoNum[z][a]*100 <<"%) spill-in:"<<isoNumIn[z][a]<<"("<<(double)isoNumIn[z][a]/isoNum[z][a]*100 <<"%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<" isoRate: "<<isoNum[z][a]/liveTime<<" /day = "<<isoNum[z][a]/liveTime/86400<<" Hz | "<<desMuInducedIsoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<endl;
                } else
                {
                    outfile<<"    "<<isoName[z-1]<<a<<" : "<<isoNumFinal <<" spill-out:"<<isoNumOut[z][a]<<"(100%) spill-in:"<<isoNumIn[z][a]<<"(0%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<" isoRate: "<<isoNum[z][a]/liveTime<< " /day = "<<isoNum[z][a]/liveTime/86400<<" Hz | "<<desMuInducedIsoNum[z][a]/adMuonLength/density*1.e7<<"e-07"<<endl;
                }
            }
        }
        outfile<<" "<<endl;
        outfile.close();
        fout->Write();
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
        delete rzAll;
        delete hrAll;
        delete hzAll;
        delete NeuT2Admuon;
        delete RvsCom;
        delete xi_th[im];
        delete NeuMultiplicity;
        delete capT2muon;
        delete capDis;
        delete capEng2;
        
        for( int yi=1 ; yi<=12 ; yi++ )
        {
            delete RvsComX[yi-1];
        }
        delete fout;
    }
    cout<<"======== xi when muon pass through LS ======== "<<endl;
    cout<<"xi_geo  : "<<neuYield[1]/neuYield[0]<<endl;
    cout<<"xi_spill  : "<<xi_spill[1]<<endl;
    cout<<"xi_Gd  : "<<xi_Gd[1]<<endl;
    cout<<"xi_time: "<<xi_time[1]<<endl;
    cout<<"xi_mu: "<<xi_mu[1]<<endl;
    cout<<"TrackLength : "<<re_adMuonLength/re_GdMuonNum<<"cm  per muon"<<endl;
}
