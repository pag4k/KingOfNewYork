#include <vector>
#include <string>
#include "common.h"

class FTile
{
public:
    FTile(ETileType TileType, int Durability, int Reward);
    bool IsBuilding() const;
    EMonsterResource GetMonsterResource() const;
    void Flip();
        //void Destroy();
private : ETileType TileType;
    int Durability;
    int Reward;
};

class FTileStack
{
public:
    FTileStack();
    void Shuffle();
    bool IsEmpty() const;
    FTileStack Draw();

private:
    void GenerateFromFile(const std::string FileName);
    std::vector<FTile> Tiles;
};