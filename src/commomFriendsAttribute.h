#include "attribute.h"
#include "graphFactory.h"

class CommomFriendsAttribute: public Attribute
{
public:
  CommomFriendsAttribute(BglGraph const * const ptrGraph, 
      const int& numVertex, const int& numEdge);
  virtual ~CommomFriendsAttribute ();
  /* Common Interface */
  void GetLabelByEdge( vector<int>& );
  void GetAttributeByEdge( vector<int>& );

private:
  /* private functions */
  void SetLinkedAttribute( vector<int>& vecAttributes);
  void SetUnLinkedAttribute( vector<int>& vecAttributes);
  void GetNeighbors(const BglVertex& selfVertex, vector<int>& vecNeighbors);
  int  GetNumCommNeighbors(const BglVertex& selfVertex, 
      const vector<int>& vecOtherNeighbors);

  /* constant data members */
  BglGraph const * const  m_ptrGraph;  
  const int               m_numVertex;
  const int               m_numEdge;
  /* data members */
  int                     m_maxCommNeighbors;
};

