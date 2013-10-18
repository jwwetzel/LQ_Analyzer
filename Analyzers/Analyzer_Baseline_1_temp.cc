#include "Analyzer.h"
#include <sstream>
#include <fstream>
//#include "Reweight.cc"


Analyzer::Analyzer() :
  MC_(false),
  SigMass_(0),
  numCuts(43),
  cuts(numCuts, false),
  ePerCut(numCuts, 0),
  ePerCutPU(numCuts, 0),
  sEvents(numCuts, 0),
  CutName(numCuts, ""),
  entrieslimit(0)
{
  CutName[0] = "Rel_Iso";
  CutName[1] = "Normalized_Chi2";
  CutName[2] = "dxy";
  CutName[3] = "tracker";
  CutName[4] = "global";
  CutName[5] = "number_tracker_hits";
  CutName[6] = "one_SA_hit";
  CutName[7] = "hcal_iso";
  CutName[8] = "ecal_iso";
  CutName[9] = "eta";
  CutName[10] = "high_pt";
  CutName[11] = "low_pt";
  CutName[12] = "plus_charge";
  CutName[13] = "minus_charge";
  CutName[14] = "etaPtSS";
  CutName[15] = "RelIsod0Chi2";
  CutName[16] = "DepositVeto";
  CutName[17] = "TrackMuonHits";
  CutName[18] = "muon_mass";
  CutName[19] = "z_cut";
  CutName[20] = "jet_mult_pt";
  CutName[21] = "vertex";
  CutName[22] = "All_Muon";
  CutName[23] = "All_Cuts";
  CutName[24] = "Mu_Quality";
  CutName[25] = "Isolation";
  CutName[26] = "Trigger";
  CutName[27] = "Trig_Cuts";
  CutName[28] = "Selection1";
  CutName[29] = "Selection2";
  CutName[30] = "MET";
  CutName[31] = "AllPlusMET";
  CutName[32] = "TrigPlusMET";
  CutName[33] = "Ferd";
  CutName[34] = "Ferd_jets";
  CutName[35] = "ferd_muons";
  CutName[36] = "btag_Medium_Veto";
  CutName[37] = "PFJetID";
  CutName[38] = "JetPT";
  CutName[39] = "btag_Tight_Veto";
  CutName[40] = "LowMassPass";
  CutName[41] = "MidMassPass";
  CutName[42] = "HighMassPass";
  
  if (debug) cout<<"inizio"<<endl;

  //  outfile->Open("test.root", "RECREATE");

  h_nVertex[0] = new TH1F("nVertex_MC", "", 100, 0, 100);
  h_nVertex[1] = new TH1F("nVertex_Reco", "", 100, 0, 100);
  h_nVertex[2] = new TH1F("nVertex_MC_rw", "", 100, 0, 100);
  h_nVertex[3] = new TH1F("nVertex_Reco_rw", "", 100, 0, 100);
  h_PUweight = new TH1F("PU_weight", "", 100, 0, 10);

  h_MuDxy[0] = new TH1F("MuonDxy_AllMu", "", 1000, 0, 1);
  h_MuDz[0] = new TH1F("MuonDz_AllMu", "", 1000, 0, 100);
  h_MuD0[0] = new TH1F("MuonD0_AllMu", "", 1000, 0, 1);
  h_MuPt[0]     = new TH1F("MuonPt_AllMu",     "", 1000, 0, 1000);	 
  h_MuPt[6]     = new TH1F("MuonPt_AllMu1",     "", 1000, 0, 1000);	 
  h_MuPt[7]     = new TH1F("MuonPt_AllMu2",     "", 1000, 0, 1000);	 
  h_MuEta[0]	= new TH1F("MuonEta_AllMu",    "", 1000, -5, 5);	 
  h_MuPhi[0]	= new TH1F("MuonPhi_AllMu",    "", 1000, -3.15, 3.15); 
  h_MuNum[0]	= new TH1F("MuonNum_AllMu",    "", 100, -.5, 99.5);	 
  h_MuTkHits[0]	= new TH1F("MuonTkHits_AllMu", "", 100, -.5, 99.5);	 
  h_MuSAHits[0]	= new TH1F("MuonSAHits_AllMu", "", 100, -.5, 99.5);	 
  h_MuEcal[0]	= new TH1F("MuonEcal_AllMu",   "", 1000, 0, 100);	 
  h_MuHcal[0]	= new TH1F("MuonHcal_AllMu",   "", 1000, 0, 100);	 
  h_MuTrk[0]	= new TH1F("MuonTrk_AllMu",   "", 1000, 0, 100);	 
  h_MuRel[0]	= new TH1F("MuonRel_AllMu",    "", 1000, 0, 10);
  h_MuRelIso[0]	= new TH1F("MuonRelCh_AllMu",    "", 1000, 0, 10);
  h_MuRelIso[1]	= new TH1F("MuonRelNeu_AllMu",    "", 1000, 0, 10);
  h_MuRelIso[2]	= new TH1F("MuonRelPho_AllMu",    "", 1000, 0, 10);
     
  h_MuDxy[1] = new TH1F("MuonDxy_TightMu", "", 1000, 0, 1);
  h_MuDz[1] = new TH1F("MuonDz_TightMu", "", 1000, 0, 100);
  h_MuD0[1] = new TH1F("MuonD0_TightMu", "", 1000, 0, 1);
  h_MuPt[1]	= new TH1F("MuonPt_TightMu",     "", 1000, 0, 1000);
  h_MuEta[1]	= new TH1F("MuonEta_TightMu",    "", 1000, -5, 5);
  h_MuPhi[1]	= new TH1F("MuonPhi_TightMu",    "", 1000, -3.15, 3.15);
  h_MuNum[1]	= new TH1F("MuonNum_TightMu",    "", 100, -.5, 99.5);
  h_MuTkHits[1]	= new TH1F("MuonTkHits_TightMu", "", 100, -.5, 99.5);
  h_MuSAHits[1]	= new TH1F("MuonSAHits_TightMu", "", 100, 0, 99.5);
  h_MuEcal[1]	= new TH1F("MuonEcal_TightMu",   "", 1000, 0, 100);
  h_MuHcal[1]	= new TH1F("MuonHcal_TightMu",   "", 1000, 0, 100);
  h_MuTrk[1]	= new TH1F("MuonTrk_TightMu",   "", 1000, 0, 100);
  h_MuRel[1]    = new TH1F("MuonRel_TightMu",    "", 1000, 0, 10);
  h_MuRelIso[3]	= new TH1F("MuonRelCh_TightMu",    "", 1000, 0, 10);
  h_MuRelIso[4]	= new TH1F("MuonRelNeu_TightMu",    "", 1000, 0, 10);
  h_MuRelIso[5]	= new TH1F("MuonRelPho_TightMu",    "", 1000, 0, 10);
  h_MuPt[2]	= new TH1F("MuonPt_TightMu1",    "", 1000, 0, 1000);
  h_MuPt[3]	= new TH1F("MuonPt_TightMu2",    "", 1000, 0, 1000);

  h_MuDxy[2] = new TH1F("MuonDxy_LooseMu", "", 1000, 0, 1);
  h_MuDz[2] = new TH1F("MuonDz_LooseMu", "", 1000, 0, 100);
  h_MuD0[2] = new TH1F("MuonD0_LooseMu", "", 1000, 0, 1);
  h_MuPt[8]	= new TH1F("MuonPt_LooseMu",     "", 1000, 0, 1000);
  h_MuEta[2]	= new TH1F("MuonEta_LooseMu",    "", 1000, -5, 5);
  h_MuPhi[2]	= new TH1F("MuonPhi_LooseMu",    "", 1000, -3.15, 3.15);
  h_MuNum[2]	= new TH1F("MuonNum_LooseMu",    "", 100, -.5, 99.5);
  h_MuTkHits[2]	= new TH1F("MuonTkHits_LooseMu", "", 100, -.5, 99.5);
  h_MuSAHits[2]	= new TH1F("MuonSAHits_LooseMu", "", 100, 0, 99.5);
  h_MuEcal[2]	= new TH1F("MuonEcal_LooseMu",   "", 1000, 0, 100);
  h_MuHcal[2]	= new TH1F("MuonHcal_LooseMu",   "", 1000, 0, 100);
  h_MuTrk[2]	= new TH1F("MuonTrk_LooseMu",   "", 1000, 0, 100);
  h_MuRel[2]    = new TH1F("MuonRel_LooseMu",    "", 1000, 0, 10);
  h_MuRelIso[6]	= new TH1F("MuonRelCh_LooseMu",    "", 1000, 0, 10);
  h_MuRelIso[7]	= new TH1F("MuonRelNeu_LooseMu",    "", 1000, 0, 10);
  h_MuRelIso[8]	= new TH1F("MuonRelPho_LooseMu",    "", 1000, 0, 10);
  h_MuPt[4]	= new TH1F("MuonPt_LooseMu1",    "", 1000, 0, 1000);
  h_MuPt[5]	= new TH1F("MuonPt_LooseMu2",    "", 1000, 0, 1000);

  h_JetPt[0] = new TH1F("Jet_Pt", "", 1000, 0, 1000);
  h_JetPt[1] = new TH1F("Jet1_Pt", "", 1000, 0, 1000);
  h_JetPt[2] = new TH1F("Jet2_Pt", "", 1000, 0, 1000);
  h_JetPt[3] = new TH1F("Jet1Match_Pt", "", 1000, 0, 1000);
  h_JetPt[4] = new TH1F("Jet2Match_Pt", "", 1000, 0, 1000);
  h_JetMatch[0] = new TH1F("Jet1Match", "", 100, -.5, 99.5);
  h_JetMatch[1] = new TH1F("Jet2Match", "", 100, -.5, 99.5);
  h_JetMatchDR[0] = new TH1F("Jet1MatchDR", "", 100, 0, 5);
  h_JetMatchDR[1] = new TH1F("Jet2MatchDR", "", 100, 0, 5);
  h_JetEta = new TH1F("Jet_Eta", "", 1000, -5, 5);
  h_JetPhi = new TH1F("Jet_Phi", "", 1000, -3.15, 3.15);
  h_JetNum[0] = new TH1F("Jet_Num", "", 100, -.5, 99.5);
  h_JetNum[1] = new TH1F("Jet_Num_AllCuts", "", 100, -.5, 99.5);
  h_JetUncert[0] = new TH1F("Jet_Err_All", "", 100, -10, 0);
  h_JetUncert[1] = new TH1F("Jet_Err_Good", "", 100, -10, 0);
  h_JetBTag = new TH1F("Jet_BTag_CSV_LMT","",4,0,4);

  h_dRjmu[0]    = new TH1F("dRJetMu1",   "", 1000, 0, 10);	  
  h_dRjmu[1]    = new TH1F("dRJetMu2",   "", 1000, 0, 10);	  
  h_Mmumu       = new TH1F("MassMuMu",   "", 1000, 0, 1000);	  

  h_Mjj[0]      = new TH1F("MassJJ_Sel1",     "", 1000, 0, 1000);	  
  h_Mjjmu[0]    = new TH1F("MassJJMu1_Sel1",  "", 100, 0, 1000);	  
  h_Mjjmu[1]    = new TH1F("MassJJMu2_Sel1",  "", 100, 0, 1000);	  
  h_Mjjmumu[0]  = new TH1F("MassJJMuMu_Sel1", "", 200, 0, 2000);	  
  h_Mjj[1]      = new TH1F("MassJJ_Sel2",     "", 1000, 0, 1000);	  
  h_Mjjmu[2]    = new TH1F("MassJJMu1_Sel2",  "", 100, 0, 1000);	  
  h_Mjjmu[3]    = new TH1F("MassJJMu2_Sel2",  "", 100, 0, 1000);	  
  h_Mjjmumu[1]  = new TH1F("MassJJMuMu_Sel2", "", 200, 0, 2000);	  
  h_Mjj[2]      = new TH1F("MassJJ_Full",     "", 1000, 0, 1000);	  
  h_Mjjmu[4]    = new TH1F("MassJJMu1_Full",  "", 100, 0, 1000);	  
  h_Mjjmu[5]    = new TH1F("MassJJMu2_Full",  "", 100, 0, 1000);	  
  h_Mjjmumu[2]  = new TH1F("MassJJMuMu_Full", "", 200, 0, 2000);	  

  h_dEtajjMu[0] = new TH1F("dEtaJJMu1",  "", 1000, 0, 10);	  
  h_dEtajjMu[1] = new TH1F("dEtaJJMu2",  "", 1000, 0, 10);	  
  h_cosPhiMuMu  = new TH1F("CosPhiMuMu", "", 1000, -1, 1);	  
  h_MET[0]      = new TH1F("MET",        "", 1000, 0, 1000);           
  h_MET[1]      = new TH1F("MET_wCuts",        "", 1000, 0, 1000);           
 
  h_MCMuPt[0]   = new TH1F("MC_SisMuPt", "", 1000, 0, 1000);
  h_MCMuPt[1]   = new TH1F("MC_DauMuPt", "", 1000, 0, 1000);
  h_MCMuEta  = new TH1F("MC_MuEta", "", 1000, -5, 5);
  h_MCMuPhi  = new TH1F("MC_MuPhi", "", 1000, -3.15, 3.15);
  h_MCJetPt = new TH1F("MC_JetPt", "", 1000, 0, 1000);
  h_MCJetPt1 = new TH1F("MC_JetPt1", "", 1000, 0, 1000);
  h_MCJetPt2 = new TH1F("MC_JetPt2", "", 1000, 0, 1000);
  h_MCNCosTh[0] = new TH1F("MC_realN_cosTheta", "", 100, -1, 1);
  h_MCNCosTh[1] = new TH1F("MC_fakeN_cosTheta", "", 100, -1, 1);
  h_MCNCosTh[2] = new TH1F("MC_N_cosTheta", "", 100, -1, 1);
  h_MCDeltaCTh = new TH1F("MC_N_DeltaCosTh", "", 200, -2, 2);
  h_MCNMass[0] = new TH1F("MC_real3N_Mass", "", 1000, 0, 1000);
  h_MCNMass[2] = new TH1F("MC_real1N_Mass", "", 1000, 0, 1000);
  h_MCNMass[1] = new TH1F("MC_fake3N_Mass", "", 1000, 0, 1000);
  h_MCWMass = new TH1F("MC_JJ_Mass", "", 1000, 0, 1000);
  h_MC4Mass = new TH1F("MC_4_Mass", "", 1000, 0, 1000);

  h_MCCTh1CTh2 = new TH2F("MC_CosTh1_vs_CosTh2", "", 100, -1, 1, 100, 1, 1);

  h_TPMass[0][1] = new TH1F("TP_dimuMass_a30_All", "", 500, 0, 500);
  h_TPMass[1][1] = new TH1F("TP_dimuMass_a30_IDp", "", 500, 0, 500);
  h_TPMass[4][1] = new TH1F("TP_dimuMass_a30_IDf", "", 500, 0, 500);
  h_TPMass[2][1] = new TH1F("TP_dimuMass_a30_Isop", "", 500, 0, 500);
  h_TPMass[5][1] = new TH1F("TP_dimuMass_a30_Isof", "", 500, 0, 500);
  h_TPMass[3][1] = new TH1F("TP_dimuMass_a30_IDIsop", "", 500, 0, 500);
  h_TPMass[6][1] = new TH1F("TP_dimuMass_a30_IDIsof", "", 500, 0, 500);
  h_TPMass[0][0] = new TH1F("TP_dimuMass_b30_All", "", 500, 0, 500);
  h_TPMass[1][0] = new TH1F("TP_dimuMass_b30_IDp", "", 500, 0, 500);
  h_TPMass[4][0] = new TH1F("TP_dimuMass_b30_IDf", "", 500, 0, 500);
  h_TPMass[2][0] = new TH1F("TP_dimuMass_b30_Isop", "", 500, 0, 500);
  h_TPMass[5][0] = new TH1F("TP_dimuMass_b30_Isof", "", 500, 0, 500);
  h_TPMass[3][0] = new TH1F("TP_dimuMass_b30_IDIsop", "", 500, 0, 500);
  h_TPMass[6][0] = new TH1F("TP_dimuMass_b30_IDIsof", "", 500, 0, 500);

  h_TPMassVert[0][0] = new TH1F("TP_dimuMass_Vert00_10_All", "", 500, 0, 500);
  h_TPMassVert[0][1] = new TH1F("TP_dimuMass_Vert00_10_Pas", "", 500, 0, 500);
  h_TPMassVert[0][2] = new TH1F("TP_dimuMass_Vert00_10_Not", "", 500, 0, 500);
  h_TPMassVert[1][0] = new TH1F("TP_dimuMass_Vert10_15_All", "", 500, 0, 500);
  h_TPMassVert[1][1] = new TH1F("TP_dimuMass_Vert10_15_Pas", "", 500, 0, 500);
  h_TPMassVert[1][2] = new TH1F("TP_dimuMass_Vert10_15_Not", "", 500, 0, 500);
  h_TPMassVert[2][0] = new TH1F("TP_dimuMass_Vert15_16_All", "", 500, 0, 500);
  h_TPMassVert[2][1] = new TH1F("TP_dimuMass_Vert15_16_Pas", "", 500, 0, 500);
  h_TPMassVert[2][2] = new TH1F("TP_dimuMass_Vert15_16_Not", "", 500, 0, 500);
  h_TPMassVert[3][0] = new TH1F("TP_dimuMass_Vert16_17_All", "", 500, 0, 500);
  h_TPMassVert[3][1] = new TH1F("TP_dimuMass_Vert16_17_Pas", "", 500, 0, 500);
  h_TPMassVert[3][2] = new TH1F("TP_dimuMass_Vert16_17_Not", "", 500, 0, 500);
  h_TPMassVert[4][0] = new TH1F("TP_dimuMass_Vert17_18_All", "", 500, 0, 500);
  h_TPMassVert[4][1] = new TH1F("TP_dimuMass_Vert17_18_Pas", "", 500, 0, 500);
  h_TPMassVert[4][2] = new TH1F("TP_dimuMass_Vert17_18_Not", "", 500, 0, 500);
  h_TPMassVert[5][0] = new TH1F("TP_dimuMass_Vert18_19_All", "", 500, 0, 500);
  h_TPMassVert[5][1] = new TH1F("TP_dimuMass_Vert18_19_Pas", "", 500, 0, 500);
  h_TPMassVert[5][2] = new TH1F("TP_dimuMass_Vert18_19_Not", "", 500, 0, 500);
  h_TPMassVert[6][0] = new TH1F("TP_dimuMass_Vert19_20_All", "", 500, 0, 500);
  h_TPMassVert[6][1] = new TH1F("TP_dimuMass_Vert19_20_Pas", "", 500, 0, 500);
  h_TPMassVert[6][2] = new TH1F("TP_dimuMass_Vert19_20_Not", "", 500, 0, 500);
  h_TPMassVert[7][0] = new TH1F("TP_dimuMass_Vert20_21_All", "", 500, 0, 500);
  h_TPMassVert[7][1] = new TH1F("TP_dimuMass_Vert20_21_Pas", "", 500, 0, 500);
  h_TPMassVert[7][2] = new TH1F("TP_dimuMass_Vert20_21_Not", "", 500, 0, 500);
  h_TPMassVert[8][0] = new TH1F("TP_dimuMass_Vert21_22_All", "", 500, 0, 500);
  h_TPMassVert[8][1] = new TH1F("TP_dimuMass_Vert21_22_Pas", "", 500, 0, 500);
  h_TPMassVert[8][2] = new TH1F("TP_dimuMass_Vert21_22_Not", "", 500, 0, 500);
  h_TPMassVert[9][0] = new TH1F("TP_dimuMass_Vert22_23_All", "", 500, 0, 500);
  h_TPMassVert[9][1] = new TH1F("TP_dimuMass_Vert22_23_Pas", "", 500, 0, 500);
  h_TPMassVert[9][2] = new TH1F("TP_dimuMass_Vert22_23_Not", "", 500, 0, 500);
  h_TPMassVert[10][0] = new TH1F("TP_dimuMass_Vert23_24_All", "", 500, 0, 500);
  h_TPMassVert[10][1] = new TH1F("TP_dimuMass_Vert23_24_Pas", "", 500, 0, 500);
  h_TPMassVert[10][2] = new TH1F("TP_dimuMass_Vert23_24_Not", "", 500, 0, 500);
  h_TPMassVert[11][0] = new TH1F("TP_dimuMass_Vert24_25_All", "", 500, 0, 500);
  h_TPMassVert[11][1] = new TH1F("TP_dimuMass_Vert24_25_Pas", "", 500, 0, 500);
  h_TPMassVert[11][2] = new TH1F("TP_dimuMass_Vert24_25_Not", "", 500, 0, 500);
  h_TPMassVert[12][0] = new TH1F("TP_dimuMass_Vert25_30_All", "", 500, 0, 500);
  h_TPMassVert[12][1] = new TH1F("TP_dimuMass_Vert25_30_Pas", "", 500, 0, 500);
  h_TPMassVert[12][2] = new TH1F("TP_dimuMass_Vert25_30_Not", "", 500, 0, 500);
  h_TPMassVert[13][0] = new TH1F("TP_dimuMass_Vert30_40_All", "", 500, 0, 500);
  h_TPMassVert[13][1] = new TH1F("TP_dimuMass_Vert30_40_Pas", "", 500, 0, 500);
  h_TPMassVert[13][2] = new TH1F("TP_dimuMass_Vert30_40_Not", "", 500, 0, 500);


  h_VertBSDelta = new TH1F("Delta_Vertex_BS", "", 1000, 0, 100);

  h_MuRelIsoVtx[0] = new TH1F("h_2Mu10", "", 100, -.5, 99.5);
  h_MuRelIsoVtx[6] = new TH1F("h_2Mu", "", 100, -.5, 99.5);
  h_MuRelIsoVtx[1] = new TH1F("h_2Mu20", "", 100, -.5, 99.5);
  h_MuRelIsoVtx[2] = new TH1F("h_2Mu10RI", "", 100, -.5, 99.5);
  h_MuRelIsoVtx[7] = new TH1F("h_2MuRI", "", 100, -.5, 99.5);
  h_MuRelIsoVtx[3] = new TH1F("h_2Mu20RI", "", 100, -.5, 99.5);
  h_MuRelIsoVtx[4] = new TH1F("h_2Mu10PURI", "", 100, -.5, 99.5);
  h_MuRelIsoVtx[8] = new TH1F("h_2MuPURI", "", 100, -.5, 99.5);
  h_MuRelIsoVtx[5] = new TH1F("h_2Mu20PURI", "", 100, -.5, 99.5);

  h_MuEff[0] = new TH1F("h_MuEff_woPU", "", 100, -.5, 99.5);
  h_MuEff[1] = new TH1F("h_MuEff_wPU", "", 100, -.5, 99.5);
  h_MuEff[2] = new TH1F("h_MuEff_All", "", 100, -.5, 99.5);

  for(int tpi=0; tpi!=7; ++tpi){
    tpCount[tpi][0] = 0;
    tpCount[tpi][1] = 0;
  }

  if (debug) cout<<"fine"<<endl;
}

void Analyzer::WriteRoot()
{
  if(outfile->cd())
  {
    if(!outfile->IsWritable())
    {
      cout << "file opened can not write" << endl;
      //     outfile->Close();
      return;
    }
    outfile->cd();

    //    h_nVertex[1]->Write();
    h_TPMass[0][0]->Write();
    h_TPMass[1][0]->Write();
    h_TPMass[2][0]->Write();
    h_TPMass[3][0]->Write();
    h_TPMass[4][0]->Write();
    h_TPMass[5][0]->Write();
    h_TPMass[6][0]->Write();
    h_TPMass[0][1]->Write();
    h_TPMass[1][1]->Write();
    h_TPMass[2][1]->Write();
    h_TPMass[3][1]->Write();
    h_TPMass[4][1]->Write();
    h_TPMass[5][1]->Write();
    h_TPMass[6][1]->Write();

    h_TPMassVert[0][0]->Write();
    h_TPMassVert[0][1]->Write();
    h_TPMassVert[0][2]->Write();
    h_TPMassVert[1][0]->Write();
    h_TPMassVert[1][1]->Write();
    h_TPMassVert[1][2]->Write();
    h_TPMassVert[2][0]->Write();
    h_TPMassVert[2][1]->Write();
    h_TPMassVert[2][2]->Write();
    h_TPMassVert[3][0]->Write();
    h_TPMassVert[3][1]->Write();
    h_TPMassVert[3][2]->Write();
    h_TPMassVert[4][0]->Write();
    h_TPMassVert[4][1]->Write();
    h_TPMassVert[4][2]->Write();
    h_TPMassVert[5][0]->Write();
    h_TPMassVert[5][1]->Write();
    h_TPMassVert[5][2]->Write();
    h_TPMassVert[6][0]->Write();
    h_TPMassVert[6][1]->Write();
    h_TPMassVert[6][2]->Write();
    h_TPMassVert[7][0]->Write();
    h_TPMassVert[7][1]->Write();
    h_TPMassVert[7][2]->Write();
    h_TPMassVert[8][0]->Write();
    h_TPMassVert[8][1]->Write();
    h_TPMassVert[8][2]->Write();
    h_TPMassVert[9][0]->Write();
    h_TPMassVert[9][1]->Write();
    h_TPMassVert[9][2]->Write();
    h_TPMassVert[10][0]->Write();
    h_TPMassVert[10][1]->Write();
    h_TPMassVert[10][2]->Write();
    h_TPMassVert[11][0]->Write();
    h_TPMassVert[11][1]->Write();
    h_TPMassVert[11][2]->Write();
    h_TPMassVert[12][0]->Write();
    h_TPMassVert[12][1]->Write();
    h_TPMassVert[12][2]->Write();
    h_TPMassVert[13][0]->Write();
    h_TPMassVert[13][1]->Write();
    h_TPMassVert[13][2]->Write();

    h_nVertex[0]->Write();
    h_nVertex[1]->Write();
    h_nVertex[2]->Write();
    h_nVertex[3]->Write();
    h_PUweight->Write();
    h_MuDxy[0]->Write();
    h_MuDz[0]->Write();
    h_MuD0[0]->Write();
    h_MuPt[0]->Write();
    h_MuPt[6]->Write();
    h_MuPt[7]->Write();
    h_MuEta[0]->Write();
    h_MuPhi[0]->Write();
    h_MuTkHits[0]->Write();
    h_MuSAHits[0]->Write();
    h_MuEcal[0]->Write();
    h_MuHcal[0]->Write();
    h_MuTrk[0]->Write();
    h_MuRel[0]->Write();
    h_MuRelIso[0]->Write();
    h_MuRelIso[1]->Write();
    h_MuRelIso[2]->Write();
    h_MuRelIso[3]->Write();
    h_MuRelIso[4]->Write();
    h_MuRelIso[5]->Write();
    h_MuRelIso[6]->Write();
    h_MuRelIso[7]->Write();
    h_MuRelIso[8]->Write();
    h_MuNum[0]->Write();

    h_MuDxy[1]->Write();
    h_MuDz[1]->Write();
    h_MuD0[1]->Write();
    h_MuPt[1]->Write();
    h_MuPt[2]->Write();
    h_MuPt[3]->Write();
    h_MuEta[1]->Write();
    h_MuPhi[1]->Write();
    h_MuTkHits[1]->Write();
    h_MuSAHits[1]->Write();
    h_MuEcal[1]->Write();
    h_MuHcal[1]->Write();
    h_MuTrk[1]->Write();
    h_MuRel[1]->Write();
    h_MuNum[1]->Write();

    h_MuDxy[2]->Write();
    h_MuDz[2]->Write();
    h_MuD0[2]->Write();
    h_MuPt[8]->Write();
    h_MuPt[4]->Write();
    h_MuPt[5]->Write();
    h_MuEta[2]->Write();
    h_MuPhi[2]->Write();
    h_MuTkHits[2]->Write();
    h_MuSAHits[2]->Write();
    h_MuEcal[2]->Write();
    h_MuHcal[2]->Write();
    h_MuTrk[2]->Write();
    h_MuRel[2]->Write();
    h_MuNum[2]->Write();

    h_JetPt[0]->Write();
    h_JetPt[1]->Write();
    h_JetPt[2]->Write();
    h_JetPt[3]->Write();
    h_JetPt[4]->Write();
    h_JetMatch[0]->Write();
    h_JetMatch[1]->Write();
    h_JetMatchDR[0]->Write();
    h_JetMatchDR[1]->Write();
    h_JetEta->Write();
    h_JetPhi->Write();
    h_JetNum[0]->Write();
    h_JetNum[1]->Write();
    h_JetUncert[0]->Write();
    h_JetUncert[1]->Write();
    h_JetBTag->Write();

    h_dRjmu[0]->Write();
    h_dRjmu[1]->Write();
    h_Mmumu->Write();

    h_Mjj[0]->Write();
    h_Mjjmu[0]->Write();
    h_Mjjmu[1]->Write();
    h_Mjjmumu[0]->Write();
    h_Mjj[1]->Write();
    h_Mjjmu[2]->Write();
    h_Mjjmu[3]->Write();
    h_Mjjmumu[1]->Write();
    h_Mjj[2]->Write();
    h_Mjjmu[4]->Write();
    h_Mjjmu[5]->Write();
    h_Mjjmumu[2]->Write();

    h_dEtajjMu[0]->Write();
    h_dEtajjMu[1]->Write();
    h_cosPhiMuMu->Write();
    h_MET[0]->Write();
    h_MET[1]->Write();

    h_MCMuPt[0]->Write();
    h_MCMuPt[1]->Write();
    h_MCMuEta->Write();
    h_MCMuPhi->Write();
    h_MCJetPt->Write();
    h_MCJetPt1->Write();
    h_MCJetPt2->Write();
    h_MCNCosTh[0]->Write();
    h_MCNCosTh[1]->Write();
    h_MCNCosTh[2]->Write();
    h_MCDeltaCTh->Write();
    h_MCNMass[0]->Write();
    h_MCNMass[2]->Write();
    h_MCNMass[1]->Write();
    h_MCWMass->Write();
    h_MC4Mass->Write();

    h_MCCTh1CTh2->Write();


    h_VertBSDelta->Write();

    h_MuRelIsoVtx[0]->Write();
    h_MuRelIsoVtx[1]->Write();
    h_MuRelIsoVtx[2]->Write();
    h_MuRelIsoVtx[3]->Write();
    h_MuRelIsoVtx[4]->Write();
    h_MuRelIsoVtx[5]->Write();
    h_MuRelIsoVtx[6]->Write();
    h_MuRelIsoVtx[7]->Write();
    h_MuRelIsoVtx[8]->Write();

    h_MuEff[0]->Write();
    h_MuEff[1]->Write();
    h_MuEff[2]->Write();
    cout << "wrote histos" << endl;

    //    outfile->ls();
    outfile->Write("", TObject::kOverwrite);
    outfile->Close();
    cout << "wrote root file" << endl;
  }
  else
  {
    cout << "Can't cd to outfile." << endl;
  }
}

Analyzer::~Analyzer()
{}

// void Analyzer::SetName(string name, Float_t version) {
//   UInt_t size = name.length();
//   completename = new Char_t [size+10];
//   strcpy(completename,name.c_str());
//   sprintf (completename,"%s_%.2f.root",completename,version);
//   outfile = new TFile(completename,"RECREATE");
//   cout << "file opened and name " << completename << endl;
// }

void Analyzer::SetName(TString name, Int_t version)
{
  completename = name + "_";
  completename += version;
  completename += ".root";
  outfile = new TFile(completename,"RECREATE");
}

void Analyzer::SetName(string name)
{
  stringstream nstream;
  //  nstream <<  "/uscms/home/wclarida/MajCode/CMSSW_5_3_3_patch2_LQ/test/LQanalyzer/" << name << ".root";
  //  nstream <<  "/uscms/home/wclarida/nobackup/Maj2012/" << name << ".root";
  //  nstream <<  name << ".root";
  nstream <<  "/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Runners/Results/JES_" << name << ".root";
  cout << "filename " << nstream.str() << endl;
  outfile = new TFile(nstream.str().c_str(), "RECREATE");
  cout << "filename " << nstream.str() << endl;
}

void Analyzer::SetWeight(Double_t CrossSection, Double_t nevents)
{
  MCweight = integratedlumi * CrossSection / nevents;
  // lumi *  cs(pb) * gen filter efficiency / MCevents
  cout<<"MCweight = "<<MCweight<<endl;
}

void Analyzer::SetEvtN(Long64_t events)
{
  events ? entrieslimit=events :  entrieslimit=-1;
  cout<<"events "<<events<<endl<<"entrieslimit "<<entrieslimit<<endl;
}

void Analyzer::SetMC(bool isMC)
{
  MC_ = isMC;
  cout << "MC is: " << MC_ << endl;
}

void Analyzer::SetMC(bool isMC, float mass)
{
  MC_ = isMC;
  SigMass_ = mass;
  cout << "MC is: " << MC_ << " Mass is: " << SigMass_ << endl;
}

void Analyzer::SetSys(bool JES_s, bool JER_s, bool PU_s, bool Mu_s, bool MET_s, bool BTag_s)
{
  sys[0] = JES_s;
  sys[1] = JER_s;
  sys[2] = PU_s;
  sys[3] = Mu_s;
  sys[4] = MET_s;
  sys[5] = BTag_s;
}

void Analyzer::TPLoop()
{
  if (fChain == 0) 
    cout << "Ciao!" << endl;

  //  ReweightPU* rwPU = new ReweightPU("MC_PU.root", "Data_PU.root");
  float puw = 1;

  if(outfile->IsWritable())
  {
    cout << "start loop can write" << endl;
  }

  std::set<int> runs;
  if(!entrieslimit || fChain->GetEntries() < entrieslimit || entrieslimit < 0) entrieslimit = fChain->GetEntries();
  cout << "Starting: "  << entrieslimit << " of " << fChain->GetEntries() << endl;
  for (Long64_t jentry = 0; jentry < entrieslimit; jentry++ )
  {
    puw = 1;
    //    if (!(jentry % 1))
    if (!(jentry % 10000))
    {
      cout << "entry  " << jentry <<endl;
    }

    fChain->GetEntry(jentry);
    
    if(MC_)
    {
      //      puw *= rwPU->GetWeight(NInteraction);
    }

    numberVertices = VertexNDF->size();
    int nv = numberVertices;
    h_nVertex[1]->Fill(numberVertices); 
    goodVerticies = new Bool_t [numberVertices];
    if (isGoodEvent(numberVertices, *VertexIsFake, *VertexNDF, *VertexX, *VertexY, *VertexZ, goodVerticies))
    {
      for(UInt_t vv=0; vv<VertexNDF->size(); vv++)
      {
        if(goodVerticies[vv])
        {
          VertexN=vv;
          break;
        }
      }
    }
    else
    {
      VertexN=0;
      cout << "Bad vertex: " << jentry << endl;
      continue;
    }

    std::vector<Lepton> muonTColl;
    std::vector<Lepton> muonPColl;

    MuonTight.SetPt2(20); 
    MuonTight.SetPt1(20); 
    MuonTight.SetEta(2.4); 
    MuonTight.SetRelIso(100); 
    MuonTight.SetChiNdof(20); 
    MuonTight.SetBSdxy(.2);
    MuonTight.SetDz(1);
    MuonTight.SetCalIso(100, 100);
    MuonTight.SetTrkHits(11);
    std::vector<int> pcuts = MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR03ChargedHadron, *MuonPFIsoR03NeutralHadron, *MuonPFIsoR03Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR03PU, muonPColl);// 03
    //std::vector<int> pcuts = MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR04ChargedHadron, *MuonPFIsoR04NeutralHadron, *MuonPFIsoR04Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR04PU, muonPColl);//04

    MuonTight.SetPt2(20); 
    MuonTight.SetPt1(20); 
    MuonTight.SetEta(2.4); 
    MuonTight.SetRelIso(0.12); 
    //    MuonTight.SetRelIso(0.15); 
    MuonTight.SetChiNdof(10); 
    MuonTight.SetBSdxy(.01);
    MuonTight.SetDz(.1);
    MuonTight.SetCalIso(4, 6);
    std::vector<int> tcuts = MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR03ChargedHadron, *MuonPFIsoR03NeutralHadron, *MuonPFIsoR03Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR03PU, muonTColl);//03
    //std::vector<int> tcuts = MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR04ChargedHadron, *MuonPFIsoR04NeutralHadron, *MuonPFIsoR04Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR04PU, muonTColl);//04

    if(muonTColl.size())
    {
      //double Vxy = sqrt(pow((*VertexX)[VertexN],2)+pow((*VertexY)[VertexN],2));
      for(unsigned int ti=0; ti!=muonTColl.size(); ++ti)
      {
        TLorentzVector tm(muonTColl[ti].lorentzVec());
        for(unsigned int pi=0; pi!=muonPColl.size(); ++pi)
        {
          //	cout << "looking at " << pi << endl;
          TLorentzVector pm(muonPColl[pi].lorentzVec());
          if(tm - pm == 0.) continue;
          
          int fillid = 0;
          
          //nv = number of vertices
          if(nv < 10) fillid=0;
          else if(nv < 15) fillid=1;
          else if(nv >= 30) fillid=13;
          else if(nv >= 25) fillid=12;
          else fillid = nv - 13;
          h_TPMassVert[fillid][0]->Fill((tm+pm).M());

          int reg = ((pm.Perp() < 30) ? 0 : 1);
          h_TPMass[0][reg]->Fill((tm+pm).M());
          int pix = muonPColl[pi].ilepton();
          bool id=false;
          bool iso=false;
          bool win=false;
          
          if ( 1
            && fabs(MuonTrkVz->at(pix)-VertexZ->at(VertexN)) < .1
            && sqrt(pow(MuonTrkVx->at(pix)-VertexX->at(VertexN),2)+pow(MuonTrkVy->at(pix)-VertexY->at(VertexN),2)) < .01
            && MuonGlobalChi2->at(pix) < 10
            && MuonIsPF->at(pix)
            && MuonIsGlobal->at(pix)
            && MuonGlobalTrkValidHits->at(pix)
            && MuonTrkPixelHits->at(pix)
            && MuonTrackLayersWithMeasurement->at(pix) > 5
            && MuonStationMatches->at(pix) > 1
          ) id=true;
          
          if ( 1
             && muonPColl[pi].relIso() < 0.1
//             && muonPColl[pi].ecalI() < 4
//              && muonPColl[pi].hcalI() < 6
          ) iso=true;
          
          if( fabs((tm+pm).M() - 91.1876) < 15)
          {
            win = true;
            tpCount[0][reg] += puw;
          }
	  
          if(iso)
            h_TPMassVert[fillid][1]->Fill((tm+pm).M());
          else
            h_TPMassVert[fillid][2]->Fill((tm+pm).M());

          if(id)
          {
            h_TPMass[1][reg]->Fill((tm+pm).M(), puw);
            if(win) tpCount[1][reg] += puw;
            if(iso)
            {
              h_TPMass[2][reg]->Fill((tm+pm).M(), puw);
              h_TPMass[3][reg]->Fill((tm+pm).M(), puw);
              if(win) tpCount[2][reg] += puw;
              if(win) tpCount[3][reg] += puw;
            }
            else
            {
              h_TPMass[5][reg]->Fill((tm+pm).M(), puw);
              if(win) tpCount[5][reg] += puw;
            }
          }
          else if(iso)
          {
            h_TPMass[2][reg]->Fill((tm+pm).M(), puw);
            h_TPMass[4][reg]->Fill((tm+pm).M(), puw);
            if(win) tpCount[2][reg] += puw;
            if(win) tpCount[4][reg] += puw;
          }
          else
          {
            h_TPMass[4][reg]->Fill((tm+pm).M(), puw);
            h_TPMass[5][reg]->Fill((tm+pm).M(), puw);
            h_TPMass[6][reg]->Fill((tm+pm).M(), puw);
            if(win) tpCount[4][reg] += puw;
            if(win) tpCount[5][reg] += puw;
            if(win) tpCount[6][reg] += puw;
          }
          //	cout << "finished " << pi << " " << iso << " " << id << endl;
        }//loop over probes
      }//loop over tags
    }//if at least 1 tag muon
    muonPColl.clear();
    muonTColl.clear();
  }//loop over entries

  if(outfile->IsWritable())
  {
    cout << "end loop can write" << endl;
  }

  cout << "Total pairs: " << tpCount[0][0] << " >20: " << tpCount[0][1] << endl;
  cout << "ID pass pairs: " << tpCount[1][0] << " >20: " << tpCount[1][1] << endl;
  cout << "Iso pass pairs: " << tpCount[2][0] << " >20: " << tpCount[2][1] << endl;
  cout << "both pass pairs: " << tpCount[3][0] << " >20: " << tpCount[3][1] << endl;
  cout << "ID fail pairs: " << tpCount[4][0] << " >20: " << tpCount[4][1] << endl;
  cout << "Iso fail pairs: " << tpCount[5][0] << " >20: " << tpCount[5][1] << endl;
  cout << "both fail pairs: " << tpCount[6][0] << " >20: " << tpCount[6][1] << endl;

}//tploop

void Analyzer::Loop()
{
  cout << "total number of entries " <<nentries<<endl;

  if (debug) cout<< "loop begins" <<endl;

  //reweightPU = new ReweightPU("pileup_NR_m130_14.19.root", "Data_pileup_14.06.root");
  if(!MCweight) MCweight=1; 

  weight=MCweight;

  if (fChain == 0) 
    cout << "Ciao!" << endl;

  //  cout << "Do you want limited events?" <<endl;
  //  cin >> entrieslimit;
  //  if (entrieslimit != -1)
  //    nentries=entrieslimit;
  //  entrieslimit = 1000000;

  std::set<int> runs;
  if(!entrieslimit || fChain->GetEntries() < entrieslimit || entrieslimit < 0) entrieslimit = fChain->GetEntries();
  cout << "Starting: "  << entrieslimit << " of " << fChain->GetEntries() << endl;
  for (Long64_t jentry = 0; jentry < entrieslimit; jentry++ )
  {
    if (!(jentry % 1000)) cout << jentry << endl;

    if (!fChain) cout<<"porcaccia"<<endl;
    fChain->GetEntry(jentry);  // nbytes += nb; // nb = number of bytes read

    //     std::vector<TString> triggerslist;
    //     triggerslist.push_back("HLT_Mu17_TkMu8_v");
    //    if ( !TriggerSelector(triggerslist, *HLTInsideDatasetTriggerNames, *HLTInsideDatasetTriggerDecisions) ) continue;

///  ***PU reweghting*** ///
//   weight_ = noreweight_;// mc weight;
//   h_nvtx_norw->Fill(NInteraction, MCweight);
//   weight = reweightPU->GetWeight(NInteraction)*MCweight;
//   h_nvtx_rw->Fill(NInteraction, weight);
    
    numberVertices = VertexNDF->size();
    goodVerticies = new Bool_t [numberVertices];
    h_nVertex[1]->Fill(numberVertices);
    if (isGoodEvent(numberVertices, *VertexIsFake, *VertexNDF, *VertexX, *VertexY, *VertexZ, goodVerticies) ) cuts[21] = true;
    if(cuts[21])
    {
      for(UInt_t vv=0; vv<VertexNDF->size(); vv++)
      {
        if(goodVerticies[vv])
        {
          VertexN=vv;
          break;
        }
      }
    }
    else
    {
      VertexN=0;
      //      cout << "Bad vertex: " << jentry << endl;
    }
    ///// STARTING WITH PHYSICS OBJECTS COLLECTIONS /////

    std::vector<Lepton> muonColl;
    std::vector<Lepton> muonS1Coll;
    std::vector<Lepton> muonTColl;

    MuonTight.SetSys(sys[3]);

    //Loose Muon Collection = muonColl
    MuonTight.SetEta(2.4); 
    MuonTight.SetPt2(10);
    MuonTight.SetPt1(10);
    MuonTight.SetPt(10);
    MuonTight.SetRelIso(0.2);
    MuonTight.SetChiNdof(100); 
    MuonTight.SetBSdxy(100);
    MuonTight.SetDz(100);
    MuonTight.SetCalIso(100, 100);
    MuonTight.SetTrkHits(0);
    //MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR04ChargedHadron, *MuonPFIsoR04NeutralHadron, *MuonPFIsoR04Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR04PU, muonColl);//04
    MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR03ChargedHadron, *MuonPFIsoR03NeutralHadron, *MuonPFIsoR03Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR03PU, muonColl);//03

    MuonTight.SetPt2(10); 
    MuonTight.SetPt1(10); 
    MuonTight.SetEta(2.4); 
    MuonTight.SetRelIso(0.4); 
    MuonTight.SetChiNdof(50); 
    MuonTight.SetBSdxy(.2);
    MuonTight.SetDz(1);
    //MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR04ChargedHadron, *MuonPFIsoR04NeutralHadron, *MuonPFIsoR04Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR04PU, muonS1Coll);
    //MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR03ChargedHadron, *MuonPFIsoR03NeutralHadron, *MuonPFIsoR03Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR03PU, muonS1Coll);//03

    MuonTight.SetPt1(20); 
    MuonTight.SetPt2(20);
    MuonTight.SetRelIso(.05);
    MuonTight.SetChiNdof(10);
    MuonTight.SetBSdxy(0.005);
    MuonTight.SetCalIso(4, 6);
    MuonTight.SetDz(0.1);
    //std::vector<int> MuCuts = MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR04ChargedHadron, *MuonPFIsoR04NeutralHadron, *MuonPFIsoR04Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR04PU, muonTColl);
    std::vector<int> MuCuts = MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR03ChargedHadron, *MuonPFIsoR03NeutralHadron, *MuonPFIsoR03Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR03PU, muonTColl);//03

    //bool goodCharge = false;
    double Vz = VertexZ->at(VertexN);
    double Vxy = sqrt(pow(VertexX->at(VertexN),2)+pow(VertexY->at(VertexN),2));
    h_MuNum[1]->Fill(muonTColl.size());
    if(muonTColl.size() > 0) h_MuPt[2]->Fill(muonTColl[0].lorentzVec().Perp());
    if(muonTColl.size() > 1) h_MuPt[3]->Fill(muonTColl[1].lorentzVec().Perp());
    for(unsigned int m1=0; m1!=muonTColl.size(); ++m1)
    {
      int mix = muonTColl[m1].ilepton();
      //      h_MuDz[1]->Fill(fabs(muonTColl[m1].dz_BS()));
      h_MuDz[1]->Fill(fabs(muonTColl[m1].dz_BS()-Vz));
      h_MuDxy[1]->Fill(fabs(muonTColl[m1].dxy_BS()-Vxy));
      h_MuD0[1]->Fill(fabs(muonTColl[m1].D0()));
      h_MuPt[1]->Fill(muonTColl[m1].lorentzVec().Perp());
      h_MuEta[1]->Fill(muonTColl[m1].eta());
      h_MuPhi[1]->Fill(muonTColl[m1].lorentzVec().Phi());
      //      h_MuTkHits[1]->Fill(muonTColl[m1].tkH());
      //       h_MuSAHits[1]->Fill(muonTColl[m1].SAH());
      float eI = MuonEcalVetoIso->at(mix);
      h_MuEcal[1]->Fill(eI);
      float hI = MuonHcalVetoIso->at(mix);
      h_MuHcal[1]->Fill(hI);
      h_MuRel[1]->Fill(muonTColl[m1].relIso());
      h_MuRelIso[3]->Fill(MuonPFIsoR04ChargedHadron->at(mix));
      h_MuRelIso[4]->Fill(MuonPFIsoR04NeutralHadron->at(mix));
      h_MuRelIso[5]->Fill(MuonPFIsoR04Photon->at(mix));

      for(unsigned int m2=m1+1; m2!=muonTColl.size(); ++m2)
      {
        if ( muonTColl[m1].charge()*muonTColl[m2].charge() > 0 && muonTColl[m1].lorentzVec().Pt() >=20 )
        {
          //goodCharge = true; //also check to make sure high pt of pair is the one above 20 GeV
          cuts[22] = true; //two muons with proper pt and same charge
        }
      }
    }

    h_MuNum[2]->Fill(muonS1Coll.size());
    
    if(muonS1Coll.size() > 0) h_MuPt[4]->Fill(muonS1Coll[0].lorentzVec().Perp());
    if(muonS1Coll.size() > 1) h_MuPt[5]->Fill(muonS1Coll[1].lorentzVec().Perp());
    
    for(unsigned int m1=0; m1!=muonS1Coll.size(); ++m1)
    {
      int mix = muonS1Coll[m1].ilepton();
      h_MuDz[2]->Fill(fabs(muonS1Coll[m1].dz_BS()-Vz));
      //      h_MuDz[2]->Fill(fabs(muonS1Coll[m1].dz_BS()));
      h_MuDxy[2]->Fill(fabs(muonS1Coll[m1].dxy_BS()-Vxy));
      h_MuD0[2]->Fill(fabs(muonS1Coll[m1].D0()));
      h_MuPt[8]->Fill(muonS1Coll[m1].lorentzVec().Perp());
      h_MuEta[2]->Fill(muonS1Coll[m1].eta());
      h_MuPhi[2]->Fill(muonS1Coll[m1].lorentzVec().Phi());
      //       h_MuTkHits[2]->Fill(muonS1Coll[m1].tkH());
      //       h_MuSAHits[2]->Fill(muonS1Coll[m1].SAH());
      float eI = MuonEcalVetoIso->at(mix);
      h_MuEcal[2]->Fill(eI);
      float hI = MuonHcalVetoIso->at(mix);
      h_MuHcal[2]->Fill(hI);
      h_MuRel[2]->Fill(muonS1Coll[m1].relIso());
      h_MuRelIso[6]->Fill(MuonPFIsoR04ChargedHadron->at(mix));
      h_MuRelIso[7]->Fill(MuonPFIsoR04NeutralHadron->at(mix));
      h_MuRelIso[8]->Fill(MuonPFIsoR04Photon->at(mix));
    }

    h_MuNum[0]->Fill(muonColl.size());
    
    for(unsigned int m1=0; m1!=muonColl.size(); ++m1)
    {
      int mix = muonColl[m1].ilepton();
      h_MuDz[0]->Fill(fabs(muonColl[m1].dz_BS()-Vz));
      //      h_MuDz[0]->Fill(fabs(muonColl[m1].dz_BS()));
      h_MuDxy[0]->Fill(fabs(muonColl[m1].dxy_BS()-Vxy));
      h_MuD0[0]->Fill(fabs(muonColl[m1].D0()));
      h_MuPt[0]->Fill(muonColl[m1].lorentzVec().Perp());
      h_MuEta[0]->Fill(muonColl[m1].eta());
      h_MuPhi[0]->Fill(muonColl[m1].lorentzVec().Phi());
      //       h_MuTkHits[0]->Fill(muonColl[m1].tkH());
      //       h_MuSAHits[0]->Fill(muonColl[m1].SAH());
      float eI = MuonEcalVetoIso->at(mix);
      h_MuEcal[0]->Fill(eI);
      float hI = MuonHcalVetoIso->at(mix);
      h_MuHcal[0]->Fill(hI);
      h_MuTrk[0]->Fill(MuonPFIsoR04ChargedHadron->at(muonColl[m1].ilepton())); 
      h_MuRel[0]->Fill(muonColl[m1].relIso());
      h_MuRelIso[0]->Fill(MuonPFIsoR04ChargedHadron->at(mix));
      h_MuRelIso[1]->Fill(MuonPFIsoR04NeutralHadron->at(mix));
      h_MuRelIso[2]->Fill(MuonPFIsoR04Photon->at(mix));
    }
    
    if(muonColl.size())
    {
      h_MuPt[6]->Fill(muonColl[0].lorentzVec().Perp());
      if(muonColl.size() > 1)
      {
        h_MuPt[7]->Fill(muonColl[1].lorentzVec().Perp());
      }
    }
    
    for(unsigned int i=0; i!=MuCuts.size(); ++i)
    {
      if(MuCuts[i] >=2) cuts[i] = true;
    }// take care of most muon cuts (2 muons passing each cut) 2 exeptions taken care of below
    
    if(MuCuts[10]) cuts[10] = true; //only need 1 muon > 20  
    //    cuts[10] = cuts[11];//only want 2 greater than 10
    //    goodCharge = cuts[12] || cuts[13];
    cuts[14] = cuts[14] && cuts[10] && (cuts[12] || cuts[13]);//before only checked for 2 muons above 10
    
    if(cuts[11])
    {
      //if(MuCuts[10] >= 2) weight = .9829*.9829;
      //else if(cuts[10]) weight = .9829*.9754;
      //else weight = .9754*.9754;
      weight = 0.99 * 0.99;
    }
    else weight = 0;
    
    weight = weight*.94; //MC scale * trigger eff
    weight = 1;// for now no rewieghting of events
    //    weight = .weight*98*.98 //muon systematic

    cuts[24] = cuts[12] || cuts[13];
    for(int i=1; i!=7; ++i)
    {
      cuts[24] = cuts[i] && cuts[24];
    }
    cuts[25] = cuts[7] && cuts[8] && cuts[0] && (cuts[12] || cuts[13]);

    /// ***simple check for double muon invariant mass and 3rd lepton Z veto*** ///
    cuts[18] = LowMassVeto(muonTColl);
    cuts[19] = looseMuonDeltaRVeto(muonColl);  //if looseMuonDeltaR and only 2 muons with looseMuons, if three muons, kill the event.
    
    std::vector<Lepton> electronTightColl;
    ElectronTight.SetPt(20);
    ElectronTight.SetEta(2.4); 
    ElectronTight.SetRelIso(0.15);
    ElectronTight.SetBSdxy(0.01);
    ElectronTight.ElectronSelection(*ElectronIsEB, *ElectronIsEE, *ElectronHasTrackerDrivenSeed, *ElectronHasEcalDrivenSeed, *ElectronEta, *ElectronPhi, *ElectronPt, *ElectronEnergy, *ElectronTrkIsoDR03, *ElectronEcalIsoDR03, *ElectronHcalIsoDR03, *ElectronCharge, *ElectronGsfCtfScPixCharge, *ElectronMissingHitsEG, *ElectronHasMatchedConvPhot, *ElectronDeltaEtaTrkSC, *ElectronDeltaPhiTrkSC, *ElectronSigmaIEtaIEta, *ElectronHoE, *ElectronCaloEnergy, *ElectronESuperClusterOverP, *ElectronTrackVx, *ElectronTrackVy, *ElectronTrackVz, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), rhoJets, electronTightColl);

    JetsVeto.SetSys(sys[0], sys[1],sys[5]);
    std::vector<Jet> jetCollS1;    
    //JetsVeto.SetPt(20);
    //JetsVeto.SetEta(2.4);
    //JetsVeto.JetSelectionLeptonVeto(*PFJetPassLooseID, *PFJetEta, *PFJetPhi, *PFJetPt, *PFJetEnergy, *PFJetNeutralEmEnergyFraction, *PFJetNeutralHadronEnergyFraction, *PFJetChargedEmEnergyFraction, *PFJetChargedHadronEnergyFraction, *PFJetChargedMultiplicity, *PFJetNConstituents, *PFJetCombinedSecondaryVertexBTag, electronTightColl, muonTColl, jetCollS1);
    std::vector<Jet> jetCollVeto;
    JetsVeto.SetPt(20);
    JetsVeto.SetEta(2.4);
    JetsVeto.JetSelectionLeptonVeto(*PFJetPassLooseID, *PFJetEta, *PFJetPhi, *PFJetPt, *PFJetEnergy, *PFJetNeutralEmEnergyFraction, *PFJetNeutralHadronEnergyFraction, *PFJetChargedEmEnergyFraction, *PFJetChargedHadronEnergyFraction, *PFJetChargedMultiplicity, *PFJetNConstituents, *PFJetCombinedSecondaryVertexBTag, *PFJetJECUnc, electronTightColl, muonTColl, jetCollVeto);

    if (debug) cout<<"Selection done"<<endl;

    MET = PFMET->at(0);
    
    if(MET < 50)
    {
      if(sys[4] && 1.06*MET < 40) cuts[30] = true;
      else cuts[30] = true;
    }
    h_MET[0]->Fill(MET);
    //    h_METsign->Fill(PFMETSig->at(0));

    int jetid[2] = {-1, -1};
    float minmassdiff = 9999;
    if(jetCollVeto.size() >= 2 && jetCollVeto.size() <= 6) //between 2-6 for Low mass, 2-5 for Mid Mass and High Mass
    {
      cuts[20] = true;
      cuts[36] = true;
      cuts[39] = true;
      for(unsigned int j1i=0; j1i!=jetCollVeto.size(); ++j1i)
      {
        for(unsigned int j2i=j1i+1; j2i!=jetCollVeto.size(); ++j2i)
        {
          TLorentzVector W;
          if(SigMass_ > 81)
          {
            W = jetCollVeto[j1i].lorentzVec() + jetCollVeto[j2i].lorentzVec();
          }
          else if (muonTColl.size() > 1)
          {
            W = jetCollVeto[j1i].lorentzVec() + jetCollVeto[j2i].lorentzVec() + muonTColl[0].lorentzVec() + muonTColl[1].lorentzVec();
          }
          if(fabs(W.M()-80.385) < minmassdiff)
          {
            jetid[0] = j1i;
            jetid[1] = j2i;
            minmassdiff = W.M();
          }
        }//2nd loop over jets
        //if(j1i != -1) Warren, WTF
        {
          if (jetCollVeto[j1i].getBTag() > 1) cuts[36] = false; //0-no btag; 1-loose; 2-medium; 3-tight;
          if (jetCollVeto[j1i].getBTag() > 2) cuts[39] = false; //0-no btag; 1-loose; 2-medium; 3-tight;
          h_JetBTag->Fill(jetCollVeto[j1i].getBTag());
          h_JetEta->Fill(jetCollVeto[j1i].lorentzVec().Eta());
          h_JetPhi->Fill(jetCollVeto[j1i].lorentzVec().Phi());
        }
      }//loop over jets
      if(jetid[0] < 0 || jetid[1] < 0)
      {
        cout << "Two jets but max mass diff to small" << endl;
      }
    }//find 2 best jets
    
    int jm[2]= {-1, -1};
    float jmdr[2]= {1000, 1000};
    float jpt[2] = {-1, -1};
    h_JetNum[0]->Fill(jetCollVeto.size());
    for(unsigned int ji=0; ji!=jetCollVeto.size(); ++ji)
    {
       // if(jetCollVeto[ji].lorentzVec().Perp() > jpt[1]){
       // if(jetCollVeto[ji].lorentzVec().Perp() > jpt[0]){
       // jpt[1] = jpt[0];
       // jpt[0] = jetCollVeto[ji].lorentzVec().Perp();
       // }
       // else
       // jpt[1] = jetCollVeto[ji].lorentzVec().Perp();
       // }
       // h_JetUncert[1]->Fill(Jet_uncminus[jetCollVeto[ji].ijet()]);
      for(unsigned int mi=0; mi!=2 && mi!=muonTColl.size(); ++mi)
      {
        if(jetCollVeto[ji].lorentzVec().DeltaR(muonTColl[mi].lorentzVec()) < jmdr[mi])
        {
          jm[mi] = ji;
          jmdr[mi] = jetCollVeto[ji].lorentzVec().DeltaR(muonTColl[mi].lorentzVec());
        }
      }
    }
    // for(int aji=0; aji!=Njet; ++aji){
    // h_JetUncert[0]->Fill(Jet_uncminus[aji]);
    // }
    // if(jpt[0] < 20) cuts[20] = false;
    if(cuts[20] && jetid[0] != -1 && jetid[1] != -1)
    {
      jpt[0] = jetCollVeto[jetid[0]].lorentzVec().Perp();
      jpt[1] = jetCollVeto[jetid[1]].lorentzVec().Perp();
      h_JetPt[0]->Fill(jpt[0]);
      h_JetPt[1]->Fill(jpt[0]);
      h_JetPt[0]->Fill(jpt[1]);
      h_JetPt[2]->Fill(jpt[1]);
    }
    if(jm[0] != -1)
    {
      h_dRjmu[0]->Fill(jetCollVeto[jm[0]].lorentzVec().DeltaR(muonTColl[0].lorentzVec()));
      if(jm[1] != -1)
      {
        h_dRjmu[1]->Fill(jetCollVeto[jm[1]].lorentzVec().DeltaR(muonTColl[0].lorentzVec()));
      }
    }
    if(muonTColl.size() > 1)
    {
      h_Mmumu->Fill((muonTColl[0].lorentzVec() + muonTColl[2].lorentzVec()).M());
      h_cosPhiMuMu->Fill(cos(muonTColl[0].lorentzVec().DeltaPhi(muonTColl[2].lorentzVec())));
    }

    cuts[28] = 1
      && muonS1Coll.size()>=2  //2 loose muons
      && jetCollS1.size()>=2 // 2 jets above 10
      && ZVeto(muonS1Coll) && LowMassVeto(muonS1Coll) && cuts[21];  //mu mass, z veto, vertex
    if(cuts[28]) cuts[28] = jetCollS1[0].lorentzVec().Perp() > 20; // 1 jet above 20
    
    cuts[29] = 1
      && cuts[28] //sel 1
      && muonTColl.size()>=2 //2 tight muons (both at least over 10))
      && cuts[18] && cuts[19]; //mu mass and z veto tight muons
    cuts[23] = cuts[22] && cuts[20] && cuts[21] && cuts[19] && cuts[18] && cuts[36]; //muon, jet, vertex, 3rd muon veto, mu mass, btag
    
    if (cuts[23])
    {
      float massjjll = ((jetCollVeto[jetid[0]].lorentzVec() + jetCollVeto[jetid[1]].lorentzVec() + muonTColl[1].lorentzVec() + muonTColl[0].lorentzVec()).M());
      float massjj = (jetCollVeto[jetid[0]].lorentzVec() + jetCollVeto[jetid[1]].lorentzVec()).M();
      int njetsLM = 0; // Number of Jets above PT 20
      int njetsH = 0; // Number jets above PT 30
      
      for (unsigned int ji = 0; ji != jetCollVeto.size(); ++ji)
      {
        if (jetCollVeto[ji].lorentzVec().Perp() > 20) njetsLM++;
        if (jetCollVeto[ji].lorentzVec().Perp() > 30) njetsH++;
      }
      
      
      //Low Mass Region Pass
      if ( massjj < 150 && massjjll < 250 && njetsLM < 6 && MET < 40)
      {
        cuts[40] = true;
      }
      //Mid Mass Region Pass
      if (massjj > 50 && massjj < 110 && MET < 40 && njetsLM < 5)
      {
        cuts[41] = true;
      }
      //High Mass Region Pass
      if (massjj > 60 && massjj < 120  && MET < 50 && njetsH < 5)
      {
        cuts[42] = true && jetCollVeto[jetid[1]].lorentzVec().Perp() > 30;
      }
      
    }
    
    
    cuts[27] = cuts[23] && cuts[26]; // all and trig
    cuts[31] = cuts[30] && cuts[23]; //met and all
    cuts[32] = cuts[31] && cuts[26]; // met and trig
    cuts[33] = cuts[18] && cuts[19] && cuts[30] && cuts[21];  //just failing met, mass low, and z
    cuts[34] = cuts[18] && cuts[19] && cuts[30] && cuts[21] && cuts[20];  //just failing met, mass low, z, and jets
    cuts[35] = cuts[18] && cuts[19] && cuts[30] && cuts[21] && cuts[22];  //just failing met, mass low, z, and muons

    //    totalE += puw;
    for(unsigned int i=0; i!=cuts.size(); ++i)
    {
      if(cuts[i])
      {
        ++ePerCut[i]; 
        // ePerCutPU[i] += puw;
        // sEvents[i] += weight*puw;
      }
      //if(cuts[i]) {ePerCut[i] += puw; sEvents[i] += weight*puw;}
    }

    if(cuts[28])//if Sel1 event
    {
      h_Mjj[0]->Fill((jetCollS1[0].lorentzVec() + jetCollS1[1].lorentzVec()).M());
      h_Mjjmu[0]->Fill((jetCollS1[0].lorentzVec() + jetCollS1[1].lorentzVec() + muonS1Coll[0].lorentzVec()).M());
      h_Mjjmu[1]->Fill((jetCollS1[0].lorentzVec() + jetCollS1[1].lorentzVec() + muonS1Coll[1].lorentzVec()).M());
      h_Mjjmumu[0]->Fill((jetCollS1[0].lorentzVec() + jetCollS1[1].lorentzVec() + muonS1Coll[1].lorentzVec() + muonS1Coll[0].lorentzVec()).M());
    }

    if(cuts[29])//if Sel2 event
    {
      h_Mjj[1]->Fill((jetCollS1[0].lorentzVec() + jetCollS1[1].lorentzVec()).M());
      h_Mjjmu[2]->Fill((jetCollS1[0].lorentzVec() + jetCollS1[1].lorentzVec() + muonTColl[0].lorentzVec()).M());
      h_Mjjmu[3]->Fill((jetCollS1[0].lorentzVec() + jetCollS1[1].lorentzVec() + muonTColl[1].lorentzVec()).M());
      h_Mjjmumu[1]->Fill((jetCollS1[0].lorentzVec() + jetCollS1[1].lorentzVec() + muonTColl[1].lorentzVec() + muonTColl[0].lorentzVec()).M());
    }

    //    if(cuts[27]){//if good event
    if(cuts[23])//if good event
    {
      h_Mjj[2]->Fill((jetCollVeto[jetid[0]].lorentzVec() + jetCollVeto[jetid[1]].lorentzVec()).M());
      h_Mjjmu[4]->Fill((jetCollVeto[jetid[0]].lorentzVec() + jetCollVeto[jetid[1]].lorentzVec() + muonTColl[0].lorentzVec()).M());
      h_Mjjmu[5]->Fill((jetCollVeto[jetid[0]].lorentzVec() + jetCollVeto[jetid[1]].lorentzVec() + muonTColl[1].lorentzVec()).M());
      h_Mjjmumu[2]->Fill((jetCollVeto[jetid[0]].lorentzVec() + jetCollVeto[jetid[1]].lorentzVec() + muonTColl[1].lorentzVec() + muonTColl[0].lorentzVec()).M());
      h_dEtajjMu[0]->Fill(fabs((jetCollVeto[jetid[0]].lorentzVec() + jetCollVeto[jetid[1]].lorentzVec()).Eta() - muonTColl[0].lorentzVec().Eta()));
      h_dEtajjMu[1]->Fill(fabs((jetCollVeto[jetid[0]].lorentzVec() + jetCollVeto[jetid[1]].lorentzVec()).Eta() - muonTColl[1].lorentzVec().Eta()));
      h_MET[1]->Fill(MET);
      h_JetNum[1]->Fill(jetCollVeto.size());    
    }

    if(MC_)
    {
      //    this.MCLoop();
      //MCLoop();

      if(Q1.Perp() != 0 && Q2.Perp() !=0)
      {
        int j1[3]={0,0,0};
        int j2[3]={0,0,0};
        TLorentzVector jtmp[3];
        for(unsigned int ji=1; ji<PFJetPt->size(); ++ji)
        {
          jtmp[0].SetPtEtaPhiE(PFJetPt->at(ji), PFJetEta->at(ji), PFJetPhi->at(ji), PFJetEnergy->at(ji));
          jtmp[1].SetPtEtaPhiE(PFJetPt->at(j1[0]), PFJetEta->at(j1[0]), PFJetPhi->at(j1[0]), PFJetEnergy->at(j1[0]));
          jtmp[2].SetPtEtaPhiE(PFJetPt->at(j2[0]), PFJetEta->at(j2[0]), PFJetPhi->at(j2[0]), PFJetEnergy->at(j2[0]));
          float drq1t = jtmp[0].DeltaR(Q1);
          float drq11 = jtmp[1].DeltaR(Q1);
          float drq12 = jtmp[2].DeltaR(Q1);
          float drq2t = jtmp[0].DeltaR(Q2);
          float drq22 = jtmp[2].DeltaR(Q2);
          if(drq1t < drq11)//is new jet closer to Q1
          {
            if(drq1t > drq2t && drq22 >  drq2t) //is new jet closer to Q2 than Q1 and is new jet closer to Q2
            {
              if(drq11 > drq12 )//is old Q2 match closer to Q1 than current Q1 match
              {
                j1[0] = j2[0];
              }
              j2[0] = ji;
            }
            else//just closer to Q1
            {
              j1[0] = ji;
            }
          }//is new jet closer to Q1
          else if(drq2t < drq22)//is new jet closer to Q2
          {
            if(drq12 > drq12 )//is old Q2 match closer to Q1 than current Q1 match
            {
              j1[0] = j2[0];
            }
            j2[0] = ji;
          }
        }//loop over pfjets
          
        if(j2[0] != j1[0])
        {
          h_JetMatchDR[0]->Fill(jtmp[1].DeltaR(Q1));
          h_JetMatchDR[1]->Fill(jtmp[2].DeltaR(Q2));
          
          if(jtmp[1].DeltaR(Q1) < 0.2)
          {
            h_JetPt[3]->Fill(PFJetPt->at(j1[0]));
            h_JetMatch[0]->Fill(j1[0]);
          }
          
          if(jtmp[2].DeltaR(Q2) < 0.2)
          {
            h_JetPt[4]->Fill(PFJetPt->at(j2[0]));
            h_JetMatch[1]->Fill(j2[0]);
          }
        }
        else if(PFJetPt->size() > 1)
        {
        //cout << "Found the same jet matches both 1: " << j1[0] << " 2: " << j2[0] << endl;
        }
      }//did i find a Q1 and Q2
    }

    muonS1Coll.clear();
    muonTColl.clear();
    muonColl.clear();
    jetCollVeto.clear();
    cuts.clear();
    cuts.resize(numCuts, false);
  }
  if (debug) cout<< "out of the loop" <<endl;

   cout << completename << " " << endl;
   //  cout << "For total events after PURW: " << totalE << " with " << entrieslimit;
   fstream dataOutFileFull;
   fstream dataOutFileAppended;
   
   dataOutFileFull.open("/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Runners/Results/baseline_FULL_JES.txt",fstream::app|fstream::out);
   dataOutFileFull << "REPLACEME1" << endl;
   
   dataOutFileAppended.open("/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Runners/Results/baseline_APPENDED_JES.csv",fstream::app|fstream::out);
   dataOutFileAppended << "REPLACEME1,";

   for(unsigned int i=0; i!=ePerCut.size(); ++i)
   {
      //cout << CutName[i] << ": " << ePerCut[i] << " " << ePerCutPU[i] << " " << sEvents[i] << " " << endl;//sEvents[i]/totalE << endl;
      dataOutFileFull << CutName[i] << "," << ePerCut[i] << ",";//<< ePerCutPU[i] << "\t" << sEvents[i] << "\t" << endl;//sEvents[i]/totalE << endl;
   }
   
//   for(unsigned int i = 0; i != ePerCut.size(); ++i)
//   {
//      if (i == 3 || i == 4 || i == 5 || i == 6 || i == 9 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 16 || i == 17 || i == 28 || i == 29 || i == 32 || i == 33 || i == 34 || i == 35) continue;
//      cout << CutName[i] << ": " << ePerCut[i] << " " << ePerCutPU[i] << " " << sEvents[i] << " " << endl;//sEvents[i]/totalE << endl;
//      dataOutFileAppended << ePerCut[i] << "\t";// << ePerCutPU[i] << "\t" << sEvents[i] << "\t" << endl;//sEvents[i]/totalE << endl;
//   }
   
   dataOutFileAppended << ePerCut[21] << ",";
   dataOutFileAppended << ePerCut[2] << ",";
   dataOutFileAppended << ePerCut[0] << ",";
   dataOutFileAppended << ePerCut[1] << ",";
   dataOutFileAppended << ePerCut[11] << ",";
   dataOutFileAppended << ePerCut[18] << ",";
   dataOutFileAppended << ePerCut[19] << ",";
   dataOutFileAppended << ePerCut[20] << ",";
   dataOutFileAppended << ePerCut[39] << ",";
   dataOutFileAppended << ePerCut[36] << ",";
   dataOutFileAppended << ePerCut[30] << ",";
   dataOutFileAppended << ePerCut[40] << ",";
   dataOutFileAppended << ePerCut[41] << ",";
   dataOutFileAppended << ePerCut[42] << ",";
   
   cout << endl;
   dataOutFileFull << endl;
   dataOutFileFull.close();
   dataOutFileAppended << endl;
   dataOutFileAppended.close();
  //   outfile->cd();
  //   outfile->Close();
}

void Analyzer::MCLoop()
{
  if(GenParticlePx->size() < 12) return;

  int mdi = 0;
  int msi = 0;
  int ni = 0;
  for(unsigned int i=0; i!=GenParticlePx->size(); ++i)
  {
    int id = GenParticlePdgId->at(i);
    int midx = GenParticleMotherIndex->at(i);
    if(GenParticleStatus->at(i) == 3 && abs(id) == 13)
    {
      if(abs(GenParticlePdgId->at(midx)) == 90)
      {
        mdi = i;
        ni = midx;
      }
      else msi = i;
      //      break;
    }
//    else if(GenParticleStatus->at(i) != 3 && (abs(id) == 13 || abs(id) == 90 || abs(id) == 24)){
//    if(GenParticleStatus->at(i) != 3 && (abs(id) == 13 || abs(id) == 90 || abs(id) == 24)){
//       cout << "i: " << i << " status: " << GenParticleStatus->at(i)
// 	   << " id: " << GenParticlePdgId->at(i) << " Mother idx: " 
//    	   << GenParticleMotherIndex->at(i) << " Mother id: "
//  	   << GenParticlePdgId->at(GenParticleMotherIndex->at(i))
//   	   << endl;
//       if(abs(id) == 90 && GenParticlePdgId->at(GenParticleMotherIndex->at(i)) == id){
// 	ni = i;
//       }
//       else if(abs(id) == 13 && GenParticleStatus->at(i) == 1){
// 	int p = GenParticleMotherIndex->at(i);
// 	while(GenParticleStatus->at(p) != 3){
// 	  p = GenParticleMotherIndex->at(p);
// 	}//get status 3 muon
// 	if(fabs(GenParticlePdgId->at(GenParticleMotherIndex->at(p))) == 90){
// 	  mdi = i;
// 	}//if mother is NR
// 	else{
// 	  msi = i;
// 	}//else is sister
//       }
//     }//if not stat 3 and muon, NR, or W
  }//loop over particles
  //  cout << endl << endl << endl;

//   if(mdi != 9 || msi != 7 || ni != 8)
//     cout << "Dau: " << mdi << " Sis: " << msi << " N: " << ni << endl;

  Msis.SetPxPyPzE(GenParticlePx->at(msi), GenParticlePy->at(msi), GenParticlePz->at(msi), GenParticleEnergy->at(msi));
  Mdau.SetPxPyPzE(GenParticlePx->at(mdi), GenParticlePy->at(mdi), GenParticlePz->at(mdi), GenParticleEnergy->at(mdi));
  Q1.SetPxPyPzE(GenParticlePx->at(12), GenParticlePy->at(12), GenParticlePz->at(12), GenParticleEnergy->at(12));
  Q2.SetPxPyPzE(GenParticlePx->at(11), GenParticlePy->at(11), GenParticlePz->at(11), GenParticleEnergy->at(11));
  NR.SetPxPyPzE(GenParticlePx->at(ni),  GenParticlePy->at(ni),  GenParticlePz->at(ni),  GenParticleEnergy->at(ni));
  TLorentzVector MsS = Msis;
  TLorentzVector MdS = Mdau;
  if(Q1.Perp() < Q2.Perp())
  {
    TLorentzVector tmp = Q1;
    Q1 = Q2;
    Q2 = tmp;
//     Q1 = Q1+Q2;
//     Q2 = Q1-Q2;
//     Q1 = Q1-Q2;
  }
  if(fabs((Mdau+Q1+Q2).M()-SigMass_) > fabs((Msis+Q1+Q2).M()-SigMass_))
  {
    TLorentzVector tmp = Mdau;
    Mdau = Msis;
    Msis = tmp;
  }
  TLorentzVector Lab = Msis+Mdau+Q1+Q2;
  TVector3 Sys = (Msis+Mdau+Q1+Q2).BoostVector();
  MsS.Boost(-Sys);
  MdS.Boost(-Sys);
  TLorentzVector Nfake = Msis + Q1 + Q2;
  TLorentzVector Nreal = Mdau + Q1 + Q2;
//   if((Nfake-NR).Mag2() < (Nreal-NR).Mag2()){
//     TLorentzVector tmp = Nfake;
//     Nfake = Nreal;
//     Nreal = tmp;
//   }
  TLorentzVector NfS = Nfake;
  TLorentzVector NrS = Nreal;
  h_MCMuPt[0]->Fill(Msis.Perp());
  h_MCMuPt[1]->Fill(Mdau.Perp());
  h_MCMuEta->Fill(Msis.Eta());
  h_MCMuEta->Fill(Mdau.Eta());
  h_MCMuPhi->Fill(Msis.Phi());
  h_MCMuPhi->Fill(Mdau.Phi());
  h_MCJetPt->Fill(Q1.Perp());
  h_MCJetPt->Fill(Q2.Perp());
  h_MCJetPt1->Fill(Q1.Perp());
  h_MCJetPt2->Fill(Q2.Perp());

  h_MCNMass[0]->Fill(Nreal.M());
  h_MCNMass[1]->Fill(Nfake.M());
  h_MCNMass[2]->Fill(NR.M());
  h_MCWMass->Fill((Q1+Q2).M());
  h_MC4Mass->Fill(Lab.M());
  //   TH1F* h_MCNCosTh[3];
  //   TH1F* h_MCDeltaCTh;
  //   TH2F* h_MCCTh1CTh2;
//   NfS.Boost(-Sys);
//   NrS.Boost(-Sys);
//   TVector3 z(0, 0, 1);
//   double cTh[3];
//   cTh[0] = cos(Lab.Angle(NrS.Vect()));
//   cTh[1] = cos(Lab.Angle(NfS.Vect()));
//   cTh[2] = cos(NR.Angle(z));
  
//   double cyTh[2];
//   cyTh[0] = cos(Lab.Angle(MdS.Vect()));
//   cyTh[1] = cos(Lab.Angle(MsS.Vect()));
}
