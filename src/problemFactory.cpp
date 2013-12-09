#include "problemFactory.h"

ProblemFactory::ProblemFactory(BglGraph const * const ptrGraph, 
    const int& numVertex, const int& numEdge)
  :m_ptrGraph(ptrGraph), m_numVertex(numVertex), m_numEdge(numEdge) 
{

}

ProblemFactory::~ProblemFactory()
{

}

const vector<vector<double> >&
ProblemFactory::GetProblemAttributes(const double& edgeRemoveRatio )
{

  return m_matAttri;
}
