// ----------------------------------------------------------------------------
// COMP345 Assignment 2
// Due date: November 4, 2018
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

namespace KingOfNewYork
{
    class FGame;
    class FDiceRoller;
    class FCard;

    class FPlayer : public std::enable_shared_from_this<FPlayer>
    {
    public:
        FPlayer(
            std::vector<std::string> &PlayerNames,
            bool bAvailableMonsters[]);
        void SelectStartingLocation(FMap &Map);
        const std::string GetPlayerName() const { return PlayerName; }
        const EMonsterName GetMonsterName() const { return MonsterName; }
        const std::string GetPlayerAndMonsterNames();
        const std::shared_ptr<FBorough> GetBorough() { return Borough; }
        void RollDice(const int DiceCount, const int RollCount);
        void TakeTurn(FMap &Map, FGame &Game);
        const bool IsVictorious() { return VictoryPoints >= VICTORY_POINTS_TO_WIN_COUNT; }
        const bool GetCelebrity() const { return bCelebrity; }
        void SetCelebrity(const bool bCelebrity);
        const bool GetStatueOfLiberty() const { return bStatueOfLiberty; }
        void SetStatueOfLiberty(const bool bStatueOfLiberty);
        const int GetAttackCount() const;
        void PrintShort() const;
        void PrintLong() const;
        const bool IsAlive() { return bAlive; }
    private :
        void EnterPlayerName(std::vector<std::string> &PlayerNames);
        void SelectMonster(bool AvailableMonsters[]);
        void SelectBorough(FMap &Map, const bool bOnlyStartingLocation, const bool bIncludeCenter);
        void ResolveDice(FGame &Game, FMap &Map);
        const bool ResolveAttack(FGame &Game, FMap &Map, const int NumberOfDice);
        const bool ResolveCelebrity(FGame &Game, const int NumberOfDice);
        const bool ResolveDestruction(const int NumberOfDice);
        const bool ResolveEnergy(const int NumberOfDice);
        const bool ResolveHeal(const int NumberOfDice);
        const bool ResolveOuch(FGame &Game, FMap &Map, const int NumberOfDice);
        void Move(FMap &Map);
        void MoveTo(std::shared_ptr<FBorough> NewBorough);
        void BuyCards(FGame &Game);
        void TakeDamage(FGame &Game, const int Damage);
        const std::string EarnMonsterResources(const EMonsterResource MonsterResource, const int Number);
        const std::string EarnEnergyCubes(const int Number);
        const std::string EarnLifePoints(const int Number);
        const std::string EarnVictoryPoints(const int Number);
        std::string PlayerName;
        EMonsterName MonsterName;
        std::shared_ptr<FBorough> Borough;
        int LevelInCenter;
        FDiceRoller DiceRoller;
        std::vector<EDiceFace> CurrentDiceResult;
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
