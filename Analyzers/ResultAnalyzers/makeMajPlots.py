#!/usr/bin/env python

print "Importing modules"
import sys
import optparse
import os
import ROOT
from math import exp, sqrt

print "Setting ROOT options"
ROOT.gROOT.SetBatch()
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(10)
ROOT.gStyle.SetOptFit(111111)
ROOT.gStyle.SetOptTitle(1)
ROOT.gStyle.SetPalette(1)
ROOT.gStyle.SetNdivisions(405,"x");
ROOT.gStyle.SetEndErrorSize(0.)
ROOT.gStyle.SetErrorX(0.001)

##########################
# Dictionary Definitions #
##########################
d_massPoints = {}
d_hists = {}
d_tfiles = {}
d_canv = {}
d_f_scale = {}
d_pad = {}

###########################
# Histograms to loop over #
###########################
#l_histList = ["MET","MuonRel_AllMu"]
#l_histList = ["MuonEta_AllMu","MuonPhi_AllMu","MuonPt_AllMu","MassJJMuMu_Full","","","",""]
l_histList = ["MuonEta_AllMu",#0
              "MuonEta_TightMu",#1
              
              "MuonPhi_AllMu",#2
              "MuonPhi_TightMu",#3
              
              "MuonPt_AllMu",#4
              "MuonPt_AllMu1",#5
              "MuonPt_AllMu2",#6
              
              "MuonPt_TightMu",#7
              "MuonPt_TightMu1",#8
              "MuonPt_TightMu2",#9
              
              "MuonRel_AllMu",#10
              "MuonRel_TightMu",#11
              
              "MuonNum_AllMu",#12
              "MuonNum_TightMu",#13
              
              "Jet_Eta",#14
              "Jet_Phi",#15
              
              "Jet_Pt",#16
              "Jet1_Pt",#17
              "Jet2_Pt",#18
              
              "Jet_Num",#19
              "Jet_Num_AllCuts",#20
              
              "dRJetMu1",#21
              "dRJetMu2",#22
              
              "MassMuMu",#23xxxx
              
              "MassJJ_Full",#24
              "MassJJ_Sel1",#25xxxx
              "MassJJ_Sel2",#26xxxx
              
              "MassJJMuMu_Full",#27
              "MassJJMuMu_Sel1",#28xxxx
              "MassJJMuMu_Sel2",#29xxxx
              
              "MassJJMu1_Full",#30
              "MassJJMu1_Sel1",#31xxxx
              "MassJJMu1_Sel2",#32xxxx
              
              "MassJJMu2_Full",#33
              "MassJJMu2_Sel1",#34xxxx
              "MassJJMu2_Sel2",#35xxxx
              
              "dEtaJJMu1",#36
              "dEtaJJMu2",#37
              "MET",#38
              "MET_wCuts"]#39

##########################
# rootFiles to loop over #
##########################
d_massPoints["R04"] = [70,175,225,275,350,700]
#massPoints["R03"] = [50,70,90,100,175,275,300,350]
#d_massPoints["R04"] = [50,500]

##########################
# Iso Cones to loop over #
##########################
#isoCone = ["R03","R04"]
d_isoCone = ["R04"]

#############################
# Import all the histograms #
#############################
for s_iC in d_isoCone:
   for i_mp in d_massPoints[s_iC]:
      d_tfiles[i_mp] = ROOT.TFile(os.path.join("DataFileOutputs_R04_WPU_V4","MNToMuMu_TuneZ2star_M"+str(i_mp)+".root"))
      for s_hist in l_histList:
         d_hists[s_hist,i_mp,s_iC] = ROOT.TH1F()
         d_tfiles[i_mp].GetObject(s_hist,d_hists[s_hist,i_mp,s_iC])
         d_hists[s_hist,i_mp,s_iC].SetNameTitle(str(i_mp)+s_hist,str(i_mp)+s_hist)

##################
# Make the Plots #
##################
for i_mp in d_massPoints["R04"]:
   ### ROOT Style Options ###
   ROOT.gStyle.SetOptStat(0)

   
   ### Muon Eta Plot ###
      ### ALL Muons
   d_canv[i_mp,l_histList[0]] = ROOT.TCanvas(l_histList[0]+"_MN_"+str(i_mp),l_histList[0]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[0],i_mp,"R04"] = d_canv[i_mp,l_histList[0]].GetPad(0)
   d_pad[l_histList[0],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[0],i_mp,"R04"].SetTitle("All Muon Eta Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[0],i_mp,"R04"].Rebin(25)
   d_hists[l_histList[0],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[0],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[0]] = 1/d_hists[l_histList[0],i_mp,"R04"].GetEntries()
   d_hists[l_histList[0],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[0]])
   d_hists[l_histList[0],i_mp,"R04"].GetXaxis().SetRangeUser(-3.5,3.5)
   d_hists[l_histList[0],i_mp,"R04"].GetYaxis().SetRangeUser(0,0.1)
   d_hists[l_histList[0],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[0],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[0],i_mp,"R04"].GetXaxis().SetTitle("\eta")
   d_hists[l_histList[0],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[0],i_mp,"R04"].GetXaxis().SetTitleOffset(0.5)
   d_hists[l_histList[0],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[0]].SaveAs("Hists/MuonEta/AllMuonEta_"+str(i_mp)+".png")
   
      ### TIGHT Muons
   d_canv[i_mp,l_histList[1]] = ROOT.TCanvas(l_histList[1]+"_MN_"+str(i_mp),l_histList[1]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[1],i_mp,"R04"] = d_canv[i_mp,l_histList[1]].GetPad(0)
   d_pad[l_histList[1],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[1],i_mp,"R04"].SetTitle("Tight Muon Eta Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[1],i_mp,"R04"].Rebin(25)
   d_hists[l_histList[1],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[1],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[1]] = 1/d_hists[l_histList[1],i_mp,"R04"].GetEntries()
   d_hists[l_histList[1],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[1]])
   d_hists[l_histList[1],i_mp,"R04"].GetXaxis().SetRangeUser(-3.5,3.5)
   d_hists[l_histList[1],i_mp,"R04"].GetYaxis().SetRangeUser(0,0.1)
   d_hists[l_histList[1],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[1],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[1],i_mp,"R04"].GetXaxis().SetTitle("\eta")
   d_hists[l_histList[1],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[1],i_mp,"R04"].GetXaxis().SetTitleOffset(0.5)
   d_hists[l_histList[1],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[1]].SaveAs("Hists/MuonEta/TightMuonEta_"+str(i_mp)+".png")

   
   ### Muon Phi Plot ###
      ### ALL Muons
   d_canv[i_mp,l_histList[2]] = ROOT.TCanvas(l_histList[2]+"_MN_"+str(i_mp),l_histList[2]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[2],i_mp,"R04"] = d_canv[i_mp,l_histList[2]].GetPad(0)
   d_pad[l_histList[2],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[2],i_mp,"R04"].SetTitle("All Muon Phi Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[2],i_mp,"R04"].Rebin(25)
   d_hists[l_histList[2],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[2],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[2]] = 1/d_hists[l_histList[2],i_mp,"R04"].GetEntries()
   d_hists[l_histList[2],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[2]])
   d_hists[l_histList[2],i_mp,"R04"].GetYaxis().SetRangeUser(0,0.035)
   d_hists[l_histList[2],i_mp,"R04"].GetXaxis().SetRangeUser(-4.5,4.5)
   d_hists[l_histList[2],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[2],i_mp,"R04"].GetYaxis().SetTitleOffset(1.9)
   d_hists[l_histList[2],i_mp,"R04"].GetXaxis().SetTitle("\phi")
   d_hists[l_histList[2],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[2],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[2],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[2]].SaveAs("Hists/MuonPhi/AllMuonPhi_"+str(i_mp)+".png")
   
      ### TIGHT Muons
   d_canv[i_mp,l_histList[3]] = ROOT.TCanvas(l_histList[3]+"_MN_"+str(i_mp),l_histList[3]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[3],i_mp,"R04"] = d_canv[i_mp,l_histList[3]].GetPad(0)
   d_pad[l_histList[3],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[3],i_mp,"R04"].SetTitle("Tight Muon Phi Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[3],i_mp,"R04"].Rebin(25)
   d_hists[l_histList[3],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[3],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[3]] = 1/d_hists[l_histList[3],i_mp,"R04"].GetEntries()
   d_hists[l_histList[3],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[3]])
   d_hists[l_histList[3],i_mp,"R04"].GetYaxis().SetRangeUser(0,0.035)
   d_hists[l_histList[3],i_mp,"R04"].GetXaxis().SetRangeUser(-4.5,4.5)
   d_hists[l_histList[3],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[3],i_mp,"R04"].GetYaxis().SetTitleOffset(1.9)
   d_hists[l_histList[3],i_mp,"R04"].GetXaxis().SetTitle("\phi")
   d_hists[l_histList[3],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[3],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[3],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[3]].SaveAs("Hists/MuonPhi/TightMuonPhi_"+str(i_mp)+".png")

   ### Muon PT Plot ###
      ### ALL Muons
   d_canv[i_mp,l_histList[4]] = ROOT.TCanvas(l_histList[4]+"_MN_"+str(i_mp),l_histList[4]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[4],i_mp,"R04"] = d_canv[i_mp,l_histList[4]].GetPad(0)
   d_pad[l_histList[4],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[4],i_mp,"R04"].SetTitle("ALL Muon PT Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[4],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[4],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[4],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[4]] = 1/d_hists[l_histList[4],i_mp,"R04"].GetEntries()
   d_hists[l_histList[4],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[4]])
   d_hists[l_histList[4],i_mp,"R04"].GetYaxis().SetRangeUser(0.,0.5)
   d_hists[l_histList[4],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[4],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[4],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[4],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[4],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[4],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[4],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[4]].SaveAs("Hists/MuonPT/AllMuonPT_"+str(i_mp)+".png")

      ### ALL Muon 1
   d_canv[i_mp,l_histList[5]] = ROOT.TCanvas(l_histList[5]+"_MN_"+str(i_mp),l_histList[5]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[5],i_mp,"R04"] = d_canv[i_mp,l_histList[5]].GetPad(0)
   d_pad[l_histList[5],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[5],i_mp,"R04"].SetTitle("ALL Leading Muon PT Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[5],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[5],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[5],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[5]] = 1/d_hists[l_histList[5],i_mp,"R04"].GetEntries()
   d_hists[l_histList[5],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[5]])
   d_hists[l_histList[5],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,0.85)
   d_hists[l_histList[5],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[5],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[5],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[5],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[5],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[5],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[5],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[5]].SaveAs("Hists/MuonPT/AllLeadingMuonPT_"+str(i_mp)+".png")

      ### ALL Muon 2
   d_canv[i_mp,l_histList[6]] = ROOT.TCanvas(l_histList[6]+"_MN_"+str(i_mp),l_histList[6]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[6],i_mp,"R04"] = d_canv[i_mp,l_histList[6]].GetPad(0)
   d_pad[l_histList[6],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[6],i_mp,"R04"].SetTitle("ALL Second Muon PT Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[6],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[6],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[6],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[6]] = 1/d_hists[l_histList[6],i_mp,"R04"].GetEntries()
   d_hists[l_histList[6],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[6]])
   d_hists[l_histList[6],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[6],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[6],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[6],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[6],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[6],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[6],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[6],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[6]].SaveAs("Hists/MuonPT/AllSecondMuonPT_"+str(i_mp)+".png")

      ### TIGHT Muons
   d_canv[i_mp,l_histList[7]] = ROOT.TCanvas(l_histList[7]+"_MN_"+str(i_mp),l_histList[7]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[7],i_mp,"R04"] = d_canv[i_mp,l_histList[7]].GetPad(0)
   d_pad[l_histList[7],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[7],i_mp,"R04"].SetTitle("TIGHT Muon PT Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[7],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[7],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[7],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[7]] = 1/d_hists[l_histList[7],i_mp,"R04"].GetEntries()
   d_hists[l_histList[7],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[7]])
   d_hists[l_histList[7],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,0.5)
   d_hists[l_histList[7],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[7],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[7],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[7],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[7],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[7],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[7],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[7]].SaveAs("Hists/MuonPT/TightMuonPT_"+str(i_mp)+".png")
   
      ### TIGHT Muon 1
   d_canv[i_mp,l_histList[8]] = ROOT.TCanvas(l_histList[8]+"_MN_"+str(i_mp),l_histList[8]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[8],i_mp,"R04"] = d_canv[i_mp,l_histList[8]].GetPad(0)
   d_pad[l_histList[8],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[8],i_mp,"R04"].SetTitle("TIGHT Leading Muon PT Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[8],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[8],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[8],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[8]] = 1/d_hists[l_histList[8],i_mp,"R04"].GetEntries()
   d_hists[l_histList[8],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[8]])
   d_hists[l_histList[8],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[8],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[8],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[8],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[8],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[8],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[8],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[8],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[8]].SaveAs("Hists/MuonPT/TightLeadingMuonPT_"+str(i_mp)+".png")
   
      ### TIGHT Muon 2
   d_canv[i_mp,l_histList[9]] = ROOT.TCanvas(l_histList[9]+"_MN_"+str(i_mp),l_histList[9]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[9],i_mp,"R04"] = d_canv[i_mp,l_histList[9]].GetPad(0)
   d_pad[l_histList[9],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[9],i_mp,"R04"].SetTitle("TIGHT Second Muon PT Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[9],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[9],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[9],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[9]] = 1/d_hists[l_histList[9],i_mp,"R04"].GetEntries()
   d_hists[l_histList[9],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[9]])
   d_hists[l_histList[9],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[9],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[9],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[9],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[9],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[9],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[9],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[9],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[9]].SaveAs("Hists/MuonPT/TightSecondMuonPT_"+str(i_mp)+".png")

   ### Muon Rel Plot ###
      ### ALL Muons
   d_canv[i_mp,l_histList[10]] = ROOT.TCanvas(l_histList[10]+"_MN_"+str(i_mp),l_histList[10]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[10],i_mp,"R04"] = d_canv[i_mp,l_histList[10]].GetPad(0)
   d_pad[l_histList[10],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[10],i_mp,"R04"].SetTitle("ALL Muon Rel Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[10],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[10],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[10],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[10]] = 1/d_hists[l_histList[10],i_mp,"R04"].GetEntries()
   d_hists[l_histList[10],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[10]])
   d_hists[l_histList[10],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[10],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1.)
   d_hists[l_histList[10],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[10],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[10],i_mp,"R04"].GetXaxis().SetTitle("Rel")
   d_hists[l_histList[10],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[10],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[10],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[10]].SaveAs("Hists/MuonRel/AllMuonRel_"+str(i_mp)+".png")
   
      ### ALL Tight Muons
   d_canv[i_mp,l_histList[11]] = ROOT.TCanvas(l_histList[11]+"_MN_"+str(i_mp),l_histList[11]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[11],i_mp,"R04"] = d_canv[i_mp,l_histList[11]].GetPad(0)
   d_pad[l_histList[11],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[11],i_mp,"R04"].SetTitle("ALL Tight Muon Rel Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[11],i_mp,"R04"].Rebin(2)
   d_hists[l_histList[11],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[11],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[11]] = 1/d_hists[l_histList[11],i_mp,"R04"].GetEntries()
   d_hists[l_histList[11],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[11]])
   d_hists[l_histList[11],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[11],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1.)
   d_hists[l_histList[11],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[11],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[11],i_mp,"R04"].GetXaxis().SetTitle("Rel")
   d_hists[l_histList[11],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[11],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[11],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[11]].SaveAs("Hists/MuonRel/AllTightMuonRel_"+str(i_mp)+".png")

   ### Muon Num Plot ###
      ### ALL Muons
   d_canv[i_mp,l_histList[12]] = ROOT.TCanvas(l_histList[12]+"_MN_"+str(i_mp),l_histList[12]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[12],i_mp,"R04"] = d_canv[i_mp,l_histList[12]].GetPad(0)
   d_pad[l_histList[12],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[12],i_mp,"R04"].SetTitle("ALL Muon Num Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[12],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[12],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[12],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[12]] = 1/d_hists[l_histList[12],i_mp,"R04"].GetEntries()
   d_hists[l_histList[12],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[12]])
   d_hists[l_histList[12],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[12],i_mp,"R04"].GetXaxis().SetRangeUser(0.,5.)
   d_hists[l_histList[12],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[12],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[12],i_mp,"R04"].GetXaxis().SetTitle("Num")
   d_hists[l_histList[12],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[12],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[12],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[12]].SaveAs("Hists/MuonNum/AllMuonNum_"+str(i_mp)+".png")

      ### TIGHT Muons
   d_canv[i_mp,l_histList[13]] = ROOT.TCanvas(l_histList[13]+"_MN_"+str(i_mp),l_histList[13]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[13],i_mp,"R04"] = d_canv[i_mp,l_histList[13]].GetPad(0)
   d_pad[l_histList[13],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[13],i_mp,"R04"].SetTitle("TIGHT Muon Num Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[13],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[13],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[13],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[13]] = 1/d_hists[l_histList[13],i_mp,"R04"].GetEntries()
   d_hists[l_histList[13],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[13]])
   d_hists[l_histList[13],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[13],i_mp,"R04"].GetXaxis().SetRangeUser(0.,5.)
   d_hists[l_histList[13],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[13],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[13],i_mp,"R04"].GetXaxis().SetTitle("Num")
   d_hists[l_histList[13],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[13],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[13],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[13]].SaveAs("Hists/MuonNum/TightMuonNum_"+str(i_mp)+".png")

   ### Jet Eta Plot ###
   d_canv[i_mp,l_histList[14]] = ROOT.TCanvas(l_histList[14]+"_MN_"+str(i_mp),l_histList[14]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[14],i_mp,"R04"] = d_canv[i_mp,l_histList[14]].GetPad(0)
   d_pad[l_histList[14],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[14],i_mp,"R04"].SetTitle("All Jet Eta Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[14],i_mp,"R04"].Rebin(25)
   d_hists[l_histList[14],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[14],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[14]] = 1/d_hists[l_histList[14],i_mp,"R04"].GetEntries()
   d_hists[l_histList[14],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[14]])
   d_hists[l_histList[14],i_mp,"R04"].GetXaxis().SetRangeUser(-3.5,3.5)
   d_hists[l_histList[14],i_mp,"R04"].GetYaxis().SetRangeUser(0,0.08)
   d_hists[l_histList[14],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[14],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[14],i_mp,"R04"].GetXaxis().SetTitle("\eta")
   d_hists[l_histList[14],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[14],i_mp,"R04"].GetXaxis().SetTitleOffset(0.5)
   d_hists[l_histList[14],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[14]].SaveAs("Hists/JetEta/AllJetEta_"+str(i_mp)+".png")

   ### Jet Phi Plot ###
   d_canv[i_mp,l_histList[15]] = ROOT.TCanvas(l_histList[15]+"_MN_"+str(i_mp),l_histList[15]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[15],i_mp,"R04"] = d_canv[i_mp,l_histList[15]].GetPad(0)
   d_pad[l_histList[15],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[15],i_mp,"R04"].SetTitle("All Jet Phi Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[15],i_mp,"R04"].Rebin(25)
   d_hists[l_histList[15],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[15],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[15]] = 1/d_hists[l_histList[15],i_mp,"R04"].GetEntries()
   d_hists[l_histList[15],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[15]])
   d_hists[l_histList[15],i_mp,"R04"].GetYaxis().SetRangeUser(0,0.035)
   d_hists[l_histList[15],i_mp,"R04"].GetXaxis().SetRangeUser(-4.5,4.5)
   d_hists[l_histList[15],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[15],i_mp,"R04"].GetYaxis().SetTitleOffset(1.9)
   d_hists[l_histList[15],i_mp,"R04"].GetXaxis().SetTitle("\phi")
   d_hists[l_histList[15],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[15],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[15],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[15]].SaveAs("Hists/JetPhi/AllMJetPhi_"+str(i_mp)+".png")

   ### Jet PT Plot ###
      ### ALL Jets
   d_canv[i_mp,l_histList[16]] = ROOT.TCanvas(l_histList[16]+"_MN_"+str(i_mp),l_histList[16]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[16],i_mp,"R04"] = d_canv[i_mp,l_histList[16]].GetPad(0)
   d_pad[l_histList[16],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[16],i_mp,"R04"].SetTitle("ALL Jet PT Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[16],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[16],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[16],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[16]] = 1/d_hists[l_histList[16],i_mp,"R04"].GetEntries()
   d_hists[l_histList[16],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[16]])
   d_hists[l_histList[16],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[16],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[16],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[16],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[16],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[16],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[16],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[16],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[16]].SaveAs("Hists/JetPT/AllJetPT_"+str(i_mp)+".png")

      ### ALL Jet 1
   d_canv[i_mp,l_histList[17]] = ROOT.TCanvas(l_histList[17]+"_MN_"+str(i_mp),l_histList[17]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[17],i_mp,"R04"] = d_canv[i_mp,l_histList[17]].GetPad(0)
   d_pad[l_histList[17],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[17],i_mp,"R04"].SetTitle("ALL Leading Jet PT Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[17],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[17],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[17],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[17]] = 1/d_hists[l_histList[17],i_mp,"R04"].GetEntries()
   d_hists[l_histList[17],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[17]])
   d_hists[l_histList[17],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,0.85)
   d_hists[l_histList[17],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[17],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[17],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[17],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[17],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[17],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[17],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[17]].SaveAs("Hists/JetPT/AllLeadingJetPT_"+str(i_mp)+".png")

      ### ALL Jet 2
   d_canv[i_mp,l_histList[18]] = ROOT.TCanvas(l_histList[18]+"_MN_"+str(i_mp),l_histList[18]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[18],i_mp,"R04"] = d_canv[i_mp,l_histList[18]].GetPad(0)
   d_pad[l_histList[18],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[18],i_mp,"R04"].SetTitle("ALL Second Jet PT Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[18],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[18],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[18],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[18]] = 1/d_hists[l_histList[18],i_mp,"R04"].GetEntries()
   d_hists[l_histList[18],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[18]])
   d_hists[l_histList[18],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[18],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[18],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[18],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[18],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[18],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[18],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[18],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[18]].SaveAs("Hists/JetPT/AllSecondJetPT_"+str(i_mp)+".png")

   ### Jet Num Plot ###
      ### ALL Jets
   d_canv[i_mp,l_histList[19]] = ROOT.TCanvas(l_histList[19]+"_MN_"+str(i_mp),l_histList[19]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[19],i_mp,"R04"] = d_canv[i_mp,l_histList[19]].GetPad(0)
   d_pad[l_histList[19],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[19],i_mp,"R04"].SetTitle("ALL Jet Num Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[19],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[19],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[19],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[19]] = 1/d_hists[l_histList[19],i_mp,"R04"].GetEntries()
   d_hists[l_histList[19],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[19]])
   d_hists[l_histList[19],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[19],i_mp,"R04"].GetXaxis().SetRangeUser(0.,10.)
   d_hists[l_histList[19],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[19],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[19],i_mp,"R04"].GetXaxis().SetTitle("Num")
   d_hists[l_histList[19],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[19],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[19],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[19]].SaveAs("Hists/JetNum/AllJetNum_"+str(i_mp)+".png")
   
      ### Jets with ALL cuts
   d_canv[i_mp,l_histList[20]] = ROOT.TCanvas(l_histList[20]+"_MN_"+str(i_mp),l_histList[20]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[20],i_mp,"R04"] = d_canv[i_mp,l_histList[20]].GetPad(0)
   d_pad[l_histList[20],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[20],i_mp,"R04"].SetTitle("Jet Num with ALL cuts Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[20],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[20],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[20],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[20]] = 1/d_hists[l_histList[20],i_mp,"R04"].GetEntries()
   d_hists[l_histList[20],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[20]])
   d_hists[l_histList[20],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[20],i_mp,"R04"].GetXaxis().SetRangeUser(0.,10.)
   d_hists[l_histList[20],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[20],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[20],i_mp,"R04"].GetXaxis().SetTitle("Num")
   d_hists[l_histList[20],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[20],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[20],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[20]].SaveAs("Hists/JetNum/JetAllCutsNum_"+str(i_mp)+".png")

   ### Jet Mu dR Plot ###
      ### dR Jet Leading Muon
   d_canv[i_mp,l_histList[21]] = ROOT.TCanvas(l_histList[21]+"_MN_"+str(i_mp),l_histList[21]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[21],i_mp,"R04"] = d_canv[i_mp,l_histList[21]].GetPad(0)
   d_pad[l_histList[21],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[21],i_mp,"R04"].SetTitle("dR Jet Leading Muon for MN Mass "+str(i_mp))
   d_hists[l_histList[21],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[21],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[21],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[21]] = 1/d_hists[l_histList[21],i_mp,"R04"].GetEntries()
   d_hists[l_histList[21],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[21]])
   d_hists[l_histList[21],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[21],i_mp,"R04"].GetXaxis().SetRangeUser(0.,6.)
   d_hists[l_histList[21],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[21],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[21],i_mp,"R04"].GetXaxis().SetTitle("\delta R")
   d_hists[l_histList[21],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[21],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[21],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[21]].SaveAs("Hists/dR/JetMu1_"+str(i_mp)+".png")

   ### dR Jet Second Muon
   d_canv[i_mp,l_histList[22]] = ROOT.TCanvas(l_histList[22]+"_MN_"+str(i_mp),l_histList[22]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[22],i_mp,"R04"] = d_canv[i_mp,l_histList[22]].GetPad(0)
   d_pad[l_histList[22],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[22],i_mp,"R04"].SetTitle("dR Jet Second Muon for MN Mass "+str(i_mp))
   d_hists[l_histList[22],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[22],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[22],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[22]] = 1/d_hists[l_histList[22],i_mp,"R04"].GetEntries()
   d_hists[l_histList[22],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[22]])
   d_hists[l_histList[22],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[22],i_mp,"R04"].GetXaxis().SetRangeUser(0.,6.)
   d_hists[l_histList[22],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[22],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[22],i_mp,"R04"].GetXaxis().SetTitle("\delta R")
   d_hists[l_histList[22],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[22],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[22],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[22]].SaveAs("Hists/dR/JetMu2_"+str(i_mp)+".png")

   ### MuMu Mass ###
   d_canv[i_mp,l_histList[23]] = ROOT.TCanvas(l_histList[23]+"_MN_"+str(i_mp),l_histList[23]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[23],i_mp,"R04"] = d_canv[i_mp,l_histList[23]].GetPad(0)
   d_pad[l_histList[23],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[23],i_mp,"R04"].SetTitle("MuMu Mass Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[23],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[23],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[23],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[23]] = 1/d_hists[l_histList[23],i_mp,"R04"].GetEntries()
   d_hists[l_histList[23],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[23]])
   d_hists[l_histList[23],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[23],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1000.)
   d_hists[l_histList[23],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[23],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[23],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[23],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[23],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[23],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[23]].SaveAs("Hists/MuMuMass/MuMuMass_"+str(i_mp)+".png")

   ### JJ Mass ###
      ### JJ Full
   d_canv[i_mp,l_histList[24]] = ROOT.TCanvas(l_histList[24]+"_MN_"+str(i_mp),l_histList[24]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[24],i_mp,"R04"] = d_canv[i_mp,l_histList[24]].GetPad(0)
   d_pad[l_histList[24],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[24],i_mp,"R04"].SetTitle("ALL JJ Mass Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[24],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[24],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[24],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[24]] = 1/d_hists[l_histList[24],i_mp,"R04"].GetEntries()
   d_hists[l_histList[24],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[24]])
   d_hists[l_histList[24],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[24],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1000.)
   d_hists[l_histList[24],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[24],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[24],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[24],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[24],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[24],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[24]].SaveAs("Hists/JJMass/JJMassFull_"+str(i_mp)+".png")

      ### JJ Select 1
   d_canv[i_mp,l_histList[25]] = ROOT.TCanvas(l_histList[25]+"_MN_"+str(i_mp),l_histList[25]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[25],i_mp,"R04"] = d_canv[i_mp,l_histList[25]].GetPad(0)
   d_pad[l_histList[25],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[25],i_mp,"R04"].SetTitle("Select 1 JJ Mass Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[25],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[25],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[25],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[25]] = 1/d_hists[l_histList[25],i_mp,"R04"].GetEntries()
   d_hists[l_histList[25],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[25]])
   d_hists[l_histList[25],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[25],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1000.)
   d_hists[l_histList[25],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[25],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[25],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[25],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[25],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[25],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[25]].SaveAs("Hists/JJMass/JJMassSel1_"+str(i_mp)+".png")

      ### JJ Select 2
   d_canv[i_mp,l_histList[26]] = ROOT.TCanvas(l_histList[26]+"_MN_"+str(i_mp),l_histList[26]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[26],i_mp,"R04"] = d_canv[i_mp,l_histList[26]].GetPad(0)
   d_pad[l_histList[26],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[26],i_mp,"R04"].SetTitle("Select 2 JJ Mass Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[26],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[26],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[26],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[26]] = 1/d_hists[l_histList[26],i_mp,"R04"].GetEntries()
   d_hists[l_histList[26],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[26]])
   d_hists[l_histList[26],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[26],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1000.)
   d_hists[l_histList[26],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[26],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[26],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[26],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[26],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[26],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[26]].SaveAs("Hists/JJMass/JJMassSel2_"+str(i_mp)+".png")

   ### JJ MuMu Mass ###
      ### JJ MuMu Full
   d_canv[i_mp,l_histList[27]] = ROOT.TCanvas(l_histList[27]+"_MN_"+str(i_mp),l_histList[27]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[27],i_mp,"R04"] = d_canv[i_mp,l_histList[27]].GetPad(0)
   d_pad[l_histList[27],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[27],i_mp,"R04"].SetTitle("JJ MuMu Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[27],i_mp,"R04"].Rebin(2)
   d_hists[l_histList[27],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[27],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[27]] = 1/d_hists[l_histList[27],i_mp,"R04"].GetEntries()
   d_hists[l_histList[27],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[27]])
   d_hists[l_histList[27],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[27],i_mp,"R04"].GetXaxis().SetRangeUser(0.,2000.)
   d_hists[l_histList[27],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[27],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[27],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[27],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[27],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[27],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[27]].SaveAs("Hists/JJMuMu/JJMuMuFull_"+str(i_mp)+".png")

      ### JJ MuMu Select 1
   d_canv[i_mp,l_histList[28]] = ROOT.TCanvas(l_histList[28]+"_MN_"+str(i_mp),l_histList[28]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[28],i_mp,"R04"] = d_canv[i_mp,l_histList[28]].GetPad(0)
   d_pad[l_histList[28],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[28],i_mp,"R04"].SetTitle("JJ MuMU Select 1 Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[28],i_mp,"R04"].Rebin(2)
   d_hists[l_histList[28],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[28],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[28]] = 1/d_hists[l_histList[28],i_mp,"R04"].GetEntries()
   d_hists[l_histList[28],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[28]])
   d_hists[l_histList[28],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[28],i_mp,"R04"].GetXaxis().SetRangeUser(0.,2000.)
   d_hists[l_histList[28],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[28],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[28],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[28],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[28],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[28],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[28]].SaveAs("Hists/JJMuMu/JJMuMuSelect1_"+str(i_mp)+".png")

      ### JJ MuMu Select 2
   d_canv[i_mp,l_histList[29]] = ROOT.TCanvas(l_histList[29]+"_MN_"+str(i_mp),l_histList[29]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[29],i_mp,"R04"] = d_canv[i_mp,l_histList[29]].GetPad(0)
   d_pad[l_histList[29],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[29],i_mp,"R04"].SetTitle("JJ MuMu Select 2 Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[29],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[29],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[29],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[29]] = 1/d_hists[l_histList[29],i_mp,"R04"].GetEntries()
   d_hists[l_histList[29],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[29]])
   d_hists[l_histList[29],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[29],i_mp,"R04"].GetXaxis().SetRangeUser(0.,2000.)
   d_hists[l_histList[29],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[29],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[29],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[29],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[29],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[29],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[29]].SaveAs("Hists/JJMuMu/JJMuMuSelect2_"+str(i_mp)+".png")

   ### JJ Leading Mu Mass ###
         ### ALL JJ Mu 1
   d_canv[i_mp,l_histList[30]] = ROOT.TCanvas(l_histList[30]+"_MN_"+str(i_mp),l_histList[30]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[30],i_mp,"R04"] = d_canv[i_mp,l_histList[30]].GetPad(0)
   d_pad[l_histList[30],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[30],i_mp,"R04"].SetTitle("ALL JJ Leading Muon Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[30],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[30],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[30],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[30]] = 1/d_hists[l_histList[30],i_mp,"R04"].GetEntries()
   d_hists[l_histList[30],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[30]])
   d_hists[l_histList[30],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[30],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1000.)
   d_hists[l_histList[30],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[30],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[30],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[30],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[30],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[30],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[30]].SaveAs("Hists/JJMu1/JJMu1Full"+str(i_mp)+".png")
   
      ### JJ Mu 1 Select 1
   d_canv[i_mp,l_histList[31]] = ROOT.TCanvas(l_histList[31]+"_MN_"+str(i_mp),l_histList[31]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[31],i_mp,"R04"] = d_canv[i_mp,l_histList[31]].GetPad(0)
   d_pad[l_histList[31],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[31],i_mp,"R04"].SetTitle("JJ Leading Muon Select 1 Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[31],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[31],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[31],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[31]] = 1/d_hists[l_histList[31],i_mp,"R04"].GetEntries()
   d_hists[l_histList[31],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[31]])
   d_hists[l_histList[31],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[31],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[31],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[31],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[31],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[31],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[31],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[31]].SaveAs("Hists/JJMu1/JJMu1Select1_"+str(i_mp)+".png")

      ### JJ Mu 1 Select 2
   d_canv[i_mp,l_histList[32]] = ROOT.TCanvas(l_histList[32]+"_MN_"+str(i_mp),l_histList[32]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[32],i_mp,"R04"] = d_canv[i_mp,l_histList[32]].GetPad(0)
   d_pad[l_histList[32],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[32],i_mp,"R04"].SetTitle("JJ Leading Muon Select 2 Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[32],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[32],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[32],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[32]] = 1/d_hists[l_histList[32],i_mp,"R04"].GetEntries()
   d_hists[l_histList[32],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[32]])
   d_hists[l_histList[32],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[32],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1000.)
   d_hists[l_histList[32],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[32],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[32],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[32],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[32],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[32],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[32]].SaveAs("Hists/JJMu1/JJMu1Select2_"+str(i_mp)+".png")
   
   ### JJ Second Mu Mass ###
      ### All JJ Mu 2
   d_canv[i_mp,l_histList[33]] = ROOT.TCanvas(l_histList[33]+"_MN_"+str(i_mp),l_histList[33]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[33],i_mp,"R04"] = d_canv[i_mp,l_histList[33]].GetPad(0)
   d_pad[l_histList[33],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[33],i_mp,"R04"].SetTitle("ALL JJ Second Muon Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[33],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[33],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[33],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[33]] = 1/d_hists[l_histList[33],i_mp,"R04"].GetEntries()
   d_hists[l_histList[33],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[33]])
   d_hists[l_histList[33],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[33],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[33],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[33],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[33],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[33],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[33],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[33],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[33]].SaveAs("Hists/JJMu2/JJMu2All"+str(i_mp)+".png")

      ### JJ Mu 2 Select 1
   d_canv[i_mp,l_histList[34]] = ROOT.TCanvas(l_histList[34]+"_MN_"+str(i_mp),l_histList[34]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[34],i_mp,"R04"] = d_canv[i_mp,l_histList[34]].GetPad(0)
   d_pad[l_histList[34],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[34],i_mp,"R04"].SetTitle("JJ Second Muon Select 1 Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[34],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[34],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[34],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[34]] = 1/d_hists[l_histList[34],i_mp,"R04"].GetEntries()
   d_hists[l_histList[34],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[34]])
   d_hists[l_histList[34],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[34],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[34],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[34],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[34],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[34],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[34],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[34],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[34]].SaveAs("Hists/JJMu2/JJMu2Select1_"+str(i_mp)+".png")

      ### JJ Mu 2 Select 2
   d_canv[i_mp,l_histList[35]] = ROOT.TCanvas(l_histList[35]+"_MN_"+str(i_mp),l_histList[35]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[35],i_mp,"R04"] = d_canv[i_mp,l_histList[35]].GetPad(0)
   d_pad[l_histList[35],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[35],i_mp,"R04"].SetTitle("JJ Second Muon Select 2 Distribution for MN Mass "+str(i_mp))
   #d_hists[l_histList[35],i_mp,"R04"].Rebin(10)
   d_hists[l_histList[35],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[35],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[35]] = 1/d_hists[l_histList[35],i_mp,"R04"].GetEntries()
   d_hists[l_histList[35],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[35]])
   d_hists[l_histList[35],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[35],i_mp,"R04"].GetXaxis().SetRangeUser(0.,1500.)
   d_hists[l_histList[35],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[35],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[35],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[35],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[35],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[35],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[35]].SaveAs("Hists/JJMu2/JJMu2Select2_"+str(i_mp)+".png")

   ### JJ Muon dEta
      ### JJ Mu1
   d_canv[i_mp,l_histList[36]] = ROOT.TCanvas(l_histList[36]+"_MN_"+str(i_mp),l_histList[36]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[36],i_mp,"R04"] = d_canv[i_mp,l_histList[36]].GetPad(0)
   d_pad[l_histList[36],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[36],i_mp,"R04"].SetTitle("dEta JJ Leading Muon Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[36],i_mp,"R04"].Rebin(8)
   d_hists[l_histList[36],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[36],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[36]] = 1/d_hists[l_histList[36],i_mp,"R04"].GetEntries()
   d_hists[l_histList[36],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[36]])
   d_hists[l_histList[36],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[36],i_mp,"R04"].GetXaxis().SetRangeUser(0.,8.)
   d_hists[l_histList[36],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[36],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[36],i_mp,"R04"].GetXaxis().SetTitle("\delta \eta")
   d_hists[l_histList[36],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[36],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[36],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[36]].SaveAs("Hists/dEta/JJMu1dEta"+str(i_mp)+".png")

      ### JJ Mu2
   d_canv[i_mp,l_histList[37]] = ROOT.TCanvas(l_histList[37]+"_MN_"+str(i_mp),l_histList[37]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[37],i_mp,"R04"] = d_canv[i_mp,l_histList[37]].GetPad(0)
   d_pad[l_histList[37],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[37],i_mp,"R04"].SetTitle("dEta JJ Second Muon Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[37],i_mp,"R04"].Rebin(8)
   d_hists[l_histList[37],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[37],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[37]] = 1/d_hists[l_histList[37],i_mp,"R04"].GetEntries()
   d_hists[l_histList[37],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[37]])
   d_hists[l_histList[37],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[37],i_mp,"R04"].GetXaxis().SetRangeUser(0.,8.)
   d_hists[l_histList[37],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[37],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[37],i_mp,"R04"].GetXaxis().SetTitle("\delta \eta")
   d_hists[l_histList[37],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[37],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[37],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[37]].SaveAs("Hists/dEta/JJMu2dEta"+str(i_mp)+".png")

   ### MET ###
      ### MET No Cuts
   d_canv[i_mp,l_histList[38]] = ROOT.TCanvas(l_histList[38]+"_MN_"+str(i_mp),l_histList[38]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[38],i_mp,"R04"] = d_canv[i_mp,l_histList[38]].GetPad(0)
   d_pad[l_histList[38],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[38],i_mp,"R04"].SetTitle("MET No Cuts Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[38],i_mp,"R04"].Rebin(8)
   d_hists[l_histList[38],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[38],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[38]] = 1/d_hists[l_histList[38],i_mp,"R04"].GetEntries()
   d_hists[l_histList[38],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[38]])
   d_hists[l_histList[38],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[38],i_mp,"R04"].GetXaxis().SetRangeUser(0.,500.)
   d_hists[l_histList[38],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[38],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[38],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[38],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[38],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[38],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[38]].SaveAs("Hists/MET/METNoCuts"+str(i_mp)+".png")

      ### MET All Cuts
   d_canv[i_mp,l_histList[39]] = ROOT.TCanvas(l_histList[39]+"_MN_"+str(i_mp),l_histList[39]+"_MN_"+str(i_mp),500,500)
   d_pad[l_histList[39],i_mp,"R04"] = d_canv[i_mp,l_histList[39]].GetPad(0)
   d_pad[l_histList[39],i_mp,"R04"].SetLeftMargin(0.15)
   d_hists[l_histList[39],i_mp,"R04"].SetTitle("MET With Cuts Distribution for MN Mass "+str(i_mp))
   d_hists[l_histList[39],i_mp,"R04"].Rebin(8)
   d_hists[l_histList[39],i_mp,"R04"].SetFillColor(4)
   d_hists[l_histList[39],i_mp,"R04"].SetFillStyle(3002)
   d_f_scale[i_mp,l_histList[39]] = 1/d_hists[l_histList[39],i_mp,"R04"].GetEntries()
   d_hists[l_histList[39],i_mp,"R04"].Scale(d_f_scale[i_mp,l_histList[39]])
   d_hists[l_histList[39],i_mp,"R04"].GetYaxis().SetRangeUser(0.0001,1.0)
   d_hists[l_histList[39],i_mp,"R04"].GetXaxis().SetRangeUser(0.,500.)
   d_hists[l_histList[39],i_mp,"R04"].GetYaxis().SetTitle("Normalized Number of Events")
   d_hists[l_histList[39],i_mp,"R04"].GetYaxis().SetTitleOffset(1.7)
   d_hists[l_histList[39],i_mp,"R04"].GetXaxis().SetTitle("GeV")
   d_hists[l_histList[39],i_mp,"R04"].GetXaxis().SetTitleSize(0.06)
   d_hists[l_histList[39],i_mp,"R04"].GetXaxis().SetTitleOffset(0.7)
   d_hists[l_histList[39],i_mp,"R04"].DrawCopy()
   d_canv[i_mp,l_histList[39]].SaveAs("Hists/MET/METWithCuts"+str(i_mp)+".png")
###
#raw_input()



#         print hists[hist,mp,iC].GetMean()
#			canv.SaveAs("Hists/"+hist+str(mp)+".pdf")
#hists[hist,mp,iC].Draw()
#canv.SaveAs(os.path.join("DataFileOutputs_R"+iC,"hists","R"+str(iC)+hist+str(mp)))
#for iC in isoCone:
#   for mp in massPoints[iC]:
#      for hist in histList:
#         print iC,mp,hists[hist,mp,iC]
#pad = canv.GetPad(0)
#pad.Draw()
#   if i == 0:
#      hists[histList[0],mp,iC].DrawCopy()
#   if i > 0 and i < 3:
#      hists[histList[0],mp,iC].DrawCopy("sames")
#   canv.Update()
#   i += 1

