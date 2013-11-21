#include "fileAdapter.h"

FileAdapter::FileAdapter( const string& m_inputFileName, const string& m_outputFileName )
{
  m_inputFile.open(m_inputFileName.c_str(), ios::in);
  m_outputFile.open(m_outputFileName.c_str(), ios::out); 
}

FileAdapter::~FileAdapter()
{
  m_inputFile.close();
  m_outputFile.close();
}
