#include <unordered_map>
#include <vector>
#include "weightFunction.h"

using namespace std;

class Node
{
private:
    long id;
    std::vector<std::pair<Node *, weightFunction *>> neighbours;

public:
    double lat;
    double lon;
    Node(long id, double lat, double lon)
    {
        this->id = id;
        this->lat = lat;
        this->lon = lon;
    }
    ~Node() {}
    long getId() const { return id; }
    void addNeighbour(Node *node, weightFunction *weight)
    {
        neighbours.push_back(std::make_pair(node, weight));
    }
    std::vector<std::pair<Node *, weightFunction *>> getNeighbours() const { return neighbours; }
};

class Edge
{
public:
    Edge(const Node &from, const Node &to, double distance) : from(from), to(to)
    {
    }

    ~Edge()
    {
    }

private:
    Node from;
    Node to;
};

class Graph
{
private:
    /* data */
    std::unordered_map<long, Node *> adjList;

public:
    Graph(/* args */);
    ~Graph();

    void addNode(Node *node);
    void addEdge(long from, long to, weightFunction *f);
    Node *getNode(long id) { return adjList[id]; }
    void printGraph();
    vector<Node *> getNodes();
};
