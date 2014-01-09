#include "commomFriendsAttribute.h"
#include <limits.h>

CommomFriendsAttribute::CommomFriendsAttribute( BglGraph const * const ptrGraph, 
   const int& numVertex, const int& numEdge )
 :m_ptrGraph(ptrGraph), m_numVertex(numVertex), m_numEdge(numEdge), 
  m_maxCommNeighbors(0) 
{

}

CommomFriendsAttribute::~CommomFriendsAttribute()
{

}

void 
CommomFriendsAttribute::GetTrainAttriByEdge( vector<double>& vecAttributes, 
    const vector<BglVertexPair>&)
{

}

void
CommomFriendsAttribute::GetAttributeByEdge( vector<double>& vecAttributes )
{
  /* set attribute(link) up to double of linkage */
  vecAttributes.resize(2*m_numEdge);
  /* construct linked edges' attribute */
  SetLinkedAttribute(vecAttributes);
  /* construct un-linked edges' attribute */
  SetUnLinkedAttribute(vecAttributes);
  /* normalize to 0.0 ~ 1.0 */
  for (int i = 0; i < vecAttributes.size(); i++) {
    vecAttributes[i] = vecAttributes[i] / m_maxCommNeighbors;
  }
}

void
CommomFriendsAttribute::GetLabelByEdge( vector<double>& vecLabels)
{
  vecLabels.resize(2*m_numEdge);
  vector<double>::iterator vecIter = vecLabels.begin();
  for (int i = 0; i < m_numEdge; ++i) ++vecIter;
  fill(vecLabels.begin(),vecIter,1);
  ++vecIter;
  fill(vecIter,vecLabels.end(),2);
}

void 
CommomFriendsAttribute::GetProblemLabelByEdge(vector<double>& vecLabels)
{
  fill(vecLabels.begin(),vecLabels.end(),1);
}

void 
CommomFriendsAttribute::GetProblemAttriByEdge(vector<double>& vecAttributes
    , const vector<BglVertexPair>& vecPairVertex)
{
  BglVertex u,v;
  vector<int> lhsNeighbor;
  int idx = 0;
  double maxNumCommNeighbors = (double)GetMaxNumCommNeghbors(); 
  for (int i = 0; i < vecPairVertex.size(); i++) {
    u = vecPairVertex[i].first;
    v = vecPairVertex[i].second;
    lhsNeighbor.clear(); 
    GetNeighbors(u,lhsNeighbor);
    vecAttributes[idx] = (double)GetNumCommNeighbors(v,lhsNeighbor) / 
      maxNumCommNeighbors;
    ++idx;
  }
}

int
CommomFriendsAttribute::GetMaxNumCommNeghbors()
{
  /* edge iterator */
  EdgeIter ep, ep_end;
  BglVertex u,v;
  BglVertexMap indices = get( vertex_index , *m_ptrGraph);
  vector<int> lhsNeighbor;
  int idx = 0;
  double maxNeighbors = 0.0;
  for (tie(ep,ep_end) = edges(*m_ptrGraph); ep != ep_end; ++ep) {
    u = source(*ep,*m_ptrGraph);
    v = target(*ep,*m_ptrGraph);
    lhsNeighbor.clear(); 
    GetNeighbors(u,lhsNeighbor);
    double tmp =  (double)GetNumCommNeighbors(v,lhsNeighbor);
    if (tmp > maxNeighbors) {
      maxNeighbors = tmp;
    }
    ++idx;
  }
  return maxNeighbors;
}

int
CommomFriendsAttribute::GetMaxNumCommNeghborsByEdge(const vector<BglVertexPair>&  vecPairVertex)
{
  /* edge iterator */
  EdgeIter ep, ep_end;
  BglVertex u,v;
  BglVertexMap indices = get( vertex_index , *m_ptrGraph);
  vector<int> lhsNeighbor;
  int idx = 0;
  double maxNeighbors = 0.0;
  for (int i = 0; i < vecPairVertex.size(); i++) {
    u = vecPairVertex[i].first;
    v = vecPairVertex[i].second;
    lhsNeighbor.clear(); 
    GetNeighbors(u,lhsNeighbor);
    double tmp =  (double)GetNumCommNeighbors(v,lhsNeighbor);
    if (tmp > maxNeighbors) {
      maxNeighbors = tmp;
    }
    ++idx;
  }
  return maxNeighbors;
}

void 
CommomFriendsAttribute::GetNeighbors(const BglVertex& selfVertex, 
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
CommomFriendsAttribute::GetNumCommNeighbors(const BglVertex& selfVertex, 
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
CommomFriendsAttribute::SetLinkedAttribute( vector<double>& vecAttributes )
{
  /* edge iterator */
  EdgeIter ep, ep_end;
  BglVertex u,v;
  BglVertexMap indices = get( vertex_index , *m_ptrGraph);
  vector<int> lhsNeighbor;
  int idx = 0;
  double maxNeighbors = 0.0;
  for (tie(ep,ep_end) = edges(*m_ptrGraph); ep != ep_end; ++ep) {
    u = source(*ep,*m_ptrGraph);
    v = target(*ep,*m_ptrGraph);
    lhsNeighbor.clear(); 
    GetNeighbors(u,lhsNeighbor);
#ifdef DEBUG
    cout << lhsNeighbor.size() <<' ' <<GetNumCommNeighbors(v,lhsNeighbor) << endl;
#endif
    vecAttributes[idx] = (double)GetNumCommNeighbors(v,lhsNeighbor);
    if (vecAttributes[idx] > maxNeighbors) {
      maxNeighbors = vecAttributes[idx];
    }
    ++idx;
  }
  m_maxCommNeighbors = maxNeighbors;
}

void 
CommomFriendsAttribute::SetUnLinkedAttribute( vector<double>& vecAttributes )
{
  VertexIter vp, vp_end, ivp, ivp_end;
  OutEdgeIter ep, ep_end;
  vector<int> lhsNeighbors;
  int counter = 0;
  bool exitLoop = false;
  for (tie(vp, vp_end) = vertices(*m_ptrGraph); vp != vp_end; ++vp) {
    if(exitLoop) break;
    for (tie(ivp, ivp_end) = vertices(*m_ptrGraph); ivp != ivp_end; ++ivp) {
      if (*vp == *ivp ) continue; 
      if (counter == m_numEdge) {
        exitLoop = true;
        break; 
      }
      if (!edge(*vp,*ivp,*m_ptrGraph).second) {
        lhsNeighbors.clear();
        GetNeighbors(*vp,lhsNeighbors);
#ifdef DEBUG
        cout << GetNumCommNeighbors(*ivp,lhsNeighbors) << endl;
#endif
        vecAttributes[m_numEdge+counter] = (double)GetNumCommNeighbors(*ivp,lhsNeighbors);
        ++counter;
      }
    }
  }
}

