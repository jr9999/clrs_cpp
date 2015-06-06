#include "GraphVertex.h"

GraphVertex::GraphVertex()
{
  source = NULL;
  //sinks = NULL;
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
  if(sinks.size() > 0)
    {
      for(deque<GraphVertex*>::iterator iter = sinks.begin(); iter != sinks.end(); iter++)
	{
	  if(*iter) 
	    {
	      delete *iter;
	      *iter = NULL;
	    }
	}
    }
}

void
GraphVertex::ConnectTo(GraphVertex *newSink)
{
  this->sinks.push_back(newSink);
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

bool
GraphVertex::hasNext()
{
  if(this->sinks.size() > 0) 
    {
      return true;
    }
  else
    {
      return false;
    }
}

GraphVertex*
GraphVertex::Next()
{
  GraphVertex* next =  this->sinks.back();

  this->sinks.pop_back();

  return next;
}
