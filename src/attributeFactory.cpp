#include "attributeFactory.h"
#include "commomFriendsAttribute.h"
#include "LHNAttribute.h"
#include <algorithm>


AttributeFactory::AttributeFactory( BglGraph const * const ptrGraph, 
    const int& numVertex, const int& numEdge)
  :m_ptrGraph(ptrGraph), m_numVertex(numVertex), m_numEdge(numEdge) 
{
  Attribute * ptrAttri = 
    new CommomFriendsAttribute(m_ptrGraph, m_numVertex, m_numEdge);
  Attribute * ptrAttri_1 = 
    new LHNAttribute(m_ptrGraph, m_numVertex, m_numEdge);
  m_vecPtrAttributes.push_back(ptrAttri);
  m_vecPtrAttributes.push_back(ptrAttri_1);
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

const vector<vector<double> >&
AttributeFactory::GetAttributesByFile( const string& fileName )
{
  m_ptrFileUtility = new FileUtility(fileName,0);
  int vertexNum = m_ptrFileUtility->GetVertexNum();
  BglGraph myCheckList(vertexNum); 
  pair<int, int> edgePair;
  m_vecTrainPair.clear();
  edgePair = m_ptrFileUtility->GetEdgePair();
  vector<int> vecLabelCheatSheet;

  /* check exist, assign label setup attribute vector */
  int nodeId = edgePair.first;
  int nodeId2 = edgePair.second;
  add_edge(
      vertex(edgePair.first, myCheckList), 
      vertex(edgePair.second, myCheckList),
      BglEdgeWeight(1), 
      myCheckList);
  if (edge(vertex(nodeId, *m_ptrGraph), vertex(nodeId2,*m_ptrGraph),
        *m_ptrGraph).second) {
    vecLabelCheatSheet.push_back(1);
  }
  else {
    vecLabelCheatSheet.push_back(2);
  }
  m_vecTrainPair.push_back(make_pair(vertex(nodeId, *m_ptrGraph), 
        vertex(nodeId2, *m_ptrGraph)
        ));

  while (edgePair.first >= 0 && edgePair.first < vertexNum ) {
    edgePair = m_ptrFileUtility->GetEdgePair();
    nodeId = edgePair.first;
    nodeId2 = edgePair.second;
    if( !edge(vertex(edgePair.first, myCheckList),
          vertex(edgePair.second, myCheckList),
          myCheckList).second ) {
      if (edge(vertex(nodeId, *m_ptrGraph), vertex(nodeId2,*m_ptrGraph),
            *m_ptrGraph).second) {
        vecLabelCheatSheet.push_back(1);
      }
      else {
        vecLabelCheatSheet.push_back(2);
      }
      m_vecTrainPair.push_back(make_pair(vertex(edgePair.first, *m_ptrGraph), 
            vertex(edgePair.second, *m_ptrGraph)
            ));

      add_edge(
          vertex(edgePair.first, myCheckList), 
          vertex(edgePair.second, myCheckList), 
          BglEdgeWeight(1),
          myCheckList);
    }
  } 

  m_matAttri.resize(m_vecPtrAttributes.size()+1,vector<double>(m_vecTrainPair.size()));
#ifdef DEBUG
  cout << m_vecTrainPair.size() << endl;
  cout << vecLabelCheatSheet.size() << endl;
#endif
  for (int i = 0; i < vecLabelCheatSheet.size(); i++) {
    m_matAttri[0][i] = (double)vecLabelCheatSheet[i];
  }
  for (int i = 0; i < m_vecPtrAttributes.size(); i++) {
    m_vecPtrAttributes[i]->GetProblemAttriByEdge(m_matAttri[i+1], m_vecTrainPair);
  }

  delete m_ptrFileUtility;
  return m_matAttri;
}


