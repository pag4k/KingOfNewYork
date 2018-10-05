#include <assert.h>
#include <iostream>
#include "game.h"
#include "player.h"

FGame::FGame(int NumberOfPlayer)
{
    Graph = FGraph("newyork.map");

    std::vector<std::string> PlayerNames;
    bool bAvailableMonsters[NUMBER_OF_MONSTERS];
    for (int i = 0; i < NUMBER_OF_MONSTERS; ++i)
    {
        bAvailableMonsters[i] = true;
    }

    assert(MINIMUM_NUMBER_OF_PLAYERS <= NumberOfPlayer &&
           NumberOfPlayer <= MAXIMUM_NUMBER_OF_PLAYERS);
    this->Number_of_Players = NumberOfPlayer;

    for (int i = 0; i < NumberOfPlayer; ++i)
    {
        Players.push_back(new FPlayer(&PlayerNames, bAvailableMonsters, Graph.Vertices()));
    }

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

FGame::~FGame()
{
    for (FPlayer *Player : Players)
    {
        delete Player;
    }
    Players.clear();
    Superstar = nullptr;
    StatusOfLiberty = nullptr;
}

void FGame::Print()
{
    std::cout << "Number of players: " << Number_of_Players << std::endl;
    for (FPlayer *Player: Players)
    {
        std::cout << "\t-";
        Player->PrintShort();
    }
    
    std::cout << "Monster in Manhattam:";
    if (PlayersInManhattan.empty())
    {
        std::cout << "No one." << std::endl;
    }
    else
    {
        for (FPlayer *Player : Players)
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
    std::cout << "Number of tiles in tile stack: " << TileStack.Size() << std::endl;

    std::cout << "Tokens left:" << std::endl;
    for (int i = 0; i < NUMBER_OF_TOKEN_TYPE; ++i)
    {
        std::cout   << "\t-"
                    << GetTokenTypeString(ETokenType(i))
                    << ": "
                    << TokenInventory[i]
                    << std::endl;
    }

    std::cout   << "Energy cubes left:"
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