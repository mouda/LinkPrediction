#include "attribute.h"
#include "graphFactory.h"

class CommomFriendsAttribute: public Attribute
{
public:
  CommomFriendsAttribute(BglGraph const * const ptrGraph, 
      const int& numVertex, const int& numEdge);
  virtual ~CommomFriendsAttribute ();
  /* Common Interface */
  void GetLabelByEdge( vector<double>& );
  void GetAttributeByEdge( vector<double>& );
  void GetTrainAttriByEdge(vector<double>& , const vector<BglVertexPair>&);
  void GetProblemLabelByEdge(vector<double>& );
  void GetProblemAttriByEdge(vector<double>& , const vector<BglVertexPair>&);

private:
  /* private functions */
  void SetLinkedAttribute( vector<double>& vecAttributes);
  void SetUnLinkedAttribute( vector<double>& vecAttributes);
  int  GetMaxNumCommNeghbors();
  int  GetMaxNumCommNeghborsByEdge( const vector<BglVertexPair>& vecNeighbors);
  void GetNeighbors(const BglVertex& selfVertex, vector<int>& vecNeighbors);
  int  GetNumCommNeighbors(const BglVertex& selfVertex, 
      const vector<int>& vecOtherNeighbors);


  /* constant data members */
  BglGraph const * const  m_ptrGraph;  
  const int               m_numVertex;
  const int               m_numEdge;
  /* data members */
  double                  m_maxCommNeighbors;
};

