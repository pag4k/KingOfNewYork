// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef RESOLVEDICESTRATEGY_H
#define RESOLVEDICESTRATEGY_H

#include "precompiledheader.h"
#include "common.h"

namespace KingOfNewYork
{
    class FGameController;
    class FGame;
    class FMap;
    class FPlayer;
    class FBorough;

    //Interface for the various resolve dice strategies.
    class IResolveDiceStrategy
    {
    public:
        virtual void Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player, std::vector<EDiceFace> &DiceResult) = 0;
    };

    class HumanResolveDiceStrategy : public IResolveDiceStrategy
    {
    public:
        void Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player, std::vector<EDiceFace> &DiceResult) override;
    };

    class AggressiveResolveDiceStrategy : public IResolveDiceStrategy
    {
    public:
        void Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player, std::vector<EDiceFace> &DiceResult) override;
    };

    class ModerateResolveDiceStrategy : public IResolveDiceStrategy
    {
    public:
        void Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player, std::vector<EDiceFace> &DiceResult) override;
    };

    namespace
    {
        std::vector<int> GetDiceSums(std::vector<EDiceFace> &DiceResult);
        bool ResolveAttack(FGameController &GameController, std::shared_ptr<FPlayer> &Player, int NumberOfDice);
        bool ResolveCelebrity(FGameController &GameController, std::shared_ptr<FPlayer> &Player, int NumberOfDice);
        int GetMinimumDurability(const std::shared_ptr<FBorough> &Borough);
        bool HumanResolveDestruction(std::shared_ptr<FPlayer> &Player, int NumberOfDice);
        bool AIResolveDestruction(std::shared_ptr<FPlayer> &Player, int NumberOfDice, bool bPrioritizeUnit);
        bool ResolveEnergy(std::shared_ptr<FPlayer> &Player, int NumberOfDice);
        bool ResolveHeal(std::shared_ptr<FPlayer> &Player, int NumberOfDice);
        bool ResolveOuch(FGameController &GameController, std::shared_ptr<FPlayer> &Player, int NumberOfDice);
    }

}

#endif