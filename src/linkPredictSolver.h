#ifndef _LPSOLVER_
#define _LPSOLVER_ 
#include <vector>
#include <string>

using std::vector;
using std::string;

class LinkPredictSolver
{
  public:
    LinkPredictSolver();
    ~LinkPredictSolver();
    virtual void SetTrainingInstance( const vector<vector<double> >& ) = 0;
    virtual void Train() = 0;
    virtual void SetProblem() = 0;
    virtual void Inference( const string& ) = 0;
  private:

};

#endif
