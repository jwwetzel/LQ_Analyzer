#!/usr/bin/env python

from __future__ import print_function

import sys
import os
import time

path = os.getcwd()

#################################################
###         Input Data/MC File locations      ###
#################################################
mcSetList = "/uscms/home/fgior8/commons/DataSetList_tag11/DY_50_jets.txt"
dataSetList = "/uscms/home/fgior8/commons/DataSetList_tag11/SingleMu.txt"


#################################################
###         Open MC list, count lines         ###
#################################################
with open(mcSetList) as f_mc:
  mcContent = f_mc.readlines()
  mcLength = len(mcContent)

#################################################
###       Open data list, count lines         ###
#################################################
with open(dataSetList) as f_data:
  dataContent = f_data.readlines()
  dataLength = len(dataContent)

#################################################
###              Ask for limits               ###
#################################################
print("MC File has ", str(mcLength),"\n")
mcLimit = input("Enter limit: ")

print("Data File has ", str(dataLength),"\n")
dataLimit = input("Enter limit: ")


#################################################
### Define own range, iterate by steps of 500 ###
#################################################
def my_range(start, end, step):
  while start <= end:
    yield start
    start += step


#################################################
###    Create MC text files for analyzer      ###
#################################################
for x in my_range(500,int(mcLimit),500):
  print("Getting MC Text Files")
  mcFileName = "InputDataSetLists/TPMC_"+str(x)+".txt"
  f = open(mcFileName,'w')
  for y in xrange(x-500,x):
    try:
      line = mcContent[y]
      f.write(line)
    except IndexError:
      print("nope")
  f.close()
  editCommand1 = "sed -e 's:CHANGEME:"+str(x)+":g' condorMCTempTP > CondorSubmissionFiles/condor_MC_"+str(x)
  editCommand2 = "sed -e 's:CHANGEME:"+str(x)+":g' runMCTP_TEMP.sh > CondorSubmissionFiles/run_condor_MC_"+str(x)+".sh"
  os.system(editCommand1)
  os.system(editCommand2)
  os.chdir(path+"/CondorSubmissionFiles")
  os.system("condor_submit condor_MC_"+str(x))
  os.chdir(path)


#################################################
###   Create data text files for analyzer     ###
#################################################
for x in my_range(500,int(dataLimit),500):
  print("Getting Data Text Files")
  dataFileName = "InputDataSetLists/TPData_"+str(x)+".txt"
  f = open(dataFileName,'w')
  for y in xrange(x-500,x):
    try:
      line = dataContent[y]
      f.write(line)
    except IndexError:
      print("nope")
  f.close()

  editCommand1 = "sed -e 's:CHANGEME:"+str(x)+":g' condorDataTempTP > CondorSubmissionFiles/condor_Data_"+str(x)
  editCommand2 = "sed -e 's:CHANGEME:"+str(x)+":g' runDataTP_TEMP.sh > CondorSubmissionFiles/run_condor_Data_"+str(x)+".sh"
  os.system(editCommand1)
  os.system(editCommand2)
  os.chdir(path+"/CondorSubmissionFiles")
  os.system("condor_submit condor_Data_"+str(x))
  os.chdir(path)



















