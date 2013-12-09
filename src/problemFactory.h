#ifndef _PROBLEMFACTORY_
#define _PROBLEMFACTORY_

#include <vector>
#include "problem.h"
#include "graphFactory.h"

using std::vector;
class ProblemFactory
{
  public:
    ProblemFactory(BglGraph const * const ptrGraph, const int& numVertex, const int& numEdge);
    ~ProblemFactory();

    const vector<vector<double> >& GetProblemAttributes(const double& edgeRemoveRatio );

  private:
    /* constant data members */
    BglGraph const * const  m_ptrGraph;  
    const int               m_numVertex;
    const int               m_numEdge;
    vector<vector<double> > m_matAttri;

};

#endif
