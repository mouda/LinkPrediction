#include "attribute.h"
#include "graph.h"

class Attribute;
class AttributeFactory: public Attribute
{
  public:
    AttributeFactory(  Graph const * const ptrGraph);
    ~AttributeFactory();
  private:
    Graph const * const m_ptrGraph;
};
