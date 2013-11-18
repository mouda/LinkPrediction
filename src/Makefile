CC=g++
CFLAGS=
PREFIX=/home/share
INCLUDE=-I$(PREFIX)/armadillo39202/include/ \
	-I$(PREFIX)/boost1540/include/

LIB_PATH=-L$(PREFIX)/armadillo39202/lib/ \
	 -L$(PREFIX)/boost1540/lib

LIB_FLAGS=-larmadillo -lboost_graph -lboost_regex -lboost_filesystem

BINPATH=../bin/


all: linkPrediction

linkPrediction: main.o utility.o fileHandler.o
	$(CC) $(CFLAGS) $(INCLUDE) $(LIB_PATH) $(LIB_FLAGS) $^ -o $(BINPATH)$@ 

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LIB_PATH) $(LIB_FLAGS) -c $< -o $@

clean:
	rm ../bin/linkPrediction *.o
