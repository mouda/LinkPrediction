#include "attribute.h"
#include "graph.h"

#include <vector>

class Attribute;
class AttributeFactory: public Attribute
{
  public:
    AttributeFactory(  Graph const * const ptrGraph, const int& numVertex);
    ~AttributeFactory();
    void SetAttribute();

  private:
    Graph const * const m_ptrGraph;
    const int m_numVertex;
    vector<int> * m_ptrVecAttr;

};
