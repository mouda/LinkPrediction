#ifndef _ATTRIBUTE_
#define _ATTRIBUTE_
#include <vector>

using std::vector;
class Attribute
{
  public:
    Attribute();
    virtual ~Attribute();
    virtual void GetAttributeByEdge( vector<int>& ) = 0;
  private:
};

#endif
