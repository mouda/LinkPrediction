#include "solverFactory.h"
#include <iostream>
#include <string>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

SolverFactory::SolverFactory( const string& modelFileName)
  :m_modelFileName(modelFileName)
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
  m_param.shrinking = 0; //default
  m_param.probability = 0;
  m_param.nr_weight = 0;
  m_param.weight_label = NULL;
  m_param.weight = NULL;
  m_cross_validation = 0;
  m_nr_fold = 2;

}

SolverFactory::~SolverFactory()
{
//  free(m_prob.y);
//  free(m_prob.x);
//  free(m_x_space);
  delete [] m_prob.y;
  delete [] m_prob.x;
  delete [] m_x_space;
}

/* @brief    Setup the training instance
 * @param    vector<vector<int> > instances
 *                        labels  attr1  attri2
 *            [0-2][0] -> (0,1)  (1,0.2) (2,0.1)
 *            [0-2][1] -> (0,1)  (1,0.3) (2,0.2)
 *            [0-2][2] -> (0,1)  (1,0.3) (2,0.3)
 *            [0-2][3] -> (0,0)  (1,1.4) (2,0.2)
 *            [0-2][4] -> (0,0)  (1,0.2) (2,0.2)
 *            ...
 * @reval
 */
void
SolverFactory::SetTrainingInstance(const vector<vector<double> >& instances )
{
  int numOfElements   = instances.size() * instances[0].size();//need one more space to store -1
  int numOfInstances  = instances[0].size() - 1;
  int numOfAttributes = instances.size() - 1;

  m_prob.l = instances[0].size();
//  m_prob.y = Malloc(double, m_prob.l); 
//  m_prob.x = Malloc(struct svm_node *, m_prob.l);
//  m_x_space = Malloc(struct svm_node, numOfElements);
  m_prob.y = new double [m_prob.l];
  m_prob.x = new struct svm_node * [m_prob.l];
  m_x_space = new struct svm_node [numOfElements];
  
  /*  */
  int elements, max_index, inst_max_index;
  max_index = 0;
  int j = 0;
  for( int i = 0; i < m_prob.l; ++i ) {
    
    inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0
    m_prob.x[i] = &m_x_space[j];
    m_prob.y[i] = instances[0][i]; 
    for(int k = 1; k < instances.size(); ++k) {
      m_x_space[j].index = k;
      inst_max_index = m_x_space[j].index;
      m_x_space[j].value = instances[k][i];
      ++j;
    }
    if(inst_max_index > max_index)
      max_index = inst_max_index;
    m_x_space[j++].index = -1;
  }
  if(m_param.gamma == 0 && max_index > 0) m_param.gamma = 1.0/max_index;
  if(m_param.kernel_type == PRECOMPUTED) {
    for(int i = 0 ; i < m_prob.l; i++ ) {
      if (m_prob.x[i][0].index != 0) {
        cerr << "Wrong input format: first column must be 0:sample_serial_number" 
          << endl;
        exit(1);
      }
      if ((int)m_prob.x[i][0].value <= 0 || (int)m_prob.x[i][0].value > max_index) {
        cerr << "Wrong input format: sample_serial_number out of range" << endl;
        exit(1);
      }
    }
  }
  const char *error_msg;
  error_msg = svm_check_parameter(&m_prob,&m_param);
  if(error_msg) {
    cerr << "ERROR: " << error_msg << endl;
    exit(1);
  }
}

void
SolverFactory::Train()
{
  string modelFileName = "model.mod";
  if(m_cross_validation) {
    do_cross_validation();
  }
  else {
    m_model = svm_train(&m_prob,&m_param);
    if(svm_save_model(modelFileName.c_str(),m_model)) {
      fprintf(stderr, "can't save model to file %s\n", modelFileName.c_str());
      exit(1);
    }
    svm_free_and_destroy_model(&m_model);
  }
}

void
SolverFactory::SetProblem()
{

}

void
SolverFactory::Inference()
{

}

void 
SolverFactory::do_cross_validation()
{
  int i;
  int total_correct = 0;
  double total_error = 0;
  double sumv = 0, sumy = 0, sumvv = 0, sumyy = 0, sumvy = 0;
  double *target = Malloc(double,m_prob.l);

  svm_cross_validation(&m_prob,&m_param,m_nr_fold,target);
  if(m_param.svm_type == EPSILON_SVR ||
      m_param.svm_type == NU_SVR)
  {
    for(i=0;i<m_prob.l;i++)
    {
      double y = m_prob.y[i];
      double v = target[i];
      total_error += (v-y)*(v-y);
      sumv += v;
      sumy += y;
      sumvv += v*v;
      sumyy += y*y;
      sumvy += v*y;
    }
    printf("Cross Validation Mean squared error = %g\n",total_error/m_prob.l);
    printf("Cross Validation Squared correlation coefficient = %g\n",
        ((m_prob.l*sumvy-sumv*sumy)*(m_prob.l*sumvy-sumv*sumy))/
        ((m_prob.l*sumvv-sumv*sumv)*(m_prob.l*sumyy-sumy*sumy))
        );
  }
  else
  {
    for(i=0;i<m_prob.l;i++)
      if(target[i] == m_prob.y[i])
        ++total_correct;
    printf("Cross Validation Accuracy = %g%%\n",100.0*total_correct/m_prob.l);
  }
  free(target);
}
