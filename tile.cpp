#include <assert.h>
#include <algorithm>
#include <fstream>
#include <iostream>
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

FTileStack::FTileStack()
{
    GenerateFromFile("tiles.txt");
}

void FTileStack::Shuffle()
{
    std::random_shuffle(TileStack.begin(), TileStack.end());
}

bool FTileStack::IsEmpty() const
{
    return (TileStack.empty());
}

FTile *FTileStack::Draw()
{
    assert(!IsEmpty());
    FTile *Card = TileStack.back();
    TileStack.pop_back();
    return Card;
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
    std::string Name = "";
    // int EnergyCost = -1;
    // EHowToPlay HowToPlay = EHowToPlay::None;
    // std::string Effect = "";
    // while (!std::getline(InputStream, Text).eof())
    // {
    //     if (Text.substr(0, 5) == "Name:")
    //     {
    //         if (Name != "" &&
    //             EnergyCost != -1 &&
    //             HowToPlay != EHowToPlay::None &&
    //             Effect != "")
    //         {
    //             Deck.push_back(new FCard(Name, EnergyCost, HowToPlay, Effect));
    //             Name = Text.substr(5, Text.length() - 5);
    //             EnergyCost = -1;
    //             HowToPlay = EHowToPlay::None;
    //             Effect = "";
    //         }
    //         else if (Deck.empty())
    //         {
    //             Name = Text.substr(5, Text.length() - 5);
    //         }
    //         else
    //         {
    //             std::cout << "There was a problem creating card: "
    //                       << Name
    //                       << std::endl;
    //         }
    //     }
    //     else if (Text.substr(0, 11) == "EnergyCost:")
    //     {
    //         EnergyCost = ParseIntFromChar(Text[11]);
    //     }
    //     else if (Text.substr(0, 10) == "HowToPlay:")
    //     {
    //         std::string temp = Text.substr(10, Text.length() - 10);
    //         if (temp == GetHowToPlayString(EHowToPlay::Discard))
    //         {
    //             HowToPlay = EHowToPlay::Discard;
    //         }
    //         else if (temp == GetHowToPlayString(EHowToPlay::Keep))
    //         {
    //             HowToPlay = EHowToPlay::Keep;
    //         }
    //         else
    //         {
    //             HowToPlay = EHowToPlay::None;
    //         }
    //     }
    //     else if (Text.substr(0, 7) == "Effect:")
    //     {
    //         Effect = Text.substr(7, Text.length() - 7);
    //     }
    //     else if (Text == "")
    //     {
    //         continue;
    //     }
    //     else
    //     {
    //         //INVALID
    //     }
    // }

    // if (Name != "" &&
    //     EnergyCost != -1 &&
    //     HowToPlay != EHowToPlay::None &&
    //     Effect != "")
    // {
    //     Deck.push_back(new FCard(Name, EnergyCost, HowToPlay, Effect));
    // }

    InputStream.close();
}
