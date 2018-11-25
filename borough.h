// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef BOROUGH_H
#define BOROUGH_H

#include <memory>
#include "tile.h"

namespace KingOfNewYork
{
    class FPlayer;

    //This will be used as the elements for the vertices of the map graph.
    class FBorough
    {
    public:
        FBorough();
        FBorough(const FBorough& Other) = delete;
        const std::string &GetName() const { return Name; }
        void SetName(const std::string &Name) { this->Name = Name; }
        bool IsStartingLocation() const { return bStartingLocation; }
        void SetStartingLocation(bool bStartingLocation) { this->bStartingLocation = bStartingLocation; }
        bool IsCenter() const { return bCenter; }
        int GetPlayerCount() const { return static_cast<int>(GetConstPlayers().size()); }
        void SetCenter(bool bCenter) { this->bCenter = bCenter; }
        const std::vector<std::unique_ptr<FTileStack>> &GetConstTileStacks() const { return TileStacks; }
        std::vector<std::unique_ptr<FTileStack>> &GetMutableTileStacks() { return TileStacks; }
        const std::vector<std::shared_ptr<FPlayer>> &GetConstPlayers() const { return Players; }
        std::vector<std::shared_ptr<FPlayer>> &GetMutablePlayers() { return Players; }
        std::vector<std::unique_ptr<FTile>> &GetUnits() { return Units; }
        int GetUnitCount() const { return static_cast<int>(Units.size()); }
    private:
        std::string Name;
        bool bStartingLocation;
        bool bCenter;
        std::vector<std::unique_ptr<FTileStack>> TileStacks;
        std::vector<std::unique_ptr<FTile>> Units;
        std::vector<std::shared_ptr<FPlayer>> Players;
    };
}

#endif
