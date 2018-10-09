#ifndef BOROUGH_H
#define BOROUGH_H

#include "tile.h"

class FPlayer;

struct FBorough
{
    std::string Name;
    bool bStartingLocation;
    bool bInManhattan;
    //int Level;
    //std::vector<std::unique_ptr<FTile>> TileStacks;
    std::vector<std::shared_ptr<FPlayer>> Players;
};

#endif
