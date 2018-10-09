#include <assert.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "tile.h"
#include "helper.h"

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

FTileStack::FTileStack()
{

}

FTileStack::FTileStack(std::string FileName)
{
    GenerateFromFile(FileName);
}

void FTileStack::Shuffle()
{
    std::random_shuffle(TileStack.begin(), TileStack.end());
}

std::unique_ptr<FTile> FTileStack::Draw()
{
    assert(!IsEmpty());
    std::unique_ptr<FTile> Card = std::move(TileStack.back());
    TileStack.pop_back();
    return nullptr;
}

void FTileStack::Print() const
{
    //TODO: MAKE UNIQUE
    for (const auto &Tile : TileStack)
    {
        std::cout << "Type: " << GetTileTypeString(Tile->GetTileType()) << std::endl
                  << "Durability: " << Tile->GetDurability() << std::endl
                  << "Reward: " << Tile->GetReward() << std::endl;
    }
}

void FTileStack::GenerateFromFile(const std::string FileName)
{

    std::ifstream InputStream;
    InputStream.open(FileName);

    if (InputStream.fail())
    {
        std::cout << "Could not open file: " << FileName << std::endl;
        return;
    }

    std::string Text;
    int Number = -1;
    ETileType TileType = ETileType::None;
    int Durability = -1;
    int Reward = -1;
    while (!std::getline(InputStream, Text).eof())
    {
        if (Text.substr(0, 7) == "Number:")
        {
            if (Number != -1 &&
                TileType != ETileType::None &&
                Durability != -1 &&
                Reward != -1)
            {
                for (int i = 0; i < Number; ++i)
                {
                    TileStack.push_back(std::make_unique<FTile>(TileType, Durability, Reward));
                }
                Number = ParseIntFromChar(Text[7]);
                TileType = ETileType::None;
                Durability = -1;
                Reward = -1;
            }
            else if (TileStack.empty())
            {
                Number = ParseIntFromChar(Text[7]);
            }
            else
            {
                std::cout << "There was a problem creating tile."
                          << std::endl;
            }
        }
        else if (Text.substr(0, 9) == "TileType:")
        {
            std::string temp = Text.substr(9, Text.length() - 9);
            if (temp == GetTileTypeString(ETileType::HighRise))
            {
                TileType = ETileType::HighRise;
            }
            else if (temp == GetTileTypeString(ETileType::PowerPlant))
            {
                TileType = ETileType::PowerPlant;
            }
            else if (temp == GetTileTypeString(ETileType::Hospital))
            {
                TileType = ETileType::Hospital;
            }
            else
            {
                TileType = ETileType::None;
            }
        }
        else if (Text.substr(0, 11) == "Durability:")
        {
            Durability = ParseIntFromChar(Text[11]);
        }
        else if (Text.substr(0, 7) == "Reward:")
        {
            Reward = ParseIntFromChar(Text[7]);
        }
        else if (Text == "")
        {
            continue;
        }
        else
        {
            //INVALID
        }
    }

    if (Number != -1 &&
        TileType != ETileType::None &&
        Durability != -1 &&
        Reward != -1)
    {
        for (int i = 0; i < Number; ++i)
        {
            TileStack.push_back(std::make_unique<FTile>(TileType, Durability, Reward));
        }
    }

    InputStream.close();
}
