#include "fileHandler.h"

FileHandler::FileHandler( const string& m_inputFileName, const string& m_outputFileName )
{
  m_inputFile.open(m_inputFileName.c_str(), ios::in);
  m_outputFile.open(m_outputFileName.c_str(), ios::out); 
  m_pGraphHandler = new GraphHandler;
}

FileHandler::~FileHandler()
{
  m_inputFile.close();
  m_outputFile.close();
  delete m_pGraphHandler;
}
