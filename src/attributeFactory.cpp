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
  for (int i = 0; i < m_vecPtrAttributes.size(); i++) {
    delete m_vecPtrAttributes[i];
  }
}

const vector<vector<double> >& 
AttributeFactory::GetAttributes()
{
  m_matAttri.resize(2,vector<double>(2*m_numEdge));
  m_vecPtrAttributes[0]->GetLabelByEdge(m_matAttri[0]); //index 0 is labels
  m_vecPtrAttributes[0]->GetAttributeByEdge(m_matAttri[1]); // attributes start from 1

#ifdef DEBUG
  for (int i = 0; i < 2*m_numEdge; i++) {
    cout << m_matAttri[1][i] << endl;
  }
#endif

  return m_matAttri;
}


