{
    int rootNum=7;
    string dataVer[4]={"whole"};
    string nameStr;
    string isoName[7]={"H","He","Li","Be","B","C","N"};
    for( int j=0 ; j<1 ; j++ )
    {
    int adMuonNum=0;
    double adMuonLength=0.;
    int neuNum=0;
    int neuNumOut=0;
    int neuNumIn=0;
    int neuNumD[15]={0};
    int isoNum[150][300]={0};
    int isoNumOut[150][300]={0};
    int isoNumIn[150][300]={0};
    

    //loop for counting
    for( int i=1 ; i<rootNum+1; i++ )
    {
        nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/data/%s/LA%03d_sim.root",dataVer[j].c_str(),i);
        //if( i%100==0 )
        //{
        //std::cout<<"filename : "<<nameStr<<endl;
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
            double muSstTrackLength;
            double muOatTrackLength;
            double muIatTrackLength;
            double muMoTrackLength;
            double muLsTrackLength;
            double muGdLsTrackLength;
            mt->SetBranchAddress("EventID",&muEventID);
            mt->SetBranchAddress("InitLocalX",&muInitLocalX);
            mt->SetBranchAddress("InitLocalY",&muInitLocalY);
            mt->SetBranchAddress("InitLocalZ",&muInitLocalZ);
            mt->SetBranchAddress("InitLocalXCos",&muInitLocalXCos);
            mt->SetBranchAddress("InitLocalYCos",&muInitLocalYCos);
            mt->SetBranchAddress("InitLocalZCos",&muInitLocalZCos);
            mt->SetBranchAddress("SstTrackLength",&muSstTrackLength);
            mt->SetBranchAddress("OatTrackLength",&muOatTrackLength);
            mt->SetBranchAddress("IatTrackLength",&muIatTrackLength);
            mt->SetBranchAddress("MoTrackLength",&muMoTrackLength);
            mt->SetBranchAddress("LsTrackLength",&muLsTrackLength);
            mt->SetBranchAddress("GdLsTrackLength",&muGdLsTrackLength);

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
            neut->SetBranchAddress("EventID",&neuEventID);
            neut->SetBranchAddress("InitTime",&neuInitTime);
            neut->SetBranchAddress("InitKineE",&neuInitKineE);
            neut->SetBranchAddress("InitLocalX",&neuInitLocalX);
            neut->SetBranchAddress("InitLocalY",&neuInitLocalY);
            neut->SetBranchAddress("InitLocalZ",&neuInitLocalZ);
            neut->SetBranchAddress("InitVolumeName",&neuInitVolumeName);
            neut->SetBranchAddress("CapVolumeName",&neuCapVolumeName);
            neut->SetBranchAddress("OriginVolumeNumber",&neuOriginVolumeNumber);

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
                if(muGdLsTrackLength==0) continue;
                //muIndex.insert(std::pair<int,int>(muEventID,u));
                adMuonNum++;
                //adMuonLength+=(muSstTrackLength+muOatTrackLength+muIatTrackLength+muMoTrackLength+muLsTrackLength+muGdLsTrackLength);
                adMuonLength+=muGdLsTrackLength;
            }

            for( int r=0 ; r<neutnum ; r++ )
            {
                neut->GetEntry(r);
                //if(muIndex.find(neuEventID)==muIndex.end()) continue;
                neuNumD[14]++;
                neuNumD[neuInitVolumeName]++;
                if( neuCapVolumeName==12 )
                {
                    neuNum++;
                    if(neuOriginVolumeNumber!=12) neuNumIn++;
                }
                if(neuOriginVolumeNumber==12 && neuCapVolumeName!=12) neuNumOut++;
            }

            for( int i=0 ; i<isotnum ; i++ )
            {
                isot->GetEntry(i);
                //if(muIndex.find(isoEventID)==muIndex.end()) continue;
                if( isoDecayVolume==12 )
                {
                    isoNum[isoZ][isoA]++;
                    if(isoOriginVolumeNumber!=12) isoNumIn[isoZ][isoA]++;
                }
                if(isoOriginVolumeNumber==12 && isoDecayVolume!=12) isoNumOut[isoZ][isoA]++;
            }

            f->Close();
        }

    }

    nameStr=Form("result_%s.txt",dataVer[j].c_str());
    cout<<"nameStr "<<nameStr<<endl;
    //print 
    cout<<"adMuonNum : "<<adMuonNum<<endl;
    cout<<"adMuonLength : "<<adMuonLength<<"   "<<adMuonLength/adMuonNum<<" per muon"<<endl;
    int neuNumFinal=neuNum+neuNumOut-neuNumIn;
    cout<<"neuNum  : "<<neuNumFinal<<"="<<neuNum<<"+"<<neuNumOut<<"("<<(double)neuNumOut/neuNum*100 <<"%)-"<<neuNumIn<<"("<<(double)neuNumIn/neuNum*100 <<"%)"<<endl;
    cout<<"neuNumFinal : "<<neuNumFinal<<"+-"<<sqrt(neuNumFinal)<<"   "<<(double)neuNumFinal/adMuonNum <<" per muon" <<"   neuYield : "<<neuNumFinal/adMuonLength/0.855*1.e5<<"e-05"<<endl;
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
            int isoNumFinal=isoNum[z][a]+isoNumOut[z][a]-isoNumIn[z][a];
            if(isoNumFinal==0) continue;
            if( isoNum[z][a]!=0 )
            {
                cout<<"    "<<isoName[z-1]<<a<<" : "<<isoNumFinal <<"="<<isoNum[z][a]<<"+"<<isoNumOut[z][a]<<"("<<(double)isoNumOut[z][a]/isoNum[z][a]*100 <<"%)-"<<isoNumIn[z][a]<<"("<<(double)isoNumIn[z][a]/isoNum[z][a]*100 <<"%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/0.855*1.e7<<"e-07"<<endl;
            } else
            {
                cout<<"    "<<isoName[z-1]<<a<<" : "<<isoNumFinal <<"="<<isoNum[z][a]<<"+"<<isoNumOut[z][a]<<"(100%)-"<<isoNumIn[z][a]<<"(0%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/0.855*1.e7<<"e-07"<<endl;
            }
        }
    }
    cout<<" "<<endl;

    ofstream outfile;
    
    outfile.open(nameStr.c_str());

    outfile<<"adMuonNum : "<<adMuonNum<<endl;
    outfile<<"adMuonLength : "<<adMuonLength<<"   "<<adMuonLength/adMuonNum<<" per muon"<<endl;
    outfile<<"neuNum  : "<<neuNumFinal<<"="<<neuNum<<"+"<<neuNumOut<<"("<<(double)neuNumOut/neuNum*100 <<"%)-"<<neuNumIn<<"("<<(double)neuNumIn/neuNum*100 <<"%)"<<endl;
    outfile<<"neuNumFinal : "<<neuNumFinal<<"+-"<<sqrt(neuNumFinal)<<"   "<<(double)neuNumFinal/adMuonNum <<" per muon" <<"   neuYield : "<<neuNumFinal/adMuonLength/0.855*1.e5<<"e-05"<<endl;
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
            int isoNumFinal=isoNum[z][a]+isoNumOut[z][a]-isoNumIn[z][a];
            if(isoNumFinal==0) continue;
            if( isoNum[z][a]!=0 )
            {
                outfile<<"    "<<z<<"/"<<a<<" : "<<isoNumFinal <<"="<<isoNum[z][a]<<"+"<<isoNumOut[z][a]<<"("<<(double)isoNumOut[z][a]/isoNum[z][a]*100 <<"%)-"<<isoNumIn[z][a]<<"("<<(double)isoNumIn[z][a]/isoNum[z][a]*100 <<"%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/0.855*1.e7<<"e-07"<<endl;
            } else
            {
                outfile<<"    "<<z<<"/"<<a<<" : "<<isoNumFinal <<"="<<isoNum[z][a]<<"+"<<isoNumOut[z][a]<<"(100%)-"<<isoNumIn[z][a]<<"(0%)"<<"   isoYield : "<<isoNum[z][a]/adMuonLength/0.855*1.e7<<"e-07"<<endl;
            }
        }
    }

    outfile<<" "<<endl;
    outfile.close();
    }
}
