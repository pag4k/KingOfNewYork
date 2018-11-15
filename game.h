// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
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
#include "subject.h"

namespace KingOfNewYork
{
  class FPlayer;

  class FGame: public FSubject
  {
  public:
      FGame();
      std::unique_ptr<FCard> GetCard(int Index);
      std::vector<std::shared_ptr<FPlayer>> &GetPlayers() { return Players; }
      std::vector<std::unique_ptr<FCard>> &GetAvailableCards() { return AvailableCards; }
      std::shared_ptr<FPlayer> GetCurrentPlayer() { assert(CurrentPlayer != -1); return Players[CurrentPlayer]; }
      void Print() const;
      void DistributeCard();
      void ChangeCelebrity(std::shared_ptr<FPlayer> NewCelebrityPlayer);
      void ChangeStatueOfLiberty(std::shared_ptr<FPlayer> NewStatueOfLibertyPlayer);
      void CheckDeadPlayer();
      void CleanDeadPlayer(std::shared_ptr<FPlayer> DeadPlayer);
      void StartMainPhase();
  private:
      const bool InitializationPhase();
      const bool SelectMap();
      const bool DistributeTiles(FTileStack &TileStack);
      const int GetPlayerCount();
      void CreatePlayers(int PlayerCount);
      const bool StartupPhase();
      void GetFirstPlayer();
      void SelectStartingBoroughs();
      void MainPhase();
      std::shared_ptr<FPlayer> VictoriousPlayer();
      bool bIsValid;
      int TokenInventory[TOKEN_TYPE_COUNT];
      int EnergyCubes = -1;
      std::shared_ptr<FMap> Map =  nullptr;
      std::vector<std::shared_ptr<FPlayer>> Players;
      std::vector<std::shared_ptr<FPlayer>> PlayersInCenter;
      std::shared_ptr<FPlayer> Superstar;
      std::shared_ptr<FPlayer> StatusOfLiberty;
      FDeck Deck;
      FDeck DiscardDeck;
      std::vector<std::unique_ptr<FCard>> AvailableCards;
      int CurrentPlayer = -1;
  };
}

#endif
