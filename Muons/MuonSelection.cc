#include "MuonSelection.h"

MuonSel::MuonSel() {};


MuonSel::~MuonSel() {};

// void MuonSel::MuonSelection(std::vector<Int_t> IsTracker, std::vector<Int_t> IsGlobal, std::vector<Double_t> Eta, std::vector<Double_t> Phi, std::vector<Double_t> Pt, std::vector<Double_t> PtErr, std::vector<Double_t> E, std::vector<Double_t> TrkIso, std::vector<Double_t> ECalIso, std::vector<Double_t> HCalIso, std::vector<Double_t> ECalIsoDeposit, std::vector<Double_t> HCalIsoDeposit, std::vector<Int_t> Charge, std::vector<Int_t> ValidHits, std::vector<Int_t> PixelValidHits, std::vector<Int_t> ValidStations, std::vector<Int_t> LayersWithMeasurement, std::vector<Double_t> GlobalChi2, std::vector<Double_t> Trkdx, std::vector<Double_t> Trkdy, std::vector<Double_t> Trkdz, std::vector<Double_t> TrkIPToolsIP, std::vector<Double_t> TrkIPToolsIPError, Double_t Vertex_X, Double_t Vertex_Y, Double_t Vertex_Z, std::vector<Double_t> PUpt, std::vector<Lepton>& leptonColl) {


//   for (UInt_t ilep=0; ilep<Pt.size(); ilep++) {

//     LeptonchiNdof = GlobalChi2[ilep]; 

//     dz = fabs(Trkdz[ilep]-Vertex_Z);
//     dxy = sqrt(pow(Trkdx[ilep]-Vertex_X,2)+pow(Trkdy[ilep]-Vertex_Y,2));
//     D0 = fabs( TrkIPToolsIP[ilep] );
//     D0Error = TrkIPToolsIPError[ilep];
   
//     // RHO
//     // = (fabs(Muon_Eta[imuon]) < 1.479) ? 0 : 1;    //we distinguish beetwen EB and EE and HB and HE
// /*
//     if (fabs(Eta[ilep]) < 0.5) ifid=0;
//     else if (fabs(Eta[ilep]) >= 0.5 && fabs(Eta[ilep]) < 1.0) ifid=1;
//     else if (fabs(Eta[ilep]) >= 1.0 && fabs(Eta[ilep]) < 1.5) ifid=2;
//     else if (fabs(Eta[ilep]) >= 1.5 && fabs(Eta[ilep]) < 2.0) ifid=3;
//     else if (fabs(Eta[ilep]) >= 2.0 && fabs(Eta[ilep]) < 2.5) ifid=4;
//     else ifid=-1;

//     MuTkIso   = TrkIso[ilep] - AreaTrackerMu[ifid] * rho;
//     MuEcalIso = ECalIso[ilep] - AreaEcalMu[ifid]  * rho;
//     MuHcalIso = HCalIso[ilep] - AreaHcalMu[ifid] * rho;
// */  
//     vLepton.SetPtEtaPhiE(Pt[ilep], Eta[ilep], Phi[ilep], E[ilep]);

//     fakeType = Lepton::unknown;
//     looseTight = Lepton::Other;
//     leptonType = Lepton::Muon;
//     /*
//     if ( isPrompt((long)Gen_Mother[ilep]) ) {
//       if ( Charge[ilep]*Gen_Mother[ilep] == -24 || Charge[ilep]*Gen_Mother[ilep] == 15 )
//         fakeType = Lepton::chargemisid;
//       else
//         fakeType = Lepton::notfake;
//     }
//     else {
//       if ( nthdigit( abs((long)Gen_Mother[ilep]),0 ) == 5 || nthdigit( abs((long)Gen_Mother[ilep]),1 ) == 5 || nthdigit( abs((long)Gen_Mother[ilep]),2 ) == 5)
//         fakeType = Lepton::bjet;

//       else if ( nthdigit( abs((long)Gen_Mother[ilep]),0 ) == 4 || nthdigit( abs((long)Gen_Mother[ilep]),1 ) == 4 || nthdigit( abs((long)Gen_Mother[ilep]),2 ) == 4)
//         fakeType = Lepton::cjet;

//       else if (nthdigit( abs((long)Gen_Mother[ilep]),0 ) == 1 || nthdigit( abs((long)Gen_Mother[ilep]),1 ) == 1 || nthdigit( abs((long)Gen_Mother[ilep]),2 ) == 1
//             || nthdigit( abs((long)Gen_Mother[ilep]),0 ) == 2 || nthdigit( abs((long)Gen_Mother[ilep]),1 ) == 2 || nthdigit( abs((long)Gen_Mother[ilep]),2 ) == 2
//             || nthdigit( abs((long)Gen_Mother[ilep]),0 ) == 3 || nthdigit( abs((long)Gen_Mother[ilep]),1 ) == 3 || nthdigit( abs((long)Gen_Mother[ilep]),2 ) == 3 )
//         fakeType = Lepton::jet;
//     }
//     */
//     if (Pt[ilep] > 0.01)
//       //LeptonRelIso = (HCalIso[ilep] + ECalIso[ilep] + TrkIso[ilep]) / std::max(Pt[ilep], 20.);
//       //LeptonRelIso  = (MuTkIso+MuEcalIso+MuHcalIso)/Pt[ilep];
// //      LeptonRelIso = (TrkIso[ilep] + std::max(0.0, ECalIso[ilep] + HCalIso[ilep] - 0.5*PUpt[ilep]))/Pt[ilep];
//       LeptonRelIso = (TrkIso[ilep] + ECalIso[ilep] + HCalIso[ilep])/Pt[ilep];
//     else LeptonRelIso = 9999.;
//     if (LeptonRelIso<0) LeptonRelIso=0.0001;
    
//     if (D0Error < 1E-6) D0Error = 1E-6;


//     (IsTracker[ilep]==1 && IsGlobal[ilep]==1 && ValidHits[ilep]>0 && PixelValidHits[ilep]>0 && ValidStations[ilep]>1 && LayersWithMeasurement[ilep]>5) ? individual = true :individual = false;

//     (HCalIsoDeposit[ilep] < HCalDeposit_max && ECalIsoDeposit[ilep] < ECalDeposit_max && (HCalIsoDeposit[ilep] >= HCalDeposit_min || ECalIsoDeposit[ilep] >= ECalDeposit_min) ) ? DepositVeto=true : DepositVeto=false;

//     (fabs(Eta[ilep]) < eta_cut && Pt[ilep] >= pt_cut_min && Pt[ilep] < pt_cut_max && PtErr[ilep]/Pt[ilep]<=0.10) ? etaPt=true : etaPt =false;

//     (LeptonchiNdof<chiNdof_cut && LeptonRelIso < relIso_cut && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || LeptonchiNdof>=chiNdofMIN_cut || fabs(dxy-Vxy)>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
//     //(LeptonchiNdof<chiNdof_cut && LeptonRelIso < relIso_cut && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || fabs(dxy-Vxy)>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
//     //(LeptonchiNdof<chiNdof_cut && dz<dz_cut && dxy<dxy_cut && LeptonRelIso < relIso_cut && LeptonRelIso >= relIsoMIN_cut) ? RelIsod0Chi2=true : RelIsod0Chi2=false; 

//     if (etaPt && RelIsod0Chi2 && DepositVeto && individual)
//       leptonColl.push_back( Lepton(leptonType, ilep, vLepton, Eta[ilep], LeptonchiNdof, D0, D0Error, dxy, dz, Charge[ilep], fakeType, looseTight, TrkIso[ilep], LeptonRelIso) );
    
//   }
  
//   std::sort( leptonColl.begin(), leptonColl.end(), LeptonPTSorter );
  
// }

vector<int> MuonSel::MuonSelection(std::vector<Int_t> IsTracker, std::vector<Int_t> IsGlobal, std::vector<Double_t> Eta, std::vector<Double_t> Phi, std::vector<Double_t> Pt, std::vector<Double_t> PtErr, std::vector<Double_t> E, std::vector<Double_t> TrkIso, std::vector<Double_t> HCalIso, std::vector<Double_t> ECalIso, std::vector<Double_t> ECalIsoDeposit, std::vector<Double_t> HCalIsoDeposit, std::vector<Int_t> Charge, std::vector<Int_t> ValidHits, std::vector<Int_t> PixelValidHits, std::vector<Int_t> ValidStations, std::vector<Int_t> LayersWithMeasurement, std::vector<Double_t> GlobalChi2, std::vector<Double_t> Trkdx, std::vector<Double_t> Trkdy, std::vector<Double_t> Trkdz, std::vector<Double_t> TrkIPToolsIP, std::vector<Double_t> TrkIPToolsIPError, Double_t Vertex_X, Double_t Vertex_Y, Double_t Vertex_Z, std::vector<Double_t> PUpt, std::vector<Lepton>& leptonColl) {

  vector<int> CutRes(18,0);

  for (UInt_t ilep=0; ilep!=Pt.size(); ilep++) {

    LeptonchiNdof = GlobalChi2[ilep]; 
    LeptonchiNdof < chiNdof_cut ? ++CutRes[1] : 0;

    dz = fabs(Trkdz[ilep]-Vertex_Z);
    dxy = sqrt(pow(Trkdx[ilep]-Vertex_X,2)+pow(Trkdy[ilep]-Vertex_Y,2));
    D0 = fabs( TrkIPToolsIP[ilep] );
    D0Error = TrkIPToolsIPError[ilep];
    //    (fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut) ? ++CutRes[2] : 0;
    (dz<dz_cut && dxy<dxy_cut) ? ++CutRes[2] : 0;
   
    vLepton.SetPtEtaPhiE(Pt[ilep], Eta[ilep], Phi[ilep], E[ilep]);

    fakeType = Lepton::unknown;
    looseTight = Lepton::Other;
    leptonType = Lepton::Muon;

    if (Pt[ilep] > 0.01)
      LeptonRelIso = (TrkIso[ilep] + std::max(0.0, ECalIso[ilep] + HCalIso[ilep] - 0.5*PUpt[ilep]))/Pt[ilep];
    //      LeptonRelIso = (TrkIso[ilep] + ECalIso[ilep] + HCalIso[ilep])/Pt[ilep];
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;
    LeptonRelIso < relIso_cut ? ++CutRes[0] : 0;
    
    if (D0Error < 1E-6) D0Error = 1E-6;


//     (Lepton_IsTracker[ilep]==1 && Lepton_IsGlobal[ilep]==1 && Lepton_TrkValidHits[ilep]>= min_trk_hits && Lepton_StandValidHits[ilep]>=1) ? individual = true :individual = false;
    IsTracker[ilep]==1 ? ++CutRes[3] : 0;
    IsGlobal[ilep]==1 ? ++CutRes[4] : 0;
    LayersWithMeasurement[ilep]>5 && PixelValidHits[ilep] ? ++CutRes[5] : 0;
    ValidStations[ilep] >= 1 && ValidHits[ilep] ? ++CutRes[6] : 0;
    (IsTracker[ilep]==1 && IsGlobal[ilep]==1 
     && ValidHits[ilep]> 0 && PixelValidHits[ilep]>0 
     //     && (ValidHits[ilep] + PixelValidHits[ilep])>= min_trk_hits
     && ValidStations[ilep]>1 && LayersWithMeasurement[ilep]>5) ? individual = true :individual = false;


//     (Lepton_HCalIsoDeposit[ilep]<=hcal_iso && Lepton_ECalIsoDeposit[ilep]<=ecal_iso) ? DepositVeto=true : DepositVeto=false;
    HCalIsoDeposit[ilep]<=hcal_iso ? ++CutRes[7] : 0;
    ECalIsoDeposit[ilep]<=ecal_iso ? ++CutRes[8] : 0;
    //    (HCalIsoDeposit[ilep] < HCalDeposit_max && ECalIsoDeposit[ilep] < ECalDeposit_max 
    (HCalIsoDeposit[ilep] < hcal_iso && ECalIsoDeposit[ilep] < ecal_iso 
     && (HCalIsoDeposit[ilep] >= HCalDeposit_min || ECalIsoDeposit[ilep] >= ECalDeposit_min) ) ? DepositVeto=true : DepositVeto=false;


//     (fabs(Lepton_Eta[ilep]) < eta_cut && Lepton_Pt[ilep] >= pt_cut_min && Lepton_Pt[ilep] < pt_cut_max && Lepton_PtErr[ilep]/Lepton_Pt[ilep]<=0.10) ? etaPt=true : etaPt =false;
    fabs(Eta[ilep]) < eta_cut ? ++CutRes[9] : 0;
    (Pt[ilep] >= pt_cut_1 && PtErr[ilep]/Pt[ilep]<=0.10) ? ++CutRes[10] : 0;  // need 1 above this cut
    (Pt[ilep] >= pt_cut_2 && PtErr[ilep]/Pt[ilep]<=0.10) ? ++CutRes[11] : 0;  // need 2 above this cut
    Charge[ilep] > 0 ? ++CutRes[12] : ++CutRes[13];
    (fabs(Eta[ilep]) < eta_cut && Pt[ilep] >= pt_cut_min 
     && Pt[ilep] < pt_cut_max && PtErr[ilep]/Pt[ilep]<=0.10) ? etaPt=true : etaPt =false;

//     (LeptonchiNdof<chiNdof_cut && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<BSdxy_cut && LeptonRelIso < relIso_cut) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
    if(etaPt) ++CutRes[14];
    if(DepositVeto) ++CutRes[16];
    if(individual) ++CutRes[17];
    (LeptonchiNdof<chiNdof_cut && LeptonRelIso < relIso_cut 
     && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut 
     && ( LeptonRelIso >= relIsoMIN_cut || LeptonchiNdof>=chiNdofMIN_cut || fabs(dxy-Vxy)>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
    if(RelIsod0Chi2) ++CutRes[15];

    if (etaPt && RelIsod0Chi2 && DepositVeto && individual){
      leptonColl.push_back( Lepton(leptonType, ilep, vLepton, Eta[ilep], LeptonchiNdof, D0, D0Error, dxy, dz, Charge[ilep], fakeType, looseTight, TrkIso[ilep], LeptonRelIso) );
    }
  }
  if(leptonColl.size() > 1) std::sort( leptonColl.begin(), leptonColl.end(), LeptonPTSorter );

  return CutRes;
}

void MuonSel::SetDeposits(Double_t ECalDeposit , Double_t HCalDeposit) {
    ECalDeposit ? ECalDeposit_max = ECalDeposit : ECalDeposit_max=4.0;
    HCalDeposit ? HCalDeposit_max = HCalDeposit : HCalDeposit_max=6.0;
    ECalDeposit_min = 0.0;
    HCalDeposit_min = 0.0;
}

void MuonSel::SetDeposits(Double_t ECalDeposit1 , Double_t HCalDeposit1, Double_t ECalDeposit2 , Double_t HCalDeposit2) {
    ECalDeposit1 ? ECalDeposit_min = ECalDeposit1 : ECalDeposit_min=0.0;
    HCalDeposit1 ? HCalDeposit_min = HCalDeposit1 : HCalDeposit_min=0.0;
    ECalDeposit2 ? ECalDeposit_max = ECalDeposit2 : ECalDeposit_max=4.0;
    HCalDeposit2 ? HCalDeposit_max = HCalDeposit2 : HCalDeposit_max=6.0;
}
void MuonSel::SetSys(bool mu_s){
  sys = mu_s;
}
