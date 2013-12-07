#include "socialSystem.h"
#include "graphFactory.h"
#include "attributeFactory.h"
#include "problemFactory.h"
#include "solverFactory.h"

#include <vector>

SocialSystem::SocialSystem(const string& inputFileName, 
    const string& outputFileName,
    const int& in_worldID):m_worldId(in_worldID)
{
  m_ptrGraph =      new GraphFactory(inputFileName, outputFileName, in_worldID);
  m_ptrAttribute =  new AttributeFactory(m_ptrGraph->GetBglGraph(),
      m_ptrGraph->GetVertexNum(), m_ptrGraph->GetEdgeNum());
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

void
SocialSystem::SetAttribute()
{
  std::vector<int> vecNeighbors;
  m_ptrGraph->GetNeighbors(29,vecNeighbors);
}
