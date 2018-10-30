// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <assert.h>
#include <iostream>

#include "game.h"
#include "player.h"
#include "helper.h"

namespace KingOfNewYork
{
    FGame::FGame()
    {
        if (!Initialize())
        {
            std::cout << "Error: There was a problem initializing the game."
                      << std::endl;
        }
    }

    FGame::~FGame()
    {
        if (Map)
        {
            delete Map;
        }
        Players.clear();
        Superstar = nullptr;
        StatusOfLiberty = nullptr;
    }

    void FGame::Print() const
    {
        std::cout << "Number of players: " << PlayerCount << std::endl;
        for (const std::shared_ptr<FPlayer> &Player : Players)
        {
            std::cout << "\t-";
            Player->PrintShort();
        }
        
        std::cout << "Monster in Manhattam: ";
        if (PlayersInManhattan.empty())
        {
            std::cout << "No one." << std::endl;
        }
        else
        {
            for (const std::shared_ptr<FPlayer> &Player : Players)
            {
                std::cout   << "\t-"
                            << GetMonsterNameString(Player->GetMonsterName())
                            << std::endl;
            }
        }

        std::cout   << "Superstar: "
                    << (Superstar ?
                        GetMonsterNameString(Superstar->GetMonsterName()) :
                        "No one")
                    << std::endl;
        std::cout << "Status of Liberty: "
                << (StatusOfLiberty ?
                    GetMonsterNameString(StatusOfLiberty->GetMonsterName()) :
                    "No one")
                << std::endl;

        std::cout << "Number of cards in deck: " << Deck.Size() << std::endl;
        std::cout << "Number of cards in discard deck: "
                  << DiscardDeck.Size()
                  << std::endl;

        std::cout << "Tokens left:" << std::endl;
        for (int i = 0; i < NUMBER_OF_TOKEN_TYPE; ++i)
        {
            std::cout   << "\t-"
                        << GetTokenTypeString(ETokenType(i))
                        << ": "
                        << TokenInventory[i]
                        << std::endl;
        }

        std::cout   << "Energy cubes left: "
                    << EnergyCubes
                    << std::endl;

        std::cout << "Available cards:" << std::endl;
        for (int i = 0; i < MAXIMUM_AVAILABLE_CARDS; ++i)
        {
            if (AvailableCards[i])
            {
                std::cout << "\t-"
                        << AvailableCards[i]->GetName()
                        << std::endl;
            }
            
        }
    }

    void FGame::ShuffleAndPrintDeck()
    {
        Deck.Shuffle();
        Deck.Print();
    }

    void FGame::ShuffleAndPrintTileStack()
    {
        TileStack.Shuffle();
        TileStack.Print();
    }

    const bool FGame::Initialize()
    {
        if (!SelectMap())
        {
            return false;
        }

        if (!GetPlayerCount())
        {
            return false;
        }

        CreatePlayers();

        Superstar = nullptr;
        StatusOfLiberty = nullptr;

        Deck = FDeck("cards.txt");
        TileStack = FTileStack("tiles.txt");

        for (int i = 0; i < NUMBER_OF_TOKEN_TYPE; ++i)
        {
            TokenInventory[i] = STARTING_TOKENS;
        }

        EnergyCubes = MAXIMUM_ENERGY_CUBES;
        return true;
    }

    const bool FGame::SelectMap()
    {
        bool isValid = false;
        std::vector<std::string> MapFiles = GetMapFiles(MAP_PATH);
        if (MapFiles.empty())
        {
            std::cout << std::endl
                      << "Error: No map files have been found."
                      << std::endl;
            return false;
        }
        while (!isValid)
        {
            std::cout << std::endl
                      << "Please choose a map by entering its number (0 to exit):"
                      << std::endl;
            for (int  i = 0; i < MapFiles.size(); ++i)
            {
                std::cout << (i+1)
                          << ". "
                          << MapFiles[i]
                          << std::endl;
            }
            std::cout << ">";
            const int FileNumber = InputSingleDigit();
            if (FileNumber == 0)
            {
                return false;
            }
            else if (1 <= FileNumber && FileNumber <= MapFiles.size())
            {
                Map = new FMap(MAP_PATH + MapFiles[FileNumber - 1]);
                if (Map->IsValid())
                {
                    isValid = true;
                }
                else
                {
                    delete Map;
                    Map = nullptr;
                }
            }
            else
            {
                std::cout << std::endl
                          << "Error: Invalid input."
                          << std::endl;
            }
        }
        return true;
    }

    const bool FGame::GetPlayerCount()
    {
        bool isValid = false;
        while (!isValid)
        {
            std::cout << std::endl
                    << "Enter the number of player ("
                    << MINIMUM_NUMBER_OF_PLAYERS
                    << "-"
                    << MAXIMUM_NUMBER_OF_PLAYERS
                    << " or 0 to exit):"
                    << std::endl
                    << ">";
            const int PlayerCount = InputSingleDigit();
            if (PlayerCount == 0)
            {
                return false;
            }
            else if (MINIMUM_NUMBER_OF_PLAYERS <= PlayerCount &&
                PlayerCount <= MAXIMUM_NUMBER_OF_PLAYERS)
            {
                std::cout << std::endl;
                this->PlayerCount = PlayerCount;
                isValid = true;
            }
            else
            {
                std::cout << "Invalid number of player. It has to be between "
                        << MINIMUM_NUMBER_OF_PLAYERS
                        << " and "
                        << MAXIMUM_NUMBER_OF_PLAYERS
                        << ". Please try again."
                        << std::endl;
            }
        }
        return true;
    }

    void FGame::CreatePlayers()
    {
        assert(MINIMUM_NUMBER_OF_PLAYERS <= PlayerCount &&
               PlayerCount <= MAXIMUM_NUMBER_OF_PLAYERS);
        std::vector<std::string> PlayerNames;
        bool bAvailableMonsters[NUMBER_OF_MONSTERS];
        for (int i = 0; i < NUMBER_OF_MONSTERS; ++i)
        {
            bAvailableMonsters[i] = true;
        }

        for (int i = 0; i < PlayerCount; ++i)
        {
            Players.push_back(
                std::make_shared<FPlayer>(
                    PlayerNames, bAvailableMonsters));
            Players.back()->SelectStartingLocation(*Map);
            Players.back()->PrintLong();
        }
    }
}
