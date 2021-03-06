#ifndef _PROBLEMFACTORY_
#define _PROBLEMFACTORY_

#include <vector>
#include <map>
#include <Eigen/Core>
#include <Eigen/SparseCore>
#include "fileUtility.h"
#include "attribute.h"
#include "graphFactory.h"

using std::vector;
using std::cout;
using std::cerr;
using std::endl;
using std::pair;
using std::find;
using std::map;

class ProblemFactory
{
  public:
    ProblemFactory(BglGraph const * const ptrGraph, const int& numVertex, const int& numEdge, const string&);
    ~ProblemFactory();

    const vector<vector<double> >& GetProblemAttributes(const double& edgeRemovedRatio );
    const vector<vector<double> >& GetProblemAttributesByFile( const string& testFileName, const bool& label);

  private:
    /* private methods */
    void SetProblemPairsByRatio( const double& ratio);
    void SetLinkedPair();
    void SetUnLinkedPair();


    /* constant data members */
    BglGraph const * const  m_ptrGraph;  
    FileUtility             *m_ptrFileUtility; 
    const int               m_numVertex;
    const int               m_numEdge;
    int                     m_numAttributes;
    int                     m_numDiscardEdge;
    vector<Attribute*>      m_vecPtrAttributes;
    vector<vector<double> > m_matAttri;

    vector<BglVertexPair>   m_vecTestPair;
    //map<pair<int,int>,int >  m_mapProblemPairs;
    Eigen::SparseMatrix<int>  m_matProblemLinks;
    vector<BglVertexPair>   m_vecLinkedPairs;
    vector<BglVertexPair>   m_vecUnLinkedPairs;
};

#endif
