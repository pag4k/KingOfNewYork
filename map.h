// ----------------------------------------------------------------------------
// COMP345 Assignment 2
// Due date: November 4, 2018
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
        FMap(): bIsValid(false) {}
        explicit FMap(const std::string &FileName);
        bool LoadMap(const std::string &FileName);
        bool SaveMap(const std::string &FileName);
        const unsigned int BoroughCount() const { return (unsigned int)Graph.ElementCount(); }
        std::shared_ptr<FBorough> GetBorough(const int n) { return Graph.GetElement(n); }
        std::shared_ptr<FBorough> GetCenterBorough();
        const std::vector<int> GetNeighbourgs(const int n) const;
        const bool IsValid() const { return bIsValid; }
    private:
        FGraph<FBorough> Graph;
        bool bIsValid;
    };
}

#endif
