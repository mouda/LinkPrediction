#include <string>

#include "fileUtility.h"
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
    FileUtility       *m_ptrFileUtility;
    Graph             *m_ptrGraph;
    Attribute         *m_ptrAttribute;
    Problem           *m_ptrProblem;
    Solver            *m_ptrSolver;
};
