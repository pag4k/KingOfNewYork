// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef MAP_H
#define MAP_H

#include <string>
#include "graph.h"
#include "borough.h"

namespace KingOfNewYork
{
    //A class that contains the game with with a graph.
    class FMap
    {
    public:
        FMap(): bIsValid(false) {}
        explicit FMap(const std::string &FileName);
        bool LoadMap(const std::string &FileName);
        bool SaveMap(const std::string &FileName);
        const unsigned int BoroughCount() const { return (unsigned int)Graph.ElementCount(); }
        std::shared_ptr<FBorough> GetBorough(const int n) { return Graph.GetElement(n); }
        std::vector<std::shared_ptr<FBorough>>& GetBoroughs() { return Boroughs; }
        std::shared_ptr<FBorough> GetCenterBorough();
        const std::vector<int> GetNeighbourgs(int n) const;
        const bool IsValid() const { return bIsValid; }
    private:
        FGraph<FBorough> Graph;
        std::vector<std::shared_ptr<FBorough>> Boroughs;
        bool bIsValid;
    };
}

#endif
