/*
 * this module is used for handle file
 * 
 * */
#include <fstream>
#include "graphHandler.h"

using namespace std;

class FileHandler
{
public:
  FileHandler( const string& inputFileName, const string& outputFileName );
  ~FileHandler();

  void parseInput();

private:
  fstream m_inputFile;
  fstream m_outputFile; 
  GraphHandler* m_pGraphHandler; 
};
