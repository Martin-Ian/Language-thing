#pragma once

#include <iostream>
#include <cstdlib>
#include "Node.h"
#include "Edge.h"

class Layer
{
private:
	vector<Node*> nodeList{};
	vector<Edge*> edgeList{};
	bool _isEdgeList;

public:
	Layer()
	{

	}

	bool isEdgeList()
	{
		return _isEdgeList;
	}

	vector<Node*> getNodeList()
	{
		return nodeList;
	}

	vector<Edge*> getEdgeList()
	{
		return edgeList;
	}

	void setEdgeList()
	{
		_isEdgeList = true;
	}

	void processLayer()
	{
		if (_isEdgeList)
		{
			for (auto edge : edgeList)
			{
				edge->process();
			}
		}
		else
		{
			for (auto node : nodeList)
			{
				node->process();
			}
		}
	}

	void addNode(Node* node)
	{
		nodeList.push_back(node);
	}

	void addEdge(Edge* edge)
	{
		edgeList.push_back(edge);
	}

	~Layer()
	{
		if (_isEdgeList)
		{
			for (auto edge : edgeList)
			{
				delete edge;
			}
		}
		else
		{
			for (auto node : nodeList)
			{
				delete node;
			}
		}
	}
};