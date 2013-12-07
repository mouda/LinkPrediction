#include "attribute.h"
#include "graph.h"

#include <Eigen/Core>

class Attribute;
class AttributeFactory: public Attribute
{
  public:
    AttributeFactory( Graph const * const ptrGraph, 
        const int& numVertex, const int& numEdge);
    ~AttributeFactory();
    void SetAttribute();

  private:
    Graph const * const m_ptrGraph;
    const int           m_numVertex;
    const int           m_numEdge;
    Eigen::RowVectorXi  m_vecAttri; 
};
