#include "multiLevelCommonNeighbor.h"
#include <limits.h>
#include <math.h>
#include <set>

MultiLevelCommonNeighbor::MultiLevelCommonNeighbor( BglGraph const * const ptrGraph, 
   const int& numVertex, const int& numEdge )
 :m_ptrGraph(ptrGraph), m_numVertex(numVertex), m_numEdge(numEdge), 
  m_maxCommNeighbors(0) 
{

}

MultiLevelCommonNeighbor::~MultiLevelCommonNeighbor()
{

}

void 
MultiLevelCommonNeighbor::GetTrainAttriByEdge( vector<double>& vecAttributes, 
    const vector<BglVertexPair>&)
{

}

void
MultiLevelCommonNeighbor::GetAttributeByEdge( vector<double>& vecAttributes )
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
MultiLevelCommonNeighbor::GetLabelByEdge( vector<double>& vecLabels)
{
  vecLabels.resize(2*m_numEdge);
  vector<double>::iterator vecIter = vecLabels.begin();
  for (int i = 0; i < m_numEdge; ++i) ++vecIter;
  fill(vecLabels.begin(),vecIter,1);
  ++vecIter;
  fill(vecIter,vecLabels.end(),2);
}

void 
MultiLevelCommonNeighbor::GetProblemLabelByEdge(vector<double>& vecLabels)
{
  fill(vecLabels.begin(),vecLabels.end(),1);
}

void 
MultiLevelCommonNeighbor::GetProblemAttriByEdge(vector<double>& vecAttributes
    , const vector<BglVertexPair>& vecPairVertex)
{
  BglVertex u,v;
  vector<int> lhsNeighbor;
  vector<int> vecCommNeighbors;
  int idx = 0;
//  double maxNumCommNeighbors = (double)GetMaxNumCommNeghbors(); 
  int level = 2;
  //double maxRAScore = (double)GetMaxRAScore(level);
  double maxRAScore = 1.0;

  for (int i = 0; i < vecPairVertex.size(); i++) {
    u = vecPairVertex[i].first;
    v = vecPairVertex[i].second;
    double uOutDegree = out_degree(u,*m_ptrGraph);
    if (uOutDegree < 1) uOutDegree = 1;
    double vOutDegree = out_degree(v,*m_ptrGraph);
    if (vOutDegree < 1) vOutDegree = 1;

    lhsNeighbor.clear(); 
    GetNeighbors(u,lhsNeighbor);
    //double numCommNeighbor_origin = (double)GetNumCommNeighbors(v,lhsNeighbor);
    vecCommNeighbors.clear();
    double numCommNeighbor_2 = (double)GetMultiLevelCommNeighbors(u,v, vecCommNeighbors, level);
    double value = GetSumInvDegree(vecCommNeighbors);

    //vecAttributes[idx] = numCommNeighbor/pow(uOutDegree*vOutDegree,0.5);
    //vecAttributes[idx] = numCommNeighbor_2/maxNumCommNeighbors;
    vecAttributes[idx] = numCommNeighbor_2;
#ifdef DEBUG 
    for (int i = 0; i < vecCommNeighbors.size(); i++) {
      cout << vecCommNeighbors[i] << ' ';
    }
    cout << endl;
    cout << "u: " << out_degree(u,*m_ptrGraph) 
      << " v: " << out_degree(v,*m_ptrGraph) << ' '
      << GetNumCommNeighbors(v,lhsNeighbor) << ' '      << vecAttributes[idx]
      << endl;   
#endif

    ++idx;
  }
}

double
MultiLevelCommonNeighbor::GetMaxRAScore( const int level)
{
  vector<int> vecCommNeighbors;
  double maxValues = 0.0;
  EdgeIter ep, ep_end;
  BglVertex u,v;
  for (tie(ep,ep_end) = edges(*m_ptrGraph); ep != ep_end; ++ep) {
    u = source(*ep,*m_ptrGraph);
    v = target(*ep,*m_ptrGraph);
    vecCommNeighbors.clear();
    double numCommNeighbor = (double)GetMultiLevelCommNeighbors(u,v, vecCommNeighbors, level);
    double value = GetSumInvDegree(vecCommNeighbors);
    if (value > maxValues) {
      maxValues = value;
    }
  }

  return maxValues;  
}

int
MultiLevelCommonNeighbor::GetMaxNumCommNeghbors()
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
MultiLevelCommonNeighbor::GetMaxNumCommNeghborsByEdge(const vector<BglVertexPair>&  vecPairVertex)
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
MultiLevelCommonNeighbor::GetNeighbors(const BglVertex& selfVertex, 
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
MultiLevelCommonNeighbor::GetNumCommNeighbors(const BglVertex& selfVertex, 
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

int
MultiLevelCommonNeighbor::GetMultiLevelCommNeighbors( const BglVertex& u, const BglVertex& v, 
    vector<int>& vecCommNeighbors, const int level)
{
  set<int> vecUNeighbor;
  set<int> vecVNeighbor;
  int initial = 0;
  BFS(u, vecUNeighbor, initial, level);
  BFS(v, vecVNeighbor, initial, level);
//  sort(vecUNeighbor.begin(), vecUNeighbor.end());
//  sort(vecVNeighbor.begin(), vecVNeighbor.end());
  int maxSize = vecUNeighbor.size() > vecVNeighbor.size()? vecUNeighbor.size():vecVNeighbor.size();
  set<int> myVecCommNeighbors;
//  myVecCommNeighbors.resize(maxSize);
  set<int>::iterator it_end;
  set_intersection(vecUNeighbor.begin(), vecUNeighbor.end(), 
      vecVNeighbor.begin(), vecVNeighbor.end(), inserter(myVecCommNeighbors, myVecCommNeighbors.begin()));
  
  vecCommNeighbors.resize(distance(myVecCommNeighbors.begin(), it_end));
  copy(myVecCommNeighbors.begin(), it_end ,vecCommNeighbors.begin());


  return myVecCommNeighbors.size() ;
}

void
MultiLevelCommonNeighbor::BFS( const BglVertex& curVertex, set<int>& vecNeighbors,
    int level, const int& levelLimit )
{
  BglVertexMap indices = get( vertex_index , *m_ptrGraph);
  vecNeighbors.insert(indices[curVertex]);
  if (level == levelLimit) {
    return;
  }
  OutEdgeIter p, p_end;
  for (tie(p, p_end) = out_edges(curVertex, *m_ptrGraph) ; p != p_end; ++p) {
    BglVertex sou = source(*p,*m_ptrGraph);
    BglVertex tar = target(*p,*m_ptrGraph);
    BFS(tar, vecNeighbors, level+1, levelLimit); 
  }
}

double
MultiLevelCommonNeighbor::GetSumInvDegree( const vector<int>& vecCommNeighbors)
{
  BglVertex u;
  double degree = 0.0;
  double sum = 0.0;
  for (int i = 0; i < vecCommNeighbors.size(); i++) {
    u = vertex(vecCommNeighbors[i],*m_ptrGraph);
    degree = out_degree(u,*m_ptrGraph);
    sum += 1/degree;
  }

  return sum;
}

void
MultiLevelCommonNeighbor::SetLinkedAttribute( vector<double>& vecAttributes )
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
MultiLevelCommonNeighbor::SetUnLinkedAttribute( vector<double>& vecAttributes )
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

