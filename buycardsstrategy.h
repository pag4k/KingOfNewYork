// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------


#ifndef BUYCARDSSTRATEGY_H
#define BUYCARDSSTRATEGY_H

#include <memory>

namespace KingOfNewYork
{

    class FGame;
    //class FMap;
    class FPlayer;

    class IBuyCardsStrategy
    {
    public:
        virtual void Execute(FGame &Game, std::shared_ptr<FPlayer> Player) = 0;
    };

    class HumanBuyCardsStrategy : public IBuyCardsStrategy
    {
    public:
        void Execute(FGame &Game, std::shared_ptr<FPlayer> Player);
    };

    class AggressiveBuyCardsStrategy : public IBuyCardsStrategy
    {
    public:
        void Execute(FGame &Game, std::shared_ptr<FPlayer> Player);
    };

    class ModerateBuyCardsStrategy : public IBuyCardsStrategy
    {
    public:
        void Execute(FGame &Game, std::shared_ptr<FPlayer> Player);
    };

}


#endif
