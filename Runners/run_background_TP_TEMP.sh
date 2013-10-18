#!/bin/sh

cd /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/
#source /uscmst1/prod/sw/cms/bashrc prod
echo `pwd`
eval `scramv1 runtime -sh`

clusterNumber=$1
cd ${_CONDOR_SCRATCH_DIR}

echo "Seeds:"
echo $var0 $var1

cat > rootiamo_job${clusterNumber}.C<<EOF
{
gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/SupportingFiles/Reweight.cc+");
gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/SupportingFiles/Data.cc+");
gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/SupportingFiles/OtherFunctions.cc+");
gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/SupportingFiles/SelectionFunctions.cc+");
gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/Leptons/LeptonSelection.cc+");
gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/Electrons/ElectronSelection.cc+");
gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/Muons/MuonSelection.cc+");
gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/Jets/JetSelection.cc+");
gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/Analyzers/Analyzer.cc+");
gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/SupportingFiles/ChainMaker.C+");

TString extralabel = "";

//////////////////////////////////////////////////////////
//                          MC                          //
//////////////////////////////////////////////////////////

if (1) {
//TChain* chain = ChainMaker("/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/DataSetList/REPLACEME1");
TChain* chain = ChainMaker("/uscms/home/fgior8/commons/DataSetList_tag11/DY_50_jets.txt");

Analyzer Pippo;
Pippo.Init(chain);

// Pippo.SetName("REPLACEME2",13.62);
// Pippo.SetName("REPLACEME2",13);
	Pippo.SetName("DY_50_jets");
//Pippo.SetWeight(10.04, 2194752);
	std::cout << "DY_50_jets\n";
	Pippo.SetEvtN(10000);
	Pippo.SetMC(false,100);
   Pippo.TPLoop();
//Pippo.Loop();
Pippo.WriteRoot();
//     Pippo.~Analyzer();
}
}
EOF

root -l -q -b rootiamo_job${clusterNumber}.C
