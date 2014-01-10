
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>  
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp> 

#include "graphFactory.h"
#include "utility.h"




using namespace std;
using namespace boost;

typedef vector< string > split_vector_type;

bool pairCompare(const std::pair<int, int>& firstElem, 
    const std::pair<int, int>& secondElem) {
    return firstElem.first < secondElem.first;
}

int main( int argc, char* argv[] )
{

  if ( argc != 4 ) {
    cout << "Usage: [input] [query number] [train number]" << endl;
    return 1;
  }

  string inputFileName(argv[1]);
  int intQueryNum = atoi(argv[2]);
  int intTrainNum = atoi(argv[3]);

  if (!FileExist(inputFileName)) {
    cerr << "Input file doesn't exist" << endl;
    return 1;
  }

  split_vector_type vecTokens;
  split( vecTokens, inputFileName, is_any_of("\."), token_compress_on );
  stringstream ss;

  ss << intTrainNum;
  string outputTrainFileName = ".."+vecTokens[1] + "_train_"+ss.str()+".txt";
  ss.str("");
  ss << intQueryNum;
  string outputTestFileName  = ".."+vecTokens[1] + "_test_"+ss.str()+".txt";
  string outputQueryTrueFileName = ".."+vecTokens[1] + "_query_true_"+ss.str()+".txt";
  string outputQueryFalseFileName = ".."+vecTokens[1] + "_query_false_"+ss.str()+".txt";
  cout << outputTrainFileName << endl;
  cout << outputTestFileName << endl;
  cout << outputQueryTrueFileName << endl;
  cout << outputQueryFalseFileName << endl;
  GraphFactory myGraphFactory(inputFileName, "NULL",0);
  cout << "vertex num: " << myGraphFactory.GetVertexNum() << endl;
  cout << "edge num: " << myGraphFactory.GetEdgeNum() << endl;
  srand (time(NULL));
  cout << "random num: " << rand()%myGraphFactory.GetVertexNum() << endl;
  int randId = rand()%myGraphFactory.GetVertexNum();
  cout << "first neighbor  " << myGraphFactory.GetFirstNeighborById(randId) 
    << " of(" << randId <<")" << endl;

  /* remove edges */
  int countUp = 0;
  int neighborId = 0;
  vector<pair<int, int> > vecRemovedPair;
  while (  countUp < intQueryNum ) {
    randId = rand()%myGraphFactory.GetVertexNum();
    neighborId = myGraphFactory.GetFirstNeighborById(randId); 
    if (neighborId != -1) {
      if (myGraphFactory.RemoveEdge(randId,neighborId,15)) {
        vecRemovedPair.push_back(make_pair(randId,neighborId));
        vecRemovedPair.push_back(make_pair(neighborId,randId));
        ++countUp;
      }
    }
  }

#ifdef DEBUG
  cout << vecRemovedPair.size() << endl;
  cout << myGraphFactory.GetEdgeNum() << endl;
#endif

  /* output removed edges (true pair) */ 
  fstream outputQueryTrueFile;
  outputQueryTrueFile.open(outputQueryTrueFileName.c_str(), ios::out);
  sort(vecRemovedPair.begin(),vecRemovedPair.end(), pairCompare);
  for (int i = 0; i < vecRemovedPair.size(); i++) {
#ifdef DEBUG
    cout << vecRemovedPair[i].first << ' ' << vecRemovedPair[i].second << endl;
#endif
    outputQueryTrueFile << vecRemovedPair[i].first << ' ' 
      << vecRemovedPair[i].second << endl;
  }
  outputQueryTrueFile.close();

  /* output random select unlink edges (false pair) */
  fstream outputQueryFalseFile;
  outputQueryFalseFile.open(outputQueryFalseFileName.c_str(), ios::out);
  BglGraph myOriginGraphCheckList(myGraphFactory.GetVertexNum());
  vector<pair<int, int> > vecUnlinkPair;
  BglGraph *myPtrGraph = myGraphFactory.GetBglGraph();
  countUp = 0;
  while ( countUp < intQueryNum) {
    randId = rand()%myGraphFactory.GetVertexNum();
    int randNeighbor = rand()%myGraphFactory.GetVertexNum();
    if (!edge(vertex(randId, myOriginGraphCheckList), vertex(randNeighbor, myOriginGraphCheckList), myOriginGraphCheckList).second &&  
        !edge(vertex(randId,*myPtrGraph), vertex(randNeighbor,*myPtrGraph), *myPtrGraph ).second ) {
      vecUnlinkPair.push_back(make_pair(randId,randNeighbor));
      vecUnlinkPair.push_back(make_pair(randNeighbor,randId));
      add_edge(
          vertex(randId, myOriginGraphCheckList), 
          vertex(randNeighbor, myOriginGraphCheckList),
          BglEdgeWeight(1), 
          myOriginGraphCheckList);
      ++countUp;
    }
  }
  sort(vecUnlinkPair.begin(), vecUnlinkPair.end(), pairCompare);
  /* output */
  for (int i = 0; i < vecUnlinkPair.size(); i++) {
    outputQueryFalseFile << vecUnlinkPair[i].first << ' '
      << vecUnlinkPair[i].second << endl;
  }
  outputQueryFalseFile.close();


  /* output graph with removed edges (train data)*/
  fstream outputTestFile;
  outputTestFile.open(outputTestFileName.c_str(), ios::out);
  EdgeIter ep, ep_end;
  BglVertex u,v;
  BglVertexMap indices = get( vertex_index , *myPtrGraph);
  vector<pair<int, int> > vecGraphPair;
  for (tie(ep,ep_end) = edges(*myPtrGraph); ep != ep_end; ++ep) {
    u = source(*ep,*myPtrGraph);
    v = target(*ep,*myPtrGraph);
#ifdef DEBUG
    cout << indices[u] << ' ' << indices[v] << endl;
#endif
    vecGraphPair.push_back(make_pair(indices[u],indices[v]));
    vecGraphPair.push_back(make_pair(indices[v],indices[u]));
  }
  sort(vecGraphPair.begin(),vecGraphPair.end(), pairCompare);
  for (int i = 0; i < vecGraphPair.size(); i++) {
    outputTestFile << vecGraphPair[i].first << ' '
      << vecGraphPair[i].second << endl;
  }
  outputTestFile.close();

  /* generate train data set */
  fstream outputTrainFile;
  outputTrainFile.open(outputTrainFileName.c_str(), ios::out); 
  vector<pair<int, int> > vecTrainPair;
  BglGraph myCheckList(myGraphFactory.GetVertexNum());

  /* generate linked data*/
  countUp = 0;
  while( countUp < intTrainNum){
    randId = rand()%myGraphFactory.GetVertexNum();
    neighborId = myGraphFactory.GetFirstNeighborById(randId); 
    if (neighborId != -1 && 
        !edge(vertex(randId, myCheckList),
          vertex(neighborId, myCheckList),
          myCheckList).second ) {
      
      vecTrainPair.push_back(make_pair(randId,neighborId));
      vecTrainPair.push_back(make_pair(neighborId,randId));
      add_edge(
          vertex(randId, myCheckList), 
          vertex(neighborId, myCheckList),
          BglEdgeWeight(1), 
          myCheckList);
      ++countUp;
    }
  }
  /* generate unlinked data */
  countUp = 0;
  int randId2 = 0;
  while ( countUp < intTrainNum) {
    randId = rand()%myGraphFactory.GetVertexNum();
    randId2 = rand()%myGraphFactory.GetVertexNum();
    if (!edge(vertex(randId, myCheckList), vertex(randId2, myCheckList), myCheckList).second &&  
        !edge(vertex(randId,*myPtrGraph), vertex(randId2,*myPtrGraph), *myPtrGraph ).second ) {
      vecTrainPair.push_back(make_pair(randId,randId2));
      vecTrainPair.push_back(make_pair(randId2,randId));
      add_edge(
          vertex(randId, myCheckList), 
          vertex(randId2, myCheckList),
          BglEdgeWeight(1), 
          myCheckList);
      ++countUp;
    }
  }
  sort(vecTrainPair.begin(), vecTrainPair.end(), pairCompare);
  /* output */
  for (int i = 0; i < vecTrainPair.size(); i++) {
    outputTrainFile << vecTrainPair[i].first << ' '
      << vecTrainPair[i].second << endl;
  }
  outputTrainFile.close();

  return 0;
}
