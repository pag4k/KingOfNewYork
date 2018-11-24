// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "borough.h"
#include <algorithm>

namespace KingOfNewYork
{
    FBorough::FBorough() : bStartingLocation(false), bCenter(false)
    {
        TileStacks.resize(TILESTACK_IN_BOROUGH_COUNT);
        for (auto &TileStack : TileStacks) TileStack = std::make_unique<FTileStack>();
    }
}