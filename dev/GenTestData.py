#!/usr/bin/python2.7
import random
from subprocess import Popen, PIPE
from subprocess import call
import re
import sys

if (len(sys.argv) != 3):
    print "Usage: [file name] [discard links]"
    exit()

filePath="../input/P3_friend/"
fileName=sys.argv[1]
fileSuffix=".txt"
discardLinkNum=int(sys.argv[2]);
inputFileName=filePath+fileName+fileSuffix
outputTestName=filePath+fileName+"_test_"+str(discardLinkNum)+fileSuffix
outputQueryName=filePath+fileName+"_query_"+str(discardLinkNum)+fileSuffix

inputFile = open(inputFileName);
for line in inputFile:
    pass
maxVertex = int(line.split()[0])
inputFile.close();
linkPairList=[];
inputFile = open(inputFileName, 'r')
print outputTestName
call(["cp",inputFileName, outputTestName])
testOutputFile = open(outputTestName,'r')
while len(linkPairList) < discardLinkNum: 
    nodeIdx = random.randint(0,maxVertex)
    for line in inputFile:
        pair = 2*[int]
        if str(nodeIdx) in line:
            pair[0] = int(line.split()[0])
            pair[1] = int(line.split()[1])
            linkPairList.append(pair)
            inputFile.seek(0)
            break

testOutputFile = open(outputTestName,'w')
queryOutputFile = open(outputQueryName,'w')
print len(linkPairList)
for line in inputFile:
    pair1 = 2*[int]
    pair2 = 2*[int]
    pair1[0] = int(line.split()[0])
    pair1[1] = int(line.split()[1])
    pair2[0] = int(line.split()[1])
    pair2[1] = int(line.split()[0])
    if (pair1 in linkPairList) or (pair2 in linkPairList):
        queryOutputFile.write(line);
    else:
        testOutputFile.write(line);

testOutputFile.close()
queryOutputFile.close()
