#!/usr/bin/env python

from __future__ import print_function

import sys
import os
import time

dataSetList = "/uscms/home/fgior8/commons/DataSetList_tag11/DY_50_jets.txt"

with open(dataSetList) as f:
  content = f.readlines()

### Define own range, iterate by steps of 500
def my_range(start, end, step):
  while start <= end:
    yield start
    start += step

for x in my_range(500,1500,500):
  fileName = "DY_"+str(x)+".txt"
  f = open(fileName,'w')
  for y in xrange(x-500,x):
    try:
      line = content[y]
      f.write(line)
    except IndexError:
      print("nope")
  editCommand1 = "sed -e 's:CHANGEME:"+str(x)+":g' condor_Data_Temp > condor_Data_"+str(x)
  editCommand2 = "sed -e 's:CHANGEME:"+str(x)+":g' run_condor.sh_Temp > run_condor_"+str(x)+".sh"
  editCommand3 = "cp ../AnalyzerTP.cc ../Analyzer"+str(x)+"_005.cc"

  os.system(editCommand1)
  os.system(editCommand2)
  os.system(editCommand3)

  os.system("condor_submit condor_Data_"+str(x))
