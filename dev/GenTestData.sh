#!/bin/bash
filePath="../input/P3_friend/"
fileName="SG1"
fileSuffix=".txt"
FullName=$filePath$fileName$fileSuffix 

outputTestName=$filePath$fileName"_test"$fileSuffix
outputQueryName=$filePath$fileName"_query"$fileSuffix
maxNodeNum=`cat $FullName | awk 'END{print $1}'`
fileLength=`cat $FullName | wc -l`
edgeNum=$(($fileLength / 2))
discardLinkNum=1;
cp $FullName $outputTestName 
for (( i = 0; i < discardLinkNum; i++ )); do
  select=$(($RANDOM%$maxNodeNum)) 
  echo $select 
  A=`cat $FullName | grep $select | awk 'END{print }'`
  B=($A)
  echo ${B[@]} | sed 's/ /\n/g' | sort
  echo ${B[@]} | sed 's/ /\n/g' | sort -r -n | tr ' ' '\n'
#  for each in ${B[@]};do
#    echo $each
#  done > Fxxk

#  cat $outputTestName | grep -v ${list[0]}" "${list[1]}  > $outputTestName
#  cat $outputTestName | grep -v ${list[1]}" "${list[0]}  > $outputTestName
#  cat $outputTestName | grep ${list[0]}" "${list[1]} 
#  cat $outputTestName | grep ${list[1]}" "${list[0]}
  
done
