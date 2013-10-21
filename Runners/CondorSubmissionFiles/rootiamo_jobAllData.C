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
    TChain* chain = ChainMaker("/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Runners/InputDataSetLists/TPMC_1000.txt");

    Analyzer Pippo;
    Pippo.Init(chain);

    Pippo.SetName("TP_MC_1000_jets");
    std::cout << "TP_MC_1000_jets\n";
    Pippo.SetEvtN(-1);
    Pippo.SetMC(false,100);
    Pippo.TPLoop();
    Pippo.WriteRoot();
    }
}
