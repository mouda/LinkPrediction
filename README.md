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
	a. ./genDataSet [graph file] [number of removed edges] [train instance number] [index]  
4. Train the data, option ``-s'' is used to specisfy similarity score, 
   we provide Common Neighbor (CN), Resource Allocation(RA), and Resource Allocation with Community (RAC) here:
    	b. ./linkPrediction -g [graph file] -m [model file] -t [train file] -s [CN|RA|RAC]
5. Evalutate the model, note that we need to provide the same score option as training procedure:
    	c. ./linkPrediction -g [graph file] -m [model file] -i [inference file] -s [CN|RA|RAC] 

