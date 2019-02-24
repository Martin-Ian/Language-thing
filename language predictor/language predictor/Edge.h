#pragma once

class Node;

#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include "Node.h"

using namespace std;

class Edge
{
private:
	//Value of the edge
	float _value;
	//The weight of the edge
	float weight;
	//Node which points to this
	Node* parentNode;
	//out going node
	Node* childNode;

public:
	//Basic constructor, needs a parent node and a child node
	Edge(Node* parent, Node* child);

	//Sets the _value, to be pushed
	void setValue(float value);

	//Applies the weight of the edge to the value
	void applyWeight();

	//Pushes the value to the child node
	void pushValue();

	//Processes this edge
	void process();

	//Mutates this Edge a small amount
	void mutate();

	float getWeight();

	//sets the weight
	void setWeight(float newWeight);
};