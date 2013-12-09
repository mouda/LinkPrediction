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
  m_ptrGraph =            new GraphFactory(inputFileName, outputFileName, in_worldID);
  m_ptrAttributeFactory = new AttributeFactory(m_ptrGraph->GetBglGraph(), 
      m_ptrGraph->GetVertexNum(), m_ptrGraph->GetEdgeNum());
  m_ptrAttributeFactory->GetAttributes();
  m_ptrProblemFactory =   new ProblemFactory(m_ptrGraph->GetBglGraph(), 
      m_ptrGraph->GetVertexNum(), m_ptrGraph->GetEdgeNum());
  m_ptrSolver =           new SolverFactory(outputFileName);
}

SocialSystem::~SocialSystem()
{
  delete m_ptrGraph;
  delete m_ptrAttributeFactory;
  delete m_ptrProblemFactory;
  delete m_ptrSolver;
}

void
SocialSystem::SetRemovedEdgeRatio( const double& edgeRemoveRatio  )
{
  m_ptrProblemFactory->GetProblemAttributes(edgeRemoveRatio);
  m_ptrSolver->SetProblem();
}

void
SocialSystem::Train()
{
  m_ptrSolver->SetTrainingInstance(m_ptrAttributeFactory->GetAttributes());
  m_ptrSolver->Train();
}
double
SocialSystem::ReportCorrectRatio( const string& testFileName)
{
  m_ptrSolver->Inference(testFileName);
  return 0.0;
}
