#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "graph.h"

class ShortestPath
{
private:
    std::unordered_map<long, weightFunction *> distMap;
    std::vector<Node *> visitedNodes;
    std::vector<long> distToVector;

public:
    ShortestPath(Graph *g, long s);
    bool hasPathTo(long v) const;
    weightFunction *distTo(long v) const;
    std::vector<long> pathTo(long v) const;
    std::vector<Node *> getNodes() const;
    std::vector<long> getDistToVector() const;
};