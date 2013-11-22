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

typedef  
class Graph;
class GraphFactory: public Graph
{
  public:
    GraphFactory(const string& inputFileName, const string& outputFileName);
    ~GraphFactory();

  private:
    FileUtility *m_ptrFileUtility;
    /* adjency list */
    /* vertex list */
    /* some label for record */
};
