#include <string>

//// Enable PBGL interfaces to BGL algorithms
//#include <boost/graph/use_mpi.hpp>
//// Communicate via MPI
//#include <boost/graph/distributed/mpi_process_group.hpp>
#include "graphFactory.h"
#include "attributeFactory.h"
#include "problemFactory.h"
#include "linkPredictSolver.h"

using std::string;
class SocialSystem 
{
  public:
    SocialSystem(const string& inputFileName, const string& outputFileName, const int& in_wordID);
    ~SocialSystem();
    double ReportCorrectRatio( const string& testFileName, const bool& label);
    void Train( const string& trainFileName);
    void SetRemovedEdgeRatio( const double& edgeRemovedRatio );
    void PrintTrainInstance( const string& trainFileName);
    void PrintTestInstance( const string& testFileName, const bool& label);

  private:
    GraphFactory      *m_ptrGraph;
    AttributeFactory  *m_ptrAttributeFactory;
    ProblemFactory    *m_ptrProblemFactory;
    LinkPredictSolver *m_ptrSolver;

    /* const values */
    const int         m_worldId;
};
