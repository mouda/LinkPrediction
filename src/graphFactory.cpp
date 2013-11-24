#include "graphFactory.h"
#include <utility>

GraphFactory::GraphFactory(const string& inputFileName, 
    const string& outputFileName, const int& wordId):m_wordId(wordId)
{
  m_ptrFileUtility = new FileUtility(inputFileName, outputFileName, wordId);

  int vertexNum = m_ptrFileUtility->GetVertexNum();
  m_ptrBglGraph = new BglGraph(vertexNum);
  
  if (process_id(m_ptrBglGraph->process_group()) == 0) { 
    pair<int, int> edgePair;
    edgePair = m_ptrFileUtility->GetEdgePair();

    add_edge(vertex(edgePair.first,*m_ptrBglGraph), vertex(edgePair.second,*m_ptrBglGraph), *m_ptrBglGraph);

    while (edgePair.first >= 0 && edgePair.first < vertexNum ) {
      edgePair = m_ptrFileUtility->GetEdgePair();
    } 
  }
  synchronize(m_ptrBglGraph->process_group());

#ifdef DEBUG 
  if (process_id(m_ptrBglGraph->process_group()) == 0) {
    cout << GetVertexId(10) << endl;
  }
#endif

}

GraphFactory::~GraphFactory()
{
  delete m_ptrFileUtility;
  delete m_ptrBglGraph;
}

int GraphFactory::GetVertexId( const int& index) 
{
  BglVertexMap indices = get( vertex_index , *m_ptrBglGraph);
  BglVertex source = vertex(index,*m_ptrBglGraph);
  return indices[source];
} 

void GraphFactory::BFS( const int& index)
{
  property_map<BglGraph, vertex_distance_t>::type distance =
    get(vertex_distance, *m_ptrBglGraph);

}
