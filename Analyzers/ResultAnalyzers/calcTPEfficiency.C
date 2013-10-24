/*
 * calcTPEfficiency.C
 *
 * Copyright 2013 james-wetzel@uiowa.edu
 *
 * This script calculates Tag and Probe efficiencies.
 *
 * Inputs: Two root files:
 *  1) MC sample of Z->MuMu
 *  2) Data of single Muon events
 *
 * Outputs: Histograms with efficiencies of muons passing TP thresholds
 *
 */

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFitResult.h"

#include <iostream>

using std::endl;
using std::cout;
using std::string;

void calcTPEfficiency(bool debug)
{
  if (debug) cout << endl << "***** RUNNING IN DEBUG MODE *****" << endl << endl;
  
  cout << endl << endl;
  cout << "********************************" << endl;
  cout << "Accessing Histograms..." << endl;
  cout << "********************************" << endl;

  
  /***************************************************
   *  Declare TFiles to open for input and analysis: *
   **************************************************/
  const char *c_ZMCPath = "../../Data/TagAndProbe/Inputs/TP_DrellYan_ZMuMu.root";
  const char *c_DataPath = "../../Data/TagAndProbe/Inputs/TP_Single_Mu_Data.root";
  
  TFile *f_ZMC = new TFile(c_ZMCPath);    //! Drell-Yan MC sample Z-> MuMu
  TFile *f_Data = new TFile(c_DataPath);  //! Single Mu data sample
  TFile *f_histos = new TFile("../../Data/TagAndProbe/Outputs/TP_Histos_RI_005_v3.root","RECREATE"); //! Histogram OutputFile
  
  
  /**************************************************
   * Declare arrays of Histograms:                  *
   **************************************************/
  TH1F *h_mcIso[3];   //! Relative Isolation
  TH1F *h_dataIso[3]; //
  
  TH1F *h_mcID[3];    //! ID
  TH1F *h_dataID[3];  //
  
  
  /**************************************************
  *   Access histograms from input root files:      *
  *   [0] = all; [1] = pass; [2] = fail             *
  **************************************************/
  
  /***    MC Histograms   ***/
  h_mcIso[0] = (TH1F*) f_ZMC->Get("TP_dimuMass_a30_All");  //!------ MC Isolation
  h_mcIso[1] = (TH1F*) f_ZMC->Get("TP_dimuMass_a30_Isop"); //
  h_mcIso[2] = (TH1F*) f_ZMC->Get("TP_dimuMass_a30_Isof"); //

  h_mcID[1] = (TH1F*) f_ZMC->Get("TP_dimuMass_a30_IDp"); //!-------- MC ID ([0] same as Iso)
  h_mcID[2] = (TH1F*) f_ZMC->Get("TP_dimuMass_a30_IDf"); //
  
  h_mcIso[0]->SetNameTitle("Z_Iso_All","Z_Iso_All");   //!---------- Set Titles (Iso)
  h_mcIso[1]->SetNameTitle("Z_Iso_Pass","Z_Iso_Pass"); //
  h_mcIso[2]->SetNameTitle("Z_Iso_Fail","Z_Iso_Fail"); //
  
  h_mcID[1]->SetNameTitle("Z_ID_Pass","Z_ID_Pass");  //!------------ Set Titles (ID)
  h_mcID[2]->SetNameTitle("Z_ID_Fail","Z_ID_Fail");  //
  
  h_mcIso[0]->GetXaxis()->SetRange(50,130); //!--------------------- ReScale X-Axis (Iso)
  h_mcIso[1]->GetXaxis()->SetRange(50,130); //
  h_mcIso[2]->GetXaxis()->SetRange(50,130); //
  
  h_mcID[1]->GetXaxis()->SetRange(50,130);  //!--------------------- ReScale X-Axis (ID)
  h_mcID[2]->GetXaxis()->SetRange(50,130);  //
  
  h_mcIso[1]->GetXaxis()->SetTitle("GeV"); //!--------------------- Set X-Axis Titles       Pass (Iso)
  h_mcIso[1]->GetYaxis()->SetTitle("Events"); //!------------------ Set Y-Axis Titles       Pass
  h_mcIso[1]->SetStats(0); //!------------------------------------- Disable Stats Box       Pass
  h_mcIso[1]->SetTitle("MC Probe Muon Rel Iso PASS"); //!---------- Set Histogram Title     Pass
  h_mcIso[1]->SetTitleOffset(1.1,"Y"); //!------------------------- Set Y-Axis Title offset Pass
  
  h_mcIso[2]->GetXaxis()->SetTitle("GeV"); //!--------------------- Set X-Axis Titles       Fail
  h_mcIso[2]->GetYaxis()->SetTitle("Events"); //!------------------ Set Y-Axis Titles       Fail
  h_mcIso[2]->SetStats(0); //!------------------------------------- Disable Stats Box       Fail
  h_mcIso[2]->SetTitle("MC Probe Muon Rel Iso FAIL"); //!---------- Set Histogram Title     Fail
  h_mcIso[2]->SetTitleOffset(1.1,"Y"); //!------------------------- Set Y-Axis Title offset Fail

  /***    Data histograms   ***/
  h_dataIso[0] = (TH1F*) f_Data->Get("TP_dimuMass_a30_All");  //!--- Data Isolation
  h_dataIso[1] = (TH1F*) f_Data->Get("TP_dimuMass_a30_Isop"); //
  h_dataIso[2] = (TH1F*) f_Data->Get("TP_dimuMass_a30_Isof"); //
  
  h_dataID[1] = (TH1F*) f_Data->Get("TP_dimuMass_a30_IDp"); //!----- Data ID
  h_dataID[2] = (TH1F*) f_Data->Get("TP_dimuMass_a30_IDf"); //
  
  h_dataIso[0]->SetNameTitle("Data_Iso_All","Data_Iso_All");    //!- Set Titles (Iso)
  h_dataIso[1]->SetNameTitle("Data_Iso_Pass","Data_Iso_Pass");  //
  h_dataIso[2]->SetNameTitle("Data_Iso_Fail","Data_Iso_Fail");  //

  h_dataID[1]->SetNameTitle("Data_ID_Pass","Data_ID_Pass"); //!----- Set Titles (ID)
  h_dataID[2]->SetNameTitle("Data_ID_Fail","Data_ID_Fail"); //
  
  h_dataIso[0]->GetXaxis()->SetRange(50,130); //!--------------------- ReScale X-Axis (Iso)
  h_dataIso[1]->GetXaxis()->SetRange(50,130); //
  h_dataIso[2]->GetXaxis()->SetRange(50,130); //
  
  h_dataID[1]->GetXaxis()->SetRange(50,130);  //!--------------------- ReScale X-Axis (ID)
  h_dataID[2]->GetXaxis()->SetRange(50,130);  //
  
  h_dataIso[1]->GetXaxis()->SetTitle("GeV"); //!--------------------- Set X-Axis Titles       Pass (Iso)
  h_dataIso[1]->GetYaxis()->SetTitle("Events"); //!------------------ Set Y-Axis Titles       Pass
  h_dataIso[1]->SetStats(0); //!------------------------------------- Disable Stats Box       Pass
  h_dataIso[1]->SetTitle("Data Probe Muon Rel Iso PASS"); //!-------- Set Histogram Title     Pass
  h_dataIso[1]->SetTitleOffset(1.1,"Y"); //!------------------------- Set Y-Axis Title offset Pass
  
  h_dataIso[2]->GetXaxis()->SetTitle("GeV"); //!--------------------- Set X-Axis Titles       Fail
  h_dataIso[2]->GetYaxis()->SetTitle("Events"); //!------------------ Set Y-Axis Titles       Fail
  h_dataIso[2]->SetStats(0); //!------------------------------------- Disable Stats Box       Fail
  h_dataIso[2]->SetTitle("Data Probe Muon Rel Iso FAIL"); //!-------- Set Histogram Title     Fail
  h_dataIso[2]->SetTitleOffset(1.1,"Y"); //!------------------------- Set Y-Axis Title offset Fail
  
  
  /**************************************************
   * Declare arrays of fit functions                *
   **************************************************/
  TF1 *fit_mc[12];    //! mc fits
  TF1 *fit_data[12];  //! data fits
  
  /**************************************************
   *  Define fit functions                          *
   **************************************************/
  // MC
  fit_mc[0] = new TF1("MC_Z_Iso_All", "gaus(0) + gaus(3) + pol3(6)", 70, 110);   //!- Iso
  fit_mc[1] = new TF1("MC_Z_Iso_Pass", "gaus(0) + gaus(3) + pol3(6)", 70, 110);  //
  fit_mc[2] = new TF1("MC_Z_Iso_Fail", "gaus(0) + gaus(3) + pol3(6)", 70, 110);  //
  
  fit_mc[3] = new TF1("MC_Z_ID_Pass", "gaus(0) + gaus(3) + pol3(6)", 70, 110); //!--- ID
  fit_mc[4] = new TF1("MC_Z_ID_Fail", "gaus(0) + gaus(3) + pol3(6)", 70, 110); //
  
  // Data
  fit_data[0] = new TF1("Data_Z_Iso_All", "gaus(0) + gaus(3) + pol3(6)", 70, 110);   //!- Iso
  fit_data[1] = new TF1("Data_Z_Iso_Pass", "gaus(0) + gaus(3) + pol3(6)", 70, 110);  //
  fit_data[2] = new TF1("Data_Z_Iso_Fail", "gaus(0) + gaus(3) + pol3(6)", 70, 110);  //
  
  fit_data[3] = new TF1("Data_Z_ID_Pass", "gaus(0) + gaus(3) + pol3(6)", 70, 110); //!--- ID
  fit_data[4] = new TF1("Data_Z_ID_Fail", "gaus(0) + gaus(3) + pol3(6)", 70, 110); //
  
  /***    Set Iso Fit Parameters    ***/
  // MC
  fit_mc[0]->SetParameter(0,h_mcIso[0]->GetBinContent(91));  //! Parameters for Iso All
  fit_mc[0]->SetParameter(1,91);
  fit_mc[0]->SetParameter(2,1);
  fit_mc[0]->SetParameter(3,h_mcIso[0]->GetBinContent(91));  //! Parameters for Iso All
  fit_mc[0]->SetParameter(4,91);
  fit_mc[0]->SetParameter(5,1);
  
  fit_mc[1]->SetParameter(0,h_mcIso[1]->GetBinContent(91));  //! Parameters for Iso Pass
  fit_mc[1]->SetParameter(1,91);
  fit_mc[1]->SetParameter(2,1);
  fit_mc[1]->SetParameter(3,h_mcIso[1]->GetBinContent(91));  //! Parameters for Iso All
  fit_mc[1]->SetParameter(4,91);
  fit_mc[1]->SetParameter(5,1);

  fit_mc[2]->SetParameter(0,h_mcIso[2]->GetBinContent(91));  //! Parameters for Iso Fail
  fit_mc[2]->SetParameter(1,91);
  fit_mc[2]->SetParameter(2,1);
  fit_mc[2]->SetParameter(3,h_mcIso[2]->GetBinContent(91));  //! Parameters for Iso All
  fit_mc[2]->SetParameter(4,91);
  fit_mc[2]->SetParameter(5,1);
  
  /***    Set ID Fit Parameters    ***/
  // MC
  fit_mc[3]->SetParameter(0,h_mcID[1]->GetBinContent(91));   //! Parameters for ID Pass
  fit_mc[3]->SetParameter(1,91);
  fit_mc[3]->SetParameter(2,1);
  fit_mc[3]->SetParameter(3,h_mcID[1]->GetBinContent(91));  //! Parameters for ID All
  fit_mc[3]->SetParameter(4,91);
  fit_mc[3]->SetParameter(5,1);

  fit_mc[4]->SetParameter(0,h_mcID[2]->GetBinContent(91));   //! Parameters for ID Fail
  fit_mc[4]->SetParameter(1,91);
  fit_mc[4]->SetParameter(2,1);
  fit_mc[4]->SetParameter(3,h_mcID[2]->GetBinContent(91));  //! Parameters for ID All
  fit_mc[4]->SetParameter(4,91);
  fit_mc[4]->SetParameter(5,1);
  
  /***    Declare and fill fit result stores   ***/
  TFitResultPtr mcFitResults[12];   //! MC fit results
  TFitResultPtr dataFitResults[12]; //! data fit results

  /**************************************************
   *    Fitting Histograms                          *
   **************************************************/
  cout << "Complete." << endl << endl << endl;
  cout << "********************************" << endl;
  cout << "Fitting MC Histograms..." << endl;
  cout << "********************************" << endl;
  
  // Options defined here: http://root.cern.ch/root/html/TH1.html#TH1:Fit
  for(int i = 0; i != 5; ++i) //! Set the fit line color to Red
    fit_mc[i]->SetLineColor(kRed);
  mcFitResults[0] = h_mcIso[0]->Fit(fit_mc[0], "ISQ", "", 71, 111); //! MC All Iso
  mcFitResults[1] = h_mcIso[1]->Fit(fit_mc[1], "ISQ", "", 71, 111); //! MC Pass Iso
  mcFitResults[2] = h_mcIso[2]->Fit(fit_mc[2], "ISQ", "", 71, 111); //! MC Fail Iso
  
  mcFitResults[3] = h_mcID[1]->Fit(fit_mc[3], "ISQ", "", 71, 111);  //! MC Pass ID
  mcFitResults[4] = h_mcID[2]->Fit(fit_mc[4], "ISQ", "", 71, 111);  //! MC Fail ID
  
  cout << endl << "Complete." << endl << endl << endl;
  cout << "********************************" << endl;
  cout << "Got MC Fit Results." << endl;
  cout << "********************************" << endl << endl;
  
  cout << endl << endl;
  cout << "********************************" << endl;
  cout << "Fitting Data Histograms...." << endl;
  cout << "********************************"<< endl;
  
  /**************************************************
   *  Use MC Fit results to fit data                *
   **************************************************/
  fit_data[0]->SetParameter(1, mcFitResults[0]->GetParams()[1]);
  fit_data[0]->SetParameter(2, mcFitResults[0]->GetParams()[2]);
  fit_data[0]->SetParameter(4, mcFitResults[0]->GetParams()[4]);
  fit_data[0]->SetParameter(5, mcFitResults[0]->GetParams()[5]);
  
  fit_data[1]->SetParameter(1, mcFitResults[1]->GetParams()[1]);
  fit_data[1]->SetParameter(2, mcFitResults[1]->GetParams()[2]);
  fit_data[1]->SetParameter(4, mcFitResults[1]->GetParams()[4]);
  fit_data[1]->SetParameter(5, mcFitResults[1]->GetParams()[5]);
  
  fit_data[2]->SetParameter(1, mcFitResults[2]->GetParams()[1]);
  fit_data[2]->SetParameter(2, mcFitResults[2]->GetParams()[2]);
  fit_data[2]->SetParameter(4, mcFitResults[2]->GetParams()[4]);
  fit_data[2]->SetParameter(5, mcFitResults[2]->GetParams()[5]);
  
  fit_data[3]->SetParameter(1, mcFitResults[3]->GetParams()[1]);
  fit_data[3]->SetParameter(2, mcFitResults[3]->GetParams()[2]);
  fit_data[3]->SetParameter(4, mcFitResults[3]->GetParams()[4]);
  fit_data[3]->SetParameter(5, mcFitResults[3]->GetParams()[5]);
  
  fit_data[4]->SetParameter(1, mcFitResults[4]->GetParams()[1]);
  fit_data[4]->SetParameter(2, mcFitResults[4]->GetParams()[2]);
  fit_data[4]->SetParameter(4, mcFitResults[4]->GetParams()[4]);
  fit_data[4]->SetParameter(5, mcFitResults[4]->GetParams()[5]);

  for(int i = 0; i != 5; ++i) //! Set the fit line color to Red
    fit_data[i]->SetLineColor(kRed);
  dataFitResults[0] = h_dataIso[0]->Fit(fit_data[0], "ISQ", "", 71, 111); //! data All Iso
  dataFitResults[1] = h_dataIso[1]->Fit(fit_data[1], "ISQ", "", 71, 111); //! data Pass Iso
  dataFitResults[2] = h_dataIso[2]->Fit(fit_data[2], "ISQ", "", 71, 111); //! data Fail Iso
  dataFitResults[3] = h_dataID[1]->Fit(fit_data[3], "ISQ", "", 71, 111);  //! data Pass ID
  dataFitResults[4] = h_dataID[2]->Fit(fit_data[4], "ISQ", "", 71, 111);  //! data Fail ID
  
  cout << "Complete." << endl << endl << endl;
  cout << "********************************" << endl;
  cout << "Calculating Efficiencies." << endl;
  cout << "********************************" << endl;
  
  
  /**************************************************************
   * Calculate integral of Gaussian fit                         *
   * http://en.wikipedia.org/wiki/Gaussian_function#Properties  *
   *                                                            *
   * Integral from -inf to +inf is rootTwoPi*StdDev*Amplitude   *
   **************************************************************/
  
  const float rootTwoPi = sqrt(2*3.14159265);
  
  // MC Integrals: Gaus 1 + Gaus 2
  float mcTagAll = rootTwoPi*(abs((mcFitResults[0]->GetParams()[0]*mcFitResults[0]->GetParams()[2]))
    + abs((mcFitResults[0]->GetParams()[3]*mcFitResults[0]->GetParams()[5])));
  
  float mcTagPass_Iso = rootTwoPi*(abs((mcFitResults[1]->GetParams()[0]*mcFitResults[1]->GetParams()[2]))
    + abs((mcFitResults[1]->GetParams()[3]*mcFitResults[1]->GetParams()[5])));
  
  float mcTagFail_Iso = rootTwoPi*(abs((mcFitResults[2]->GetParams()[0]*mcFitResults[2]->GetParams()[2]))
    + abs((mcFitResults[2]->GetParams()[3]*mcFitResults[2]->GetParams()[5])));
  
  float mcTagPass_ID = rootTwoPi*(abs((mcFitResults[3]->GetParams()[0]*mcFitResults[3]->GetParams()[2]))
    + abs((mcFitResults[3]->GetParams()[3]*mcFitResults[3]->GetParams()[5])));
  
  float mcTagFail_ID = rootTwoPi*(abs((mcFitResults[4]->GetParams()[0]*mcFitResults[4]->GetParams()[2]));
    + abs((mcFitResults[4]->GetParams()[3]*mcFitResults[4]->GetParams()[5])));
  
  //  Data Integrals: Gaus 1 + Gaus 2
  float dataTagAll = rootTwoPi*(abs((dataFitResults[0]->GetParams()[0]*dataFitResults[0]->GetParams()[2]));
    + abs((dataFitResults[0]->GetParams()[3]*dataFitResults[0]->GetParams()[5])));
  
  float dataTagPass_Iso = rootTwoPi*(abs((dataFitResults[1]->GetParams()[0]*dataFitResults[1]->GetParams()[2]));
    + abs((dataFitResults[1]->GetParams()[3]*dataFitResults[1]->GetParams()[5])));
  
  float dataTagFail_Iso = rootTwoPi*(abs((dataFitResults[2]->GetParams()[0]*dataFitResults[2]->GetParams()[2]));
    + abs((dataFitResults[2]->GetParams()[3]*dataFitResults[2]->GetParams()[5])));
  
  float dataTagPass_ID = rootTwoPi*(abs((dataFitResults[3]->GetParams()[0]*dataFitResults[3]->GetParams()[2]));
    + abs((dataFitResults[3]->GetParams()[3]*dataFitResults[3]->GetParams()[5])));
  
  float dataTagFail_ID = rootTwoPi*(abs((dataFitResults[4]->GetParams()[0]*dataFitResults[4]->GetParams()[2]));
    + abs((dataFitResults[4]->GetParams()[3]*dataFitResults[4]->GetParams()[5])));
  
  
  /**************************************************************
   *               Calculate Errors of stuff                    *
   **************************************************************/
  
  // Calculate integral of events, 'N'
  float integralOnAll       = h_mcIso[0]->Integral(60,120);
  float integralOnMCIsoPass = h_mcIso[1]->Integral(60,120);
  float integralOnMCIsoFail = h_mcIso[2]->Integral(60,120);
  float integralOnMCIDPass  = h_mcID[1]->Integral(60,120);
  float integralOnMCIDFail  = h_mcID[2]->Integral(60,120);
  
  float integralOnDataIsoPass = h_dataIso[1]->Integral(60,120);
  float integralOnDataIsoFail = h_dataIso[2]->Integral(60,120);
  float integralOnDataIDPass  = h_dataID[1]->Integral(60,120);
  float integralOnDataIDFail  = h_dataID[2]->Integral(60,120);
  
  // Calculate stat error: sqrt(N)/N
  float errorOnAll        = sqrt(integralOnAll)/integralOnAll;
  float errorOnMCIsoPass  = sqrt(integralOnMCIsoPass)/integralOnMCIsoPass;
  float errorOnMCIsoFail  = sqrt(integralOnMCIsoFail)/integralOnMCIsoFail;
  float errorOnMCIDPass   = sqrt(integralOnMCIDPass)/integralOnMCIDPass;
  float errorOnMCIDFail   = sqrt(integralOnMCIDFail)/integralOnMCIDFail;
  
  float errorOnDataIsoPass  = sqrt(integralOnDataIsoPass)/integralOnDataIsoPass;
  float errorOnDataIsoFail  = sqrt(integralOnDataIsoFail)/integralOnDataIsoFail;
  float errorOnDataIDPass   = sqrt(integralOnDataIDPass)/integralOnDataIDPass;
  float errorOnDataIDFail   = sqrt(integralOnDataIDFail)/integralOnDataIDFail;
  
  // Calculate Propagation of errors
  float finalErrorMCID    = sqrt(2*pow(errorOnMCIDPass,2) + pow(errorOnMCIDFail,20));
  float finalErrorMCIso   = sqrt(2*pow(errorOnMCIsoPass,2) + pow(errorOnMCIsoFail,20));
  float finalErrorDataID  = sqrt(2*pow(errorOnDataIDPass,2) + pow(errorOnDataIDFail,20));
  float finalErrorDataIso = sqrt(2*pow(errorOnDataIsoPass,2) + pow(errorOnDataIsoFail,20));
  
  
  
  cout << "Complete." << endl << endl << endl;
  /**************************************************
   *  Spit out Efficiencies                         *
   **************************************************/
  
  float finalMCIDEfficiency     = mcTagPass_ID/(mcTagPass_ID+mcTagFail_ID);
  float finalMCIsoEfficiency    = mcTagPass_Iso/(mcTagPass_Iso+mcTagFail_Iso);
  float finalDataIDEfficiency   = dataTagPass_ID/(dataTagPass_ID+dataTagFail_ID);
  float finalDataIsoEfficiency  = dataTagPass_Iso/(dataTagPass_Iso+dataTagFail_Iso);
  
  cout << "Final Numbers:" << endl;
  cout << "mcPassID: "    << mcTagPass_ID << endl;
  cout << "mcFailID: "    << mcTagFail_ID << endl;
  cout << "mcPassIso: "   << mcTagPass_Iso << endl;
  cout << "mcFailIso: "   << mcTagFail_Iso << endl;
  
  cout << "dataPassID: "  << dataTagPass_ID << endl;
  cout << "dataFailID: "  << dataTagFail_ID << endl;
  cout << "dataPassIso: " << dataTagPass_Iso << endl;
  cout << "dataFailIso: " << dataTagFail_Iso << endl << endl;
  
  cout << "Efficiencies: " << endl;
  cout << "MC Efficiencies):" << endl;
  cout << "MC ID (Pass/(Pass+Fail)): " << finalMCIDEfficiency << " +/- " << finalErrorMCID*finalMCIDEfficiency << endl;
  cout << "MC Iso (Pass/(Pass+Fail)): " << finalMCIsoEfficiency << " +/- " << finalErrorMCIso*finalMCIsoEfficiency << endl << endl;

  cout << "Data Efficiencies):" << endl;
  cout << "Data ID (Pass/(Pass+Fail)): " << finalDataIDEfficiency << " +/- " << finalErrorDataID*finalDataIDEfficiency << endl;
  cout << "Data Iso (Pass/(Pass+Fail)): " << finalDataIsoEfficiency << " +/- " << finalErrorDataIso*finalDataIsoEfficiency << endl << endl;

  
  /**************************************************
   *          Calculate FInal Scale Factor          *
   **************************************************/
  float finalScaleFactor = (finalDataIsoEfficiency*finalDataIDEfficiency)/(finalMCIsoEfficiency*finalMCIDEfficiency);
  float finalScaleFactorError = sqrt(pow(finalErrorMCID,2)+pow(finalErrorMCIso,2)+pow(finalErrorDataID,2)+pow(finalErrorDataIso,2));
  
  cout << "Final Data to MC Scale Factor: " << finalScaleFactor << " +/- " << finalScaleFactor*finalScaleFactorError << endl;

  
  /**************************************************
   *  Write Histograms                              *
   **************************************************/
  f_histos->cd();
  for (int i = 0; i != 3; ++i)
  {
    h_mcIso[i]->Write();
    h_dataIso[i]->Write();
    if (i != 0)
    {
      h_mcID[i]->Write();
      h_dataID[i]->Write();
    }
  }
  f_histos->Close();
  
  f_ZMC->Close();
  f_Data->Close();
  cout << endl;
  cout << "Success!" << endl;
  cout << "Complete.";
  cout << endl << endl;
}