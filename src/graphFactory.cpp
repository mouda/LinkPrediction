#include "graphFactory.h"
#include <utility>

GraphFactory::GraphFactory(const string& inputFileName, 
    const string& outputFileName, const int& wordId):m_wordId(wordId)
{
  m_ptrFileUtility = new FileUtility(inputFileName, outputFileName, wordId);

  int vertexNum = m_ptrFileUtility->GetVertexNum();
  m_ptrBglGraph = new BglGraph(vertexNum);
  //m_ptrFileUtility->parseInput();

  
  if (process_id(m_ptrBglGraph->process_group()) == 0) { 
    pair<int, int> edgePair;
    edgePair = m_ptrFileUtility->GetEdgePair();
    add_edge(vertex(edgePair.first,*m_ptrBglGraph), vertex(edgePair.second,*m_ptrBglGraph), *m_ptrBglGraph);
    while (edgePair.first >= 0 && edgePair.first < vertexNum ) {
      edgePair = m_ptrFileUtility->GetEdgePair();
    } 
  }
  synchronize(m_ptrBglGraph->process_group());
}

GraphFactory::~GraphFactory()
{
  delete m_ptrFileUtility;
  delete m_ptrBglGraph;
}
