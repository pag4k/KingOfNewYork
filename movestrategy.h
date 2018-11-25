// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef MOVESTRATEGY_H
#define MOVESTRATEGY_H

#include <memory>
#include <vector>

namespace KingOfNewYork
{
    class FMap;
    class FBorough;
    class FPlayer;

    //Interface for the various move strategies.
    class IMoveStrategy
    {
    public:
        virtual void Execute(FMap &Map, std::shared_ptr<FPlayer> Player, bool bMovePhase, bool bOnlyStartingLocation) = 0;
    };

    class HumanMoveStrategy : public IMoveStrategy
    {
    public:
        void Execute(FMap &Map, std::shared_ptr<FPlayer> Player, bool bMovePhase, bool bOnlyStartingLocation) override;
    };

    class AggressiveMoveStrategy : public IMoveStrategy
    {
    public:
        void Execute(FMap &Map, std::shared_ptr<FPlayer> Player, bool bMovePhase, bool bOnlyStartingLocation) override;
    };

    class ModerateMoveStrategy : public IMoveStrategy
    {
    public:
        void Execute(FMap &Map, std::shared_ptr<FPlayer> Player, bool bMovePhase, bool bOnlyStartingLocation) override;
    };

    namespace
    {
        std::vector<std::shared_ptr<FBorough>> GetValidBorough(FMap &Map, std::shared_ptr<FPlayer> Player, bool bOnlyStartingLocation);
        void HumanSelectBorough(FMap &Map, std::shared_ptr<FPlayer> Player, bool bOnlyStartingLocation);
        void AISelectBorough(FMap &Map, std::shared_ptr<FPlayer> Player, bool bOnlyStartingLocation, bool bPreferManhattan);
        void MoveTo(std::shared_ptr<FPlayer> Player, std::shared_ptr<FBorough> NewBorough);
        void ForceMoveToCenter(FMap &Map, std::shared_ptr<FPlayer> Player);
        void ForceProgressInCenter(FMap &Map, std::shared_ptr<FPlayer> Player);

    }

}


#endif
