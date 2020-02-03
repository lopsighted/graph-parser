/*
Graph.cpp
Explicit definitions and functions of Graph.h definitions
Manuel Loera

*/
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;

//Edge instantiates with default nullptrs
Edge::Edge()
{
	this->dest = nullptr;
	this->source = nullptr;
}

//mutates deired destination node and weight which is def at 1
void Edge::addTo(MapNode &dest, int weight = 1)
{
	this->dest = &dest;
	this->weight = weight;
};

//mutates deired source node and weight which is def at 1
void Edge::addFrom(MapNode &source, int weight = 1)
{
	this->source = &source;
	this->weight = weight;
}

// Default instance of mapnode assigns string null to label
MapNode::MapNode()
{
	this->label = "null";
}

// add method pushes label into mapnode obj
void MapNode::add(string token)
{
	this->label = token;
}

// overloaded add method pushes edge into mapnode obj
void MapNode::add(Edge &edge)
{
	this->edges.push_back(&edge);
}

// overloaded add method pushes both token and string
void MapNode::add(string token, Edge &edge)
{
	this->label = token;
	this->edges.push_back(&edge);
}

// add method for graph adds a node by label
void Graph::add(string token)
{
	if (!Graph::contains(token))
	{
		MapNode *node = new MapNode;
		node->label = token;
		this->verts.push_back(node);
	}
}

// overloaded add method for graph adds node by a character for optimized memory capability
void Graph::add(char token)
{
	if (!Graph::contains(string(1, token)))
	{
		MapNode *node = new MapNode;
		node->label = token;
		this->verts.push_back(node);
	}
}

// Link method for graph creates source node and dest node by strings passed, 
// and adds node if the graph doesn't already contain it 
void Graph::link(string source, string dest, int weight = 1)
{
	MapNode *sourceNode, *destNode;

	add(source);
	add(dest);
	sourceNode = find(source);
	destNode = find(dest);
	if (sourceNode != nullptr && destNode != nullptr)
	{
		Edge *sourceEdge = new Edge;
		Edge *destEdge = new Edge;

		sourceEdge->addTo(*destNode, weight);
		destEdge->addFrom(*sourceNode, weight);
		sourceNode->add(*sourceEdge);
		destNode->add(*destEdge);
	}
}

// Link method for graph creates source node and dest node by char passed, 
// and adds node only if the graph doesn't already contain it 
void Graph::link(char source, char dest, int weight = 1)
{
	MapNode *sourceNode, *destNode;

	add(source);
	add(dest);
	sourceNode = find(source);
	destNode = find(dest);
	if (sourceNode != nullptr && destNode != nullptr)
	{
		Edge *sourceEdge = new Edge;
		Edge *destEdge = new Edge;

		sourceEdge->addTo(*destNode, weight);
		destEdge->addFrom(*sourceNode, weight);
		sourceNode->add(*sourceEdge);
		destNode->add(*destEdge);
	}
}

// Graph method finds nodes within graph mapode array by string, returns node found or nullptr if not found 
MapNode *Graph::find(string token)
{
	for (int i = 0; i < verts.size(); i++)
	{
		if (verts.at(i)->label == token)
			return verts.at(i);
	}
	return nullptr;
}

// Graph method finds nodes within graph mapode array by char, returns node found or nullptr if not found 
MapNode *Graph::find(char token)
{
	for (int i = 0; i < verts.size(); i++)
	{
		if (this->verts.at(i)->label == string(1, token))
			return verts.at(i);
	}
	return nullptr;
}

// Graph method searches graph if it contains node matching string that is passed. boolean returned
bool Graph::contains(string token)
{
	for (int i = 0; i < verts.size(); i++)
	{
		if (verts.at(i)->label == token)
			return true;
	}
	return false;
}

//Graph method returns vector array of nodes that contains zero edges/source edges
vector<string> Graph::getRoots()
{

	vector<string> roots;
	for (int i = 0; i < verts.size(); i++)
	{
		if (verts.at(i)->edges.size() == 0)
		{
			roots.push_back(verts.at(i)->label);
		}
		else
		{
			bool nullSource = true;
			for (int n = 0; n < verts.at(i)->edges.size() && nullSource; n++)
			{
				if (verts.at(i)->edges.at(n)->source != nullptr)
				{
					nullSource = false;
				}
			}
			if (nullSource)
			{
				roots.push_back(verts.at(i)->label);
			}
		}
	}
	return roots;
}

//Graph method returns vector array of nodes that contains zero destination edges
vector<string> Graph::getLeaves()
{
	vector<string> leaves;
	for (int i = 0; i < verts.size(); i++)
	{
		if (verts.at(i)->edges.size() != 0)
		{
			bool nullDest = true;
			for (int n = 0; n < verts.at(i)->edges.size() && nullDest; n++)
			{
				if (verts.at(i)->edges.at(n)->dest != nullptr)
					nullDest = false;
			}
			if (nullDest)
			{
				leaves.push_back(verts.at(i)->label);
			}
		}
	}
	return leaves;
}

// Graph method returns a vector array of strings of nodes that point to themselves
vector<string> Graph::getSelfNodes()
{
	vector<string> self;
	for (int i = 0; i < verts.size(); i++)
	{
		if (verts.at(i)->edges.size() != 0)
		{
			bool selfPoint = false;
			for (int n = 0; n < verts.at(i)->edges.size() && !selfPoint; n++)
			{
				if (verts.at(i)->edges.at(n)->dest == verts.at(i))
					selfPoint = true;
			}
			if (selfPoint)
			{
				self.push_back(verts.at(i)->label);
			}
		}
	}
	return self;
}