// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <assert.h>
#include <iostream>

#include "game.h"
#include "player.h"

namespace KingOfNewYork
{
    FGame::FGame()
    {
        LoadGameData();
    }

    FGame::FGame(const int NumberOfPlayers)
    {
        LoadGameData();
        AddPlayers(NumberOfPlayers);
    }

    FGame::~FGame()
    {
        delete Map;
        Players.clear();
        Superstar = nullptr;
        StatusOfLiberty = nullptr;
    }

    void FGame::Print() const
    {
        std::cout << "Number of players: " << NumberOfPlayers << std::endl;
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
        std::cout << "Number of cards in discard deck: " << DiscardDeck.Size() << std::endl;

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

    void FGame::LoadGameData()
    {
        Map = new FMap("newyork.map");

        Superstar = nullptr;
        StatusOfLiberty = nullptr;

        Deck = FDeck("cards.txt");
        TileStack = FTileStack("tiles.txt");

        for (int i = 0; i < NUMBER_OF_TOKEN_TYPE; ++i)
        {
            TokenInventory[i] = STARTING_TOKENS;
        }

        EnergyCubes = MAXIMUM_ENERGY_CUBES;
    }

    void FGame::AddPlayers(const int NumberOfPlayers)
    {
        assert(MINIMUM_NUMBER_OF_PLAYERS <= NumberOfPlayers &&
               NumberOfPlayers <= MAXIMUM_NUMBER_OF_PLAYERS);
        this->NumberOfPlayers = NumberOfPlayers;

        std::vector<std::string> PlayerNames;
        bool bAvailableMonsters[NUMBER_OF_MONSTERS];
        for (int i = 0; i < NUMBER_OF_MONSTERS; ++i)
        {
            bAvailableMonsters[i] = true;
        }

        for (int i = 0; i < NumberOfPlayers; ++i)
        {
            Players.push_back(std::make_shared<FPlayer>(PlayerNames, bAvailableMonsters));
            Players.back()->SelectStartingLocation(*Map);
            Players.back()->PrintLong();
        }
    }
}
