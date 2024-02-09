#include "shortestpath.h"
#include "weightFunctionAdd.h"
#include "weightFunctionCompare.h"

ShortestPath::ShortestPath(Graph *g, long s)
{
    std::priority_queue<std::pair<weightFunction *, long>, std::vector<std::pair<weightFunction *, long>>, weightFunctionCompare> pq;
    distMap[s] = new constantFunction(0);
    pq.push(std::make_pair(distMap[s], s));
    while (!pq.empty())
    {
        long v = pq.top().second;
        visitedNodes.push_back(g->getNode(v));
        pq.pop();
        std::vector<std::pair<Node *, weightFunction *>> neighbours = g->getNode(v)->getNeighbours();
        for (auto it = neighbours.begin(); it != neighbours.end(); it++)
        {
            long w = it->first->getId();
            weightFunction *weight = it->second;
            if (distMap.find(w) == distMap.end() || (*distMap[w])(0) > (*distMap[v])(0) + (*weight)(0))
            {
                distMap[w] = add(distMap[v], weight);
                pq.push(std::make_pair(distMap[w], w));
            }
        }
    }
}

bool ShortestPath::hasPathTo(long v) const
{
    return distMap.find(v) != distMap.end();
}

weightFunction *ShortestPath::distTo(long v) const
{
    if (hasPathTo(v))
    {
        return distMap.at(v);
    }
    return new constantFunction(std::numeric_limits<double>::infinity());
}

std::vector<Node *> ShortestPath::getNodes() const
{
    return visitedNodes;
}
