#ifndef Analyzer_h
#define Analyzer_h

#include <set>
#include <string>
#include "../SupportingFiles/Data.h"
#include "../Electrons/ElectronSelection.h"
#include "../Muons/MuonSelection.h"
#include "../Jets/JetSelection.h"
#include "../GenParticles/GenSelection.h"
#include "../SupportingFiles/SelectionFunctions.h"
#include "../SupportingFiles/OtherFunctions.h"
#include "../Plots/ElectronPlots.h"
#include "../Plots/MuonPlots.h"
#include "../Plots/SignalPlots.h"
#include "../SupportingFiles/Reweight.cc"

class Analyzer : public Data {

  static const Bool_t debug = false; 
  static const Double_t integratedlumi = 10841.661;
  static const Double_t Mass_Z = 91.1876;
  static const Double_t Mass_W = 80.398;
  static const Double_t trigeff = 0.94;
  static const Double_t mu1scale = 0.927;
  static const Double_t mu2scale = 0.992;

  //  Double_t ****doubleFake; Double_t **singleFake; Double_t ****prova;
  //  Double_t finalbkg1, finalbkgerror1, finalbkg2, finalbkgerror2, jets2mass, triggerweight, realsingle, realsingleerror, realdouble, realtotal, doubletosingle, errdoubletosingle;
  Int_t tempCharge, index;
  Double_t Wcand_tmp, Wcand;

  TLorentzVector Msis;
  TLorentzVector Mdau;
  TLorentzVector Q1;
  TLorentzVector Q2;
  TLorentzVector NR;

  //  Bool_t VETO, SINGLEFAKE, DOUBLEFAKE;

  ReweightPU *reweightPU;
  TH1F *h_nvtx_norw, *h_nvtx_rw;

 public:
 
  UInt_t numberVertices;
  TString completename;
  //  Char_t* completename;

  TDirectory *Dir;
  TH1F *h_nVertex[4];//MC, Reco, MC rw, reco rw
  TH1F *h_PUweight;

  TH1F *h_MuDxy[3];
  TH1F *h_MuDz[3];
  TH1F *h_MuD0[3];
  TH1F *h_MuPt[9];
  TH1F *h_MuEta[3];
  TH1F *h_MuPhi[3];
  TH1F *h_MuNum[3];
  TH1F *h_MuTkHits[3];
  TH1F *h_MuSAHits[3];
  TH1F *h_MuEcal[3];
  TH1F *h_MuHcal[3];
  TH1F *h_MuTrk[3];
  TH1F *h_MuRel[3];
  TH1F *h_MuEff[3];
  TH1F *h_MuRelIso[9];

  TH1F* h_JetPt[5];	  
  TH1F* h_JetEta;	  
  TH1F* h_JetPhi;	  
  TH1F* h_JetNum[2];	  
  TH1F* h_JetUncert[2];
  TH1F* h_JetMatch[2];
  TH1F* h_JetMatchDR[2];
  TH1F* h_JetBTag;
				  
  TH1F* h_dRjmu[2];	  
  TH1F* h_Mmumu;	  
  TH1F* h_Mjj[3];		  
  TH1F* h_Mjjmu[6];	  
  TH1F* h_Mjjmumu[3];	  
  TH1F* h_dEtajjMu[2];	  
  TH1F* h_cosPhiMuMu;	  
				  
  TH1F* h_MET[2];            
  
  TH1F* h_MCMuPt[2];
  TH1F* h_MCMuEta;
  TH1F* h_MCMuPhi;
  TH1F* h_MCJetPt;
  TH1F* h_MCJetPt1;
  TH1F* h_MCJetPt2;
  TH1F* h_MCNCosTh[3];
  TH1F* h_MCDeltaCTh;
  TH2F* h_MCCTh1CTh2;
  TH1F* h_MCNMass[3];
  TH1F* h_MCWMass;
  TH1F* h_MC4Mass;

  TH1F* h_TPMass[7][2];
  TH1F* h_TPMassVert[14][3];//all pass not
  int tpCount[7][2];

  TH1F* h_VertBSDelta;

  TH1F* h_MuRelIsoVtx[9];

  bool MC_;
  float SigMass_;
  TFile *outfile;
  Bool_t *goodVerticies;

  int numCuts;
  std::vector<bool> cuts;
  std::vector<int> ePerCut;
  std::vector<float> ePerCutPU;
  std::vector<float> sEvents;
  std::vector<std::string> CutName;

  bool sys[6];

  Long64_t entrieslimit;
  Double_t METx, METy, MET, dr, MCweight, weight;
  UInt_t VertexN;

  MuonSel MuonTight;
  ElectronSel ElectronTight, ElectronLoose;
  JJ  JetsVeto, Jets; 
  //  std::vector<Lepton> lepton;

  Analyzer();
  ~Analyzer();
  void Loop();
  void TPLoop();
  void MCLoop();
  void SetWeight(Double_t CrossSection, Double_t nevents);
  void SetName(TString name, Int_t version);
  void SetName(string name);
  void WriteRoot();
  //  void SetName(string name, Float_t version);
  void SetEvtN(Long64_t events);
  void SetMC(bool isMC);
  void SetMC(bool isMC, float mass);
  void SetSys(bool JES_s, bool JER_s, bool PU_s, bool Mu_s, bool MET_s, bool BTag_s);
  //  std::string TrigNameV(std::string tn);
};
#endif
