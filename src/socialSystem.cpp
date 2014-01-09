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
  //m_ptrAttributeFactory->GetAttributes();
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
SocialSystem::Train( const string& trainFileName)
{
  //m_ptrAttributeFactory->GetAttributesByFile(trainFileName);
  //m_ptrSolver->SetTrainingInstance(m_ptrAttributeFactory->GetAttributes());
  m_ptrSolver->SetTrainingInstance(
      m_ptrAttributeFactory->GetAttributesByFile(trainFileName)
      );
  m_ptrSolver->Train();
}
double
SocialSystem::ReportCorrectRatio( const string& testFileName, const bool& label)
{
  m_ptrSolver->Inference(
      m_ptrProblemFactory->GetProblemAttributesByFile(testFileName, label)
      );
  return 0.0;
}

void 
SocialSystem::PrintTrainInstance( const string& trainFileName)
{
  fstream instanceFile;
  instanceFile.open("./trainInstance.arff",ios::out);
  instanceFile << "@RELATION data" << endl;
  instanceFile << "@ATTRIBUTE x NUMERIC" << endl;
  instanceFile << "@ATTRIBUTE class {1,2}" << endl;
  instanceFile << "@DATA" << endl;

  vector<vector<double> > matData = m_ptrAttributeFactory->GetAttributesByFile(trainFileName);
  for (int i = 0; i < matData[0].size(); ++i) {
    for (int j = matData.size()-1 ; j >= 0 ; --j) {
      if (j == 0) {
//        cout << matData[j][i]; 
        instanceFile << matData[j][i];
      }
      else {
//        cout << matData[j][i] << ','; 
        instanceFile << matData[j][i] << ',';
      }
    }
    instanceFile << endl;
//    cout << endl;
  }
  instanceFile.close();
}

void
SocialSystem::PrintTestInstance( const string& testFileName, const bool& label)
{
  string strName = "testInstance_";
  if (label == false) {
    strName = strName+"false.arff";
  }
  else{
    strName = strName+"true.arff";
  }
  fstream instanceFile;
  instanceFile.open(strName.c_str(),ios::out);
  instanceFile << "@RELATION data" << endl;
  instanceFile << "@ATTRIBUTE x NUMERIC" << endl;
  instanceFile << "@ATTRIBUTE class {1,2}" << endl;
  instanceFile << "@DATA" << endl;

  vector<vector<double> > matData = m_ptrProblemFactory->GetProblemAttributesByFile(testFileName, label);
  for (int i = 0; i < matData[0].size(); ++i) {
    for (int j = matData.size()-1 ; j >= 0 ; --j) {
      if (j == 0) {
        instanceFile << matData[j][i];
      }
      else {
        instanceFile << matData[j][i] << ',';
      }
    }
    instanceFile << endl;
  }
  instanceFile.close();
  
}
