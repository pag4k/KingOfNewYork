// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <memory>
#include <vector>
#include "unordered_set"
#include <string>

#include "playercontroller.h"
#include "player.h"
#include "common.h"

namespace KingOfNewYork
{
    class FGame;
    class FMap;
    class FDiceRoller;
    class IRollDiceStrategy;
    class IResolveDiceStrategy;
    class IMoveStrategy;
    class IBuyCardsStrategy;

    class FPlayerController
    {

    public:
        FPlayerController(std::unordered_set<std::string> &PlayerNames, std::vector<bool> &AvailableMonsters);
        ~FPlayerController();

        //Getters and setters
        const std::string &GetName() const { return Name; }
        const std::string GetMonsterName() const { return Player->GetMonsterName(); }
        std::shared_ptr<FPlayer> &GetPlayer() { return Player; }
        std::shared_ptr<FDiceRoller> &GetDiceRoller() { return DiceRoller; }
        void RemovePlayer() { Player = nullptr; }

        //Turn methods
        void TakeTurn(FMap &Map, FGame &Game);
        std::vector<EDiceFace> RollStartDice(int DiceCount);
        void Move(FMap &Map, bool bMovePhase, bool bOnlyStartingLocation);

        //Initialization methods
        void SelectStartingLocation(FMap &Map);

    private:
        //Initialization methods
        std::string EnterPlayerName(std::unordered_set<std::string> &PlayerNames);
        EMonsterName SelectMonster(std::vector<bool> &AvailableMonsters);
        void SelectStrategy();

        //Turn methods
        void StartPhase();
        void RollDicePhase(int DiceCount, int RollCount, std::vector<EDiceFace> &OutDiceResult);
        void ResolveDicePhase(FGame &Game, FMap &Map, std::vector<EDiceFace> &DiceResult);
        void MovePhase(FMap &Map);
        void BuyCardsPhase(FGame &Game);

        std::string Name;
        std::shared_ptr<FPlayer> Player;
        std::shared_ptr<FDiceRoller> DiceRoller;

        //Strategy pointers
        IRollDiceStrategy *RollDiceStrategy = nullptr;
        IResolveDiceStrategy *ResolveDiceStrategy = nullptr;
        IMoveStrategy *MoveStrategy = nullptr;
        IBuyCardsStrategy *BuyCardsStrategy = nullptr;
    };
}
#endif
