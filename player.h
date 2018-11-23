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
#include "borough.h"
#include "map.h"
#include "subject.h"

namespace KingOfNewYork
{
    class FGame;
    class FCard;

    //Player class.
    class FPlayer : public FSubject, public std::enable_shared_from_this<FPlayer>
    {
    public:
        explicit FPlayer(EMonsterName MonsterName);

        //Getters and Setters
        const std::string GetMonsterName() const { return GetMonsterNameString(MonsterName); }
        const std::shared_ptr<FBorough> &GetBorough() const { return Borough; }
        const std::shared_ptr<FBorough> &GetMutableBorough() { return Borough; }
        void SetBorough(const std::shared_ptr<FBorough> &Borough) { this->Borough = Borough; }
        const std::vector<std::unique_ptr<FCard>>& GetCards() const { return Cards; }
        const std::vector<int>& GetTokenInventory() const { return TokenInventory; }
        void SetDestroyedBuilding(bool bDestroyerBuilding) { this->bDestroyedBuilding = bDestroyerBuilding; }
        const bool IsVictorious() const { return bVictorious || VictoryPoints >= VICTORY_POINTS_TO_WIN_COUNT; }
        void SetVictorious() { bVictorious = true; }
        const bool IsCelebrity() const { return bCelebrity; }
        void SetCelebrity(const bool bCelebrity);
        const bool IsStatueOfLiberty() const { return bStatueOfLiberty; }
        void SetStatueOfLiberty(const bool bStatueOfLiberty) { this->bStatueOfLiberty = bStatueOfLiberty; }
        const int GetLifePoints() const { return LifePoints; }
        const int GetEnergyCubes() const { return EnergyCubes; }
        const int GetVictoryPoints() const { return VictoryPoints; }
        void SetEnergyCubes(const int EnergyCubes) { this->EnergyCubes = EnergyCubes; }
        const int GetLevelInCenter() const { return LevelInCenter; }
        void SetLevelInCenter(const int LevelInCenter) { this->LevelInCenter = LevelInCenter; }
        const bool IsAlive() const { return bAlive; }

        //Turn methods
        void SetTurnPhase(ETurnPhase NewTurnPhase);
        void TakeDamage(FGame &Game, int Damage);
        void Move(std::shared_ptr<FBorough> OldBorough, int OldLevelInCenter);
        void EarnMonsterResources(EMonsterResource MonsterResource, int Number);
        void ChangeEnergyCubes(int Number);
        void ChangeLifePoints(int Number);
        void ChangeVictoryPoints(int Number);
        void DestroyBuilding(std::unique_ptr<FTileStack> &TileStack);
        void DestroyUnit(std::unique_ptr<FTile> &DestroyedUnit);
        void BuyCard(std::unique_ptr<FCard> Card);
        bool UseCard(int Id);
        void Died(FGame &Game);

    private :

        ETurnPhase  TurnPhase;

        //Player variables
        EMonsterName MonsterName;
        std::shared_ptr<FBorough> Borough;
        int LevelInCenter;
        std::vector<int> TokenInventory;
        std::vector<std::unique_ptr<FCard>> Cards;
        bool bAlive;
        int EnergyCubes;
        int LifePoints;
        int VictoryPoints;
        bool bCelebrity;
        bool bStatueOfLiberty;
        bool bDestroyedBuilding;
        bool bVictorious;
    };
}

#endif
