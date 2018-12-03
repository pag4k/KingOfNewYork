// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef TILE_H
#define TILE_H

#include "precompiledheader.h"
#include "common.h"

namespace KingOfNewYork
{
    //Class representing a single tile.
    class FTile
    {
    public:
        FTile(ETileType TileType, int Durability, int Reward);
        bool IsBuilding() const;
        void Flip();
        ETileType GetTileType() const { return TileType; }
        int GetDurability() const { return Durability; }
        int GetReward() const { return Reward; }
        std::string GetTileInfo() const;
    private:
        ETileType TileType;
        int Durability;
        int Reward;
    };

    //Class representing a stack of tiles.
    class FTileStack
    {
    public:
        FTileStack() = default;
        explicit FTileStack(std::string FileName);
        void Shuffle();
        bool IsEmpty() const { return TileStack.empty(); }
        std::unique_ptr<FTile> Draw();
        std::unique_ptr<FTile> &GetMutableTopTile();
        const std::unique_ptr<FTile> &GetTopTile() const;
        void AddTileOnTop(std::unique_ptr<FTile> Tile);
        std::unique_ptr<FTile> DestructTopTile();
    private:
        void GenerateFromFile(std::string FileName);
        std::vector<std::unique_ptr<FTile>> TileStack;
    };
}

#endif
