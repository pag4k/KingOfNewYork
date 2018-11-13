
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
        virtual void Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player) = 0;
    };

    class HumanResolveDiceStrategy : public IResolveDiceStrategy
    {
    public:
        void Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player);
    };

    class AggressiveResolveDiceStrategy : public IResolveDiceStrategy
    {
    public:
        void Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player);
    };

    class ModerateResolveDiceStrategy : public IResolveDiceStrategy
    {
    public:
        void Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player);
    };

    namespace
    {
        const bool ResolveAttack(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool ResolveCelebrity(FGame &Game, std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool ResolveDestruction(std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool ResolveEnergy(std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool ResolveHeal(std::shared_ptr<FPlayer> Player, const int NumberOfDice);
        const bool ResolveOuch(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, const int NumberOfDice);
    }

}

#endif