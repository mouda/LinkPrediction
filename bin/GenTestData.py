#!/usr/bin/python2.6
import random

filePath="../input/P3_friend/"
fileName="SG1"
fileSuffix=".txt"
discardLinkNum=1;
outputTestName=filePath+fileName+"_test"+fileSuffix
outputQueryName=filePath+fileName+"_query"+fileSuffix

inputFile = open(filePath+fileName+fileSuffix);
for line in inputFile:
    #print line.split()[1], line.split()[1]
    pass
maxVertex = int(line.split()[0])
inputFile.close();
inputFile = open(filePath+fileName+fileSuffix)
for i in range(discardLinkNum):
    print random.randint(0,maxVertex)

