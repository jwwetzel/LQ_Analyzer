#include "SignalPlots.h"

SignalPlots::SignalPlots(TString name) {
  h_jjmass =         new TH1F("h_dijetsmass_"    + name,"Invariant mass of the two leading jets",100,0,1000);
  h_llmass =         new TH1F("h_llmass_"        + name,"Invariant mass of the two leading muons",100,0,1000);
  h_l1jjmass =       new TH1F("h_l1jjmass_"      + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
  h_l2jjmass =       new TH1F("h_l2jjmass_"      + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
  h_lljjmass =       new TH1F("h_lljjmass_"      + name,"Invariant mass of the four particles",200,0,2000);
  h_WandNmass =      new TH2F("h_WandNmass_"     + name,"Invariant mass of the W and the N",200,0,2000,200,0,2000);
  h_leadingMuonPt =  new TH1F("h_leadingMuonPt_" + name,"leading muon pt",60,0,300);
  h_secondMuonPt =   new TH1F("h_secondMuonPt_"  + name,"secondary muon pt",60,0,300);
  h_leadingJetPt =   new TH1F("h_leadingJetPt_"  + name,"leading jet pt",60,0,300);
  h_secondJetPt =    new TH1F("h_secondJetPt_"   + name,"secondary jet pt",60,0,300);
  h_leadingMuonIso = new TH1F("h_leadingMuonIso_"+ name,"leading muon relIso",40,0,0.4);
  h_secondMuonIso =  new TH1F("h_secondMuonIso_" + name,"secondary muon relIso",40,0,0.4);
  h_MET =            new TH1F("h_MET_"           + name,"Missing Et",50,0.0,500.0);
  h_paircharge =     new TH1F("h_paircharge_"    + name,"Charge of the muon pair",5,-2,3);
  h_muonseta =       new TH1F("h_muonseta_"      + name,"#eta distribution of the two muons",50,-3,3);
  h_jetseta =        new TH1F("h_jetseta_"       + name,"#eta distribution of the two jets",50,-3,3);
  h_bTag =           new TH1F("h_bTag_"          + name,"bTag discrimant",100,-2,3);
  h_cosTheta1 =      new TH1F("h_cosTheta1_"     + name,"cos#theta first muon",100,-1,1);
  h_cosTheta2 =      new TH1F("h_cosTheta2_"     + name,"cos#theta second muon",100,-1,1);
}

SignalPlots::~SignalPlots() {
  delete h_jjmass;
  delete h_llmass;
  delete h_l1jjmass;
  delete h_l2jjmass;
  delete h_lljjmass;
  delete h_WandNmass;
  delete h_leadingMuonPt;
  delete h_secondMuonPt;
  delete h_leadingJetPt;
  delete h_secondJetPt;
  delete h_leadingMuonIso;
  delete h_secondMuonIso;
  delete h_MET;
  delete h_paircharge;
  delete h_muonseta;
  delete h_jetseta;
  delete h_bTag;
  delete h_cosTheta1;
  delete h_cosTheta2;
}

void SignalPlots::Fill(Double_t MET, std::vector<Lepton>& muons, std::vector<Jet>& jets, Double_t weight, Bool_t ptok, Bool_t ssok) {
  dijetmass_tmp=dijetmass=0;
  UInt_t m,n;
  for(UInt_t i=0; i<muons.size()-1; i++)
    for(UInt_t j=i+1; j<muons.size(); j++) {
      if (muons[i].charge()*muons[j].charge()>0 || ssok)
	if (muons[i].lorentzVec().Pt()>=20 || ptok) {

          h_MET->Fill(MET, weight);
	  m=0; n=1;
	  h_jjmass->Fill( (jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
          h_llmass->Fill( (muons[i].lorentzVec()+muons[j].lorentzVec()).M(),weight);
	  h_l1jjmass->Fill( (muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	  h_l2jjmass->Fill( (muons[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
/*
          cout << "muon px " << muons[j].lorentzVec().Px() << " py " << muons[j].lorentzVec().Py() << " pz " << muons[j].lorentzVec().Pz() << " E " << muons[j].lorentzVec().Energy() << endl;
cout << "jet1 px " << jets[m].lorentzVec().Px() << " py " << jets[m].lorentzVec().Py() << " pz " << jets[m].lorentzVec().Pz() << " E " << jets[m].lorentzVec().Energy() << endl;
cout << "jet2 px " << jets[n].lorentzVec().Px() << " py " << jets[n].lorentzVec().Py() << " pz " << jets[n].lorentzVec().Pz() << " E " << jets[n].lorentzVec().Energy() << endl;
*/
	  h_lljjmass->Fill( (muons[i].lorentzVec()+muons[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	  h_WandNmass->Fill( (muons[i].lorentzVec()+muons[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M() , (muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	  h_leadingMuonPt->Fill( muons[i].lorentzVec().Pt(),weight);
	  h_secondMuonPt->Fill( muons[j].lorentzVec().Pt(),weight);
	  h_leadingJetPt->Fill( jets[m].lorentzVec().Pt(),weight);
	  h_secondJetPt->Fill( jets[n].lorentzVec().Pt(),weight);
	  h_leadingMuonIso->Fill( muons[i].relIso(),weight);
	  h_secondMuonIso->Fill( muons[j].relIso(),weight);
          h_paircharge->Fill(muons[i].charge(),weight);
          h_muonseta->Fill(muons[i].eta(),weight);
          h_muonseta->Fill(muons[j].eta(),weight);
          h_jetseta->Fill(jets[m].eta(),weight);
          h_jetseta->Fill(jets[n].eta(),weight);
          h_bTag->Fill(jets[m].btag_disc(),weight);
          h_bTag->Fill(jets[n].btag_disc(),weight);
          h_cosTheta1->Fill(cos(muons[i].lorentzVec().Theta()),weight);
          h_cosTheta2->Fill(cos(muons[j].lorentzVec().Theta()),weight);
	}
   }
}

void SignalPlots::Fill(Double_t MET, std::vector<Lepton>& muons, std::vector<Lepton>& muonsloose, std::vector<Jet>& jets, Double_t weight, Bool_t ptok, Bool_t ssok) {
  dijetmass_tmp=dijetmass=0;
  UInt_t m,n;
  for(UInt_t i=0; i<muons.size(); i++)
    for(UInt_t j=0; j<muonsloose.size(); j++) {
      if (muons[i].charge()*muonsloose[j].charge()>0 || ssok)
	if (muons[i].lorentzVec().Pt()>=20 || muonsloose[j].lorentzVec().Pt()>=20 || ptok) {
	  if (muons[i].lorentzVec().Pt()>=muonsloose[j].lorentzVec().Pt()) {
	    
            m=0; n=1;
	    h_MET->Fill(MET, weight);
	    h_jjmass->Fill( (jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	    h_llmass->Fill( (muons[i].lorentzVec()+muonsloose[j].lorentzVec()).M(),weight);
	    h_l1jjmass->Fill( (muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	    h_l2jjmass->Fill( (muonsloose[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	    h_lljjmass->Fill( (muons[i].lorentzVec()+muonsloose[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	    h_WandNmass->Fill( (muons[i].lorentzVec()+muonsloose[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M() , (muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	    h_leadingMuonPt->Fill( muons[i].lorentzVec().Pt(),weight);
	    h_secondMuonPt->Fill( muonsloose[j].lorentzVec().Pt(),weight);
	    h_leadingJetPt->Fill( jets[m].lorentzVec().Pt(),weight);
	    h_secondJetPt->Fill( jets[n].lorentzVec().Pt(),weight);
	    h_leadingMuonIso->Fill( muons[i].relIso(),weight);
	    h_secondMuonIso->Fill( muonsloose[j].relIso(),weight);
	    h_paircharge->Fill(muons[i].charge(),weight);
	    h_muonseta->Fill(muons[i].eta(),weight);
	    h_muonseta->Fill(muons[j].eta(),weight);
	    h_jetseta->Fill(jets[m].eta(),weight);
	    h_jetseta->Fill(jets[n].eta(),weight);
	    h_bTag->Fill(jets[m].btag_disc(),weight);
	    h_bTag->Fill(jets[n].btag_disc(),weight);
	    h_cosTheta1->Fill(cos(muons[i].lorentzVec().Theta()),weight);
	    h_cosTheta2->Fill(cos(muons[j].lorentzVec().Theta()),weight);
	  }
	  else {
	    
            m=0; n=1;	      
	    h_MET->Fill(MET, weight);
	    h_jjmass->Fill( (jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	    h_llmass->Fill( (muonsloose[j].lorentzVec()+muons[i].lorentzVec()).M(),weight);
	    h_l1jjmass->Fill( (muonsloose[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	    h_l2jjmass->Fill( (muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	    h_lljjmass->Fill( (muonsloose[j].lorentzVec()+muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	    h_WandNmass->Fill( (muonsloose[j].lorentzVec()+muons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M() , (muonsloose[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
	    h_leadingMuonPt->Fill( muonsloose[j].lorentzVec().Pt(),weight);
	    h_secondMuonPt->Fill( muons[i].lorentzVec().Pt(),weight);
	    h_leadingJetPt->Fill( jets[m].lorentzVec().Pt(),weight);
	    h_secondJetPt->Fill( jets[n].lorentzVec().Pt(),weight);
	    h_leadingMuonIso->Fill( muonsloose[j].relIso(),weight);
	    h_secondMuonIso->Fill( muons[i].relIso(),weight);
	    h_paircharge->Fill(muons[i].charge(),weight);
	    h_muonseta->Fill(muons[i].eta(),weight);
	    h_muonseta->Fill(muons[j].eta(),weight);
	    h_jetseta->Fill(jets[m].eta(),weight);
	    h_jetseta->Fill(jets[n].eta(),weight);
	    h_bTag->Fill(jets[m].btag_disc(),weight);
	    h_bTag->Fill(jets[n].btag_disc(),weight);
	    h_cosTheta1->Fill(cos(muons[i].lorentzVec().Theta()),weight);
	    h_cosTheta2->Fill(cos(muons[j].lorentzVec().Theta()),weight); 
	  }
	}
    }
}

void SignalPlots::Write() {
  h_jjmass->Write();
  h_llmass->Write();
  h_l1jjmass->Write();
  h_l2jjmass->Write();
  h_lljjmass->Write();
  h_WandNmass->Write();
  h_leadingMuonPt->Write();
  h_secondMuonPt->Write();
  h_leadingJetPt->Write();
  h_secondJetPt->Write();
  h_leadingMuonIso->Write();
  h_secondMuonIso->Write();
  h_MET->Write();
  h_paircharge->Write();
  h_muonseta->Write();
  h_jetseta->Write();
  h_bTag->Write();
  h_cosTheta1->Write();
  h_cosTheta2->Write();
}

