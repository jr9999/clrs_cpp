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

 private:
  deque<GraphVertex> mAdjArray;
};

#endif
