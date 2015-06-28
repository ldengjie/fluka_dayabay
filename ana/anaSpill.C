{
    //0 neuInitKineE,1 neuInitLocalX,2 neuInitLocalY,3 neuInitLocalZ,4 neuInitLocalXCos,5 neuInitLocalYCos,6 neuInitLocalZCos,7 desMuInducedNeu,8 muInitLocalX,9 muInitLocalY,10 muInitLocalZ,11 muInitLocalXCos,12 muInitLocalYCos,13 muInitLocalZCos
    ifstream infile; 
    string infileName="../neutronGen.DYB";
    infile.open(infileName.c_str(),ios::in);
    int inLineNum=0;
    std::cout<<"get value "<<endl;
    double neuInf[300000][14]={0.};
    int inducedNeuNum=0;
    while(inLineNum<200000)
    {
        //cout<<inLineNum+1<<" ";
        for( int j=0 ; j<14 ; j++ )
        {
            infile>>neuInf[inLineNum][j];
            //cout<<" "<<neuInf[inLineNum][j];
        }
        if( neuInf[inLineNum][7] )
        {
            inducedNeuNum++;
        }
        //cout<<" "<<endl;
        inLineNum++;
    }
    infile.close();
    std::cout<<"done "<<endl;
    string nameStr;
    //for( int fi=001 ; fi<=1000 ; fi++ )
    for( int fi=001 ; fi<=2; fi++ )
    {
        TH1F* capDis=new TH1F("capDis","distance between neutron captured positon and muon track",41,40,450);//cm
        //nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/FAR/data/PART34/rootFile/fluSim_%06d.root",fi);
        nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/FAR/FAR%03d_sim.root",fi);
        //cout<<"nameStr  : "<<nameStr<<endl;
        int capNum=0;
        TFile* f= new TFile(nameStr.c_str());
        if( f->IsZombie() )
        {
            f->Close();
            delete f;
            continue;
        }
        TTree* neut= (TTree*)f->Get("Neutron");
        int neutnum=neut->GetEntries();
        Int_t neuEventID;
        double neuInitTime;
        double neuInitKineE;
        double neuInitLocalX;
        double neuInitLocalY;
        double neuInitLocalZ;
        double neuInitLocalXCos;
        double neuInitLocalYCos;
        double neuInitLocalZCos;
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
        neut->SetBranchAddress("InitLocalXCos",&neuInitLocalXCos);
        neut->SetBranchAddress("InitLocalYCos",&neuInitLocalYCos);
        neut->SetBranchAddress("InitLocalZCos",&neuInitLocalZCos);
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
        double NeuEFrac=0.;
        for( int ni=0 ; ni<neutnum ; ni++ )
        {
            neut->GetEntry(ni);
            if( ni==0 )
            {
                NeuEFrac=neuInitKineE;
                //cout<<" NeuEFrac  : "<<NeuEFrac <<endl;
                continue;
            }
    //0 neuInitKineE,1 neuInitLocalX,2 neuInitLocalY,3 neuInitLocalZ,4 neuInitLocalXCos,5 neuInitLocalYCos,6 neuInitLocalZCos,7 desMuInducedNeu,8 muInitLocalX,9 muInitLocalY,10 muInitLocalZ,11 muInitLocalXCos,12 muInitLocalYCos,13 muInitLocalZCos
            if(neuCapVolumeName==12)
            {
                capNum++;
                double disV=sqrt(
                        (neuInf[ni][12]*(neuCapLocalZ-neuInf[ni][10])-neuInf[ni][13]*(neuCapLocalY-neuInf[ni][9]))*(neuInf[ni][12]*(neuCapLocalZ-neuInf[ni][10])-neuInf[ni][13]*(neuCapLocalY-neuInf[ni][9]))+
                        (neuInf[ni][11]*(neuCapLocalZ-neuInf[ni][10])-neuInf[ni][13]*(neuCapLocalX-neuInf[ni][8]))*(neuInf[ni][11]*(neuCapLocalZ-neuInf[ni][10])-neuInf[ni][13]*(neuCapLocalX-neuInf[ni][8]))+
                        (neuInf[ni][11]*(neuCapLocalY-neuInf[ni][9])-neuInf[ni][12]*(neuCapLocalX-neuInf[ni][8]))*(neuInf[ni][11]*(neuCapLocalY-neuInf[ni][9])-neuInf[ni][12]*(neuCapLocalX-neuInf[ni][8])));
                //cout<<"neuCapLocalX  : "<<neuCapLocalX<<endl;
                //cout<<"neuCapLocalY  : "<<neuCapLocalY<<endl;
                //cout<<"neuCapLocalZ  : "<<neuCapLocalZ<<endl;
                //for( int nii=8 ; nii<=13 ; nii++ )
                //{
                //cout<<"neuInf[ni]  : "<<neuInf[ni][nii]<<endl;
                //}
                //cout<<"disV  : "<<disV<<endl;
                //
                //if( disV>0 )
                //{
                //cout<<"disV  : "<<disV<<endl;
                //}
                capDis->Fill(disV);
            }
        }
        //capDis->Draw();
        capDis->Fit("expo","q");
        TF1 *tf=capDis->GetFunction("expo");
        double par0=tf->GetParameter(0);
        double par1=tf->GetParameter(1);
        cout<< " "<<NeuEFrac<<" ~ "<<par1<<" ("<<fi<<")"<<" Xi_spill  ~ "<<capNum<<"/"<<inducedNeuNum<<" "<<(double)capNum/inducedNeuNum<<endl;
    }
}
