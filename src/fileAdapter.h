/*
 * this module is used for handle file
 * 
 * */
#include <fstream>

using namespace std;

class FileAdapter
{
  public:
    FileAdapter( const string& inputFileName, const string& outputFileName );
    ~FileAdapter();

    void parseInput();

  private:
    fstream m_inputFile;
    fstream m_outputFile; 
};
