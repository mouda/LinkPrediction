CC=g++
#CC=mpic++.mpich2
CFLAGS=
MPI=1
SOURCES=main.cpp utility.cpp socialSystem.cpp graph.cpp graphFactory.cpp \
	fileUtility.cpp problem.cpp problemFactory.cpp \
	attribute.cpp attributeFactory.cpp \
	solver.cpp solverFactory.cpp
OBJECTS=$(SOURCES:.cpp=.o)
#PREFIX=/home/share
PREFIX=/opt
INCLUDE=-I$(PREFIX)/armadillo39202/include/ \
	-I$(PREFIX)/boost1550/include/ \
	-I$(PREFIX)/libsvm-3.17/ \
	-I$(PREFIX)/openblas/include 

LIB_PATH=-L$(PREFIX)/armadillo39202/lib/ \
	 -L$(PREFIX)/boost1550/lib \
	 -L$(PREFIX)/libsvm-3.17/ \
	 -L$(PREFIX)/openblas/lib

#LIB_FLAGS=-lsvm -larmadillo  -lboost_regex -lboost_filesystem -lboost_system -lboost_graph -lboost_graph_parallel -lboost_serialization 
LIB_FLAGS=-lsvm \
	  -larmadillo \
	  -lboost_regex \
	  -lboost_filesystem \
	  -lboost_system \
	  -lboost_graph \
	  -lboost_graph_parallel \
	  -lboost_serialization \
	  -lboost_mpi \
	  -lopenblas 

BIN_PATH=../bin/


all: linkPrediction

linkPrediction: $(OBJECTS)
	@echo Building $@
	@-$(CC)  $^ $(CFLAGS) $(INCLUDE) $(LIB_PATH) -o $(BIN_PATH)$@ $(LIB_FLAGS) 

%.o: %.cpp
	@echo Making $@
	@-$(CC)  $< $(CFLAGS) $(INCLUDE) $(LIB_PATH)  -c -o $@ $(LIB_FLAGS)
clean:
	rm $(BIN_PATH)linkPrediction *.o
