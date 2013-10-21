#!/bin/sh

cd /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/
source /uscmst1/prod/sw/cms/bashrc prod
#echo `pwd`
eval `scramv1 runtime -sh`
export CMSSW_SEARCH_PATH=${CMSSW_SEARCH_PATH}:`pwd`
cd -

clusterNumber=$1
#list=$2
#num=$3

cd ${_CONDOR_SCRATCH_DIR}

echo "Seeds:"
echo $var0 $var1

cp /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/*.cc .
cp /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/ChainMaker.C .
cp /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/*.h .

mv AnalyzerCHANGEME_005.cc Analyzer.cc

cat > rootiamo_job${clusterNumber}.C<<EOF
{
  gROOT->ProcessLine(".L Reweight.cc+");
  gROOT->ProcessLine(".L Data.cc+");
  gROOT->ProcessLine(".L OtherFunctions.cc+");
  gROOT->ProcessLine(".L SelectionFunctions.cc+");
  gROOT->ProcessLine(".L LeptonSelection.cc+");
  gROOT->ProcessLine(".L ElectronSelection.cc+");
  gROOT->ProcessLine(".L MuonSelection.cc+");
  gROOT->ProcessLine(".L JetSelection.cc+");
  gROOT->ProcessLine(".L Analyzer.cc+");
  gROOT->ProcessLine(".L ChainMaker.C+");

  TString extralabel = "";

  //////////////////////////////////////////////////////////
  //                          MC                          //
  //////////////////////////////////////////////////////////

  if (1) {
	TChain* chain = ChainMaker("/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/TPData/DY_CHANGEME.txt");
	//TChain* chain = ChainMaker("/uscms/home/wclarida/MajCode/CMSSW_5_3_3_patch2_LQ/test/LQanalyzer/DataSetList/DoubleMu.txt");

   Analyzer Pippo; 
   Pippo.Init(chain); 
//    Pippo.SetName("Data_DoubleMuA",13.62); 
//    Pippo.SetName("Data_DoubleMu_04_wPU_May6"); 
	Pippo.SetName("DY_NoRegion_TPStudy_CHANGEME_RelIso_005");
    //Pippo.SetWeight(10.04, 2194752);
     std::cout << "DY\n";  
     Pippo.SetEvtN(-1);
     Pippo.SetMC(false);
     Pippo.TPLoop();
//     Pippo.Loop();
     Pippo.WriteRoot();
//     Pippo.~Analyzer();
  }
}
EOF

root -l -q -b rootiamo_job${clusterNumber}.C

rm *.cc
rm *.h
rm ChainMaker.C

cp *.root /uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQanalyzer/TPData/RelIsoStudyData/

