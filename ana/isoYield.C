//#include  <iostream>
//#include  <TTree.h>
//#include  <TH1F.h>
//#include  <TCanvas.h>
//#include  <TFile.h>
//#include  <TChain.h>
//using namespace std;
//int main(int argc, char *argv[])
{
    /*
    TCanvas* c=new TCanvas("c","c",800,600);
    //TString dataPath="/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/data0/PART2/rootFile/1.root";
    TString dataPath="/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/data0/PART2/rootFile/.root";
    TChain* f_mu=new TChain("Muon");
    f_mu->Add(dataPath);
    //cout<<"Entries  : "<<f_mu->GetEntries()<<endl;
    f_mu->Draw("EventID>>h_mu","MoTrackLength>0");
    int ADMuonNum=h_mu->GetEntries();
    cout<<"ADMuonNum  : "<<ADMuonNum<<endl;
    //c->SaveAs("c.eps");

    TChain* f_iso=new TChain("Isotope");
    f_iso->Add(dataPath);
    //cout<<"Entries  : "<<f_iso->GetEntries()<<endl;
    f_iso->Draw("Z:A>>h_iso","DecayVolume>=8");
    int IsoNum;
    for( int z=0 ; z<250 ; z++ )
    {
        for( int a=0 ; a<250 ; a++ )
        {
            IsoNum=h_iso->GetBinContent(z,a);
            if( IsoNum>0 )
            {
                cout<<z<<"/"<<a<<" : "<<IsoNum<<endl;
            }
        }
        
    }
    
    TChain* f_neu=new TChain("Neutron");
    f_neu->Add(dataPath);
    f_neu->Draw("InitKineE>>h_neu(30000,0,0.3)","InitLocalY>-250&&InitLocalY<250&&InitLocalZ>-250&&InitLocalZ<250&&((InitLocalX>-550&&InitLocalX<-50)||(InitLocalX>50&&InitLocalX<550))");
    int NeuNum=f_neu->GetEntries();
    cout<<"NeuNum  : "<<NeuNum<<endl;
    */
    int rootNum=4027;
    int adMuonNum=0;
    double adMuonLength=0.;
    int neuNum=0;
    int isoNum[150][300]={0};
    

    //loop for counting
    for( int i=1 ; i<rootNum+1; i++ )
    {
        TString nameStr=Form("/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/FAR/data/whole/fluSim_%06d.root",i);
        if( i%100==0 )
        {
            std::cout<<"filename : "<<nameStr<<endl;
        } 
        TFile* f= new TFile(nameStr);
        if( f->IsZombie() )
        {
            std::cout<<"not exist "<<endl;
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
            neut->SetBranchAddress("EventID",&neuEventID);
            neut->SetBranchAddress("InitTime",&neuInitTime);
            neut->SetBranchAddress("InitKineE",&neuInitKineE);
            neut->SetBranchAddress("InitLocalX",&neuInitLocalX);
            neut->SetBranchAddress("InitLocalY",&neuInitLocalY);
            neut->SetBranchAddress("InitLocalZ",&neuInitLocalZ);

            TTree* isot=(TTree*)f->Get("Isotope");
            int isotnum=isot->GetEntries();
            int isoEventID;
            double isoDecayLocalX;
            double isoDecayLocalY;
            double isoDecayLocalZ;
            int isoZ;
            int isoA;
            isot->SetBranchAddress("EventID",&isoEventID);
            isot->SetBranchAddress("DecayLoaclX",&isoDecayLocalX);
            isot->SetBranchAddress("DecayLoaclY",&isoDecayLocalY);
            isot->SetBranchAddress("DecayLoaclZ",&isoDecayLocalZ);
            isot->SetBranchAddress("Z",&isoZ);
            isot->SetBranchAddress("A",&isoA);

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
                if(!(neuInitLocalY>-250&&neuInitLocalY<250&&neuInitLocalZ>-250&&neuInitLocalZ<250&&((neuInitLocalX>-550&&neuInitLocalX<-50)||(neuInitLocalX>50&&neuInitLocalX<550)))) continue;
                neuNum++;
            }

            for( int i=0 ; i<isotnum ; i++ )
            {
                isot->GetEntry(i);
                if(muIndex.find(isoEventID)==muIndex.end()) continue;
                if(!(isoDecayLocalY>-250&&isoDecayLocalY<250&&isoDecayLocalZ>-250&&isoDecayLocalZ<250&&((isoDecayLocalX>-550&&isoDecayLocalX<-50)||(isoDecayLocalX>50&&isoDecayLocalX<550)))) continue;
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
