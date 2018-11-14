// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef TILE_H
#define TILE_H

#include <vector>
#include <string>
#include <memory>
#include "common.h"

namespace KingOfNewYork
{
    class FTile
    {
    public:
        FTile(const ETileType TileType, const int Durability, const int Reward);
        const bool IsBuilding() const;
        const EMonsterResource GetMonsterResource() const;
        void Flip();
        const ETileType GetTileType() const { return TileType; }
        const int GetDurability() const { return Durability; }
        const int GetReward() const { return Reward; }
        const std::string GetTileInfo();
    private:
        ETileType TileType;
        int Durability;
        int Reward;
    };

    class FTileStack
    {
    public:
        FTileStack() = default;
        explicit FTileStack(const std::string FileName);
        void Shuffle();
        const bool IsEmpty() const { return TileStack.empty(); }
        std::unique_ptr<FTile> Draw();
        std::unique_ptr<FTile> &GetTopTileInfo();
        void AddTileOnTop(std::unique_ptr<FTile> Tile);
        void DestructTopTile();
    private:
        void GenerateFromFile(const std::string FileName);
        std::vector<std::unique_ptr<FTile>> TileStack;
    };
}

#endif
