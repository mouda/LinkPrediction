#include "attributeFactory.h"


AttributeFactory::AttributeFactory( Graph const * const ptrGraph, 
    const int& numVertex, const int& numEdge)
  :m_ptrGraph(ptrGraph), m_numVertex(numVertex), m_numEdge(numEdge) 
{
  /* TODO: Here to generate the attribute  */
#ifdef DEBUG
  cout << "m_numVertex: " << m_numVertex << ' ' 
    << "m_numEdge: " << m_numEdge << endl;
#endif
  /* set attribute(link) up to double of linkage */
  m_vecAttri = Eigen::RowVectorXi::Zero(2*m_numEdge); 

  /* edge iterator */
}

AttributeFactory::~AttributeFactory()
{

}
