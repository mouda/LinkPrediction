#include "attributeFactory.h"
#include "commomFriendsAttribute.h"
#include <algorithm>


AttributeFactory::AttributeFactory( BglGraph const * const ptrGraph, 
    const int& numVertex, const int& numEdge)
  :m_ptrGraph(ptrGraph), m_numVertex(numVertex), m_numEdge(numEdge) 
{
  Attribute * ptrAttri = 
    new CommomFriendsAttribute(m_ptrGraph, m_numVertex, m_numEdge);
  m_vecPtrAttributes.push_back(ptrAttri);
}

AttributeFactory::~AttributeFactory()
{

}

vector<vector<int> >& 
AttributeFactory::GetAttributes()
{
  m_matAttri.resize(1,vector<int>(2*m_numEdge));
  m_vecPtrAttributes[0]->GetAttributeByEdge(m_matAttri[0]);
  for (int i = 0; i < 2*m_numEdge; i++) {
    cout << m_matAttri[0][i] << endl;
  }
  return m_matAttri;
}



