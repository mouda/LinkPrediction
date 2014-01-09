#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

#include "socialSystem.h"
#include "utility.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace std;

int main( int argc, char* argv[] )
{
  string inputFileName(argv[1]);
  string outputFileName(argv[2]);
  string strFlag(argv[3]);
  string trainFileName;
  bool boolPrintFlag=false;
  bool boolAnswerFlag=false;
  try {
    po::options_description desc("Allowed options");
    desc.add_options()
      ("help,h", "Produce help message")
      ("graph,g", po::value<string>(), "Graph file name")
      ("model,m", po::value<string>(), "Model file name")
      ("train,t", po::value<string>(), "Train file name")
      ("inference,i", po::value<string>(), "Tnference file name")
      ("answer,a", po::value<bool>(), "Answer, true or false")
      ("print,p", "Use this option to print instance");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.size() == 0 || vm.count("help")) {
      cout << desc << "\n";
      return 0;
    }

    if (vm.count("train") && vm.size() == 3) {

      if (!vm.count("model")) {
        cerr << "You must provide model file"<<endl;
      }

      if (!vm.count("graph")) {
        cerr << "You must provide graph file"<<endl;
      }

      inputFileName = vm["graph"].as<string>();
      outputFileName = vm["model"].as<string>();
      trainFileName = vm["train"].as<string>();
      if (!FileExist(inputFileName)) {
        cerr << "Graph file ``" << inputFileName << "'' doesn't exist" << endl;
        return 1;
      }
      if (!FileExist(trainFileName)) {
        cerr << "Train file ``" << trainFileName << "'' doesn't exist" << endl;
        return 1;
      }

      SocialSystem mySocialSystem(inputFileName, outputFileName, 0);
      mySocialSystem.Train(trainFileName);
    }
    else if (vm.count("inference") && (vm.size() == 4 || vm.size() == 5)) {

      if (!vm.count("model")) {
        cerr << "You must provide model file"<<endl;
      }
      if (!vm.count("graph")) {
        cerr << "You must provide graph file"<<endl;
      }

      outputFileName = vm["model"].as<string>();
      inputFileName = vm["graph"].as<string>();
      string inferenceFileName = vm["inference"].as<string>();

      if (!FileExist(inferenceFileName)) {
        cerr << "Inference file ``" << inferenceFileName << "'' doesn't exist" << endl;
        return 1;
      }
      if (!FileExist(outputFileName)) {
        cerr << "Error: model file doesn't exist" << endl;
        return 1;
      } 
      if (!FileExist(inputFileName)) {
        cerr << "Graph file ``" << inputFileName << "'' doesn't exist" << endl;
        return 1;
      }

      boolAnswerFlag =  vm["answer"].as<bool>();

      SocialSystem mySocialSystem(inputFileName, outputFileName, 0);
      if (!vm.count("print")) {
        mySocialSystem.ReportCorrectRatio(inferenceFileName, boolAnswerFlag);
      }
      else {
        mySocialSystem.PrintTestInstance(inferenceFileName, boolAnswerFlag);
      }

    } else {
      cout << desc << "\n";
      return 0;
    }

  }
  catch(std::exception& e) {
    cerr << "error: " << e.what() << "\n";
    return 1;
  }
  catch(...) {
    cerr << "Exception of unknown type!\n";
  }
  return 0;
}
