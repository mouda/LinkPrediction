LinkPrediction
==============

Link Prediction

TODO list:


HOWTO execute:

1. Go to $PROJECT/src, complile the main program:
	$ make
2. Compile the testing data generator:
	$ make getDataSet
3. Execution flow, go to $PROJECT/bin/:
	a. ./genDataSet [origin graph file] 1000 1000
4. Train the data:
	b. ./linkPrediction [graph file] [model file] train:<train list file>:true  
5. Evalutate the model:
	c. ./linkPrediction [graph file] [model file] infrence:<query list file>:false

