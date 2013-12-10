#include <svm.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include "linkPredictSolver.h"
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

using std::vector;
using std::string;
class LinkPredictSolver;
class SolverFactory: public LinkPredictSolver
{
  public:
    SolverFactory(const string& modelFileName );
    ~SolverFactory();

    void SetTrainingInstance( const vector<vector<double> >& instances );
    void Train();
    void SetProblem();
    void Inference( const vector<vector<double> > & instances );

  private:
    const string          m_modelFileName;
    void   do_cross_validation();
    struct svm_parameter  m_param;		// set by parse_command_line
    struct svm_problem    m_prob;		// set by read_problem
    struct svm_model      *m_model;
    struct svm_node       *m_x_space;
    int                   m_cross_validation;
    int                   m_nr_fold;
};
