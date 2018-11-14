// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
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
        const bool IsStartingLocation() const { return bStartingLocation; }
        void SetStartingLocation(const bool bStartingLocation) { this->bStartingLocation = bStartingLocation; }
        const bool IsCenter() const { return bCenter; }
        int GetPlayerCount() { return static_cast<int>(GetConstPlayers().size()); }
        void SetCenter(const bool bCenter) { this->bCenter = bCenter; }
        const std::vector<std::unique_ptr<FTileStack>> &GetConstTileStacks() const { return TileStacks; }
        std::vector<std::unique_ptr<FTileStack>> &GetMutableTileStacks() { return TileStacks; }
        const std::vector<std::shared_ptr<FPlayer>> &GetConstPlayers() const { return Players; }
        std::vector<std::shared_ptr<FPlayer>> &GetMutablePlayers() { return Players; }
        const int GetUnitCount();
    private:
        std::string Name;
        bool bStartingLocation;
        bool bCenter;
        std::vector<std::unique_ptr<FTileStack>> TileStacks;
        std::vector<std::shared_ptr<FPlayer>> Players;
    };
}

#endif
