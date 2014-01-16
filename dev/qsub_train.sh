SG1_edges=291637
SG2_edges=5622665
SG3_sorted_edges=2842283

#Data="SG3_sorted"
#Data="SG1"
Data="SG2"
suffix="random"


FLAGS="CN RA RAC"
TrainInstances="20000"
for (( i = 5; i <= 20; i=i+5 )); do
  for (( j = 0; j < 10; j++ )); do
    removeEdges=$((SG3_sorted_edges*i/100))
    ../bin/genDataSet ../input/P3_friend/${Data}.txt $removeEdges 20000 ${j} 
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
    ../bin/linkPrediction -g ../input/P3_friend/${Data}_test_${TrainInstances}_${removeEdges}_${j}.txt \
    -m model_${Data}_${suffix}/${Data}_p_${i}_idx_${j}_flag_${token}.model -t ../input/P3_friend/${Data}_train_${TrainInstances}_${removeEdges}_${j}.txt -s ${token} 
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
