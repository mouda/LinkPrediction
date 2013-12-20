#ifndef _ATTRIBUTEFACTORY_
#define _ATTRIBUTEFACTORY_
#include "graphFactory.h"
#include "attribute.h"
#include "fileUtility.h"

#include <Eigen/Core>

class Attribute;
class AttributeFactory
{
  public:
    AttributeFactory( BglGraph const * const ptrGraph, 
        const int& numVertex, const int& numEdge);
    ~AttributeFactory();

    const vector<vector<double> >& GetAttributes();
    const vector<vector<double> >& GetAttributesByFile( const string& );

  private:
    BglGraph const * const  m_ptrGraph;
    const int               m_numVertex;
    const int               m_numEdge;
    vector<Attribute*>      m_vecPtrAttributes;
    vector<vector<double> > m_matAttri;
    FileUtility             *m_ptrFileUtility; 
    

    /* for unified attributed generation */
    vector<BglVertexPair>   m_vecTrainPair;
    vector<BglVertexPair>   m_vecLinkedPair;
    vector<BglVertexPair>   m_vecUnLinkedPair;
};

#endif
