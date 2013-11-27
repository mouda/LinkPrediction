#include "socialSystem.h"
#include "graphFactory.h"
#include "attributeFactory.h"
#include "problemFactory.h"
#include "solverFactory.h"

SocialSystem::SocialSystem(const string& inputFileName, 
    const string& outputFileName,
    const int& in_worldID):m_worldId(in_worldID)
{
  m_ptrGraph =      new GraphFactory(inputFileName, outputFileName, in_worldID);

  if ( m_worldId == 0) {
    cout << m_ptrGraph->GetVertexId(10) << endl;
  }

  m_ptrAttribute =  new AttributeFactory;
  m_ptrProblem =    new ProblemFactory;
  m_ptrSolver =     new SolverFactory;


}

SocialSystem::~SocialSystem()
{
  delete m_ptrGraph;
  delete m_ptrAttribute;
  delete m_ptrProblem;
  delete m_ptrSolver;

}
