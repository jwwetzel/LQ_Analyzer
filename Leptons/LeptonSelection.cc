#include "LeptonSelection.h"

Lep::Lep() {}

Lep::~Lep() {}

void Lep::SetPt(Double_t minPt) {
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  pt_cut_max=10000.0;
}

void Lep::SetPt1(double minPt) {
  minPt ? pt_cut_1=minPt : pt_cut_1=0.0;
}

void Lep::SetPt2(double minPt) {
  minPt ? pt_cut_2=minPt : pt_cut_2=0.0;
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  pt_cut_max=10000.0;  
}

void Lep::SetPt(Double_t minPt, Double_t maxPt) {
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  maxPt ? pt_cut_max=maxPt : pt_cut_max=10000.0;
}

void Lep::SetEta(Double_t Eta) {
  Eta ? eta_cut=Eta : eta_cut=3.0;
}

void Lep::SetRelIsoPU(bool pucorr){
  usePUcorr = pucorr;
}

void Lep::SetRelIso(Double_t RelIso) {
  RelIso ? relIso_cut=RelIso : relIso_cut=10.0;
  relIsoMIN_cut=0.0;
}

void Lep::SetRelIso(Double_t RelIsoMIN, Double_t RelIso) {
  RelIsoMIN ? relIsoMIN_cut=RelIsoMIN : relIsoMIN_cut=0.0;
  RelIso ? relIso_cut=RelIso : relIso_cut=10.0;
}


void Lep::SetCalIso(double ecalIso, double hcalIso){
  ecalIso ? ecal_iso=ecalIso : ecal_iso=0;
  hcalIso ? hcal_iso=hcalIso : hcal_iso=0;
}

void Lep::SetChiNdof(Double_t ChiNdof) {
  ChiNdof ? chiNdof_cut=ChiNdof : chiNdof_cut=100.0;
  chiNdofMIN_cut=0.0;
}

void Lep::SetChiNdof(Double_t ChiNdofMIN, Double_t ChiNdof) {
  ChiNdofMIN ? chiNdofMIN_cut=ChiNdofMIN : chiNdofMIN_cut=0.0;
  ChiNdof ? chiNdof_cut=ChiNdof : chiNdof_cut=100.0;
}

void Lep::SetBSdxy(Double_t dxyvar) {
   dxyvar ? dxy_cut=dxyvar : dxy_cut=2.0;
   dxyMIN_cut=0.0;
}

void Lep::SetBSdxy(Double_t dxyMIN, Double_t BSdxy) {
   dxyMIN ? dxyMIN_cut=dxyMIN : dxyMIN_cut=0.0;
   BSdxy ? dxy_cut=BSdxy : dxy_cut=2.0;
}

void Lep::SetDz(double dzMAX){
  dz_cut = dzMAX;
}

void Lep::SetTrkHits(int TH){
  min_trk_hits = TH;
}
