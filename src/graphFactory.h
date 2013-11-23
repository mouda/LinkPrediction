/*
 * this module is used for handle graph
 * 
 * */

#include <boost/graph/adjacency_list.hpp> 
// for customizable graphs
#include <boost/graph/directed_graph.hpp> 
// A subclass to provide reasonable arguments to adjacency_list for a typical directed graph
//

/* parallel graph */

// Enable PBGL interfaces to BGL algorithms
#include <boost/graph/use_mpi.hpp>

// Communicate via MPI
#include <boost/graph/distributed/mpi_process_group.hpp>

// Breadth-first search algorithm
#include <boost/graph/breadth_first_search.hpp>

// Distributed adjacency list
#include <boost/graph/distributed/adjacency_list.hpp>

// For choose_min_reducer
#include <boost/graph/distributed/distributed_graph_utility.hpp>




#include "graph.h"

using namespace boost;
using boost::graph::distributed::mpi_process_group;


typedef adjacency_list<vecS, distributedS<mpi_process_group, vecS>, undirectedS,
        /* Vertex properties=*/
        property<vertex_distance_t, std::size_t> >
        BglGraph;

class Graph;
class GraphFactory: public Graph
{
  public:
    GraphFactory(const string& inputFileName, const string& outputFileName, const int& wordId);
    ~GraphFactory();

  private:
    FileUtility *m_ptrFileUtility;
    /* adjency list */
    BglGraph    *m_ptrBglGraph;
    /* vertex list */
    /* some label for record */
};


