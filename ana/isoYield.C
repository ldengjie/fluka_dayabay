{
    int rootNum=1000;
    string dataVer[4]={"PART2"};
    string nameStr;
    //double density=0.8602;
    double muonRate=15.*0.6;
    double density=0.8550;
    string isoName[7]={"H","He","Li","Be","B","C","N"};
    for( int j=0 ; j<1 ; j++ )
    {
        int adMuonNum=0;
        double adMuonLength=0.;
        int neuNum=0;
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
        TH1D* hz=new TH1D("hz","z of neutron",500,-250,250);
        TH1D* inVol=new TH1D("inVol","volume of spill-in neutron",12,0,12);
        TH2D* inVolvsClass=new TH2D("inVolvsClass","volume of spill-in neutron",12,0,12,5,0,5);
        TH1D* inVolforCap=new TH1D("inVolforCap","volume of spill-in neutron",12,0,12);
        TH2D* inVolvsClassforCap=new TH2D("inVolvsClassforCap","volume of spill-in neutron",12,0,12,5,0,5);
        TCanvas* c=new TCanvas("c","c",1400,700);
        c->Divide(3,2);


        for( int i=1; i<rootNum+1; i++ )
        {
            nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/data/%s/rootFile/fluSim_%06d.root",dataVer[j].c_str(),i);
=======
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
                int neuInitVolumeName;
                int neuCapVolumeName;
                int neuOriginVolumeNumber;
                int neuMotherInteractionType;
                neut->SetBranchAddress("EventID",&neuEventID);
                neut->SetBranchAddress("InitTime",&neuInitTime);
                neut->SetBranchAddress("InitKineE",&neuInitKineE);
                neut->SetBranchAddress("InitLocalX",&neuInitLocalX);
                neut->SetBranchAddress("InitLocalY",&neuInitLocalY);
                neut->SetBranchAddress("InitLocalZ",&neuInitLocalZ);
                neut->SetBranchAddress("InitVolumeName",&neuInitVolumeName);
                neut->SetBranchAddress("CapVolumeName",&neuCapVolumeName);
                neut->SetBranchAddress("OriginVolumeNumber",&neuOriginVolumeNumber);
                neut->SetBranchAddress("MotherInteractionType",&neuMotherInteractionType);

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
                for( int u=0 ; u<mtnum ; u++ )
                {
                    mt->GetEntry(u);
                    bool passGdLs=0;
                    for( int ai=0 ; ai<4 ; ai++ )
                    {
                        if(muGdLsTrackLength[ai]==0) continue;
                        passGdLs=1;
                        adMuonNum++;
                        adMuonLength+=muGdLsTrackLength[ai];
                    }
                    if( passGdLs )
                    {
                        muIndex.insert(std::pair<int,int>(muEventID,u));
                    }

                }

                //cout<<"neutnum  : "<<neutnum<<endl;
                for( int r=0 ; r<neutnum ; r++ )
                {
                    neut->GetEntry(r);

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
                    if( neuInitVolumeName== 12 )
                    {
                        initDet=neuInitLocalX>0?2:1;
                        if( neuInitLocalY>300 )
                        {
                            initDet+=2;
                        }
                    }
                    int capDet;
                    if( neuCapVolumeName== 12 )
                    {
                        capDet=neuInitLocalX>0?2:1;
                        if( neuInitLocalY>300 )
                        {
                            capDet+=2;
                        }
                    }
                    mt->GetEntry(neuEventID-1);
                    if( muGdLsTrackLength[0]>0||  muGdLsTrackLength[1]>0|| muGdLsTrackLength[2]>0|| muGdLsTrackLength[3]>0)
                    {
                        if( neuInitVolumeName== 12  && muGdLsTrackLength[initDet-1]>0)
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
                            //cout<<"initDet,neuInitLocalX,neuInitLocalY,centerX,centerY,radius  : "<<initDet<<","<<neuInitLocalX<<","<<neuInitLocalY<<","<<centerX<<","<<centerY<<","<<radius<<endl;

                            rz->Fill(radius,neuInitLocalZ,1/radius);
                            rzNoW->Fill(radius,neuInitLocalZ);
                            hz->Fill(neuInitLocalZ);
                            //hr->Fill(radius,radius); 
                            hr->Fill(radius,1/radius); 
                        }
                        if((neuCapVolumeName== 12&&muGdLsTrackLength[capDet-1]>0)  && !(neuInitVolumeName== 12 &&muGdLsTrackLength[initDet-1]>0))
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
                        if((neuCapVolumeName== 12)  && !(neuInitVolumeName== 12))
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
                        if(!(neuCapVolumeName== 12 &&muGdLsTrackLength[capDet-1]>0) && (neuInitVolumeName== 12 &&muGdLsTrackLength[initDet-1]>0)) neuNumOut++;
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
                    if( isoDecayVolume== 12 )
                    {
                        initDet=neuInitLocalX>0?2:1;
                        if( neuInitLocalY>300 )
                        {
                            initDet+=2;
                        }
                    }
                    int capDet;
                    if( isoDecayVolume== 12 )
                    {
                        capDet=neuInitLocalX>0?2:1;
                        if( neuInitLocalY>300 )
                        {
                            capDet+=2;
                        }
                    }
                    mt->GetEntry(neuEventID-1);
                    if( muGdLsTrackLength[0]>0||  muGdLsTrackLength[1]>0|| muGdLsTrackLength[2]>0|| muGdLsTrackLength[3]>0)
                    {
                        if( isoDecayVolume== 12  && muGdLsTrackLength[initDet-1]>0)
                        { 
                            isoNum[isoZ][isoA]++;
                        }
                        if((isoDecayVolume== 12&&muGdLsTrackLength[capDet-1]>0)  && !(isoDecayVolume== 12 &&muGdLsTrackLength[initDet-1]>0)) isoNumIn[isoZ][isoA]++; 
                        if(!(isoDecayVolume== 12 &&muGdLsTrackLength[capDet-1]>0) && (isoDecayVolume== 12 &&muGdLsTrackLength[initDet-1]>0)) isoNumOut[isoZ][isoA]++;
                    }
                }

                f->Close();
            }

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
        xy->Draw("COLZ");
        c->cd(4);
        rz->Draw("COLZ");
        c->cd(5);
        rzNoW->Draw("COLZ");
        //inVolforCap->Draw();
        c->cd(6);
        //inVolvsClassforCap->Draw("TEXT");
        nameStr=Form("c_%s.eps",dataVer[j].c_str());
        c->SaveAs(nameStr.c_str());

        nameStr=Form("result_%s.txt",dataVer[j].c_str());
        cout<<"nameStr "<<nameStr<<endl;
        //print 
        double liveTime=adMuonNum/(muonRate*86400);
        cout<<"adMuonNum : "<<adMuonNum<<" liveTime : "<<liveTime<< " days"<<endl;
        cout<<"adMuonLength : "<<adMuonLength<<"   "<<adMuonLength/adMuonNum<<" per muon"<<endl;
        //int neuNumCap=neuNum+neuNumOut-neuNumIn;
        //cout<<"neuNumInit  : "<<neuNumInit<<endl;
        cout<<"neuNum2  : "<<neuNum2<<endl;
        cout<<"capNeuNum  : "<<neuNum-neuNumOut+neuNumIn<<"="<<neuNum<<"-"<<neuNumOut<<"("<<(double)neuNumOut/neuNum*100 <<"%)+"<<neuNumIn<<"("<<(double)neuNumIn/neuNum*100 <<"%)"<<endl;
        cout<<"InitNeuNum : "<<neuNum<<"+-"<<sqrt(neuNum)<<"   "<<(double)neuNum/adMuonNum <<" per muon" <<"   neuYield : "<<neuNum/adMuonLength/density*1.e5<<"e-05"<<" neuRate: "<<neuNum/liveTime<<" /day = "<<neuNum/liveTime/86400<<" Hz"<<endl;
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

        outfile<<"adMuonNum : "<<adMuonNum<<" liveTime : "<<liveTime<< " days"<<endl;
        outfile<<"adMuonLength : "<<adMuonLength<<"   "<<adMuonLength/adMuonNum<<" per muon"<<endl;
        //outfile<<"neuNumInit  : "<<neuNumInit<<endl;
        outfile<<"neuNum  : "<<neuNum<<"="<<neuNum<<"+"<<neuNumOut<<"("<<(double)neuNumOut/neuNum*100 <<"%)-"<<neuNumIn<<"("<<(double)neuNumIn/neuNum*100 <<"%)"<<endl;
        outfile<<"neuNum : "<<neuNum<<"+-"<<sqrt(neuNum)<<"   "<<(double)neuNum/adMuonNum <<" per muon" <<"   neuYield : "<<neuNum/adMuonLength/density*1.e5<<"e-05"<<" neuRate: "<<neuNum/liveTime<<" /day = "<<neuNum/liveTime/86400<<" Hz"<<endl;
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
