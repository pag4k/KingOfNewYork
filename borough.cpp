// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "borough.h"

namespace KingOfNewYork
{
    FBorough::FBorough() : bStartingLocation(false), bCenter(false)
    {
        TileStacks.resize(TILESTACK_IN_BOROUGH_COUNT);
        for (auto &TileStack : TileStacks) TileStack = std::make_unique<FTileStack>();
    }
}