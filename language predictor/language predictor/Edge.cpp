#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include "Edge.h"

//Basic constructor, needs a parent node and a child node
Edge::Edge(Node* parent, Node* child)
{
	parentNode = parent;
	childNode = child;

	weight = (rand() % 1000) / 1000.0; // random number between 0-1 for weight
}

//Sets the _value, to be pushed
void Edge::setValue(float value)
{
	_value = value;
}

//Applies the weight of the edge to the value
void Edge::applyWeight()
{
	_value *= weight;
}

//Pushes the value to the child node
void Edge::pushValue()
{
	childNode->addValue(_value);
}

//Processes this edge
void Edge::process()
{
	applyWeight();

	pushValue();
}

//Mutates this Edge a small amount
void Edge::mutate()
{
	if (rand() % 100 < 10) // 10% chance to mutate entirely
	{
		weight = (rand() % 1000) / 1000; // random number between 0-1 for weight
	}
	else
	{
		weight += ((rand() % 100) / 500.0) - 0.1; //adds random number from -.05 to .05

		if (weight > 1)
		{
			weight = 1;
		}

		if (weight < 0)
		{
			weight = 0;
		}
	}
}

float Edge::getWeight()
{
	return weight;
}

//sets the weight
void Edge::setWeight(float newWeight)
{
	weight = newWeight;
}