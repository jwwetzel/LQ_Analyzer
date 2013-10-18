#ifndef Jet_h
#define Jet_h

#include "TLorentzVector.h"

class Jet {
  public:
    Jet(int btagged00, TLorentzVector& lorentzVec00, double& eta00, double& btag_disc00, unsigned int jetIndex00)
      : btagged_(btagged00), lorentzVec_(lorentzVec00), eta_(eta00), btag_disc_(btag_disc00), jetIndex_(jetIndex00) {};

    ~Jet() {}

    // BTagging Jets with CSV L,M,T.
    // 0 = no tag. 
    // 1 = Loose tag.
    // 2 = Medium tag.
    // 3 = Tight tag.
    void set_btagged(int btagged) { btagged_ = btagged; }
  
    int getBTag(){ return btagged_;}

    TLorentzVector& lorentzVec() { return lorentzVec_; }
    double eta() {return eta_; }
    unsigned int ijet() { return jetIndex_; }
    double btag_disc() { return btag_disc_; }


  private:
    int btagged_;
    TLorentzVector lorentzVec_;
    double eta_;
    double btag_disc_;
    unsigned int jetIndex_;
}; 

bool JetPTSorter(Jet jet1, Jet jet2) {
  return jet1.lorentzVec().Pt() > jet2.lorentzVec().Pt();
}

#endif
