// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <memory>
#include <vector>
#include <optional>
#include "playercontroller.h"
#include "game.h"

namespace KingOfNewYork
{
    class FMap;
    class FPlayer;
    class FTileStack;

    class FGameController
    {
    public:
        FGameController();
        FGame &GetGame() { return *Game; }
        int GetPlayerCount() const;
        std::vector<std::unique_ptr<FPlayerController>> &GetPlayerControllers() { return PlayerControllers; }
        std::unique_ptr<FPlayerController> &GetPlayerController(const std::shared_ptr<FPlayer> &Player);
        void ChangeCelebrity(std::shared_ptr<FPlayer> &NewCelebrityPlayer);
        void ChangeStatueOfLiberty(std::shared_ptr<FPlayer> &NewStatueOfLibertyPlayer);
        const bool IsValid() const { return bIsValid; }

        //Initiatilization
        void StartupPhase();
        void StartMainPhase();
        bool DistributeCard();

    private:
        //Initiatilization
        bool InitializationPhase();
        std::unique_ptr<FMap> SelectMap();
        bool DistributeTiles(FTileStack &TileStack, FMap &Map);
        int PromptPlayerCount();
        void CreatePlayerControllers(int PlayerCount);
        void GetFirstPlayer();
        void SelectStartingBoroughs();

        void MainPhase();
        std::optional<std::shared_ptr<FPlayer>> CheckVictoriousPlayer();

        std::shared_ptr<FGame> Game;
        std::vector<std::unique_ptr<FPlayerController>> PlayerControllers;
        int CurrentPlayer;
        bool bIsValid;


    };
}

#endif
