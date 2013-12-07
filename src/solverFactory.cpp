#include "solverFactory.h"

SolverFactory::SolverFactory()
{
  // default values
  m_param.svm_type = C_SVC;
  m_param.kernel_type = RBF;
  m_param.degree = 3;
  m_param.gamma = 0;	// 1/num_features
  m_param.coef0 = 0;
  m_param.nu = 0.5;
  m_param.cache_size = 100;
  m_param.C = 1;
  m_param.eps = 1e-3;
  m_param.p = 0.1;
  m_param.shrinking = 1;
  m_param.probability = 0;
  m_param.nr_weight = 0;
  m_param.weight_label = NULL;
  m_param.weight = NULL;
  m_cross_validation = 0;

}

SolverFactory::~SolverFactory()
{

}
