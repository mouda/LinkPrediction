#include "graphFactory.h"
#include <utility>

GraphFactory::GraphFactory(const string& inputFileName, 
    const string& outputFileName, const int& wordId):m_wordId(wordId)
{
  m_ptrFileUtility = new FileUtility(inputFileName, outputFileName, wordId);

  int vertexNum = m_ptrFileUtility->GetVertexNum();
  m_ptrBglGraph = new BglGraph(vertexNum);
  
  //if (process_id(m_ptrBglGraph->process_group()) == 0) { 
    pair<int, int> edgePair;
    edgePair = m_ptrFileUtility->GetEdgePair();

    add_edge(
        vertex(edgePair.first,*m_ptrBglGraph), 
        vertex(edgePair.second,*m_ptrBglGraph),
        BglEdgeWeight(1), 
        *m_ptrBglGraph);

    while (edgePair.first >= 0 && edgePair.first < vertexNum ) {
      edgePair = m_ptrFileUtility->GetEdgePair();
      add_edge(
          vertex(edgePair.first,*m_ptrBglGraph), 
          vertex(edgePair.second,*m_ptrBglGraph), 
          BglEdgeWeight(1),
          *m_ptrBglGraph);
    } 
  //}
  //synchronize(m_ptrBglGraph->process_group());

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
  // Compute shortest paths from vertex 0
  distance_map(get(vertex_distance, *m_ptrBglGraph));
//  color_map(get(vertex_color,*m_ptrBglGraph));
  BglColorMap colorMap;

  // Keeps track of the predecessor of each vertex
  std::vector<BglVertex> p(num_vertices(*m_ptrBglGraph));
  // Keeps track of the distance to each vertex
  std::vector<int> d(num_vertices(*m_ptrBglGraph));

  dijkstra_shortest_paths(*m_ptrBglGraph, start,
                          distance_map(get(vertex_distance, *m_ptrBglGraph)));
//  dijkstra_shortest_paths
//    (*m_ptrBglGraph, start,
//     predecessor_map(make_iterator_property_map(p.begin(), get(vertex_index, *m_ptrBglGraph))),
//     predecessor_map(
//       make_iterator_property_map(p.begin(), get(vertex_index, *m_ptrBglGraph))).
//     distance_map(
//       make_iterator_property_map(d.begin(), get(vertex_index, *m_ptrBglGraph))),
//     get(edge_weight,*m_ptrBglGraph),
//     get(vertex_index, *m_ptrBglGraph),
//     std::less<float>(),
//     boost::closed_plus<float>(),
//     std::numeric_limits<float>::max(),
//     (float)0.0,
//       default_dijkstra_visitor(),
//    color_map(get(vertex_color,*m_ptrBglGraph))
//    );
}

void GraphFactory::GetNeighbors( const int& idx, std::vector<int>& neighbors )
{
  //* validate */
  BglVertex testVertex = vertex(13,*m_ptrBglGraph);
  std::pair<OutEdgeIter,OutEdgeIter> p = out_edges(testVertex,*m_ptrBglGraph);
  BglVertexMap indices = get( vertex_index , *m_ptrBglGraph);
  BglVertex sou = source(*(p.first),*m_ptrBglGraph);
  BglVertex tar = target(*(p.first),*m_ptrBglGraph);

  cout << indices[testVertex] << endl;
  cout << indices[sou] << ' ' << indices[tar] << endl;

} 

void GraphFactory::PrintNeighbors( const int& idx )
{

}
