#include <iostream>
#include "graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
    for (auto it = adjList.begin(); it != adjList.end(); it++)
    {
        delete it->second;
    }
}

void Graph::addNode(Node *node)
{
    adjList[node->getId()] = node;
}

void Graph::addEdge(long from, long to, weightFunction *f)
{
    Node *fromNode = adjList[from];
    Node *toNode = adjList[to];
    fromNode->addNeighbour(toNode, f);
}

vector<Node *> Graph::getNodes()
{
    vector<Node *> nodes;
    for (auto it = adjList.begin(); it != adjList.end(); it++)
    {
        nodes.push_back(it->second);
    }
    return nodes;
}

void Graph::printGraph()
{
    std::cout << "Printing graph\n";
    for (auto it = adjList.begin(); it != adjList.end(); it++)
    {
        std::cout << it->first << " : ";
        vector<pair<Node *, weightFunction *>> neighbours = it->second->getNeighbours();
        for (auto it2 = neighbours.begin(); it2 != neighbours.end(); it2++)
        {
            std::cout << it2->first->getId() << " ";
        }
        std::cout << "\n";
    }
}