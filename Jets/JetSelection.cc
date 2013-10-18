#include "JetSelection.h"

JJ::JJ() { }
JJ::~JJ() { }

void JJ::JetSelection (std::vector<Int_t> Jet_Id_loose, std::vector<Double_t> Jet_Eta, std::vector<Double_t> Jet_Phi, std::vector<Double_t> Jet_Pt, std::vector<Double_t> Jet_E, std::vector<Double_t> Jet_neutralEmEnergyFraction, std::vector<Double_t> Jet_neutralHadronEnergyFraction, std::vector<Double_t> Jet_chargedEmEnergyFraction, std::vector<Double_t> Jet_chargedHadronEnergyFraction, std::vector<Int_t> Jet_chargedMultiplicity, std::vector<Int_t> Jet_NConstituents, std::vector<Double_t> Jet_BTag, std::vector<Jet>& jetColl) {

  for (UInt_t ijet = 0; ijet < Jet_Pt.size(); ++ijet)
  {
    if (Jet_Pt[ijet] >= pt_cut_min && Jet_Pt[ijet] < pt_cut_max && 
        fabs(Jet_Eta[ijet]) < eta_cut
        //&& Jet_Id_loose[ijet]
        && Jet_neutralHadronEnergyFraction[ijet] < 0.99
        && Jet_neutralEmEnergyFraction[ijet] < 0.99
        && Jet_NConstituents[ijet] > 1
        && (fabs(Jet_Eta[ijet]) > 2.4 || (Jet_chargedHadronEnergyFraction[ijet] > 0. && Jet_chargedMultiplicity[ijet] > 0. && Jet_chargedEmEnergyFraction[ijet] < 0.99))
      )
    {
      //std::cout << "                             PASS\n";
      vJet.SetPtEtaPhiE(Jet_Pt[ijet], Jet_Eta[ijet], Jet_Phi[ijet], Jet_E[ijet]);
      jetColl.push_back( Jet(0,vJet, Jet_Eta[ijet], Jet_BTag[ijet], ijet) );
    }
  }
  std::sort( jetColl.begin(), jetColl.end(), JetPTSorter );
}

/***********************************************************
*
* Function: JetSelectionLeptonVeto
*
************************************************************/
void JJ::JetSelectionLeptonVeto(std::vector<Int_t> Jet_Id_loose, std::vector<Double_t> Jet_Eta, std::vector<Double_t> Jet_Phi, std::vector<Double_t> Jet_Pt, std::vector<Double_t> Jet_E, std::vector<Double_t> Jet_neutralEmEnergyFraction, std::vector<Double_t> Jet_neutralHadronEnergyFraction, std::vector<Double_t> Jet_chargedEmEnergyFraction, std::vector<Double_t> Jet_chargedHadronEnergyFraction, std::vector<Int_t> Jet_chargedMultiplicity, std::vector<Int_t> Jet_NConstituents, std::vector<Double_t> Jet_BTag, std::vector<Double_t>& Jet_Un_Minus,std::vector<Lepton>& leptonColl1, std::vector<Lepton>& leptonColl2, std::vector<Jet>& jetColl) {
  std::vector<Jet> pre_jetColl;

  for (UInt_t ijet = 0; ijet < Jet_Pt.size(); ijet++)
  {
    TLorentzVector jp; jp.SetPtEtaPhiE(Jet_Pt[ijet], Jet_Eta[ijet], Jet_Phi[ijet], Jet_E[ijet]);
    
    if(sys[0]) jp = jp-jp*Jet_Un_Minus[ijet];
    else if(sys[1]) jp = jp-jp*Jet_Un_Minus[ijet]*1.1;
    
    if (jp.Perp() >= pt_cut_min && jp.Perp() < pt_cut_max
          && fabs(Jet_Eta[ijet]) < eta_cut
          //&& Jet_Id_loose[ijet]
          && Jet_neutralHadronEnergyFraction[ijet] < 0.99
          && Jet_neutralEmEnergyFraction[ijet] < 0.99
          && Jet_NConstituents[ijet] > 1
          && (fabs(Jet_Eta[ijet]) > 2.4 || (Jet_chargedHadronEnergyFraction[ijet] > 0.
          && Jet_chargedMultiplicity[ijet] > 0.
          &&Jet_chargedEmEnergyFraction[ijet] < 0.99))
        )
    {
      //vJet.SetPtEtaPhiE(Jet_Pt[ijet], Jet_Eta[ijet], Jet_Phi[ijet], Jet_E[ijet]);
      Double_t jetEta = jp.Eta();
      pre_jetColl.push_back( Jet(0,jp, jetEta, Jet_BTag[ijet], ijet));
    }
  }

  for (UInt_t ijet = 0; ijet < pre_jetColl.size(); ijet++)
  {
    jetIsOK = true;
    
    for (UInt_t ilep = 0; ilep < leptonColl1.size(); ilep++)
    {
      if (leptonColl1[ilep].leptonType()==Lepton::Muon)
      {
        if (leptonColl1[ilep].lorentzVec().DeltaR( pre_jetColl[ijet].lorentzVec()) < 0.4)
        {
          jetIsOK = false;
          ilep = leptonColl1.size();
        }
      }
    }
    
    for (UInt_t ilep = 0; ilep < leptonColl2.size(); ilep++)
    {
      if (leptonColl2[ilep].leptonType()==Lepton::Electron)
      {
        if (leptonColl2[ilep].lorentzVec().DeltaR( pre_jetColl[ijet].lorentzVec()) < 0.4 )
        {
          jetIsOK = false;
          ilep = leptonColl2.size();
        }
      }
    }
    
    // b-tag, CSV discriminators defined:
    // CombinedSecondaryVertex:
    // 0 - no btag
    // 1 - loose	 CSVL	> 0.244
    // 2 - medium	 CSVM	> 0.679
    // 3 - tight	 CSVT	> 0.898

    if (pre_jetColl[ijet].btag_disc() > 0.898)
    {
      pre_jetColl[ijet].set_btagged(3);
    }
    else if (pre_jetColl[ijet].btag_disc() > 0.679)
    {
      pre_jetColl[ijet].set_btagged(2);
    }
    else if (pre_jetColl[ijet].btag_disc() > 0.244)
    {
      pre_jetColl[ijet].set_btagged(1);
    }
    else
    {
      pre_jetColl[ijet].set_btagged(0);
    }
    
    if (jetIsOK)
    {
      jetColl.push_back(pre_jetColl[ijet]);
    }
  }
  std::sort( jetColl.begin(), jetColl.end(), JetPTSorter );
}

void JJ::SetPt(Double_t minPt)
{
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  pt_cut_max=10000.0;
}

void JJ::SetPt(Double_t minPt, Double_t maxPt)
{
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  maxPt ? pt_cut_max=maxPt : pt_cut_max=10000.0;
}

void JJ::SetEta(Double_t Eta)
{
  Eta ? eta_cut=Eta : eta_cut=3.0;
}
