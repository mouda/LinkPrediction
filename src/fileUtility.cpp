#include "fileUtility.h"

FileUtility::FileUtility( const string& m_inputFileName, const string& m_outputFileName, const int& wordId):
  m_wordId(wordId)
{
  m_inputFile.open(m_inputFileName.c_str(), ios::in);
  m_outputFile.open(m_outputFileName.c_str(), ios::out); 
  string s;
  int col_1, col_2;
  while(!m_inputFile.eof()){
    getline(m_inputFile,s);
    stringstream ss(s);
    ss >> col_1 >> col_2;
    set<int> tmpSet;
    tmpSet.insert(col_1);
    tmpSet.insert(col_2);
    m_edgeSet.insert(tmpSet);
  }

#ifdef DEBUG
  if (m_wordId == 0) {
    set<set<int> >::iterator itUSet = m_edgeSet.begin();
    for (; itUSet != m_edgeSet.end(); ++itUSet) {
      set<int>::iterator itSubSet = itUSet->begin();
      for (; itSubSet != itUSet->end(); ++itSubSet) {
        cout << *itSubSet << ' ';
      }
      cout << endl;
    }
  }
#endif

}

FileUtility::~FileUtility()
{
  m_inputFile.close();
  m_outputFile.close();
}

void
FileUtility::ParseInput()
{
  string col_1;
  string col_2;

}

pair<int, int> FileUtility::GetEdgePair()
{
  string s;
  unsigned int col_1, col_2;
  if (!m_inputFile.eof()) { 
    getline(m_inputFile,s);
    stringstream ss(s);
    ss >> col_1 >> col_2;
    return pair<int, int>(col_1, col_2);
  }
  else {
    return pair<int, int>(-1, -1);
  }
}

unsigned int FileUtility::GetVertex()
{

  return 0;
}

unsigned int FileUtility::GetVertexNum()
{
  return 0;
}
