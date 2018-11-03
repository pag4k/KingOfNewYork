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
        ~FGame();
        const bool IsValid() const { return bIsValid; }
        void Print() const;
        void ShuffleAndPrintDeck();
    private:
        const bool InitializationPhase();
        const bool SelectMap();
        const bool DistributeTiles(FTileStack &TileStack);
        const bool GetPlayerCount();
        void CreatePlayers();
        const bool StartupPhase();
        void GetFirstPlayer();
        void SelectStartingBoroughs();
        void MainPhase();
        const int VictoriousPlayer();
        bool bIsValid;
        int TokenInventory[TOKEN_TYPE_COUNT];
        int EnergyCubes = -1;
        int PlayerCount = -1;
        std::shared_ptr<FMap> Map =  nullptr;
        std::vector<std::shared_ptr<FPlayer>> Players;
        std::vector<std::shared_ptr<FPlayer>> PlayersInManhattan;
        std::shared_ptr<FPlayer> Superstar;
        std::shared_ptr<FPlayer> StatusOfLiberty;
        FDeck Deck;
        FDeck DiscardDeck;
        
        //TODO: ADD CARD BUYING CODE.
        std::unique_ptr<FCard> AvailableCards[MAXIMUM_AVAILABLE_CARDS];
        int CurrentPlayer = -1;
  };
}

#endif
