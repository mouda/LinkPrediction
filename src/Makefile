CC=g++
CFLAGS=-O3
MPI=1
SOURCES=main.cpp utility.cpp socialSystem.cpp graphFactory.cpp \
	fileUtility.cpp problemFactory.cpp \
	attribute.cpp attributeFactory.cpp  commomFriendsAttribute.cpp \
	resourceAllocation.cpp RACScore.cpp\
	linkPredictSolver.cpp solverFactory.cpp
GENSOURCE=genDataSet.cpp graphFactory.cpp fileUtility.cpp utility.cpp
OBJECTS=$(SOURCES:.cpp=.o)
GENOBJECTS=$(GENSOURCE:.cpp=.o)
PREFIX=/home/share
#PREFIX=/opt
INCLUDE=-I$(PREFIX)/armadillo39202/include/ \
	-I$(PREFIX)/boost1550/include/ \
	-I$(PREFIX)/libsvm-3.17/ \
	-I$(PREFIX)/openblas/include \
	-I$(PREFIX)/eigen320/include/eigen3

LIB_PATH=-L$(PREFIX)/armadillo39202/lib/ \
	 -L$(PREFIX)/boost1550/lib \
	 -L$(PREFIX)/libsvm-3.17/ \
	 -L$(PREFIX)/openblas/lib

#LIB_FLAGS=-lsvm -larmadillo  -lboost_regex -lboost_filesystem -lboost_system -lboost_graph -lboost_graph_parallel -lboost_serialization 
LIB_FLAGS=-lsvm \
	  -larmadillo \
	  -lboost_program_options\
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


genDataSet: $(GENOBJECTS) 
	@echo Building $@
	@-$(CC)  $^ $(CFLAGS) $(INCLUDE) $(LIB_PATH) -o $(BIN_PATH)$@ $(LIB_FLAGS) 

linkPrediction: $(OBJECTS)
	@echo Building $@
	@-$(CC)  $^ $(CFLAGS) $(INCLUDE) $(LIB_PATH) -o $(BIN_PATH)$@ $(LIB_FLAGS) 

%.o: %.cpp
	@echo Making $@
	@-$(CC)  $< $(CFLAGS) $(INCLUDE) $(LIB_PATH)  -c -o $@ $(LIB_FLAGS)
clean:
	rm $(BIN_PATH)linkPrediction $(BIN_PATH)genDataSet *.o
