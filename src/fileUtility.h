/*
 * this module is used for handle file
 * 
 * */
#include <fstream>

using namespace std;

class FileUtility
{
  public:
    FileUtility( const string& inputFileName, const string& outputFileName );
    ~FileUtility();

    void parseInput();

  private:
    fstream m_inputFile;
    fstream m_outputFile; 
};
