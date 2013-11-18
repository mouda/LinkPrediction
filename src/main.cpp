#include <iostream>
#include <string>
#include <boost/graph/adjacency_list.hpp> // for customizable graphs
#include <boost/graph/directed_graph.hpp> // A subclass to provide reasonable arguments to adjacency_list for a typical directed graph

#include "fileHandler.h"
#include "utility.h"

using namespace std;

int main( int argc, char* argv[] )
{
  if ( argc != 4 ) {
    cout << "Usage: [input] [output] [percentage]" << endl;
    return 1;
  }

  string inputFileName(argv[1]);
  string outputFileName(argv[2]);

  if (!FileExist(inputFileName)) {
    cerr << "Input file doesn't exist" << endl;
    return 1;
  }



  return 0;
}
