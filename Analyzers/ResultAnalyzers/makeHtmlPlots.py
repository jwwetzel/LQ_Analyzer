#!/usr/bin/env python

#############################################################################################################
#                                                                                                           #
#  File: makeHtmlPlots.py                                                                                   #
#  Author: James Wetzel | james-wetzel@uiowa.edu                                                            #
#  Description:  Script to take histograms in a folder and post them to the public area on AFS              #
#  Usage:  $ python makeHtmlPlots.py --options /Directory/to/Histograms                                     #
#  Result:  Creates index.html in /Directory/to/Histograms                                                  #
#                                                                                                           #
#  NOTES:  This only works if the images are in path structure:                                             #
#          Directory/Plots1/images_n.pdf                                                                    #
#          Directory/Plots2/images_n.pdf                                                                    #
#          index.html will be created in Directory/index.html                                               #
#                                                                                                           #
#          In this case arguments would be:                                                                 #
#                  $ python makeHtmlPlots.py Directory/                                                     #
#                                                                                                           #
#           For the page at http://home.fnal.gov/~jwwetzel/MN/Plots, I execute the following:               #
#                                                                                                           #
#  $ python makeHtmlPlots.py Hists --rw 3 --img png --s 400; cp -r Hists/* ~/afshome/public_html/MN/Plots/  #
#                                                                                                           #
#  My directory structure is Hists/MuonPhi/images...                                                        #
#                            Hists/MuonEta/images...                                                        #
#                            .                                                                              #
#                            .                                                                              #
#                            .                                                                              #
#############################################################################################################


######################
## Conventions:     ##
## d_ = Dictionary  ##
## s_ = String      ##
## i_ = Int         ##
## f_ = Float       ##
## l_ = List        ##
## h_ = Histogram   ##
######################

import sys
import optparse
import commands
import os
import glob

#######################
# Get options         #
#######################

parser = optparse.OptionParser("usage: %prog [options]\
                               <input directory> \n")

#parser.add_option ('--t', dest='title', type='string',
#                   default = 'Plots',
#                   help="Title of html page.")
parser.add_option ('--s', dest='size', type='int',
                   default = 100,
                   help="Size of displayed plots.")
parser.add_option ('--rw', dest='rowWidth', type='int',
                   default = -1,
                   help="Size of displayed plots.")
parser.add_option ('--ext', type="string",
                   dest="ext", default="png",
                   help="Format of linked image.")
parser.add_option ('--img', type='string',
                   dest="img", default="png",
                   help="Format of displayed image.")
options, args = parser.parse_args()


if len(args) != 1:
  print "Please specify input dir.  Exiting."
  sys.exit()

s_indir  = args[0]+"/"
#title = options.title
size = options.size
ext = options.ext
img = options.img
i_rowWidth = options.rowWidth

###############
# Check dir   #
###############
if not os.path.isdir(s_indir) :
  print "Cannot find %s.  Exiting." % infile
  sys.exit()

#if title == "make":
#  print s_indir
#  sindir = s_indir.split("/")
#  # remove white spaces
#  while '' in sindir: sindir.remove('')
#  print sindir
#  title = sindir[len(sindir)-1]
#  print len(sindir)-1
#  print title


###############################
# Create new index.html file  #
###############################
os.system("rm -f "+s_indir+"index.html")
os.system("touch "+s_indir+"index.html")
findex = open(s_indir+"index.html","w")

#print >> findex, "<h1> "+title+"</h1>"
#print >> findex, "<style>"
#print >> findex, "h1 {page-break-before: always;}"
#print >> findex, "</style>"
#print >> findex, "<hr>\n"


############################
# Format Default Row Width #
############################
if i_rowWidth == -1:
  if int(size) <= 300:
    i_rowWidth = 3
  else:
    i_rowWidth = 2

#################
# Create Table  #
#################
print >> findex, "<style>"
print >> findex, "#top {"
print >> findex, "color: white;"
print >> findex, "width: 150px;"
print >> findex, "background-color: white;"
print >> findex, "right:0px;"
print >> findex, "float:right;"
print >> findex, "position: fixed;"
print >> findex, "}"

print >> findex, "#content {"
#print >> findex, "padding-top: 150px;"
print >> findex, "}"

print >> findex, "</style>"

j = 0
print >> findex, '<div id="top">'
print >> findex, '<table width="800">'
print >> findex, '<tr>'

##############################
# List links to folder names #
##############################
for folder, subs, files in os.walk(s_indir):
    files.sort()
    s_title = folder.split("/")[-1]
    if j >= 1:
        print >> findex, '<td><a href="#'+s_title+'"><b>'+s_title+'</b></a></td>'
        if j != 0 and j % 1 == 0:
            print >> findex, '</tr>'
    j += 1
print >> findex, "</table>"
print >> findex, "<hr>"
print >> findex, "</div>"
print >> findex, '<div id="content">'
print >> findex, "<table>"

######################################
# Begin plot creation and formatting #
######################################
i = 0
for folder, subs, files in os.walk(s_indir):
  files.sort()
  s_title = folder.split("/")[-1]
  if i >= 1:
    nfile = 0
    #################################################################################################
    # Convert images to format/size, stores them in same directory as image, adds small to filename #
    #################################################################################################
    for file in files:
      base = os.path.splitext(file)[0]
      if 'small' not in base and size != 100:
        command = "convert %s/%s/%s.%s -resize %sx%s %s/%s/%s_small.%s" % (s_indir,s_title,base, ext, size, size, s_indir, s_title,base, img)
        print "Processing", file
        os.system(command)
    
      ###############################################################################################
      # Creates table rows filled with histograms, using small images linked to the original images #
      ###############################################################################################
      if 'small' not in base:
        if nfile == 0: print >> findex, '<tr id="'+s_title+'"><td><h2>'+s_title+'</h2></td></tr><tr>'
        print >> findex, '<td><a href="'+s_title+'/'+file+'"><img src="'+s_title+'/'+base+'_small.'+img+'"></a></td>'
        nfile += 1
        if nfile % i_rowWidth == 0:
          print >> findex, "</tr>\n<tr>"
        if nfile % 9 == 0 and nfile != 0:
          print >> findex, "</tr></table><p style=\"page-break-before: always\"></p><table><tr>"
        ################################################
        # nfile % 19 because there are 13 mass points: #
        ################################################
        if nfile % 19 == 0 and nfile != 0:
          print >> findex, "</tr></table><p style=\"page-break-before: always\"></p><table>"
          nfile = 0
  i += 1

print >> findex, "</tr>\n</table>\n"
print >> findex, "</div>"

findex.close()









