/*
 * this module is used for handle graph
 * 
 * */
#include <boost/graph/adjacency_list.hpp> 
// for customizable graphs
#include <boost/graph/directed_graph.hpp> 
// A subclass to provide reasonable arguments to adjacency_list for a typical directed graph

#include "graph.h"
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
