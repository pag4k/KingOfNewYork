// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef MAP_H
#define MAP_H

#include <string>
#include "graph.h"
#include "borough.h"

namespace KingOfNewYork
{
    class FMap
    {
    public:
        FMap() {}
        FMap(const std::string FileName);

        const int BoroughCount() const { return Graph.ElementCount(); }
        FBorough &GetBorough(const int n) { return Graph.GetElement(n); }
        const std::vector<int> GetNeighbourgs(const int n) const { return Graph.GetNeighbours(n); }

    private:
        FGraph<FBorough> Graph;
    };
}

#endif
