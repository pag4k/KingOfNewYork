// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <cassert>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include "tile.h"
#include "helper.h"

namespace KingOfNewYork
{
    FTile::FTile(ETileType TileType, int Durability, int Reward)
            : TileType(TileType), Durability(Durability), Reward(Reward) {}

    bool FTile::IsBuilding() const
    {
        return (TileType == ETileType::HighRise ||
                TileType == ETileType::PowerPlant ||
                TileType == ETileType::Hospital);
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
        default:
            assert(true);
        }
        Reward = Durability;
        Durability++;
    }

    std::string FTile::GetTileInfo() const
    {
        return GetTileTypeString(GetTileType()) + ": Durability: " + std::to_string(GetDurability()) + " Reward: " + std::to_string(GetReward()) + " " + GetMonsterResourceString(EMonsterResource(static_cast<int>(GetTileType())/2));
    }

    FTileStack::FTileStack(const std::string FileName)
    {
        GenerateFromFile(FileName);
    }

    void FTileStack::Shuffle()
    {
        std::shuffle(TileStack.begin(), TileStack.end(), std::default_random_engine(
                static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count())));
    }

    std::unique_ptr<FTile> FTileStack::Draw()
    {
        assert(!IsEmpty());
        std::unique_ptr<FTile> Tile = std::move(TileStack.back());
        TileStack.pop_back();
        return Tile;
    }

    std::unique_ptr<FTile> &FTileStack::GetMutableTopTile()
    {
        assert(!TileStack.empty());
        return TileStack.back();
    }

    const std::unique_ptr<FTile> &FTileStack::GetTopTile() const
    {
        assert(!TileStack.empty());
        return TileStack.back();
    }

    void FTileStack::AddTileOnTop(std::unique_ptr<FTile> Tile)
    {
        assert(Tile != nullptr);
        TileStack.push_back(std::move(Tile));
    }

    //Destroy the top Building, flip it to a unit, and return it.
    std::unique_ptr<FTile> FTileStack::DestructTopTile()
    {
        auto Tile = std::move(TileStack.back());
        TileStack.pop_back();
        Tile->Flip();
        return Tile;
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
            else if (Text.empty())
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
