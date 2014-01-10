../bin/linkPrediction -g ../input/P3_friend/SG1_test_2000.txt  -m model -t ../input/P3_friend/SG1_train_20000.txt
../bin/linkPrediction -g ../input/P3_friend/SG1_test_2000.txt  -m model -i ../input/P3_friend/SG1_query_true_2000.txt -a true
../bin/linkPrediction -g ../input/P3_friend/SG1_test_2000.txt  -m model -i ../input/P3_friend/SG1_query_false_2000.txt -a false
