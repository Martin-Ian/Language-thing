#pragma once

class Edge;

#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include "Edge.h"

using namespace std;

class Node
{
private:
	float _value;
	vector<Edge*> _edges{};
	vector<float> _toAdd{};

public:
	//Basic Constructor
	Node();

	//This function takes a float value, and adds it to the toAdd vector, 
	//   which add all the values together before we process the node.
	void addValue(float value);

	//This sets the value of the node;
	void setValue(float value);

	//Gets the current value, not really useful, but here you go...
	float getValue();

	//This function pushes the current value through the outgoing edges.
	void pushValue();

	//This function adds up all the floats in toAdd and makes that the value
	void totalValues();

	//Processes this node, totals the value and pushes it to the edges.
	void process();

	//Adds a new Edge
	void addEdge(Edge* newEdge);
};