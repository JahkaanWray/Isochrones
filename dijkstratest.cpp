#include <iostream>
#include "shortestpath.h"

int main()
{
    Graph g;
    Node *n1 = new Node(1, 0, 0);
    Node *n2 = new Node(2, 0, 0);
    Node *n3 = new Node(3, 0, 0);
    Node *n4 = new Node(4, 0, 0);
    Node *n5 = new Node(5, 0, 0);

    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);
    g.addNode(n4);
    g.addNode(n5);

    g.addEdge(1, 2, new constantFunction(1));
    g.addEdge(2, 3, new constantFunction(1));
    g.addEdge(3, 4, new constantFunction(1));
    g.addEdge(4, 5, new constantFunction(1));
    g.addEdge(1, 5, new constantFunction(1));
    g.addEdge(5, 1, new constantFunction(1));

    ShortestPath sp(&g, 3);
    std::cout << sp.distTo(1) << "\n";
    std::cout << sp.distTo(2) << "\n";
    std::cout << sp.distTo(3) << "\n";
    std::cout << sp.distTo(4) << "\n";
    std::cout << sp.distTo(5) << "\n";
    return 0;
}