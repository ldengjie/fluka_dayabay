{
    int rootNum=50;
    int adMuonNum=0;
    double adMuonLength=0.;
    int neuNum=0;
    int isoNum[150][300]={0};
    

    //loop for counting
    for( int i=1 ; i<rootNum+1; i++ )
    {
        TString nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/data/whole/fluSim_%06d.root",i);
        //if( i%100==0 )
        //{
            std::cout<<"filename : "<<nameStr<<endl;
            //} 
        TFile* f= new TFile(nameStr);
        if( f->IsZombie() )
        {
            //std::cout<<"not exist "<<endl;
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
            neut->SetBranchAddress("EventID",&neuEventID);
            neut->SetBranchAddress("InitTime",&neuInitTime);
            neut->SetBranchAddress("InitKineE",&neuInitKineE);
            neut->SetBranchAddress("InitLocalX",&neuInitLocalX);
            neut->SetBranchAddress("InitLocalY",&neuInitLocalY);
            neut->SetBranchAddress("InitLocalZ",&neuInitLocalZ);
            neut->SetBranchAddress("InitVolumeName",&neuInitVolumeName);

            TTree* isot=(TTree*)f->Get("Isotope");
            int isotnum=isot->GetEntries();
            int isoEventID;
            double isoDecayLocalX;
            double isoDecayLocalY;
            double isoDecayLocalZ;
            int isoZ;
            int isoA;
            int isoInitVolume;
            isot->SetBranchAddress("EventID",&isoEventID);
            isot->SetBranchAddress("DecayLocalX",&isoDecayLocalX);
            isot->SetBranchAddress("DecayLocalY",&isoDecayLocalY);
            isot->SetBranchAddress("DecayLocalZ",&isoDecayLocalZ);
            isot->SetBranchAddress("Z",&isoZ);
            isot->SetBranchAddress("A",&isoA);
            isot->SetBranchAddress("InitVolume",&isoInitVolume);

            map<int,int> muIndex;
            for( int u=0 ; u<mtnum ; u++ )
            {
                mt->GetEntry(u);
                if(muMoTrackLength==0) continue;
                muIndex.insert(std::pair<int,int>(muEventID,u));
                adMuonNum++;
                adMuonLength+=(muMoTrackLength+muLsTrackLength+muGdLsTrackLength);
            }

            for( int r=0 ; r<neutnum ; r++ )
            {
                neut->GetEntry(r);
                if(muIndex.find(neuEventID)==muIndex.end()) continue;
                if(neuInitVolumeName<7) continue;
                neuNum++;
            }

            for( int i=0 ; i<isotnum ; i++ )
            {
                isot->GetEntry(i);
                if(muIndex.find(isoEventID)==muIndex.end()) continue;
                if(isoInitVolume<7) continue;
                isoNum[isoZ][isoA]++;
            }

            f->Close();
        }

    }

    //print 
    cout<<"adMuonNum : "<<adMuonNum<<endl;
    cout<<"adMuonLength : "<<adMuonLength<<endl;
    cout<<" "<<endl;
    cout<<"neuNum : "<<neuNum<<"   neuYield : "<<neuNum/adMuonLength/0.855<<endl;
    cout<<" "<<endl;
    cout<<"isoNum : "<<endl;
    for( int z=0 ; z<150 ; z++ )
    {
        for( int a=0 ; a<300 ; a++ )
        {
            if(isoNum[z][a]==0) continue;
            cout<<"    "<<z<<"/"<<a<<" : "<<isoNum[z][a]<<"   isoYield : "<<isoNum[z][a]/adMuonLength/0.855<<endl;
        }
    }
    cout<<" "<<endl;

    ofstream outfile;
    outfile.open("result.txt");

    outfile<<"adMuonNum : "<<adMuonNum<<endl;
    outfile<<"adMuonLength : "<<adMuonLength<<endl;
    outfile<<" "<<endl;
    outfile<<"neuNum : "<<neuNum<<"   neuYield : "<<neuNum/adMuonLength/0.855<<endl;
    outfile<<" "<<endl;
    outfile<<"isoNum : "<<endl;
    for( int z=0 ; z<150 ; z++ )
    {
        for( int a=0 ; a<300 ; a++ )
        {
            if(isoNum[z][a]==0) continue;
            outfile<<"    "<<z<<"/"<<a<<" : "<<isoNum[z][a]<<"   isoYield : "<<isoNum[z][a]/adMuonLength/0.855<<endl;
        }
    }
    outfile<<" "<<endl;
    outfile.close();
}
