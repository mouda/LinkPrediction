#include "socialSystem.h"
#include "graphFactory.h"
#include "attributeFactory.h"
#include "problemFactory.h"
#include "solverFactory.h"

SocialSystem::SocialSystem(const string& inputFileName, 
    const string& outputFileName,
    const int& in_wordID)
{
  m_ptrGraph =      new GraphFactory(inputFileName, outputFileName, in_wordID);


  m_ptrAttribute =  new AttributeFactory;
  m_ptrProblem =    new ProblemFactory;
  m_ptrSolver =     new SolverFactory;

  m_wordId = in_wordID;

}

SocialSystem::~SocialSystem()
{
  delete m_ptrGraph;
  delete m_ptrAttribute;
  delete m_ptrProblem;
  delete m_ptrSolver;

}
