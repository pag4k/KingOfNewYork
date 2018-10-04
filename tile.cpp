#include <assert.h>
#include "tile.h"

FTile::FTile(ETileType TileType, int Durability, int Reward)
{
    this->TileType = TileType;
    this->Durability = Durability;
    this->Reward = Reward;
}

bool FTile::IsBuilding() const
{
    return (TileType == ETileType::HighRise ||
            TileType == ETileType::PowerPlant ||
            TileType == ETileType::Hospital);
}

EMonsterResource FTile::GetMonsterResource() const
{
    //This only works if ETileType and EMonsterResources are in the right order.
    return EMonsterResource(static_cast<int>(TileType) / 2);
}

void FTile::Flip()
{
    assert(IsBuilding());
    switch (Durability)
    {
    case 1:
        TileType = ETileType::Infantry;
        break;
    case 2:
        TileType = ETileType::Jet;
        break;
    case 3:
        TileType = ETileType::Tank;
        break;
    }
    Reward = Durability;
    Durability++;
}