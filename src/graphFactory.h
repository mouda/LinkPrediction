/*
 * this module is used for handle graph
 * 
 * */

#ifndef _GRAPHFACTORY_
#define _GRAPHFACTORY_ 
#include <boost/graph/adjacency_list.hpp> 
// for customizable graphs
#include <boost/graph/directed_graph.hpp> 
// A subclass to provide reasonable arguments to adjacency_list for a typical directed graph
//

/* parallel graph */

//// Enable PBGL interfaces to BGL algorithms
//#include <boost/graph/use_mpi.hpp>
//
//// Communicate via MPI
//#include <boost/graph/distributed/mpi_process_group.hpp>
// Dijkstra's single-source shortest paths algorithm
#include <boost/graph/dijkstra_shortest_paths.hpp>

// Breadth-first search algorithm
#include <boost/graph/breadth_first_search.hpp>

//// Distributed adjacency list
//#include <boost/graph/distributed/adjacency_list.hpp>
//
//// For choose_min_reducer
//#include <boost/graph/distributed/distributed_graph_utility.hpp>

#include <boost/graph/visitors.hpp>
#include "fileUtility.h"

using namespace boost;
//using boost::graph::distributed::mpi_process_group;
using std::string;

struct VertexProperty 
{
  VertexProperty(){ }
  VertexProperty(const int& id):m_nodeId(id){ }
  int m_nodeId;

  template<typename Archiver>
    void serialize(Archiver& ar, const unsigned int /* version*/) {
      ar & m_nodeId;
    }
};

struct EdgeProperty
{
  EdgeProperty(){ }
  template<typename Archiver>
    void serialize(Archiver& ar, const unsigned int /* version*/) {
      ar ;
    }

};

typedef adjacency_list<vecS, vecS, undirectedS,
        /* Vertex properties=*/
        property<vertex_index_t, int, 
        property<vertex_distance_t, int,
        property<vertex_color_t, boost::default_color_type> > >, 
        /* Edge properties */
        property<edge_weight_t, int> 
        > BglGraph;
typedef graph_traits<BglGraph>::vertex_descriptor     BglVertex;
typedef graph_traits<BglGraph>::edge_descriptor       BglEdge;
typedef graph_traits<BglGraph>::out_edge_iterator     OutEdgeIter;
typedef property_map<BglGraph, vertex_index_t>::type  BglVertexMap;
typedef property_map<BglGraph, vertex_index_t>::type  BglVertexMap;
typedef property_map<BglGraph, vertex_color_t>::type  BglColorMap;
typedef BglGraph::edge_property_type                  BglEdgeWeight;
typedef graph_traits<BglGraph>::edge_iterator         EdgeIter;
typedef graph_traits<BglGraph>::vertex_iterator       VertexIter;
typedef std::pair<EdgeIter,EdgeIter>                  EdgePair;
// for attribute size control
typedef std::pair<BglVertex,BglVertex>                BglVertexPair; 

class GraphFactory 
{
  public:
    GraphFactory(const string& inputFileName, const string& outputFileName, const int& wordId);
    ~GraphFactory();

    int GetVertexId(const int& index);
    int GetVertexNum(){ return m_numVertex; }
    int GetEdgeNum(){ return m_numEdge; }
    BglGraph * GetBglGraph(){ return m_ptrBglGraph; }


    bool RemoveEdge(const int& vlhs, const int& vrhs);
    int  GetFirstNeighborById( const int& idx);

    void BFS(const int& startIdx);
    void dijkstra( const int& startIdx);
    void GetNeighbors( const int& idx, std::vector<int>& );
    void PrintNeighbors( const int& idx );

  private:
    FileUtility *m_ptrFileUtility;
    BglGraph    *m_ptrBglGraph;
    int         m_numVertex;
    int         m_numEdge;
    const int   m_wordId;
};

#endif

