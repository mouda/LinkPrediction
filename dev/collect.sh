Percentage="5 10 15 20"
Flag="CN RA RAC"
Data="SG3_sorted"
suffix="random"

for p in $Percentage;
do
  for f in $Flag;
  do
    cat result_${Data}_${suffix}/${Data}_p_${p}_${f}_true_* > ${Data}_${suffix}_p_${p}_${f}_true.txt 
    cat result_${Data}_${suffix}/${Data}_p_${p}_${f}_false_* > ${Data}_${suffix}_p_${p}_${f}_false.txt 
  done
done
