#include "attributeFactory.h"
#include <algorithm>


AttributeFactory::AttributeFactory( BglGraph const * const ptrGraph, 
    const int& numVertex, const int& numEdge)
  :m_ptrGraph(ptrGraph), m_numVertex(numVertex), m_numEdge(numEdge) 
{
  /* TODO: Here to generate the attribute  */
#ifdef DEBUG
  cout << "m_numVertex: " << m_numVertex << ' ' 
    << "m_numEdge: " << m_numEdge << endl;
#endif
  /* set attribute(link) up to double of linkage */
  //m_vecAttri = Eigen::RowVectorXi::Zero(2*m_numEdge); 
  m_vecAttri.resize(2*m_numEdge);
  /* construct linked edges' attribute */
  SetLinkedAttribute();
  /* construct un-linked edges' attribute */
  SetUnLinkedAttribute();
   
}

AttributeFactory::~AttributeFactory()
{

}

void 
AttributeFactory::GetNeighbors(const BglVertex& selfVertex, 
    std::vector<int>& vecNeighbors)
{
  OutEdgeIter p, p_end;
  BglVertexMap indices = get( vertex_index , *m_ptrGraph);
  for (tie(p, p_end) = out_edges(selfVertex, *m_ptrGraph) ; p != p_end; ++p) {
    //BglVertex sou = source(*p,*m_ptrGraph);
    BglVertex tar = target(*p,*m_ptrGraph);
    vecNeighbors.push_back(indices[tar]);
  }
}

int 
AttributeFactory::GetNumCommNeighbors(const BglVertex& selfVertex, 
    const std::vector<int>& vecOtherNeighbors)
{
  int numCommNeighbor = 0;
  OutEdgeIter p, p_end;
  BglVertexMap indices = get( vertex_index , *m_ptrGraph);
  for (tie(p, p_end) = out_edges(selfVertex, *m_ptrGraph) ; p != p_end; ++p) {
    BglVertex sou = source(*p,*m_ptrGraph);
    BglVertex tar = target(*p,*m_ptrGraph);
    if ( find(vecOtherNeighbors.begin(),vecOtherNeighbors.end(),(int)indices[tar]) 
         != vecOtherNeighbors.end()) {
      ++numCommNeighbor;
    }
  }
  return numCommNeighbor;
}

void
AttributeFactory::SetLinkedAttribute()
{
  /* edge iterator */
  EdgeIter ep, ep_end;
  BglVertex u,v;
  BglVertexMap indices = get( vertex_index , *m_ptrGraph);
  vector<int> lhsNeighbor;
  int idx = 0;
  for (tie(ep,ep_end) = edges(*m_ptrGraph); ep != ep_end; ++ep) {
    u = source(*ep,*m_ptrGraph);
    v = target(*ep,*m_ptrGraph);
    lhsNeighbor.clear(); 
    GetNeighbors(u,lhsNeighbor);
#ifdef DEBUG
    cout << lhsNeighbor.size() <<' ' <<GetNumCommNeighbors(v,lhsNeighbor) << endl;
#endif
    m_vecAttri[idx] = GetNumCommNeighbors(v,lhsNeighbor);
    ++idx;
  }
}

void 
AttributeFactory::SetUnLinkedAttribute()
{
  VertexIter vp, vp_end, ivp, ivp_end;
  OutEdgeIter ep, ep_end;
  vector<int> lhsNeighbors;
  int counter = 0;
  for (tie(vp, vp_end) = vertices(*m_ptrGraph); vp != vp_end; ++vp) {
    for (tie(ivp, ivp_end) = vertices(*m_ptrGraph); ivp != ivp_end; ++ivp) {
      if (*vp == *ivp ) continue; 
      if (counter == m_numVertex) break; 
      if (!edge(*vp,*ivp,*m_ptrGraph).second) {
        lhsNeighbors.clear();
        GetNeighbors(*vp,lhsNeighbors);
#ifdef DEBUG
        cout << GetNumCommNeighbors(*ivp,lhsNeighbors) << endl;
#endif
        m_vecAttri[m_numEdge+counter] = GetNumCommNeighbors(*ivp,lhsNeighbors);
        ++counter;
      }
    }
  }
}
