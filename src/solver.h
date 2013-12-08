#ifndef _SOLVER_
#define _SOLVER_ 
#include <vector>

using std::vector;

class Solver
{
  public:
    Solver();
    ~Solver();
    virtual void SetTrainingInstance( const vector<vector<double> >& ) = 0;
    virtual void Train() = 0;
    virtual void SetProblem() = 0;
    virtual void Inference() = 0;
  private:

};

#endif
