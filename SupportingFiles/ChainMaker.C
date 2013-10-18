#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TChain.h"
#include "TString.h"
#include "TFile.h"

TChain* ChainMaker(std::string filelist)
{
  std::cout << "In ChainMaker\n";
  std::ifstream fin(filelist.c_str());
  std::string word;

  std::cout << "root file .txt list: input file stream bad? 0 is No, 1 is Yes: " << fin.bad() << "." << endl;

  TChain* chain = new TChain("rootTupleTree/tree");

  if (!chain) std::cout << "\n\nTChain is null!\n\n";

  while ( fin >> word )
  {
    chain->Add( word.c_str() );
  }
  fin.close();
  std::cout << "There are " << chain->GetEntries() << "events" <<  std::endl;
  return chain;

}
