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
#include "rolldicestrategy.h"
#include "resolvedicestrategy.h"
#include "movestrategy.h"
#include "buycardsstrategy.h"

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
        ~FPlayer();

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
        const int GetEnergyCubes() { return EnergyCubes; }
        void SetEnergyCubes(const int EnergyCubes) { this->EnergyCubes = EnergyCubes; }
        const int GetLevelInCenter() { return LevelInCenter; }
        void SetLevelInCenter(const int LevelInCenter) { this->LevelInCenter = LevelInCenter; }
        const bool IsAlive() { return bAlive; }

        //Initialization methods
        void SelectStartingLocation(FMap &Map);

        //Turn methods
        void TakeTurn(FMap &Map, FGame &Game);
        void TakeDamage(FGame &Game, const int Damage);
        void Move(FMap &Map, bool bOnlyStartingLocation);
        const std::string EarnMonsterResources(const EMonsterResource MonsterResource, const int Number);
        const std::string EarnEnergyCubes(const int Number);
        const std::string EarnLifePoints(const int Number);
        const std::string EarnVictoryPoints(const int Number);
        void BuyCard(std::unique_ptr<FCard> Card);
        std::vector<EDiceFace> RollStartDice(const int DiceCount);

        //Output methods
        void PrintShort() const;
        void PrintLong() const;
    private :
        //Initialization methods
        void EnterPlayerName(std::vector<std::string> &PlayerNames);
        void SelectMonster(bool AvailableMonsters[]);

        //Turn methods
        void RollDicePhase(const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult);
        void ResolveDicePhase(FGame &Game, FMap &Map, std::vector<EDiceFace> &DiceResult);
        void MovePhase(FMap &Map);
        void BuyCardsPhase(FGame &Game);

        //Strategy pointers
        IRollDiceStrategy *RollDiceStrategy;
        IResolveDiceStrategy *ResolveDiceStrategy;
        IMoveStrategy *MoveStrategy;
        IBuyCardsStrategy *BuyCardsStrategy;

        //Player variables
        std::string PlayerName;
        EMonsterName MonsterName;
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
