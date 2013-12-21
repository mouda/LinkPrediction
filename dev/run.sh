../bin/linkPrediction ../input/P3_friend/SG1_test_2000.txt ../output/SG1_model_2000.model train:../input/P3_friend/SG1_train_20000.txt
../bin/linkPrediction ../input/P3_friend/SG1_test_2000.txt ../output/SG1_model_2000.model inference:../input/P3_friend/SG1_query_true_2000.txt:true
../bin/linkPrediction ../input/P3_friend/SG1_test_2000.txt ../output/SG1_model_2000.model inference:../input/P3_friend/SG1_query_false_2000.txt:false
