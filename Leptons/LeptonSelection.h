#ifndef LeptonSelection_h
#define LeptonSelection_h

#include <iostream>
using namespace std;

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "Lepton.h"
#include "../SupportingFiles/OtherFunctions.h"

class Lep {

 public:
  Int_t ifid;
  Lepton::FakeType fakeType;
  Lepton::LooseTight looseTight;
  Lepton::LeptonType leptonType;
  TLorentzVector vLepton;
  bool etaPt,RelIsod0Chi2,DepositVeto,individual,RelIsod0;//fiducial;//muonid,pTcut,isIso;
  double LeptonRelIso;
  double dz, dxy, dz_BS,dxy_BS,D0,D0Error,D0Significance;
  double Vz, Vxy;
  unsigned int ilepton,numlep;
  double pt_cut_min, pt_cut_max, pt_cut_1, pt_cut_2, eta_cut, relIso_cut, relIsoMIN_cut;
  double ecal_iso, hcal_iso, chiNdof_cut, chiNdofMIN_cut, BSdxy_cut, dz_cut, BSdxyMIN_cut;
  Int_t casediscriminator,simpleselection, min_trk_hits;
  bool usePUcorr;
  Double_t dxy_cut, dxyMIN_cut;

  Double_t LeptonchiNdof;
  Lep();
  ~Lep();

  void SetPt(double minPt, double maxPt);
  void SetPt(double minPt);
  void SetPt1(double minPt);
  void SetPt2(double minPt);
  void SetEta(double Eta);
  void SetRelIso(double RelIso);
  void SetRelIsoPU(bool pucorr);
  void SetRelIso(double RelIsoMIN, double RelIso);
  void SetCalIso(double ecalIso, double hcalIso);
  void SetChiNdof(double ChiNdof);
  void SetChiNdof(double ChiNdofMIN, double ChiNdof);
  void SetBSdxy(double dxyvar);
  void SetDz(double dzMAX);
  void SetBSdxy(double BSdxyMIN, double BSdxy);
  void SetTrkHits(int TH);
};

#endif
