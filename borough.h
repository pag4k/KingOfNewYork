#ifndef BOROUGH_H
#define BOROUGH_H

#include <memory>

namespace KingOfNewYork
{
    class FPlayer;

    //This struct will be used as the elements for the vertices of the map graph.
    struct FBorough
    {
        std::string Name;
        bool bStartingLocation;
        bool bInManhattan;
        //int Level; //TODO: Decide how to work with Manhattan.
        //std::vector<std::unique_ptr<FTile>> TileStacks; //TODO: Get this to work with unique_ptr.
        std::vector<std::shared_ptr<FPlayer>> Players;
    };
}

#endif
