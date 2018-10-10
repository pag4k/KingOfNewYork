// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "common.h"
#include <memory>

#include "map.h"
#include "card.h"
#include "tile.h"
#include <borough.h>

namespace KingOfNewYork
{
  class FPlayer;

  class FGame
  {
  public:
      FGame();
      FGame(const int NumberOfPlayers);
      ~FGame();
    
      void Print() const;
      void ShuffleAndPrintDeck();
      void ShuffleAndPrintTileStack();

    private:
      void LoadGameData();
      void AddPlayers(const int NumberOfPlayers);
      FMap *Map =  nullptr;
      int NumberOfPlayers;
      std::vector<std::shared_ptr<FPlayer>> Players;
      std::vector<std::shared_ptr<FPlayer>> PlayersInManhattan;
      std::shared_ptr<FPlayer> Superstar;
      std::shared_ptr<FPlayer> StatusOfLiberty;
      FDeck Deck;
      FDeck DiscardDeck;
      FTileStack TileStack;
      int TokenInventory[NUMBER_OF_TOKEN_TYPE];
      int EnergyCubes;

      //TODO: ADD CARD BUYING CODE.
      std::unique_ptr<FCard> AvailableCards[MAXIMUM_AVAILABLE_CARDS];
  };
}

#endif
