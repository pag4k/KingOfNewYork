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
#include "playercontroller.h"
#include "common.h"
#include "map.h"
#include "card.h"
#include "tile.h"
#include "borough.h"
#include "subject.h"

namespace KingOfNewYork
{
    class FPlayerController;

    //The main class of the game that handles its basic functions.
    class FGame: public FSubject, public std::enable_shared_from_this<FGame>
    {
    public:
        FGame();
        std::unique_ptr<FCard> GetCard(int Index);
        std::vector<std::unique_ptr<FPlayerController>> &GetPlayerControllers() { return PlayerControllers; }
        std::unique_ptr<FPlayerController> &GetPlayerController(const std::shared_ptr<FPlayer> &Player);
        std::vector<std::unique_ptr<FCard>> &GetAvailableCards() { return AvailableCards; }
        std::shared_ptr<FMap> &GetMap() { return Map; }
        int GetPlayerCount() const;
        FDeck &GetDeck() { return Deck; }
        FDeck &GetDiscardDeck() { return DiscardDeck; }
        bool DistributeCard();
        void ChangeCelebrity(std::shared_ptr<FPlayer> &NewCelebrityPlayer);
        void ChangeStatueOfLiberty(std::shared_ptr<FPlayer> &NewStatueOfLibertyPlayer);
        void CheckDeadPlayer();
        void CleanDeadPlayer(std::shared_ptr<FPlayer> &DeadPlayer);
        void StartupPhase();
        void StartMainPhase();
    private:
        bool InitializationPhase();
        bool SelectMap();
        bool DistributeTiles(FTileStack &TileStack);
        int PromptPlayerCount();
        void CreatePlayerControllers(int PlayerCount);
        void GetFirstPlayer();
        void SelectStartingBoroughs();
        void MainPhase();
        std::optional<std::shared_ptr<FPlayer>> VictoriousPlayer();
        int TokenInventory[TOKEN_TYPE_COUNT];
        int EnergyCubes = -1;
        std::shared_ptr<FMap> Map =  nullptr;
        std::vector<std::unique_ptr<FPlayerController>> PlayerControllers;
        FDeck Deck;
        FDeck DiscardDeck;
        std::vector<std::unique_ptr<FCard>> AvailableCards;
        int CurrentPlayer = -1;
    };
}

#endif
