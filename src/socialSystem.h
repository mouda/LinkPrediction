#include <string>

//// Enable PBGL interfaces to BGL algorithms
//#include <boost/graph/use_mpi.hpp>
//// Communicate via MPI
//#include <boost/graph/distributed/mpi_process_group.hpp>
#include "graphFactory.h"
#include "attributeFactory.h"
#include "attribute.h"
#include "problem.h"
#include "solver.h"

using std::string;
class SocialSystem 
{
  public:
    SocialSystem(const string& inputFileName, const string& outputFileName, const int& in_wordID);
    ~SocialSystem();
    void SetRemovedEdgeRatio( const double& numOfRemovedEdges );
    double ReportCorrectRatio();

  private:
    GraphFactory      *m_ptrGraph;
    AttributeFactory  *m_ptrAttributeFactory;
    Problem           *m_ptrProblem;
    Solver            *m_ptrSolver;

    /* const values */
    const int         m_worldId;
};
