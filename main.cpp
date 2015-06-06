#include <iostream>
#include "AdjacencyList.h"

#include <thread>

using namespace std;

void hello() 
{
  std::cout << "hello world" << endl;
}

int main(int argc, char* argv[])
{
  std::thread t(hello);
  t.join();

  cout << "proj2 bfs" << endl;
 
  AdjacencyList* pMyAdjacencyList = new AdjacencyList();

  GraphVertex* pNewVertex = new GraphVertex();
  pNewVertex->setValue(0);
  pNewVertex->setCost(0);

  GraphVertex* pLv1Vert = new GraphVertex();
  pLv1Vert->setValue(1);
  pLv1Vert->setCost(1);

  pNewVertex->ConnectTo(pLv1Vert);

  GraphVertex* pLv2Vert1 = new GraphVertex();
  pLv2Vert1->setValue(2);
  pLv2Vert1->setCost(1);

  GraphVertex* pLv2Vert2 = new GraphVertex();
  pLv2Vert2->setValue(3);
  pLv2Vert2->setCost(1);

  pLv1Vert->ConnectTo(pLv2Vert1);
  pLv1Vert->ConnectTo(pLv2Vert2);

  

  //cleanup
  if(pMyAdjacencyList)
    {
      delete pMyAdjacencyList;
    }
}
