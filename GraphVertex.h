#ifndef GRAPH_VERTEX_H
#define GRAPH_VERTEX_H

#include <iostream>

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

 private:
  GraphVertex* source;
  GraphVertex* sink;
  int value;
  int cost;
};

#endif
