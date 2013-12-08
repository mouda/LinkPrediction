#include <svm.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "solver.h"
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

using std::vector;
class Solver;
class SolverFactory: public Solver
{
  public:
    SolverFactory();
    ~SolverFactory();

    void SetTrainingInstance( const vector<vector<double> >& instances );
    void Train();
    void SetProblem();
    void Inference();

  private:
    void   do_cross_validation();
    struct svm_parameter  m_param;		// set by parse_command_line
    struct svm_problem    m_prob;		// set by read_problem
    struct svm_model      *m_model;
    struct svm_node       *m_x_space;
    int                   m_cross_validation;
    int                   m_nr_fold;
};
