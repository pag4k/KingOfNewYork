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
    FTileStack TileStacks[NUMBER_OF_TILESTACKS_IN_BOROUGH];
    std::vector<std::shared_ptr<FPlayer>> Players;
};

#endif
