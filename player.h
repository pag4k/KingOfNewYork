// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "common.h"
#include "diceroller.h"
#include "borough.h"
#include "map.h"

namespace KingOfNewYork
{
    class FDiceRoller;
    class FCard;

    class FPlayer : public std::enable_shared_from_this<FPlayer>
    {
    public:
    FPlayer(std::vector<std::string> &PlayerNames, bool bAvailableMonsters[]);
    ~FPlayer();

    void SelectStartingLocation(FMap &Map);

    const std::string GetPlayerName() const { return PlayerName; }
    const EMonsterName GetMonsterName() const { return MonsterName; }
    const bool GetCelebrity() const { return bCelebrity; }
    void SetCelebrity(const bool bCelebrity) { this->bCelebrity = bCelebrity; }

    void RollDice();
    void ResolveDice();
    void Move();
    void BuyCards();

    void PrintShort() const;
    void PrintLong() const;

    private :
        void EnterPlayerName(std::vector<std::string> &PlayerNames);
        void SelectMonster(bool AvailableMonsters[]);
        const bool ResolveAttack(const int NumberOfDice);
        const bool ResolveCelebrity(const int NumberOfDice);
        const bool ResolveDestruction(const int NumberOfDice);
        const bool ResolveEnergy(const int NumberOfDice);
        const bool ResolveHeal(const int NumberOfDice);
        const bool ResolveOuch(const int NumberOfDice);

        std::string PlayerName;
        EMonsterName MonsterName;
        std::shared_ptr<FBorough> Position;
        FDiceRoller DiceRoller;
        std::vector<EDiceFace> CurrentDiceResult;
        int TokenInventory[NUMBER_OF_TOKEN_TYPE];
        std::vector<std::unique_ptr<FCard>> Cards;
        int EnergyCubes;
        int LifePoints;
        int VictoryPoints;

        bool bCelebrity;
        bool bStatueOfLiberty;

        //TODO: ADD CARD BUYING CODE.
    };
}

#endif
