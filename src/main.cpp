#include <iostream>
#include <string>
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

  if ( argc != 5 ) {
    cout << "Usage: [input] [output] [percentage] [train/inference]" << endl;
    return 1;
  }
//  boost::mpi::environment env(argc,argv);
//  boost::mpi::communicator world;

  string inputFileName(argv[1]);
  string outputFileName(argv[2]);
  string strEdgeRemoveRatio(argv[3]);
  string strFlag(argv[4]);
  stringstream ss;
  double valEdgeRemoveRatio = 0;
  ss << strEdgeRemoveRatio;
  ss >> valEdgeRemoveRatio;

  if (!FileExist(inputFileName)) {
    cerr << "Input file doesn't exist" << endl;
    return 1;
  }

  SocialSystem mySocialSystem(inputFileName, outputFileName, 0);
  
  if (strFlag == "train") {
    mySocialSystem.Train();
  }
  else if (strFlag == "inference") {
    if (!FileExist("model.mod")) {
      cerr << "Error: model file doesn't exist" << endl;
    } 
    mySocialSystem.ReportCorrectRatio();
  }
  return 0;
}
