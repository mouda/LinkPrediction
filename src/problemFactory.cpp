#include "problemFactory.h"
#include "commomFriendsAttribute.h"
#include "LHNAttribute.h"


ProblemFactory::ProblemFactory(BglGraph const * const ptrGraph, 
    const int& numVertex, const int& numEdge)
  :m_ptrGraph(ptrGraph), m_numVertex(numVertex), m_numEdge(numEdge) 
{
//  Attribute * ptrAttri = 
//    new CommomFriendsAttribute(m_ptrGraph, m_numVertex, m_numEdge);
  Attribute * ptrAttri_1 = 
    new LHNAttribute(m_ptrGraph, m_numVertex, m_numEdge);
  m_numAttributes = 1;
//  m_vecPtrAttributes.push_back(ptrAttri);
  m_vecPtrAttributes.push_back(ptrAttri_1);
}

ProblemFactory::~ProblemFactory()
{
  for (int i = 0; i < m_vecPtrAttributes.size(); i++) {
    delete m_vecPtrAttributes[i];
  }
}

const vector<vector<double> >&
ProblemFactory::GetProblemAttributes(const double& edgeRemovedRatio )
{
  SetProblemPairsByRatio( edgeRemovedRatio);
  SetLinkedPair();
  SetUnLinkedPair();
  return m_matAttri;
}
const vector<vector<double> >&
ProblemFactory::GetProblemAttributesByFile( const string& testFileName, const bool& label)
{
  m_ptrFileUtility = new FileUtility(testFileName,0);
  int vertexNum = m_ptrFileUtility->GetVertexNum();
  BglGraph myCheckList(vertexNum); 

  pair<int, int> edgePair;
  m_vecTestPair.clear();

  edgePair = m_ptrFileUtility->GetEdgePair();
  m_vecTestPair.push_back(make_pair(vertex(edgePair.first, *m_ptrGraph), 
        vertex(edgePair.second, *m_ptrGraph)
        ));
  add_edge(
      vertex(edgePair.first, myCheckList), 
      vertex(edgePair.second, myCheckList),
      BglEdgeWeight(1), 
      myCheckList);

  while (edgePair.first >= 0 && edgePair.first < vertexNum ) {
    edgePair = m_ptrFileUtility->GetEdgePair();
    if( !edge(vertex(edgePair.first, myCheckList),
          vertex(edgePair.second, myCheckList),
          myCheckList).second ) {

      m_vecTestPair.push_back(make_pair(vertex(edgePair.first, *m_ptrGraph), 
            vertex(edgePair.second, *m_ptrGraph)
            ));

      add_edge(
          vertex(edgePair.first, myCheckList), 
          vertex(edgePair.second, myCheckList), 
          BglEdgeWeight(1),
          myCheckList);
    }
  } 
  m_matAttri.resize(m_numAttributes+1,vector<double>(m_vecTestPair.size()));
  if (label) {
    for (int i = 0; i < m_vecTestPair.size(); i++) {
      m_matAttri[0][i] = 1; 
    }
  }
  else {
    for (int i = 0; i < m_vecTestPair.size(); i++) {
      m_matAttri[0][i] = 2; 
    }
  }
  //m_vecPtrAttributes[0]->GetProblemAttriByEdge(m_matAttri[1], m_vecTestPair ); 
  for (int i = 0; i < m_vecPtrAttributes.size(); i++) {
    m_vecPtrAttributes[i]->GetProblemAttriByEdge(m_matAttri[i+1], m_vecTestPair);
  }
  delete m_ptrFileUtility;
  return m_matAttri;
}

void
ProblemFactory::SetProblemPairsByRatio( const double& ratio)
{
  VertexIter vp, vp_end, ivp, ivp_end;
  int numOfDiscardedEdges = static_cast<int>(ratio*m_numEdge);
  m_numDiscardEdge = numOfDiscardedEdges;
  int counter = 0;
  int i = 0;
  bool exitLoop = false;
  m_matProblemLinks.resize(m_numVertex, m_numVertex);
  m_matProblemLinks.setZero();
  //m_mapProblemPairs.resize(numOfDiscardedEdges);
  for (tie(vp, vp_end) = vertices(*m_ptrGraph); vp != vp_end; ++vp, ++i) {
    if (exitLoop) break; // break the nested loop; 
    int j = 0;
    for (tie(ivp, ivp_end) = vertices(*m_ptrGraph), j = 0; ivp != ivp_end; ++ivp, ++j) {
      if (counter == numOfDiscardedEdges ) {
        exitLoop = true; // break the nested loop;
        break;
      } 
      else if (!edge(*vp,*ivp,*m_ptrGraph).second){
        //m_vecProblemPairs[counter] = make_pair(i,j);
        //m_mapProblemPairs.insert(make_pair(make_pair(i,j),i));
        m_matProblemLinks.coeffRef(i,j) = 1;
        ++counter;
      }
    }
  }
}

void
ProblemFactory::SetLinkedPair()
{
  VertexIter vp, vp_end, ivp, ivp_end;
  int numOfRemainEdges = m_numEdge - m_numDiscardEdge;
  int counter = 0;
  int i = 0;
  bool exitLoop = false;
  m_vecLinkedPairs.clear();
  //cout << m_numEdge <<" " << m_mapProblemPairs.size() <<" "<< numOfRemainEdges <<endl; 
  cout << numOfRemainEdges << endl;
  m_vecLinkedPairs.resize(numOfRemainEdges);
  cout << m_matProblemLinks.cols() << endl;
  for (tie(vp, vp_end) = vertices(*m_ptrGraph); vp != vp_end; ++vp, ++i) {
    if (exitLoop) break; // break the nested loop; 
    int j = 0;
    for (tie(ivp, ivp_end) = vertices(*m_ptrGraph); ivp != ivp_end; ++ivp, ++j) {
      if (counter == numOfRemainEdges ) {
        exitLoop = true; // break the nested loop;
        break;
      } 
      else if (i < m_numVertex && j < m_numVertex && m_matProblemLinks.coeffRef(i,j) == 1) {
        continue;
      }
      else if (edge(*vp,*ivp,*m_ptrGraph).second){
        m_vecLinkedPairs[counter] = make_pair(*vp,*ivp);
        ++counter;
      }
    }
  }
}

void
ProblemFactory::SetUnLinkedPair()
{
  VertexIter vp, vp_end, ivp, ivp_end;
  int numOfRemainEdges = m_numEdge - m_numDiscardEdge;
  int counter = 0;
  int i = 0;
  bool exitLoop = false;
  m_vecLinkedPairs.clear();
  //cout << m_numEdge <<" " << m_mapProblemPairs.size() <<" "<< numOfRemainEdges <<endl; 
  cout << numOfRemainEdges << endl;
  m_vecLinkedPairs.resize(numOfRemainEdges);
  cout << m_matProblemLinks.cols() << endl;
  for (tie(vp, vp_end) = vertices(*m_ptrGraph); vp != vp_end; ++vp, ++i) {
    if (exitLoop) break; // break the nested loop; 
    int j = 0;
    for (tie(ivp, ivp_end) = vertices(*m_ptrGraph); ivp != ivp_end; ++ivp, ++j) {
      if (counter == numOfRemainEdges ) {
        exitLoop = true; // break the nested loop;
        break;
      } 
      else if (i < m_numVertex && j < m_numVertex && m_matProblemLinks.coeffRef(i,j) == 1) {
        continue;
      }
      else if (edge(*vp,*ivp,*m_ptrGraph).second){
        m_vecLinkedPairs[counter] = make_pair(*vp,*ivp);
        ++counter;
      }
    }
  }

}
