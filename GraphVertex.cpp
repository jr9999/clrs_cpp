#include "GraphVertex.h"

GraphVertex::GraphVertex()
{
  source = NULL;
  sink = NULL;
  value = 0;
  cost = 0;
}

GraphVertex::~GraphVertex()
{
  if(source) 
    {
      delete source;
      source = NULL;
    }
  if(sink)
    {
      delete sink;
      sink = NULL;
    }
}

void
GraphVertex::ConnectTo(GraphVertex *newSink)
{
  if(!this->sink || this->sink != newSink)
    {
      this->sink = newSink;
    }
}

int
GraphVertex::getValue()
{
  return this->value;
}

void
GraphVertex::setValue(int value)
{
  this->value = value;
}

int 
GraphVertex::getCost()
{
  return this->cost;
}

void
GraphVertex::setCost(int cost)
{
  this->cost = cost;
}
