
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>  
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp> 

#include "graphFactory.h"
#include "utility.h"




using namespace std;
using namespace boost;

typedef vector< string > split_vector_type;
int main( int argc, char* argv[] )
{

  if ( argc != 4 ) {
    cout << "Usage: [input] [query number] [testing number]" << endl;
    return 1;
  }

  string inputFileName(argv[1]);
  int intQueryNum = atoi(argv[2]);
  int intTestNum = atoi(argv[3]);

  if (!FileExist(inputFileName)) {
    cerr << "Input file doesn't exist" << endl;
    return 1;
  }

  split_vector_type vecTokens;
  split( vecTokens, inputFileName, is_any_of("\."), token_compress_on );
  stringstream ss;

  ss << intTestNum;
  string outputTrainFileName = ".."+vecTokens[1] + "_train_"+ss.str()+".txt";
  ss.str("");
  ss << intQueryNum;
  string outputTestFileName  = ".."+vecTokens[1] + "_test_"+ss.str()+".txt";
  string outputQueryFileName = ".."+vecTokens[1] + "_query_"+ss.str()+".txt";
  cout << outputTrainFileName << endl;
  cout << outputTestFileName << endl;
  cout << outputQueryFileName << endl;
  GraphFactory myGraphFactory(inputFileName, "NULL",0);

  return 0;
}
