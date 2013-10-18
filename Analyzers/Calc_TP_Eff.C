#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFitResult.h"

#include <iostream>

using namespace std;

void Calc_TP_Eff(){
  TFile* fZ = new TFile("/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Data/TagAndProbe/Inputs/DY_NoRegion_RI_005.root");
  //  TFile* fd = new TFile("Singlemu_2011_NewTP_8.45.root");
  TFile* fd = new TFile("/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Data/TagAndProbe/Inputs/Data_TP_NoRegion_RI_005.root");

  TH1F* ZIs_a[3];
  TH1F* dIs_a[3];
  //TH1F* ZIs_b[3];
  //TH1F* dIs_b[3];
  TH1F* ZId_a[3];
  TH1F* dId_a[3];
  //TH1F* ZId_b[3];
  //TH1F* dId_b[3];

  ZIs_a[0] = (TH1F*) fZ->Get("TP_dimuMass_a30_All");
  //ZIs_b[0] = (TH1F*) fZ->Get("TP_dimuMass_b30_All");

  ZIs_a[1] = (TH1F*) fZ->Get("TP_dimuMass_a30_Isop");
  ZIs_a[2] = (TH1F*) fZ->Get("TP_dimuMass_a30_Isof");
  //ZIs_b[1] = (TH1F*) fZ->Get("TP_dimuMass_b30_Isop");
  //ZIs_b[2] = (TH1F*) fZ->Get("TP_dimuMass_b30_Isof");
  ZId_a[1] = (TH1F*) fZ->Get("TP_dimuMass_a30_IDp");
  ZId_a[2] = (TH1F*) fZ->Get("TP_dimuMass_a30_IDf");
  //ZId_b[1] = (TH1F*) fZ->Get("TP_dimuMass_b30_IDp");
  //ZId_b[2] = (TH1F*) fZ->Get("TP_dimuMass_b30_IDf");

  ZIs_a[0]->SetNameTitle("Z_Isa_a", "Z_Isa_a");
  //ZIs_b[0]->SetNameTitle("Z_Isb_a", "Z_Isb_a");

  ZIs_a[1]->SetNameTitle("Z_Isa_p", "Z_Isa_p");
  ZIs_a[2]->SetNameTitle("Z_Isa_f", "Z_Isa_f");
  //ZIs_b[1]->SetNameTitle("Z_Isb_p", "Z_Isb_p");
  //ZIs_b[2]->SetNameTitle("Z_Isb_f", "Z_Isb_f");
  ZId_a[1]->SetNameTitle("Z_Ida_p", "Z_Ida_p");
  ZId_a[2]->SetNameTitle("Z_Ida_f", "Z_Ida_f");
  //ZId_b[1]->SetNameTitle("Z_Idb_p", "Z_Idb_p");
  //ZId_b[2]->SetNameTitle("Z_Idb_f", "Z_Idb_f");

  dIs_a[0] = (TH1F*) fd->Get("TP_dimuMass_a30_All");
  //dIs_b[0] = (TH1F*) fd->Get("TP_dimuMass_b30_All");
  dIs_a[1] = (TH1F*) fd->Get("TP_dimuMass_a30_Isop");
  dIs_a[2] = (TH1F*) fd->Get("TP_dimuMass_a30_Isof");
  //dIs_b[1] = (TH1F*) fd->Get("TP_dimuMass_b30_Isop");
  //dIs_b[2] = (TH1F*) fd->Get("TP_dimuMass_b30_Isof");
  dId_a[1] = (TH1F*) fd->Get("TP_dimuMass_a30_IDp");
  dId_a[2] = (TH1F*) fd->Get("TP_dimuMass_a30_IDf");
  //dId_b[1] = (TH1F*) fd->Get("TP_dimuMass_b30_IDp");
  //dId_b[2] = (TH1F*) fd->Get("TP_dimuMass_b30_IDf");

  dIs_a[0]->SetNameTitle("d_Isa_a", "d_Isa_a");
  //dIs_b[0]->SetNameTitle("d_Isb_a", "d_Isb_a");

  dIs_a[1]->SetNameTitle("d_Isa_p", "d_Isa_p");
  dIs_a[2]->SetNameTitle("d_Isa_f", "d_Isa_f");
  //dIs_b[1]->SetNameTitle("d_Isb_p", "d_Isb_p");
  //dIs_b[2]->SetNameTitle("d_Isb_f", "d_Isb_f");
  dId_a[1]->SetNameTitle("d_Ida_p", "d_Ida_p");
  dId_a[2]->SetNameTitle("d_Ida_f", "d_Ida_f");
  //dId_b[1]->SetNameTitle("d_Idb_p", "d_Idb_p");
  //dId_b[2]->SetNameTitle("d_Idb_f", "d_Idb_f");


  TF1 *mc_[12];
  TF1 *dta[12];

//   mc_[0]  = new TF1("mcg_Z_Isa_a", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   mc_[1]  = new TF1("mcg_Z_Isa_p", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   mc_[2]  = new TF1("mcg_Z_Isa_f", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   mc_[3]  = new TF1("mcg_Z_Isb_a", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   mc_[4]  = new TF1("mcg_Z_Isb_p", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   mc_[5]  = new TF1("mcg_Z_Isb_f", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   mc_[7]  = new TF1("mcg_Z_Ida_p", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   mc_[8]  = new TF1("mcg_Z_Ida_f", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   mc_[10] = new TF1("mcg_Z_Idb_p", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   mc_[11] = new TF1("mcg_Z_Idb_f", "gaus(0) + gaus(3) + expo(6)", 60, 120);

//   mc_[0]  = new TF1("mcg_Z_Isa_a", "gaus(0) + expo(6)", 60, 120);
//   mc_[1]  = new TF1("mcg_Z_Isa_p", "gaus(0) + expo(6)", 60, 120);
//   mc_[2]  = new TF1("mcg_Z_Isa_f", "gaus(0) + expo(6)", 60, 120);
//   mc_[3]  = new TF1("mcg_Z_Isb_a", "gaus(0) + expo(6)", 60, 120);
//   mc_[4]  = new TF1("mcg_Z_Isb_p", "gaus(0) + expo(6)", 60, 120);
//   mc_[5]  = new TF1("mcg_Z_Isb_f", "gaus(0) + expo(6)", 60, 120);
//   mc_[7]  = new TF1("mcg_Z_Ida_p", "gaus(0) + expo(6)", 60, 120);
//   mc_[8]  = new TF1("mcg_Z_Ida_f", "gaus(0) + expo(6)", 60, 120);
//   mc_[10] = new TF1("mcg_Z_Idb_p", "gaus(0) + expo(6)", 60, 120);
//   mc_[11] = new TF1("mcg_Z_Idb_f", "gaus(0) + expo(6)", 60, 120);

  mc_[0]  = new TF1("mcg_Z_Isa_a", "gaus(0) + pol3(6)", 60, 120);
  mc_[1]  = new TF1("mcg_Z_Isa_p", "gaus(0) + pol3(6)", 60, 120);
  mc_[2]  = new TF1("mcg_Z_Isa_f", "gaus(0) + pol3(6)", 60, 120);
  //mc_[3]  = new TF1("mcg_Z_Isb_a", "gaus(0) + pol3(6)", 60, 120);
  //mc_[4]  = new TF1("mcg_Z_Isb_p", "gaus(0) + pol3(6)", 60, 120);
  //mc_[5]  = new TF1("mcg_Z_Isb_f", "gaus(0) + pol3(6)", 60, 120);
  mc_[7]  = new TF1("mcg_Z_Ida_p", "gaus(0) + pol3(6)", 60, 120);
  mc_[8]  = new TF1("mcg_Z_Ida_f", "gaus(0) + pol3(6)", 60, 120);
  //mc_[10] = new TF1("mcg_Z_Idb_p", "gaus(0) + pol3(6)", 60, 120);
  //mc_[11] = new TF1("mcg_Z_Idb_f", "gaus(0) + pol3(6)", 60, 120);

  mc_[0]->SetParameter(1, 91);
  //  mc_[0]->SetParameter(4, 91);
  //  mc_[0]->SetParameter(5, 6);
  mc_[0]->SetParameter(2, 1);
  mc_[0]->SetParameter(0, ZIs_a[0]->GetBinContent(91));
  //  mc_[0]->SetParameter(3, ZIs_a[0]->GetBinContent(91));
  mc_[1]->SetParameter(1, 91);
  //  mc_[1]->SetParameter(4, 91);
  //  mc_[1]->SetParameter(5, 6);
  mc_[1]->SetParameter(2, 1);
  mc_[1]->SetParameter(0, ZIs_a[1]->GetBinContent(91));
  //  mc_[1]->SetParameter(3, ZIs_a[1]->GetBinContent(91));
  mc_[2]->SetParameter(1, 91);
  //  mc_[2]->SetParameter(4, 91);
  //  mc_[2]->SetParameter(5, 6);
  mc_[2]->SetParameter(2, 1);
  mc_[2]->SetParameter(0, ZIs_a[2]->GetBinContent(91));
  //  mc_[2]->SetParameter(3, ZIs_a[2]->GetBinContent(91));
  //mc_[3]->SetParameter(1, 91);
  //  mc_[3]->SetParameter(4, 91);
  //  mc_[3]->SetParameter(5, 6);
  //mc_[3]->SetParameter(2, 1);
  //mc_[3]->SetParameter(0, ZIs_b[0]->GetBinContent(91));
  //  mc_[3]->SetParameter(3, ZIs_b[0]->GetBinContent(91));
  //mc_[4]->SetParameter(1, 91);
  //  mc_[4]->SetParameter(4, 91);
  //  mc_[4]->SetParameter(5, 6);
  //mc_[4]->SetParameter(2, 1);
  //mc_[4]->SetParameter(0, ZIs_b[1]->GetBinContent(91));
  //  mc_[4]->SetParameter(3, ZIs_b[1]->GetBinContent(91));
  //mc_[5]->SetParameter(1, 91);
  //  mc_[5]->SetParameter(4, 91);
  //  mc_[5]->SetParameter(5, 6);
  //mc_[5]->SetParameter(2, 1);
  //mc_[5]->SetParameter(0, ZIs_b[2]->GetBinContent(91));
  //  mc_[5]->SetParameter(3, ZIs_b[2]->GetBinContent(91));
  mc_[7]->SetParameter(1, 91);
  //  mc_[7]->SetParameter(4, 91);
  //  mc_[7]->SetParameter(5, 6);
  mc_[7]->SetParameter(2, 1);
  mc_[7]->SetParameter(0, ZId_a[1]->GetBinContent(91));
  //  mc_[7]->SetParameter(3, ZId_a[1]->GetBinContent(91));
  mc_[8]->SetParameter(1, 91);
  //  mc_[8]->SetParameter(4, 91);
  //  mc_[8]->SetParameter(5, 6);
  mc_[8]->SetParameter(2, 1);
  mc_[8]->SetParameter(0, ZId_a[2]->GetBinContent(91));
  //  mc_[8]->SetParameter(3, ZId_a[2]->GetBinContent(91));
  //mc_[10]->SetParameter(1, 91);
  //  mc_[10]->SetParameter(4, 91);
  //  mc_[10]->SetParameter(5, 6);
  //mc_[10]->SetParameter(2, 1);
  //mc_[10]->SetParameter(0, ZIs_b[1]->GetBinContent(91));
  //  mc_[10]->SetParameter(3, ZIs_b[1]->GetBinContent(91));
  //mc_[11]->SetParameter(1, 91);
  //  mc_[11]->SetParameter(4, 91);
  //  mc_[11]->SetParameter(5, 6);
  //mc_[11]->SetParameter(2, 1);
  //mc_[11]->SetParameter(0, ZIs_b[2]->GetBinContent(91));
  //  mc_[11]->SetParameter(3, ZIs_b[2]->GetBinContent(91));

  TFitResultPtr mcFR[12];
  TFitResultPtr daFR[12];

  mcFR[0]  = ZIs_a[0]->Fit(mc_[0],  "IS", "", 71, 111);
  mcFR[1]  = ZIs_a[1]->Fit(mc_[1],  "IS", "", 71, 111); 
  mcFR[2]  = ZIs_a[2]->Fit(mc_[2],  "IS", "", 71, 111); 
  //mcFR[3]  = ZIs_b[0]->Fit(mc_[3],  "IS", "", 71, 111);
  //mcFR[4]  = ZIs_b[1]->Fit(mc_[4],  "IS", "", 71, 111);
  //mcFR[5]  = ZIs_b[2]->Fit(mc_[5],  "IS", "", 71, 111);
  mcFR[7]  = ZId_a[1]->Fit(mc_[7],  "IS", "", 71, 111); 
  mcFR[8]  = ZId_a[2]->Fit(mc_[8],  "IS", "", 71, 111); 
  //mcFR[10] = ZId_b[1]->Fit(mc_[10], "IS", "", 71, 111);
  //mcFR[11] = ZId_b[2]->Fit(mc_[11], "IS", "", 71, 111);

  cout << "Got MC fits" << endl << endl << endl;

//   dta[0]  = new TF1("dta_Z_Isa_a", "gausn(9)*(gaus(0) + gaus(3)) + expo(6)", 60, 120);
//   dta[1]  = new TF1("dta_Z_Isa_p", "gausn(9)*(gaus(0) + gaus(3)) + expo(6)", 60, 120);
//   dta[2]  = new TF1("dta_Z_Isa_f", "gausn(9)*(gaus(0) + gaus(3)) + expo(6)", 60, 120);
//   dta[3]  = new TF1("dta_Z_Isb_a", "gausn(9)*(gaus(0) + gaus(3)) + expo(6)", 60, 120);
//   dta[4]  = new TF1("dta_Z_Isb_p", "gausn(9)*(gaus(0) + gaus(3)) + expo(6)", 60, 120);
//   dta[5]  = new TF1("dta_Z_Isb_f", "gausn(9)*(gaus(0) + gaus(3)) + expo(6)", 60, 120);
//   dta[7]  = new TF1("dta_Z_Ida_p", "gausn(9)*(gaus(0) + gaus(3)) + expo(6)", 60, 120);
//   dta[8]  = new TF1("dta_Z_Ida_f", "gausn(9)*(gaus(0) + gaus(3)) + expo(6)", 60, 120);
//   dta[10] = new TF1("dta_Z_Idb_p", "gausn(9)*(gaus(0) + gaus(3)) + expo(6)", 60, 120);
//   dta[11] = new TF1("dta_Z_Idb_f", "gausn(9)*(gaus(0) + gaus(3)) + expo(6)", 60, 120);

//   dta[0]  = new TF1("dta_Z_Isa_a", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   dta[1]  = new TF1("dta_Z_Isa_p", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   dta[2]  = new TF1("dta_Z_Isa_f", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   dta[3]  = new TF1("dta_Z_Isb_a", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   dta[4]  = new TF1("dta_Z_Isb_p", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   dta[5]  = new TF1("dta_Z_Isb_f", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   dta[7]  = new TF1("dta_Z_Ida_p", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   dta[8]  = new TF1("dta_Z_Ida_f", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   dta[10] = new TF1("dta_Z_Idb_p", "gaus(0) + gaus(3) + expo(6)", 60, 120);
//   dta[11] = new TF1("dta_Z_Idb_f", "gaus(0) + gaus(3) + expo(6)", 60, 120);

//   dta[0]  = new TF1("dta_Z_Isa_a", "gaus(0) + expo(6)", 60, 120);
//   dta[1]  = new TF1("dta_Z_Isa_p", "gaus(0) + expo(6)", 60, 120);
//   dta[2]  = new TF1("dta_Z_Isa_f", "gaus(0) + expo(6)", 60, 120);
//   dta[3]  = new TF1("dta_Z_Isb_a", "gaus(0) + expo(6)", 60, 120);
//   dta[4]  = new TF1("dta_Z_Isb_p", "gaus(0) + expo(6)", 60, 120);
//   dta[5]  = new TF1("dta_Z_Isb_f", "gaus(0) + expo(6)", 60, 120);
//   dta[7]  = new TF1("dta_Z_Ida_p", "gaus(0) + expo(6)", 60, 120);
//   dta[8]  = new TF1("dta_Z_Ida_f", "gaus(0) + expo(6)", 60, 120);
//   dta[10] = new TF1("dta_Z_Idb_p", "gaus(0) + expo(6)", 60, 120);
//   dta[11] = new TF1("dta_Z_Idb_f", "gaus(0) + expo(6)", 60, 120);

  dta[0]  = new TF1("dta_Z_Isa_a", "gaus(0) + pol3(6)", 60, 120);
  dta[1]  = new TF1("dta_Z_Isa_p", "gaus(0) + pol3(6)", 60, 120);
  dta[2]  = new TF1("dta_Z_Isa_f", "gaus(0) + pol3(6)", 60, 120);
  //dta[3]  = new TF1("dta_Z_Isb_a", "gaus(0) + pol3(6)", 60, 120);
  //dta[4]  = new TF1("dta_Z_Isb_p", "gaus(0) + pol3(6)", 60, 120);
  //dta[5]  = new TF1("dta_Z_Isb_f", "gaus(0) + pol3(6)", 60, 120);
  dta[7]  = new TF1("dta_Z_Ida_p", "gaus(0) + pol3(6)", 60, 120);
  dta[8]  = new TF1("dta_Z_Ida_f", "gaus(0) + pol3(6)", 60, 120);
  //dta[10] = new TF1("dta_Z_Idb_p", "gaus(0) + pol3(6)", 60, 120);
  //dta[11] = new TF1("dta_Z_Idb_f", "gaus(0) + pol3(6)", 60, 120);
  
  for(int i = 0; i != 12; ++i)
  {
    if (i == 6 || i == 9) continue;
    dta[i]->SetLineColor(kRed);
  }

	cout << "Made it here";
//   int which = 1;
//   cout << "Getting MC Params " << which++ << endl << endl << endl;

//   dta[0]->FixParameter(1, mcFR[0]->GetParams()[1]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[0]->FixParameter(2, mcFR[0]->GetParams()[2]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[1]->FixParameter(1, mcFR[1]->GetParams()[1]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[1]->FixParameter(2, mcFR[1]->GetParams()[2]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[2]->FixParameter(1, mcFR[2]->GetParams()[1]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[2]->FixParameter(2, mcFR[2]->GetParams()[2]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[3]->FixParameter(1, mcFR[3]->GetParams()[1]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[3]->FixParameter(2, mcFR[3]->GetParams()[2]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[4]->FixParameter(1, mcFR[4]->GetParams()[1]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[4]->FixParameter(2, mcFR[4]->GetParams()[2]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[5]->FixParameter(1, mcFR[5]->GetParams()[1]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[5]->FixParameter(2, mcFR[5]->GetParams()[2]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[7]->FixParameter(1, mcFR[7]->GetParams()[1]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[7]->FixParameter(2, mcFR[7]->GetParams()[2]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[8]->FixParameter(1, mcFR[8]->GetParams()[1]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[8]->FixParameter(2, mcFR[8]->GetParams()[2]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[10]->FixParameter(1, mcFR[10]->GetParams()[1]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[10]->FixParameter(2, mcFR[10]->GetParams()[2]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[11]->FixParameter(1, mcFR[11]->GetParams()[1]);
//   cout << "Getting MC Params " << which++ << endl << endl << endl;
//   dta[11]->FixParameter(2, mcFR[11]->GetParams()[2]);

   dta[00]->SetParameter(1, mcFR[0]->GetParams()[1]);
   dta[00]->SetParameter(2, mcFR[0]->GetParams()[2]);
   dta[01]->SetParameter(1, mcFR[1]->GetParams()[1]);
   dta[01]->SetParameter(2, mcFR[1]->GetParams()[2]);
   dta[02]->SetParameter(1, mcFR[2]->GetParams()[1]);
   dta[02]->SetParameter(2, mcFR[2]->GetParams()[2]);
   //dta[03]->SetParameter(1, mcFR[3]->GetParams()[1]);
   //dta[03]->SetParameter(2, mcFR[3]->GetParams()[2]);
   //dta[04]->SetParameter(1, mcFR[4]->GetParams()[1]);
   //dta[04]->SetParameter(2, mcFR[4]->GetParams()[2]);
   //dta[05]->SetParameter(1, mcFR[5]->GetParams()[1]);
   //dta[05]->SetParameter(2, mcFR[5]->GetParams()[2]);
   dta[07]->SetParameter(1, mcFR[7]->GetParams()[1]);
   dta[07]->SetParameter(2, mcFR[7]->GetParams()[2]);
   dta[08]->SetParameter(1, mcFR[8]->GetParams()[1]);
   dta[08]->SetParameter(2, mcFR[8]->GetParams()[2]);
   //dta[10]->SetParameter(1, mcFR[10]->GetParams()[1]);
   //dta[10]->SetParameter(2, mcFR[10]->GetParams()[2]);
   //dta[11]->SetParameter(1, mcFR[11]->GetParams()[1]);
   //dta[11]->SetParameter(2, mcFR[11]->GetParams()[2]);

//   dta[0]->FixParameter(4, mcFR[0]->GetParams()[4]);
//   dta[0]->FixParameter(5, mcFR[0]->GetParams()[5]);
//   dta[1]->FixParameter(4, mcFR[1]->GetParams()[4]);
//   dta[1]->FixParameter(5, mcFR[1]->GetParams()[5]);
//   dta[2]->FixParameter(4, mcFR[2]->GetParams()[4]);
//   dta[2]->FixParameter(5, mcFR[2]->GetParams()[5]);
//   dta[3]->FixParameter(4, mcFR[3]->GetParams()[4]);
//   dta[3]->FixParameter(5, mcFR[3]->GetParams()[5]);
//   dta[4]->FixParameter(4, mcFR[4]->GetParams()[4]);
//   dta[4]->FixParameter(5, mcFR[4]->GetParams()[5]);
//   dta[5]->FixParameter(4, mcFR[5]->GetParams()[4]);
//   dta[5]->FixParameter(5, mcFR[5]->GetParams()[5]);
//   dta[7]->FixParameter(4, mcFR[7]->GetParams()[4]);
//   dta[7]->FixParameter(5, mcFR[7]->GetParams()[5]);
//   dta[8]->FixParameter(4, mcFR[8]->GetParams()[4]);
//   dta[8]->FixParameter(5, mcFR[8]->GetParams()[5]);
//   dta[10]->FixParameter(4, mcFR[10]->GetParams()[4]);
//   dta[10]->FixParameter(5, mcFR[10]->GetParams()[5]);
//   dta[11]->FixParameter(4, mcFR[11]->GetParams()[4]);
//   dta[11]->FixParameter(5, mcFR[11]->GetParams()[5]);

  cout << "Doing data fits" << endl << endl << endl;

  daFR[0]  = dIs_a[0]->Fit(dta[0],  "IS", "", 71, 111);
  daFR[1]  = dIs_a[1]->Fit(dta[1],  "IS", "", 71, 111); 
  daFR[2]  = dIs_a[2]->Fit(dta[2],  "IS", "", 71, 111); 
  //daFR[3]  = dIs_b[0]->Fit(dta[3],  "IS", "", 71, 111);
  //daFR[4]  = dIs_b[1]->Fit(dta[4],  "IS", "", 71, 111);
  //daFR[5]  = dIs_b[2]->Fit(dta[5],  "IS", "", 71, 111);
  daFR[7]  = dId_a[1]->Fit(dta[7],  "IS", "", 71, 111); 
  daFR[8]  = dId_a[2]->Fit(dta[8],  "IS", "", 71, 111); 
  //daFR[10] = dId_b[1]->Fit(dta[10], "IS", "", 71, 111);
  //daFR[11] = dId_b[2]->Fit(dta[11], "IS", "", 71, 111);

  cout << "Got data fits." << endl << endl << endl;
  
  
  const float tp = sqrt(2*3.14159265);

//   float mcTAa  = tp*(mcFR[0]->GetParams()[0]*mcFR[0]->GetParams()[2]+mcFR[0]->GetParams()[3]*mcFR[0]->GetParams()[5]);
//   float mcTAb  = tp*(mcFR[3]->GetParams()[0]*mcFR[3]->GetParams()[2]+mcFR[3]->GetParams()[3]*mcFR[3]->GetParams()[5]);
  float mcTAa  = tp*abs((mcFR[0]->GetParams()[0]*mcFR[0]->GetParams()[2]));
  //float mcTAb  = tp*abs((mcFR[3]->GetParams()[0]*mcFR[3]->GetParams()[2]));

//   float mcTpDa = tp*(mcFR[7]->GetParams()[0]*mcFR[7]->GetParams()[2]+mcFR[7]->GetParams()[3]*mcFR[7]->GetParams()[5]);
//   float mcTpSa = tp*(mcFR[1]->GetParams()[0]*mcFR[1]->GetParams()[2]+mcFR[1]->GetParams()[3]*mcFR[1]->GetParams()[5]);
  float mcTpDa = tp*abs((mcFR[7]->GetParams()[0]*mcFR[7]->GetParams()[2]));
  float mcTpSa = tp*abs((mcFR[1]->GetParams()[0]*mcFR[1]->GetParams()[2]));

//   float mcTfDa = tp*(mcFR[8]->GetParams()[0]*mcFR[8]->GetParams()[2]+mcFR[8]->GetParams()[3]*mcFR[8]->GetParams()[5]);
//   float mcTfSa = tp*(mcFR[2]->GetParams()[0]*mcFR[2]->GetParams()[2]+mcFR[2]->GetParams()[3]*mcFR[2]->GetParams()[5]);
  float mcTfDa = tp*abs((mcFR[8]->GetParams()[0]*mcFR[8]->GetParams()[2]));
  //  float mcTfDa = 0;
  float mcTfSa = tp*abs((mcFR[2]->GetParams()[0]*mcFR[2]->GetParams()[2]));

//   float mcTpDb = tp*(mcFR[10]->GetParams()[0]*mcFR[10]->GetParams()[2]+mcFR[10]->GetParams()[3]*mcFR[10]->GetParams()[5]);
//   float mcTpSb = tp*(mcFR[4]->GetParams()[0]*mcFR[4]->GetParams()[2]+mcFR[4]->GetParams()[3]*mcFR[4]->GetParams()[5]);
  //float mcTpDb = tp*abs((mcFR[10]->GetParams()[0]*mcFR[10]->GetParams()[2]));
  //float mcTpSb = tp*abs((mcFR[4]->GetParams()[0]*mcFR[4]->GetParams()[2]));

//   float mcTfDb = tp*(mcFR[11]->GetParams()[0]*mcFR[11]->GetParams()[2]+mcFR[11]->GetParams()[3]*mcFR[11]->GetParams()[5]);
//   float mcTfSb = tp*(mcFR[5]->GetParams()[0]*mcFR[5]->GetParams()[2]+mcFR[5]->GetParams()[3]*mcFR[5]->GetParams()[5]);
  //float mcTfDb = tp*abs((mcFR[11]->GetParams()[0]*mcFR[11]->GetParams()[2]));
	//cout << "mcTfDb: " << mcTfDb << endl;
  //  float mcTfDb = 0;
  //float mcTfSb = tp*(mcFR[5]->GetParams()[0]*mcFR[5]->GetParams()[2]));

//   float daTAa  = tp*(daFR[0]->GetParams()[0]* daFR[0]->GetParams()[2]  + daFR[0]->GetParams()[3]* daFR[0]->GetParams()[5]);
//   float daTAb  = tp*(daFR[3]->GetParams()[0]* daFR[3]->GetParams()[2]  + daFR[3]->GetParams()[3]* daFR[3]->GetParams()[5]);
//   float daTpDa = tp*(daFR[7]->GetParams()[0]* daFR[7]->GetParams()[2]  + daFR[7]->GetParams()[3]* daFR[7]->GetParams()[5]);
//   float daTpSa = tp*(daFR[1]->GetParams()[0]* daFR[1]->GetParams()[2]  + daFR[1]->GetParams()[3]* daFR[1]->GetParams()[5]);
//   float daTfDa = tp*(daFR[8]->GetParams()[0]* daFR[8]->GetParams()[2]  + daFR[8]->GetParams()[3]* daFR[8]->GetParams()[5]);
//   float daTfSa = tp*(daFR[2]->GetParams()[0]* daFR[2]->GetParams()[2]  + daFR[2]->GetParams()[3]* daFR[2]->GetParams()[5]);
//   float daTpDb = tp*(daFR[10]->GetParams()[0]*daFR[10]->GetParams()[2] + daFR[10]->GetParams()[3]*daFR[10]->GetParams()[5]);
//   float daTpSb = tp*(daFR[4]->GetParams()[0]* daFR[4]->GetParams()[2]  + daFR[4]->GetParams()[3]* daFR[4]->GetParams()[5]);
//   float daTfDb = tp*(daFR[11]->GetParams()[0]*daFR[11]->GetParams()[2] + daFR[11]->GetParams()[3]*daFR[11]->GetParams()[5]);
//   float daTfSb = tp*(daFR[5]->GetParams()[0]* daFR[5]->GetParams()[2]  + daFR[5]->GetParams()[3]* daFR[5]->GetParams()[5]);

  float daTAa  = tp*abs((daFR[0]->GetParams()[0]* daFR[0]->GetParams()[2] ));
  //float daTAb  = tp*abs((daFR[3]->GetParams()[0]* daFR[3]->GetParams()[2] ));
  float daTpDa = tp*abs((daFR[7]->GetParams()[0]* daFR[7]->GetParams()[2] ));
  float daTpSa = tp*abs((daFR[1]->GetParams()[0]* daFR[1]->GetParams()[2] ));
  float daTfDa = tp*abs((daFR[8]->GetParams()[0]* daFR[8]->GetParams()[2] ));
  float daTfSa = tp*abs((daFR[2]->GetParams()[0]* daFR[2]->GetParams()[2] ));
  //float daTpDb = tp*abs((daFR[10]->GetParams()[0]*daFR[10]->GetParams()[2]));
  //float daTpSb = tp*abs((daFR[4]->GetParams()[0]* daFR[4]->GetParams()[2] ));
  //float daTfDb = tp*abs((daFR[11]->GetParams()[0]*daFR[11]->GetParams()[2]));
  //float daTfSb = tp*abs((daFR[5]->GetParams()[0]* daFR[5]->GetParams()[2] ));

  cout << "MC above ID eff3 " << mcTpDa/(mcTpDa+mcTfDa) << " eff2: " << mcTpDa/mcTAa << endl; 
//  cout << "MC below ID eff3 " << mcTpDb/(mcTpDb+mcTfDb) << " eff2: " << mcTpDb/mcTAb << endl;
  cout << "MC above Iso eff3 " << mcTpSa/(mcTpSa+mcTfSa) << " eff2: " << mcTpSa/mcTAa << endl; 
//  cout << "MC below Iso eff3 " << mcTpSb/(mcTpSb+mcTfSb) << " eff2: " << mcTpSb/mcTAb << endl;
 
 cout << "Data above ID eff3 " <<  daTpDa/(daTpDa+daTfDa) << " eff2: " << daTpDa/daTAa << endl; 
//  cout << "Data below ID eff3 " <<  daTpDb/(daTpDb+daTfDb) << " eff2: " << daTpDb/daTAb << endl;
  cout << "Data above Iso eff3 " << daTpSa/(daTpSa+daTfSa) << " eff2: " << daTpSa/daTAa << endl; 
//  cout << "Data below Iso eff3 " << daTpSb/(daTpSb+daTfSb) << " eff2: " << daTpSb/daTAb << endl;

  TFile* tph = new TFile("/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Data/TagAndProbe/Outputs/TP_Output_RI_005_v1.root", "RECREATE");
  tph->cd();
  for(int i=0; i!=3; ++i){
    ZIs_a[i]->Write();
    dIs_a[i]->Write();
    //ZIs_b[i]->Write();
    //dIs_b[i]->Write();
    if(i != 0){
      ZId_a[i]->Write();
      dId_a[i]->Write();
      //ZId_b[i]->Write();
      //dId_b[i]->Write();
    }
  }
  tph->Close();
}
