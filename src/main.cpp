#include <iostream>
#include <string>

#include "socialSystem.h"
#include "utility.h"


#include <boost/mpi.hpp>

// Enable PBGL interfaces to BGL algorithms
#include <boost/graph/use_mpi.hpp>

// Communicate via MPI
#include <boost/graph/distributed/mpi_process_group.hpp>


using namespace std;

int main( int argc, char* argv[] )
{

  if ( argc != 4 ) {
    cout << "Usage: [input] [output] [percentage]" << endl;
    return 1;
  }
  boost::mpi::environment env(argc,argv);
  boost::mpi::communicator world;

  string inputFileName(argv[1]);
  string outputFileName(argv[2]);

  if (!FileExist(inputFileName)) {
    cerr << "Input file doesn't exist" << endl;
    return 1;
  }

  SocialSystem(inputFileName, outputFileName, world.rank());
  return 0;
}
