#ifndef TILE_H
#define TILE_H

#include <vector>
#include <string>
#include <memory>
#include "common.h"

class FTile
{
public:
    FTile(ETileType TileType, int Durability, int Reward);
    bool IsBuilding() const;
    EMonsterResource GetMonsterResource() const;
    void Flip();
    ETileType GetTileType() const { return TileType; }
    int GetDurability() const { return Durability; }
    int GetReward() const { return Reward; }

private :
    ETileType TileType;
    int Durability;
    int Reward;
};

class FTileStack
{
public:
    FTileStack();
    FTileStack(std::string FileName);
    void Shuffle();
    int Size() const { return TileStack.size(); } 
    bool IsEmpty() const { return TileStack.empty(); }
    std::unique_ptr<FTile> Draw();
    void Print() const;

private:
    void GenerateFromFile(const std::string FileName);
    std::vector<std::unique_ptr<FTile>> TileStack;
};

#endif
