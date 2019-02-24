#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include "Edge.h"

//Basic constructor
Node::Node()
{
	_value = -1;
}

//This function takes a float value, and adds it to the toAdd vector, 
	//   which add all the values together before we process the node.
void Node::addValue(float value)
{
	_toAdd.push_back(value);
}

//Gets the current value, not really useful, but here you go...
float Node::getValue()
{
	return _value;
}

//This function pushes the current value through the outgoing edges.
void Node::pushValue()
{
	for (auto edge : _edges)
	{
		edge->setValue(_value); //setValue stores the value, to be pushed 
								//	along to the resulting node
	}
}

//This function adds up all the floats in toAdd and makes that the value
void Node::totalValues()
{
	_value = 0;

	for (auto num : _toAdd)
	{
		_value += num;
	}

	_toAdd.clear();
}

//Processes this node, totals the value and pushes it to the edges.
void Node::process()
{
	//Total the values up
	totalValues();

	//Push them to the edges
	pushValue();
}

//This sets the value of the node;
void Node::setValue(float value)
{
	_value = value;
}

//Adds a new Edge
void Node::addEdge(Edge* newEdge)
{
	_edges.push_back(newEdge);
}