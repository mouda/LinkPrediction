Percentage="5 10 15 20"
Flag="CN RA RAC"
Data="SG1"

for p in $Percentage;
do
  for f in $Flag;
  do
    cat result_${Data}/SG1_p_${p}_${f}_true_* > SG1_p_${p}_${f}_true.txt 
    cat result_${Data}/SG1_p_${p}_${f}_false_* > SG1_p_${p}_${f}_false.txt 
  done
done
