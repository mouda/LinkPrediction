#include "graphFactory.h"
#include <utility>

GraphFactory::GraphFactory(const string& inputFileName, const string& outputFileName, const int& wordId)
{
  m_ptrFileUtility = new FileUtility(inputFileName, outputFileName, wordId);
  m_ptrBglGraph = new BglGraph();
  //m_ptrFileUtility->parseInput();
  
//  pair<int, int> edgePair;
//  do {
//    edgePair = m_ptrFileUtility->GetEdgePair();
//    cout << edgePair.first << ' ' << edgePair.second << endl;
//  } while(edgePair.first != -1 );
  
}

GraphFactory::~GraphFactory()
{
  delete m_ptrFileUtility;
  delete m_ptrBglGraph;
}
