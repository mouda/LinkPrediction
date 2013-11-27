CC=g++
CFLAGS=
SOURCES=main.cpp utility.cpp socialSystem.cpp graph.cpp graphFactory.cpp \
	fileUtility.cpp problem.cpp problemFactory.cpp \
	attribute.cpp attributeFactory.cpp \
	solver.cpp solverFactory.cpp
OBJECTS=$(SOURCES:.cpp=.o)
#PREFIX=/home/share
PREFIX=/opt
INCLUDE=-I$(PREFIX)/armadillo39202/include/ \
	-I$(PREFIX)/boost1550/include/

LIB_PATH=-L$(PREFIX)/armadillo39202/lib/ \
	 -L$(PREFIX)/boost1550/lib

LIB_FLAGS=-larmadillo -lboost_graph -lboost_regex -lboost_filesystem -lboost_system

BIN_PATH=../bin/


all: linkPrediction

linkPrediction: $(OBJECTS)
	$(CC)  $^ $(CFLAGS) $(INCLUDE) $(LIB_PATH) $(LIB_FLAGS) -o $(BIN_PATH)$@ 

%.o: %.cpp
	$(CC)  $< $(CFLAGS) $(INCLUDE) $(LIB_PATH) $(LIB_FLAGS) -c -o $@

clean:
	rm $(BIN_PATH)linkPrediction *.o
