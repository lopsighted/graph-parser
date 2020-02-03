/* 
Graph.h
Definitions of node, edge, and graph structures.
Manuel Loera
 */
#include <vector>
#include <string>

using namespace std;

class MapNode;
class Edge;
class Graph;

//Node object with label and vector(set) of edges has 3 overloaded add methods
class MapNode
{
public:
    string label;
    vector<Edge *> edges;

    MapNode();
    void add(string token);
    void add(Edge &edge);
    void add(string token, Edge &edge);
};

//Edge object with weight and destination/source mapnode instances.
class Edge
{
public:
    int weight;
    MapNode *dest;
    MapNode *source;

    Edge();
    void addTo(MapNode &dest, int weight);
    void addFrom(MapNode &source, int weight);
};

//graph object contains set of all mapnodes(verticies) with various methods for accessing
//and mutating objects within mapnodes
class Graph
{
public:
    vector<MapNode *> verts;

    void add(string token);
    void add(char token);
    void link(string source, string dest, int weight);
    void link(char source, char dest, int weight);
    MapNode *find(string token);
    MapNode *find(char token);
    vector<string> getRoots();
    vector<string> getLeaves();
    vector<string> getSelfNodes();
    bool contains(string token);
};