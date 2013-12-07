#include <svm.h>
#include <stdio.h>
#include "solver.h"

class Solver;
class SolverFactory: public Solver
{
  public:
    SolverFactory();
    ~SolverFactory();

    void SetTranningInstance();
    void Train();
    void SetProblem();
    void Inference();

  private:
    struct svm_parameter  m_param;		// set by parse_command_line
    struct svm_problem    m_prob;		// set by read_problem
    struct svm_model      *m_model;
    struct svm_node       *m_x_space;
    int                   m_cross_validation;
    int                   m_nr_fold;


};
