#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <string.h>
#include <deque>
#include "GraphVertex.h"

using namespace std;

class AdjacencyList 
{
 public:

  AdjacencyList();
  virtual ~AdjacencyList();

  void AddStartNode(GraphVertex* startNode);

  void bfs();

 private:
  deque<GraphVertex*> mAdjArray;
};

#endif
