// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "borough.h"
#include <algorithm>

namespace KingOfNewYork {

    FBorough::FBorough() : bStartingLocation(false), bCenter(false)
    {
        TileStacks.resize(TILESTACK_IN_BOROUGH_COUNT);
        std::for_each(TileStacks.begin(), TileStacks.end(), [](auto &TileStack) { TileStack = std::make_unique<FTileStack>(); });
    }

//    int FBorough::GetUnitCount() const
//    {
//
//        return static_cast<int>(std::count_if(TileStacks.begin(), TileStacks.end(), [](const auto &TileStack) { return !TileStack->IsEmpty() && !TileStack->GetConstTopTile()->IsBuilding(); }));
////        int UnitCount = 0;
////        for (const std::unique_ptr<FTileStack> &TileStack : TileStacks)
////        {
////            if (!TileStack->IsEmpty() && !TileStack->GetTopTile()->IsBuilding())
////            {
////                UnitCount++;
////            }
////        }
////        return UnitCount;
//    }
}