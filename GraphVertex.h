#ifndef GRAPH_VERTEX_H
#define GRAPH_VERTEX_H

#include <iostream>
#include <deque>

using namespace std;

class GraphVertex
{
 public:

  GraphVertex();
  virtual ~GraphVertex();

  void ConnectTo(GraphVertex* newSink);

  int getValue();
  void setValue(int value);

  int getCost();
  void setCost(int cost);

  //for traversal
  GraphVertex* Next();

 private:

  GraphVertex* source;
  deque<GraphVertex*> sinks;

  int value;
  int cost;
};

#endif
