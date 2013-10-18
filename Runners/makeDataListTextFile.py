#!/usr/bin/env python

##
##  This code takes a path as an argument, opens the text files, and runs the code
##

import os
import sys
import time

outDir = '/uscms/home/jwwetzel/WorkingArea/Majorana/CMSSW_5_3_8_LQ/test/LQ_Analyzer/Runners/InputDataSetLists'

i = 0

rootdir = sys.argv[1]
files = os.listdir(rootdir)

for filename in files:
    if 'Combined' in filename:
        if "Mass_50." in filename or "Mass_70." in filename:
            mass = "50"
        else:
            mass = "90"
        print filename
        localFile = os.path.join(outDir,filename[:-5]+".txt")
        dest = open(localFile, 'w')
        dest.write("file:"+os.path.join(rootdir,filename)+'\n') # for local files
        #dest.write("dccp://"+os.path.join(rootdir,filename)+'\n') # for pnfs files
        dest.close()
        command1 = "sed -e 's/REPLACEME1/"+filename[:-5]+".txt/g' ../Analyzers/Analyzer_Baseline_1_temp.cc > ../Analyzers/Analyzer.cc"
        command2 = "sed -e 's/REPLACEME1/"+filename[:-5]+".txt/g' -e 's/REPLACEME2/"+filename[:-5]+"/g' -e 's/SIGMASS/"+mass+"/g' run_background_temp.sh > run_background.sh"
        os.system(command1)
        os.system(command2)
        os.system('./run_background.sh')
