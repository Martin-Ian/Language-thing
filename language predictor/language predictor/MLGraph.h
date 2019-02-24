#pragma once

#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include "Layer.h"

using namespace std;

class MLGraph
{
private:
	vector<Layer*> layers{};
	pair<float, float> score;

public:
	//Basic constructor
	MLGraph();

	//Constructor for copy
	MLGraph(bool copy);

	void updateLayers(vector<Layer*> newLayer);

	//Mutates the edges
	void mutate();

	//Creates a pointer to a copy of this graph
	MLGraph* copy();

	//Processes a word
	pair<float, float> processWord(string word);

	//Deletion
	~MLGraph();
};