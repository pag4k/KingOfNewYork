#ifndef BOROUGH_H
#define BOROUGH_H

#include <memory>

namespace KingOfNewYork
{
    class FPlayer;

    //This will be used as the elements for the vertices of the map graph.
    struct FBorough
    {
        std::string Name;
        bool bStartingLocation;
        bool bInManhattan;
        //TODO: Decide how to work with Manhattan.
        //int Level;
        //TODO: Get this to work with unique_ptr.
        //std::vector<std::unique_ptr<FTile>> TileStacks;
        std::vector<std::shared_ptr<FPlayer>> Players;
    };
}

#endif
