#include <iostream>
#include "AdjacencyList.h"

using namespace std;


int main(int argc, char* argv[])
{
  cout << "proj2 bfs" << endl;
 
  AdjacencyList* pMyAdjacencyList = new AdjacencyList();

  //cleanup
  if(pMyAdjacencyList)
    {
      delete pMyAdjacencyList;
    }
}
