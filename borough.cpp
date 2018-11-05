
#include "borough.h"

namespace KingOfNewYork {

    FBorough::FBorough() : bStartingLocation(false), bCenter(false) {
        for (int i = 0; i < TILESTACK_IN_BOROUGH_COUNT; ++i) {
            TileStacks.push_back(std::make_unique<FTileStack>());
        }
    }

    const int FBorough::GetUnitCount() {
        int UnitCount = 0;
        for (std::unique_ptr<FTileStack> &TileStack : TileStacks)
        {
            if (!TileStack->GetTopTileInfo()->IsBuilding())
            {
                UnitCount++;
            }
        }
        return UnitCount;
    }
}