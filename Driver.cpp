/*
Driver.cpp
Author: Manuel Loera
RedID: 817105387
Assignment: Build graph of verticies with edges from CSV read-in. 
"Vertex names need not appear before being introduced in a connection."
Demonstrate roots, leaves, and self verticies by function call.
*/

#include <iostream>
#include <fstream>
#include "Graph.h"
#include <stdio.h>

using namespace std;

void print(Graph &graph);
void print(Graph &graph, string selector);
void buildGraph(Graph &graph, string &fileName);

int main()
{
	Graph graph;
	string fName;

	cout << "Enter path of graph CSV file: \n";
	getline(cin, fName);
	cout << endl;

	buildGraph(graph, fName);

	print(graph);
	print(graph, "roots");
	print(graph, "leaves");
	print(graph, "self");

	cout << "Press Enter to exit:";
	cin.get();
}

void print(Graph &graph)
{
	cout << "Graph of (" << graph.verts.size() << ") verticies:\n{";
	if (graph.verts.size() != 0)
	{
		for (int i = 0; i < graph.verts.size() - 1; i++)
		{
			cout << graph.verts.at(i)->label << ", ";
		}
		cout << graph.verts.at(graph.verts.size() - 1)->label;
	}
	else
	{
		cout << "null";
	}
	cout << "}\n\n";
}

void print(Graph &graph, string selector)
{
	vector<string> edges;
	if (selector == "roots")
	{
		edges = graph.getRoots();
		cout << "roots (0 inbound edges) for the graph:\n{";
		if (edges.size() != 0)
		{
			for (int i = 0; i < edges.size() - 1; i++)
			{
				cout << edges.at(i) << ", ";
			}
			cout << edges.at(edges.size() - 1);
		}
		else
		{
			cout << "null";
		}
		cout << "}\n\n";
	}
	if (selector == "leaves")
	{
		edges = graph.getLeaves();
		cout << "leaves (0 outbound edges) for the graph:\n{";
		if (edges.size() != 0)
		{
			for (int i = 0; i < edges.size() - 1; i++)
			{
				cout << edges.at(i) << ", ";
			}
			cout << edges.at(edges.size() - 1);
		}
		else
		{
			cout << "null";
		}
		cout << "}\n\n";
	}
	if (selector == "self")
	{
		edges = graph.getSelfNodes();
		cout << "self edges (point to self) for the graph:\n{";
		if (edges.size() != 0)
		{
			for (int i = 0; i < edges.size() - 1; i++)
			{
				cout << edges.at(i) << ", ";
			}
			cout << edges.at(edges.size() - 1);
		}
		else
		{
			cout << "null";
		}
		cout << "}\n\n";
	}
}

void buildGraph(Graph &graph, string &fileName)
{
	ifstream file;
	string line, token, token2;
	const char *buff;
	bool isLinking;

	file.open(fileName, ifstream::in);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			buff = line.c_str();
			isLinking = false;
			token = "", token2 = "";

			while (*buff != '\0')
			{
				if (isLinking)
				{
					if (*buff != ',')
					{
						token2 += *buff;
					}
					else
					{
						graph.link(token, token2, ((int)(*(buff + 1))) - 48);
						buff++;
					}
				}
				else if (*buff == ',')
				{
					isLinking = true;
				}
				else
				{
					token += *buff;
					if (*(buff + 1) == '\0' && !isLinking)
					{
						graph.add(token);
					}
				}
				buff++;
			}
		}
		file.close();
	}
}

/*
Output:
Enter path of graph CSV file:
graph.csv

Graph of (10) verticies:
{Basic, Grimer, Tapu Koko, Jirachi, Charmander, Stage 1, 
Muk, Charmeleon, Stage 2, Charizard}

roots (0 inbound edges) for the graph:
{Basic}

leaves (0 outbound edges) for the graph:
{Tapu Koko, Jirachi, Muk, Charizard}

self edges (point to self) for the graph:
{null}

Press Enter to exit:
*/