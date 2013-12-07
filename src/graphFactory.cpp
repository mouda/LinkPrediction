#include "graphFactory.h"
#include <utility>

GraphFactory::GraphFactory(const string& inputFileName, 
    const string& outputFileName, const int& wordId):
  m_wordId(wordId), m_numEdge(0)

{
  m_ptrFileUtility = new FileUtility(inputFileName, outputFileName, wordId);

  int vertexNum = m_ptrFileUtility->GetVertexNum();
  m_numVertex = vertexNum;
  m_ptrBglGraph = new BglGraph(vertexNum);
  
    pair<int, int> edgePair;
    edgePair = m_ptrFileUtility->GetEdgePair();

    add_edge(
        vertex(edgePair.first,*m_ptrBglGraph), 
        vertex(edgePair.second,*m_ptrBglGraph),
        BglEdgeWeight(1), 
        *m_ptrBglGraph);
    ++m_numEdge;

    while (edgePair.first >= 0 && edgePair.first < vertexNum ) {
      edgePair = m_ptrFileUtility->GetEdgePair();
      if( !edge(vertex(edgePair.first,*m_ptrBglGraph),
          vertex(edgePair.second,*m_ptrBglGraph),
          *m_ptrBglGraph).second ) {
        add_edge(
            vertex(edgePair.first,*m_ptrBglGraph), 
            vertex(edgePair.second,*m_ptrBglGraph), 
            BglEdgeWeight(1),
            *m_ptrBglGraph);
        ++m_numEdge;
      }
    } 

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

void GraphFactory::dijkstra( const int& startIdx)
{
  BglVertex start = vertex(0,*m_ptrBglGraph);

  // Keeps track of the predecessor of each vertex
  std::vector<BglVertex> p(num_vertices(*m_ptrBglGraph));
  // Keeps track of the distance to each vertex
  std::vector<int> d(num_vertices(*m_ptrBglGraph));

  dijkstra_shortest_paths(*m_ptrBglGraph, start,
                          distance_map(get(vertex_distance, *m_ptrBglGraph)));
}

void GraphFactory::GetNeighbors( const int& idx, std::vector<int>& neighbors )
{
  /* validate */
  BglVertex testVertex = vertex(idx,*m_ptrBglGraph);
  //std::pair<OutEdgeIter,OutEdgeIter> p = out_edges(testVertex,*m_ptrBglGraph);
  BglVertexMap indices = get( vertex_index , *m_ptrBglGraph);

  OutEdgeIter p, p_end;
  for (tie(p, p_end) = out_edges(testVertex,*m_ptrBglGraph) ; p != p_end; ++p) {
    BglVertex sou = source(*p,*m_ptrBglGraph);
    BglVertex tar = target(*p,*m_ptrBglGraph);
    neighbors.push_back(indices[tar]);
  }
} 

void GraphFactory::PrintNeighbors( const int& idx )
{

}
