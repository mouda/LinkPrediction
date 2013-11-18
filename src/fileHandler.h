/*
 * this module is used for handle file
 * 
 * */
#include <fstream>

using namespace std;

class FileHandler
{
public:
  FileHandler( const string& inputFileName, const string& outputFileName );
  ~FileHandler();

private:
  fstream inputFile;
  fstream outputFile; 
};
