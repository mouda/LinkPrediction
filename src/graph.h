#ifndef _GRAPH_
#define _GRAPH_
#include <string>
#include <vector>

#include "fileUtility.h"

using namespace std;

class Graph
{
  public:
    /* let a graph object handle a description file and an output file*/
    Graph();
    virtual ~Graph() = 0;
    virtual int GetVertexId(const int& ) = 0;
    virtual int GetVertexNum() = 0;
    virtual int GetEdgeNum() = 0;

    virtual void GetNeighbors(const int&, vector<int>& neigbors) = 0;
    virtual void BFS(const int& id) = 0;
    virtual void dijkstra(const int& startIdx) = 0;
    
  private:

};


#endif
