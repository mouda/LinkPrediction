#ifndef _ATTRIBUTE_
#define _ATTRIBUTE_
#include <vector>

using std::vector;
class Attribute
{
  public:
    Attribute();
    virtual ~Attribute();
    virtual void GetLabelByEdge( vector<double>& ) = 0;
    virtual void GetAttributeByEdge( vector<double>& ) = 0;
  private:
};

#endif
