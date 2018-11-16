// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "common.h"
#include "diceroller.h"
#include "borough.h"
#include "map.h"
#include "rolldicestrategy.h"
#include "resolvedicestrategy.h"
#include "movestrategy.h"
#include "buycardsstrategy.h"
#include "subject.h"

namespace KingOfNewYork
{
    class FGame;
    class FDiceRoller;
    class FCard;

    class FPlayer : public FSubject, public std::enable_shared_from_this<FPlayer>
    {
    public:
        FPlayer(std::vector<std::string> &PlayerNames, bool bAvailableMonsters[]);
        ~FPlayer() override;

        //Getters and Setters
        const std::string GetPlayerName() const { return PlayerName; }
        const EMonsterName GetMonsterName() const { return MonsterName; }
        const std::string GetPlayerAndMonsterNames();
        const std::shared_ptr<FBorough> GetBorough() { return Borough; }
        void SetBorough(const std::shared_ptr<FBorough> &Borough) { this->Borough = Borough; }
        const bool IsVictorious() { return VictoryPoints >= VICTORY_POINTS_TO_WIN_COUNT; }
        const bool IsCelebrity() const { return bCelebrity; }
        void SetCelebrity(const bool bCelebrity) { this->bCelebrity = bCelebrity; }
        const bool IsStatueOfLiberty() const { return bStatueOfLiberty; }
        void SetStatueOfLiberty(const bool bStatueOfLiberty) { this->bStatueOfLiberty = bStatueOfLiberty; }
        const int GetLifePoints() { return LifePoints; }
        const int GetEnergyCubes() { return EnergyCubes; }
        const int GetVictoryPoints() { return VictoryPoints; }
        void SetEnergyCubes(const int EnergyCubes) { this->EnergyCubes = EnergyCubes; }
        const int GetLevelInCenter() { return LevelInCenter; }
        void SetLevelInCenter(const int LevelInCenter) { this->LevelInCenter = LevelInCenter; }
        const bool IsAlive() { return bAlive; }

        //Initialization methods
        void SelectStartingLocation(FMap &Map);

        //Turn methods
        void TakeTurn(FMap &Map, FGame &Game);
        void TakeDamage(FGame &Game, int Damage);
        void Move(FMap &Map, bool bOnlyStartingLocation);
        void EarnMonsterResources(EMonsterResource MonsterResource, int Number);
        void ChangeEnergyCubes(int Number);
        void ChangeLifePoints(int Number);
        void ChangeVictoryPoints(int Number);
        void BuyCard(std::unique_ptr<FCard> Card);
        std::vector<EDiceFace> RollStartDice(int DiceCount);
        void SetTurnResult(std::string Message);

        //Output methods
        void PrintShort() const;
        void PrintLong() const;
    private :
        //Initialization methods
        void EnterPlayerName(std::vector<std::string> &PlayerNames);
        void SelectMonster(bool AvailableMonsters[]);
        void SelectStrategy();

        //Turn methods
        void SetTurnPhase(ETurnPhase NewTurnPhase);
        void StartPhase();
        void RollDicePhase(int DiceCount, int RollCount, std::vector<EDiceFace> &OutDiceResult);
        void ResolveDicePhase(FGame &Game, FMap &Map, std::vector<EDiceFace> &DiceResult);
        void MovePhase(FMap &Map);
        void BuyCardsPhase(FGame &Game);

        //Strategy pointers
        IRollDiceStrategy *RollDiceStrategy = nullptr;
        IResolveDiceStrategy *ResolveDiceStrategy = nullptr;
        IMoveStrategy *MoveStrategy = nullptr;
        IBuyCardsStrategy *BuyCardsStrategy = nullptr;

        //Player variables
        std::string PlayerName;
        EMonsterName MonsterName;
        ETurnPhase  TurnPhase;
        std::shared_ptr<FBorough> Borough;
        int LevelInCenter;
        FDiceRoller DiceRoller;
        int TokenInventory[TOKEN_TYPE_COUNT];
        std::vector<std::unique_ptr<FCard>> Cards;
        bool bAlive;
        int EnergyCubes;
        int LifePoints;
        int VictoryPoints;
        bool bCelebrity;
        bool bStatueOfLiberty;
    };
}

#endif
