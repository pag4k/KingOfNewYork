//
// Created by oscar on 13/11/18.
//

#ifndef MOVESTRATEGY_H
#define MOVESTRATEGY_H

#include <memory>

namespace KingOfNewYork
{

    //class FGame;
    class FMap;
    class FPlayer;

    class IMoveStrategy
    {
    public:
        virtual void Execute(FMap &Map, std::shared_ptr<FPlayer> Player) = 0;
    };

    class HumanMoveStrategy : public IMoveStrategy
    {
    public:
        void Execute(FMap &Map, std::shared_ptr<FPlayer> Player);
    };

    class AggressiveMoveStrategy : public IMoveStrategy
    {
    public:
        void Execute(FMap &Map, std::shared_ptr<FPlayer> Player);
    };

    class ModerateMoveStrategy : public IMoveStrategy
    {
    public:
        void Execute(FMap &Map, std::shared_ptr<FPlayer> Player);
    };

}


#endif
