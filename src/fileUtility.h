/*
 * this module is used for handle file
 * 
 * */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <set>

#include "utility.h"

using namespace std;

class FileUtility
{
  public:
    FileUtility( const string& inputFileName, const string& outputFileName, 
        const int& wordId);
    ~FileUtility();

    void ParseInput();
    pair<int, int> GetEdgePair();
    unsigned int GetVertex();
    int GetVertexNum();


  private:
    ifstream m_inputFile;
    ofstream m_outputFile; 
    set<set<int> > m_edgeSet;

    const int      m_wordId;
};
