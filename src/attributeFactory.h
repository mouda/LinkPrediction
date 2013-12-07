#include "attribute.h"
#include "graphFactory.h"

#include <Eigen/Core>

class Attribute;
class AttributeFactory: public Attribute
{
  public:
    AttributeFactory( BglGraph const * const ptrGraph, 
        const int& numVertex, const int& numEdge);
    ~AttributeFactory();
    vector<int>& GetAttributes();

  private:
    void GetNeighbors(const BglVertex& , std::vector<int>& vecNeighbors); 
    int  GetNumCommNeighbors( const BglVertex&, 
        const std::vector<int>& vecNeighbors);
    void SetLinkedAttribute();
    void SetUnLinkedAttribute();

    BglGraph const * const m_ptrGraph;
    const int           m_numVertex;
    const int           m_numEdge;
    //Eigen::RowVectorXi  m_vecAttri; 
    vector<int>         m_vecAttri;
};
