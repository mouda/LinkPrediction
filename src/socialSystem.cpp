#include "socialSystem.h"

SocialSystem::SocialSystem(const string& inputFileName, const string& outputFileName)
{
  m_ptrFileAdapter = new FileAdapter(inputFileName, outputFileName);
  m_ptrGraphAdapter = new GraphAdapter;
  m_ptrAttributeGen = new AttributeGenerator;
  m_ptrProblemGen = new ProblemGenerator;
  m_ptrSolver = new Solver;

}

SocialSystem::~SocialSystem()
{
  delete m_ptrFileAdapter;
  delete m_ptrGraphAdapter;
  delete m_ptrAttributeGen;
  delete m_ptrProblemGen;
  delete m_ptrSolver;

}
