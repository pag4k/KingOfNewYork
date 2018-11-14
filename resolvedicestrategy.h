// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef RESOLVEDICESTRATEGY_H
#define RESOLVEDICESTRATEGY_H

#include <vector>
#include <memory>
#include "common.h"


namespace KingOfNewYork
{

    class FGame;
    class FMap;
    class FPlayer;

    class IResolveDiceStrategy
    {
    public:
        virtual void Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, std::vector<EDiceFace> &DiceResult) = 0;
    };

    class HumanResolveDiceStrategy : public IResolveDiceStrategy
    {
    public:
        void Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, std::vector<EDiceFace> &DiceResult);
    };

    class AggressiveResolveDiceStrategy : public IResolveDiceStrategy
    {
    public:
        void Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, std::vector<EDiceFace> &DiceResult);
    };

    class ModerateResolveDiceStrategy : public IResolveDiceStrategy
    {
    public:
        void Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, std::vector<EDiceFace> &DiceResult);
    };

    namespace
    {
        std::vector<int> GetDiceSums(std::vector<EDiceFace> &DiceResult);
        const bool ResolveAttack(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool ResolveCelebrity(FGame &Game, std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool HumanResolveDestruction(std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool AIResolveDestruction(std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool ResolveEnergy(std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool ResolveHeal(std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool ResolveOuch(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, const int NumberOfDice);
    }

}

#endif