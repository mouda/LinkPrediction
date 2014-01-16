SG1_edges=291637
SG2_edges=5622665
SG3_sorted_edges=2842283

Data="SG3_sorted"

#Data="SG1"

suffix="random"
FLAGS="CN RA RAC"
TrainInstances="20000"
for (( i = 5; i <= 20; i=i+5 )); do
  removeEdges=$((SG3_sorted_edges*i/100))
  for (( j = 0; j < 10; j++ )); do
    for token in $FLAGS;
    do
    echo "
    ### Job name
    #PBS -N DM_${i}%_${j}_${token} 
    ### out files
    #PBS -e ./log/DM_${i}%_${j}_${token}.err 
    #PBS -o ./log/DM_${i}%_${j}_${token}.log 
    ### put the job to which queue (qwork)
    #PBS -q qwork" > ./run_temp.sh
    echo ' 
    echo Working directory is $PBS_O_WORKDIR
    cd $PBS_O_WORKDIR
    echo running on host `hostname`
    echo Start time is `date`
    time1=`date +%s`
    echo Directory is `pwd`' >> ./run_temp.sh
    echo " 
    ../bin/linkPrediction -g ../input/P3_friend/${Data}_test_${TrainInstances}_${removeEdges}_${j}.txt -m model_${Data}/${Data}_p_${i}_idx_${j}_flag_${token}.model \
    -i ../input/P3_friend/${Data}_query_true_${removeEdges}_${j}.txt -a true -s ${token} >> result_${Data}_${suffix}/${Data}_p_${i}_${token}_true_${j}.txt
    ../bin/linkPrediction -g ../input/P3_friend/${Data}_test_${TrainInstances}_${removeEdges}_${j}.txt -m model_${Data}/${Data}_p_${i}_idx_${j}_flag_${token}.model \
    -i ../input/P3_friend/${Data}_query_false_${removeEdges}_${j}.txt -a false -s ${token} >> result_${Data}_${suffix}/${Data}_p_${i}_${token}_false_${j}.txt
    " >> ./run_temp.sh
    echo '
    echo End time is `date`
    time2=`date +%s`
    echo Computing time is `echo $time2-$time1 | bc` sec
    ' >> ./run_temp.sh
    qsub run_temp.sh
    done
  done
done

