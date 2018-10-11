// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <assert.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "tile.h"
#include "helper.h"

namespace KingOfNewYork
{
    FTile::FTile(
        const ETileType TileType,
        const int Durability,
        const int Reward) :
        TileType(TileType),
        Durability(Durability),
        Reward(Reward) {}

    const bool FTile::IsBuilding() const
    {
        return (TileType == ETileType::HighRise ||
                TileType == ETileType::PowerPlant ||
                TileType == ETileType::Hospital);
    }

    const EMonsterResource FTile::GetMonsterResource() const
    {
        //This only works if ETileType and EMonsterResources are in right order.
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

    FTileStack::FTileStack(const std::string FileName)
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
        for (const auto &Tile : TileStack)
        {
            std::cout << "Type: "
                      << GetTileTypeString(Tile->GetTileType())
                      << std::endl
                      << "Durability: "
                      << Tile->GetDurability()
                      << std::endl
                      << "Reward: "
                      << Tile->GetReward()
                      << std::endl;
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
                        //TODO: Not sure if this does a copy or not.
                        TileStack.push_back(
                            std::make_unique<FTile>(
                                TileType,
                                Durability,
                                Reward));
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
                std::cout << "Error: Invalid line detected: "
                          << Text
                          << std::endl;
                Number = -1;
                TileType = ETileType::None;
                Durability = -1;
                Reward = -1;
            }
        }

        if (Number != -1 &&
            TileType != ETileType::None &&
            Durability != -1 &&
            Reward != -1)
        {
            for (int i = 0; i < Number; ++i)
            {
                TileStack.push_back(
                    std::make_unique<FTile>(
                        TileType,
                        Durability,
                        Reward));
            }
        }

        InputStream.close();
    }
}
