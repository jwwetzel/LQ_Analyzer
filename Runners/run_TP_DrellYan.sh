#!/bin/sh

cd /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/
source /uscmst1/prod/sw/cms/bashrc prod
echo `pwd`
eval `scramv1 runtime -sh`

clusterNumber=$1
cd ${_CONDOR_SCRATCH_DIR}

cat > rootiamo_job${clusterNumber}.C<<EOF
{
	gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/SupportingFiles/Reweight.cc+");
	gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/SupportingFiles/Data.cc+");
	gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/SupportingFiles/OtherFunctions.cc+");
	gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/SupportingFiles/SelectionFunctions.cc+");
	gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Leptons/LeptonSelection.cc+");
	gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Electrons/ElectronSelection.cc+");
	gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Muons/MuonSelection.cc+");
	gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Jets/JetSelection.cc+");
	gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Analyzers/Analyzer.cc+");
	gROOT->ProcessLine(".L /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/SupportingFiles/ChainMaker.C+");

	TString extralabel = "";

	//////////////////////////////////////////////////////////
	//                          MC                          //
	//////////////////////////////////////////////////////////

	if (1)
	{
		TChain* chain = ChainMaker("/uscms/home/fgior8/commons/DataSetList_tag11/DY_50_jets.txt");
	
		Analyzer Pippo;
		Pippo.Init(chain);

		Pippo.SetName("DY_50_jets",1.0);
		std::cout << "DY_50_jets\n";
		Pippo.SetEvtN(-1);
		Pippo.SetMC(false,100);
   	Pippo.TPLoop();
		Pippo.WriteRoot();
	}
}
EOF

root -l -q -b rootiamo_job${clusterNumber}.C
