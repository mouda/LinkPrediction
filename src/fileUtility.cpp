#include "fileUtility.h"

FileUtility::FileUtility( const string& m_inputFileName, const int& wordId):
  m_wordId(wordId)
{
  m_inputFile.open(m_inputFileName.c_str());

#ifdef DEBUG
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
  int col_1, col_2;
  if (m_inputFile.good()) { 
    getline(m_inputFile,s,'\n');
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

int FileUtility::GetVertexNum()
{
  string line = GetLastLine(m_inputFile);
  int maxNum;
  stringstream ss(line);
  ss >> maxNum;
  return maxNum;
}

