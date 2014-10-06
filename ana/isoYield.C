{
    int rootNum=6;
    string dataVer[4]={"PART5","PART6","PART9","PART10"};
    string nameStr;
    string isoName[7]={"H","He","Li","Be","B","C","N"};
    for( int j=0 ; j<4 ; j++ )
    {
    int adMuonNum=0;
    double adMuonLength=0.;
    int neuNum=0;
    int neuNumD[15]={0};
    int isoNum[150][300]={0};
    

    //loop for counting
    for( int i=1 ; i<rootNum+1; i++ )
    {
        nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/data/%s/fluSim_%06d.root",dataVer[j].c_str(),i);
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
            neut->SetBranchAddress("EventID",&neuEventID);
            neut->SetBranchAddress("InitTime",&neuInitTime);
            neut->SetBranchAddress("InitKineE",&neuInitKineE);
            neut->SetBranchAddress("InitLocalX",&neuInitLocalX);
            neut->SetBranchAddress("InitLocalY",&neuInitLocalY);
            neut->SetBranchAddress("InitLocalZ",&neuInitLocalZ);
            neut->SetBranchAddress("InitVolumeName",&neuInitVolumeName);
            neut->SetBranchAddress("CapVolumeName",&neuCapVolumeName);

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
            isot->SetBranchAddress("EventID",&isoEventID);
            isot->SetBranchAddress("DecayLocalX",&isoDecayLocalX);
            isot->SetBranchAddress("DecayLocalY",&isoDecayLocalY);
            isot->SetBranchAddress("DecayLocalZ",&isoDecayLocalZ);
            isot->SetBranchAddress("Z",&isoZ);
            isot->SetBranchAddress("A",&isoA);
            isot->SetBranchAddress("InitVolume",&isoInitVolume);
            isot->SetBranchAddress("DecayVolume",&isoDecayVolume);

            map<int,int> muIndex;
            for( int u=0 ; u<mtnum ; u++ )
            {
                mt->GetEntry(u);
                //if(muMoTrackLength==0) continue;
                //if(muLsTrackLength==0) continue;
                if(muSstTrackLength==0) continue;
                muIndex.insert(std::pair<int,int>(muEventID,u));
                adMuonNum++;
                //adMuonLength+=(muMoTrackLength+muLsTrackLength+muGdLsTrackLength);
                //adMuonLength+=(muLsTrackLength+muGdLsTrackLength);
                adMuonLength+=(muSstTrackLength+muOatTrackLength+muIatTrackLength+muMoTrackLength+muLsTrackLength+muGdLsTrackLength);
            }

            for( int r=0 ; r<neutnum ; r++ )
            {
                neut->GetEntry(r);
                //if(muIndex.find(neuEventID)==muIndex.end()) continue;
                //if(neuInitVolumeName<7) continue;
                //neuNum++;
                neuNumD[14]++;
                neuNumD[neuInitVolumeName]++;
                //if(neuInitVolumeName==8 || neuInitVolumeName==10 ||neuInitVolumeName==12) neuNum++;
                //if(neuInitVolumeName==10 ||neuInitVolumeName==12) neuNum++;
                //if(neuInitVolumeName>=7) neuNum++;
                if(neuCapVolumeName>=7) neuNum++;
            }

            for( int i=0 ; i<isotnum ; i++ )
            {
                isot->GetEntry(i);
                if(muIndex.find(isoEventID)==muIndex.end()) continue;
                //if(isoInitVolume<7) continue;
                //isoNum[isoZ][isoA]++;
                //if(isoInitVolume==8 || isoInitVolume==10 ||isoInitVolume==12)isoNum[isoZ][isoA]++;
                //if(isoInitVolume==10 ||isoInitVolume==12)isoNum[isoZ][isoA]++;
                //if(isoInitVolume>=7)isoNum[isoZ][isoA]++;
                if(isoDecayVolume>=7)isoNum[isoZ][isoA]++;
            }

            f->Close();
        }

    }

    nameStr=Form("result_%s.txt",dataVer[j].c_str());
    cout<<"nameStr "<<nameStr<<endl;
    //print 
    cout<<"adMuonNum : "<<adMuonNum<<endl;
    cout<<"adMuonLength : "<<adMuonLength<<"   "<<adMuonLength/adMuonNum<<" per muon"<<endl;
    cout<<"neuNum : "<<neuNum<<"+-"<<sqrt(neuNum)<<"   "<<(double)neuNum/adMuonNum <<" per muon" <<"   neuYield : "<<neuNum/adMuonLength/0.855*1.e5<<"e-05"<<endl;
    for( int i=0 ; i<15 ; i++ )
    {
        if(neuNumD[i]!=0) cout<<"    "<<i<<" : "<<neuNumD[i]<<endl;
    }
    
    cout<<"isoNum : "<<endl;
    for( int z=1 ; z<=7 ; z++ )
    {
        for( int a=1 ; a<300 ; a++ )
        {
            if(isoNum[z][a]==0) continue;
            cout<<"    "<<isoName[z-1]<<a<<" : "<<isoNum[z][a]<<"   isoYield : "<<isoNum[z][a]/adMuonLength/0.855*1.e7<<"e-07"<<endl;
        }
    }
    cout<<" "<<endl;

    ofstream outfile;
    
    outfile.open(nameStr.c_str());

    outfile<<"adMuonNum : "<<adMuonNum<<endl;
    outfile<<"adMuonLength : "<<adMuonLength<<"   "<<adMuonLength/adMuonNum<<" per muon"<<endl;
    outfile<<" "<<endl;
    outfile<<"neuNum : "<<neuNum<<"+-"<<sqrt(neuNum)<<"   "<<(double)neuNum/adMuonNum <<" per muon" <<"   neuYield : "<<neuNum/adMuonLength/0.855*1.e5<<"e-05"<<endl;
    for( int i=0 ; i<15 ; i++ )
    {
        if(neuNumD[i]!=0) outfile<<"    "<<i<<" : "<<neuNumD[i]<<endl;
    }
    outfile<<" "<<endl;
    outfile<<"isoNum : "<<endl;
    for( int z=1 ; z<150 ; z++ )
    {
        for( int a=1 ; a<300 ; a++ )
        {
            if(isoNum[z][a]==0) continue;
            if( z<8 )
            {
            outfile<<"    "<<isoName[z-1]<<a<<" : "<<isoNum[z][a]<<"   isoYield : "<<isoNum[z][a]/adMuonLength/0.855*1.e7<<"e-07"<<endl;
            } else
            {
            outfile<<"    "<<z<<"/"<<a<<" : "<<isoNum[z][a]<<"   isoYield : "<<isoNum[z][a]/adMuonLength/0.855*1.e7<<"e-07"<<endl;
            }
        }
    }
    outfile<<" "<<endl;
    outfile.close();
    }
}
