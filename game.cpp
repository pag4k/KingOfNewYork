#include <assert.h>
#include "game.h"
#include "player.h"
#include "tile.h"
#include "card.h"

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

    Deck = new FDeck();
    TileStack = new FTileStack();

    Superstar = nullptr;
    StatusOfLiberty = nullptr;

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
    delete Deck;
    Deck = nullptr;
    delete TileStack;
    TileStack = nullptr;
}