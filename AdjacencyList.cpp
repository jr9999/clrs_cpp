#include "AdjacencyList.h"
#include <vector>

//use adjacency lists to represent sparse graphs.

AdjacencyList::AdjacencyList() 
{
}

AdjacencyList::~AdjacencyList()
{
}

void 
AdjacencyList::AddStartNode(GraphVertex* startNode)
{
  GraphVertex* newStartNode = startNode;
  mAdjArray.push_back(newStartNode);
}

void
AdjacencyList::bfs()
{
  vector<GraphVertex*> traversal;

  
}
