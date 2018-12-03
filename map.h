// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef MAP_H
#define MAP_H

#include "precompiledheader.h"
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
        const std::vector<std::shared_ptr<FBorough>> &GetConstBoroughs() const { return Boroughs; }
        std::vector<std::shared_ptr<FBorough>> &GetMutableBoroughs() { return Boroughs; }
        std::shared_ptr<FBorough> GetCenterBorough();
        const bool IsValid() const { return bIsValid; }
    private:
        FGraph<FBorough,int> Graph;
        std::vector<std::shared_ptr<FBorough>> Boroughs;
        bool bIsValid;
    };
}

#endif
