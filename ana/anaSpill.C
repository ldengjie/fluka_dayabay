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
    for( int fi=134 ; fi<=134 ; fi++ )
    //for( int fi=001 ; fi<=2; fi++ )
    {
        nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/data/PART34/rootFile/fluSim_%06d.root",fi);
        //nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/dayabay%03d_sim.root",fi);
        //cout<<"nameStr  : "<<nameStr<<endl;
        int capNum=0;
        TFile* f= new TFile(nameStr.c_str());
        if( f->IsZombie() )
        {
            f->Close();
            delete f;
            continue;
        }
        TH1F* capDis=new TH1F("capDis","distance between neutron captured positon and muon track",41,40,450);//cm
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
                capDis->Fill(disV);
            }
        }
        if(abs( NeuEFrac -1)<0.001)
        {
            double xl[1000]={0.};
            double yl[1000]={0.};
            double xh[1000]={0.};
            double yh[1000]={0.};
            for( int ci=1 ; ci<=41 ; ci++ )
            {
               xl[ci-1]=capDis->GetBinLowEdge(ci)-10;
               yl[ci-1]=capDis->GetBinContent(ci)-sqrt(capDis->GetBinContent(ci));
               xh[ci-1]=capDis->GetBinLowEdge(ci+1)+10;
               yh[ci-1]=capDis->GetBinContent(ci)+sqrt(capDis->GetBinContent(ci));
            }
            TGraph* gl=new TGraph(41,xl,yl);
            TGraph* gh=new TGraph(41,xh,yh);
            gl->Fit("expo","q");
            gh->Fit("expo","q");
            TF1* fl=gl->GetFunction("expo");
            TF1* fh=gh->GetFunction("expo");
            double p1l=fl->GetParameter(1);
            double p1h=fh->GetParameter(1);
            cout<<"Find  "<<"p1l~p1h  : "<<p1l<<"~"<<p1h<<endl;
            //delete fl;
            //delete fh;
            //delete gl;
            //delete gh;
            
        }else
        {
            cout<<"+ NeuEFrac  : "<<NeuEFrac<<endl;
        }
        capDis->Draw();
        capDis->Fit("expo","q");
        TF1 *tf=capDis->GetFunction("expo");
        double par0=tf->GetParameter(0);
        double par1=tf->GetParameter(1);
        cout<< " "<<NeuEFrac<<" ~ "<<par1<<" ("<<fi<<")"<<" Xi_spill  ~ "<<capNum<<"/"<<inducedNeuNum<<" "<<(double)capNum/inducedNeuNum<<endl;
        //f->Close();
        //delete tf;
        //delete capDis;
        //delete neut;
        //delete f;
    }
}
