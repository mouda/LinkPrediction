#ifndef _ATTRIBUTE_
#define _ATTRIBUTE_
#include <vector>
#include "graphFactory.h"

using std::vector;
class Attribute
{
  public:
    Attribute();
    virtual ~Attribute();
    virtual void GetLabelByEdge( vector<double>& ) = 0;
    virtual void GetAttributeByEdge( vector<double>& ) = 0;
    virtual void GetTrainAttriByEdge( vector<double>&, const vector<BglVertexPair>& ) = 0;
    virtual void GetProblemLabelByEdge(vector<double>& ) = 0;
    virtual void GetProblemAttriByEdge(vector<double>&, const vector<BglVertexPair>&) = 0;
  private:
};

#endif
