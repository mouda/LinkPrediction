#include "graphFactory.h"

GraphFactory::GraphFactory(const string& inputFileName, const string& outputFileName)
{
  m_ptrFileUtility = new FileUtility(inputFileName, outputFileName);

}

GraphFactory::~GraphFactory()
{

}
