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

private:
  /* private functions */
  void SetLinkedAttribute( vector<double>& vecAttributes);
  void SetUnLinkedAttribute( vector<double>& vecAttributes);
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
