// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
#include "common.h"
#include "map.h"
#include "card.h"
#include "tile.h"
#include "borough.h"

namespace KingOfNewYork
{
  class FPlayer;

  class FGame
  {
  public:
        FGame();
        FGame(const int NumberOfPlayers);
        ~FGame();
        const bool IsValid() const { return bIsValid; }
        void Print() const;
        void ShuffleAndPrintDeck();
        void ShuffleAndPrintTileStack();
    private:
        const bool LoadGameData();
        void AddPlayers(const int NumberOfPlayers);
        bool bIsValid;
        int TokenInventory[NUMBER_OF_TOKEN_TYPE];
        int EnergyCubes = 0;
        int NumberOfPlayers = 0;
        FMap *Map =  nullptr;
        std::vector<std::shared_ptr<FPlayer>> Players;
        std::vector<std::shared_ptr<FPlayer>> PlayersInManhattan;
        std::shared_ptr<FPlayer> Superstar;
        std::shared_ptr<FPlayer> StatusOfLiberty;
        FDeck Deck;
        FDeck DiscardDeck;
        FTileStack TileStack;
        //TODO: ADD CARD BUYING CODE.
        std::unique_ptr<FCard> AvailableCards[MAXIMUM_AVAILABLE_CARDS];
  };
}

#endif
