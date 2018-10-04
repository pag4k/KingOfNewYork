#include <assert.h>
#include <iostream>
#include "game.h"
#include "player.h"

FGame::FGame(int NumberOfPlayer)
{
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
        Players.push_back(new FPlayer(&PlayerNames, bAvailableMonsters));
    }

    Deck = FDeck("cards.txt");
    TileStack = FTileStack("tiles.txt");

    Superstar = nullptr;
    StatusOfLiberty = nullptr;

    for (int i = 0; i < NUMBER_OF_TOKEN_TYPE; ++i)
    {
        TokenInventory[i] = STARTING_TOKENS;
    }
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