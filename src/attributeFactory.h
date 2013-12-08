#ifndef _ATTRIBUTEFACTORY_
#define _ATTRIBUTEFACTORY_
#include "graphFactory.h"
#include "attribute.h"

#include <Eigen/Core>

class Attribute;
class AttributeFactory
{
  public:
    AttributeFactory( BglGraph const * const ptrGraph, 
        const int& numVertex, const int& numEdge);
    ~AttributeFactory();

    const vector<vector<int> >& GetAttributes();

  private:
    BglGraph const * const  m_ptrGraph;
    const int               m_numVertex;
    const int               m_numEdge;
    vector<Attribute*>      m_vecPtrAttributes;
    vector<vector<int> >    m_matAttri;
};

#endif
