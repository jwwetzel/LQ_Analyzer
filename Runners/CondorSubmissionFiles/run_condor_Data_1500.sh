#!/bin/sh

cd /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/
source /uscmst1/prod/sw/cms/bashrc prod
eval `scramv1 runtime -sh`

clusterNumber=$1
cd ${_CONDOR_SCRATCH_DIR}

cp -r /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/SupportingFiles/ .
cp -r /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Leptons/ .
cp -r /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Electrons/ .
cp -r /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Muons/ .
cp -r /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Jets/ .
cp -r /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Analyzers/ .
cp -r /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Data/ .
cp -r /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Plots/ .

cat > rootiamo_job${clusterNumber}.C<<EOF
{
  gROOT->ProcessLine(".L SupportingFiles/Reweight.cc+");
  gROOT->ProcessLine(".L SupportingFiles/Data.cc+");
  gROOT->ProcessLine(".L SupportingFiles/OtherFunctions.cc+");
  gROOT->ProcessLine(".L SupportingFiles/SelectionFunctions.cc+");
  gROOT->ProcessLine(".L Leptons/LeptonSelection.cc+");
  gROOT->ProcessLine(".L Electrons/ElectronSelection.cc+");
  gROOT->ProcessLine(".L Muons/MuonSelection.cc+");
  gROOT->ProcessLine(".L Jets/JetSelection.cc+");
  gROOT->ProcessLine(".L Analyzers/Analyzer.cc+");
  gROOT->ProcessLine(".L SupportingFiles/ChainMaker.C+");

  TString extralabel = "";

  //////////////////////////////////////////////////////////
  //                          MC                          //
  //////////////////////////////////////////////////////////

  if (1)
  {
    TChain* chain = ChainMaker("/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Runners/InputDataSetLists/TPData_1500.txt");

    Analyzer Pippo;
    Pippo.Init(chain);

    Pippo.SetName("TP_Data_1500_jets");
    std::cout << "TP_Data_1500_jets\n";
    Pippo.SetEvtN(-1);
    Pippo.SetMC(false,100);
    Pippo.TPLoop();
    Pippo.WriteRoot();
    }
}
EOF

root -l -q -b rootiamo_job${clusterNumber}.C