#ifndef BOROUGH_H
#define BOROUGH_H

#include <memory>
#include "tile.h"

namespace KingOfNewYork
{
    class FPlayer;

    //This will be used as the elements for the vertices of the map graph.
    struct FBorough
    {
        FBorough() = default;
        FBorough(const FBorough& Other) = delete;
        //~FBorough() { TileStacks.clear(); }
        std::string Name;
        bool bStartingLocation;
        bool bInManhattan;
        //TODO: Decide how to work with Manhattan.
        //int Level;
        std::vector<std::unique_ptr<FTileStack>> TileStacks;
        std::vector<std::shared_ptr<FPlayer>> Players;
    };
}

#endif
