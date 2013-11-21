#include <iostream>
#include <string>

#include "socialSystem.h"
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

  FileAdapter fileAdapter(inputFileName, outputFileName);



  return 0;
}
