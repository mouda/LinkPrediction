#include "fileAdapter.h"
#include "graphAdapter.h"
#include "problemGenerator.h"
#include "attributeGenerator.h"
#include "solver.h"

#include <string>

class SocialSystem
{
  public:
    SocialSystem(const string& inputFileName, const string& outputFileName);
    ~SocialSystem();

  private:
    FileAdapter         *m_ptrFileAdapter;
    GraphAdapter        *m_ptrGraphAdapter;
    AttributeGenerator  *m_ptrAttributeGen;
    ProblemGenerator    *m_ptrProblemGen;
    Solver              *m_ptrSolver;
};
