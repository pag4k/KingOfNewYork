#ifndef MAP_H
#define MAP_H

#include <string>
#include "graph.h"
#include "borough.h"

class FMap
{
public:
    FMap() {}
    FMap(std::string FileName);

    int BoroughCount() { return Graph.ElementCount(); }
    FBorough &GetBorough(int n) { return Graph.GetElement(n); }
    std::vector<int> GetNeighbourgs(int n) { return Graph.GetNeighbours(n); }

private:
    FGraph<FBorough> Graph;
};

#endif
