#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "socialSystem.h"
#include "utility.h"


//#include <boost/mpi.hpp>

//// Enable PBGL interfaces to BGL algorithms
//#include <boost/graph/use_mpi.hpp>
//
//// Communicate via MPI
//#include <boost/graph/distributed/mpi_process_group.hpp>


using namespace std;

int main( int argc, char* argv[] )
{

  if ( argc != 4 ) {
    cout << "Usage: [input] [model] [train:<train file>|inference:<test file>:<true|false>|printTrain:<train file>|printTest:<file name>:<true|false>]" << endl;
    return 1;
  }
//  boost::mpi::environment env(argc,argv);
//  boost::mpi::communicator world;

  string inputFileName(argv[1]);
  string outputFileName(argv[2]);
  string strFlag(argv[3]);

  if (!FileExist(inputFileName)) {
    cerr << "Input file doesn't exist" << endl;
    return 1;
  }

  SocialSystem mySocialSystem(inputFileName, outputFileName, 0);
  
  vector<string> flagStrings = split(strFlag,':');
  if (flagStrings[0] == "train") {
    if (!FileExist(flagStrings[1])) {
      cerr << "Error: train file doesn't exist" << endl;
      return 1;
    }
    mySocialSystem.Train(flagStrings[1]);
  }
  else if (flagStrings[0] == "inference") {
    if (!FileExist(outputFileName)) {
      cerr << "Error: model file doesn't exist" << endl;
      return 1;
    } 
    if (!FileExist(flagStrings[1])) {
      cerr << "Error: query file doesn't exist" << endl;
      return 1;
    } 

    if (flagStrings[2] == "true") {
      mySocialSystem.ReportCorrectRatio(flagStrings[1], true);
    }
    else if (flagStrings[2] == "false") {
      mySocialSystem.ReportCorrectRatio(flagStrings[1], false);
    }
    else {
      cerr << "Error: unknown predice result" << endl;
    }
  } else if (flagStrings[0] == "printTrain"){
    if (!FileExist(flagStrings[1])) {
      cerr << "Error: train file doesn't exist" << endl;
      return 1;
    }
    mySocialSystem.PrintTrainInstance(flagStrings[1]);
  } else if (flagStrings[0] == "printTest") {

    if (!FileExist(outputFileName)) {
      cerr << "Error: model file doesn't exist" << endl;
      return 1;
    } 
    if (!FileExist(flagStrings[1])) {
      cerr << "Error: query file doesn't exist" << endl;
      return 1;
    } 

    if (flagStrings[2] == "true") {
      mySocialSystem.PrintTestInstance( flagStrings[1], true);
    }
    else if (flagStrings[2] == "false") {
      mySocialSystem.PrintTestInstance( flagStrings[1], false);
    }
    else {
      cerr << "Error: unknown predice result" << endl;
    }

  }
  else {
    cerr << "Error: unknown option" << endl;
  }
  return 0;
}
