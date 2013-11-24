#ifndef _GRAPH_
#define _GRAPH_
#include <string>

#include "fileUtility.h"

using namespace std;

class Graph
{
  public:
    /* let a graph object handle a description file and an output file*/
    Graph();
    virtual ~Graph() = 0;
    virtual int GetVertexId(const int& ) = 0;
    
  private:

};


#endif
