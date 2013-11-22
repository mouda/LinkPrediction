#include <string>

#include "graph.h"
#include "attribute.h"
#include "problem.h"
#include "solver.h"

class SocialSystem
{
  public:
    SocialSystem(const string& inputFileName, const string& outputFileName);
    ~SocialSystem();

  private:
    Graph             *m_ptrGraph;
    Attribute         *m_ptrAttribute;
    Problem           *m_ptrProblem;
    Solver            *m_ptrSolver;
};
