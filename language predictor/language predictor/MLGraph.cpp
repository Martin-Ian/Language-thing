#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include "Edge.h"
#include "Node.h"
#include "MLGraph.h"
#include "Layer.h"

//Basic constructor
MLGraph::MLGraph()
{
	//Set up the layers
	for (int i = 0; i < 9; i++)
	{
		layers.push_back(new Layer());
		if (i % 2 == 1)
		{
			layers[i]->setEdgeList();
		}
	}

	//0,2,4,6 layers are 20 nodes each
	for (int i = 0; i <= 6; i += 2)
	{
		for (int j = 0; j < 20; j++)
		{
			layers[i]->addNode(new Node());
		}
	}

	//Last layer is 2 nodes to determine the language
	layers[8]->addNode(new Node());
	layers[8]->addNode(new Node());

	//Odd layers are edges, and need to be connected to adjacent nodes.
	for (int i = 0; i <= 6; i += 2)
	{
		for (auto node : layers[i]->getNodeList())
		{
			for (auto node2 : layers[i+2]->getNodeList())
			{
				Edge* boi = new Edge(node, node2);

				layers[i + 1]->addEdge(boi);

				node->addEdge(boi);
			}
		}
	}
}

MLGraph::MLGraph(bool copy)
{
	//intentionally empty
}

//Mutates the edges
void MLGraph::mutate()
{
	for (int i = 1; i <= 7; i += 2)
	{
		for (auto e : layers[i]->getEdgeList())
		{
			if (rand() % 100 < 80)
			{
				e->mutate();
			}
		}
	}
}

void MLGraph::updateLayers(vector<Layer*> newLayer)
{
	for (int i = 0; i < newLayer.size(); i++)
	{
		layers.push_back(new Layer());
		if (newLayer[i]->isEdgeList())
		{
			layers[i]->setEdgeList();
		}
		else
		{
			for (auto node : newLayer[i]->getNodeList())
			{
				layers[i]->addNode(new Node());
			}
		}
	}

	for (int i = 0; i <= 6; i += 2)
	{
		for (auto node : layers[i]->getNodeList())
		{
			for (auto node2 : layers[i + 2]->getNodeList())
			{
				Edge* egde = new Edge(node, node2);
				layers[i + 1]->addEdge(egde);
			}
		}
	}
}

//Creates a pointer to a copy of this graph
MLGraph* MLGraph::copy()
{
	MLGraph* toReturn = new MLGraph();

	for (int i = 1; i < layers.size(); i++)
	{
		for (int j = 0; j < toReturn->layers[i]->getEdgeList().size(); j++)
		{
			toReturn->layers[i]->getEdgeList()[j]->setWeight(this->layers[i]->getEdgeList()[j]->getWeight());
		}
	}

	toReturn->mutate();

	return toReturn;
}

//Processes a word
pair<float, float> MLGraph::processWord(string word)
{
	for (auto N : layers[0]->getNodeList())
	{
		N->setValue(-1);
	}

	for (int i = 0; i < word.length(); i++)
	{
		layers[0]->getNodeList()[i]->addValue(float(word[i])/10.0);
	}

	for (int i = word.length()-1; i >= 0; i--)
	{
		layers[0]->getNodeList()[layers[0]->getNodeList().size() - 1 - i]->addValue(float(word[i])/10.0);
	}

	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->processLayer();
	}

	pair<float, float> toReturn = make_pair(layers[8]->getNodeList()[0]->getValue(), layers[8]->getNodeList()[1]->getValue());

	float total = toReturn.first + toReturn.second;

	float temp1 = toReturn.first / total;
	float temp2 = toReturn.second / total;

	toReturn.first = temp1;
	toReturn.second = temp2;

	score = toReturn;

	return toReturn;
}

//Deletion
MLGraph::~MLGraph()
{
	for (auto layer : layers)
	{
		delete layer;
	}
}