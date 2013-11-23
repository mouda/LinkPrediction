#include <string>

// Enable PBGL interfaces to BGL algorithms
#include <boost/graph/use_mpi.hpp>
// Communicate via MPI
#include <boost/graph/distributed/mpi_process_group.hpp>
#include "graph.h"
#include "attribute.h"
#include "problem.h"
#include "solver.h"

class SocialSystem 
{
  public:
    SocialSystem(const string& inputFileName, const string& outputFileName, const int& in_wordID);
    ~SocialSystem();

  private:
    Graph             *m_ptrGraph;
    Attribute         *m_ptrAttribute;
    Problem           *m_ptrProblem;
    Solver            *m_ptrSolver;

    int               m_wordId;
};
