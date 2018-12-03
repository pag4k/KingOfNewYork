// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------


#ifndef BUYCARDSSTRATEGY_H
#define BUYCARDSSTRATEGY_H

#include "precompiledheader.h"

namespace KingOfNewYork
{
    class FGameController;
    class FGame;
    class FPlayer;

    //Interface for the various buy cards strategies.
    class IBuyCardsStrategy
    {
    public:
        virtual void Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player) = 0;
    };

    class HumanBuyCardsStrategy : public IBuyCardsStrategy
    {
    public:
        void Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player) override;
    };

    class AggressiveBuyCardsStrategy : public IBuyCardsStrategy
    {
    public:
        void Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player) override;
    };

    class ModerateBuyCardsStrategy : public IBuyCardsStrategy
    {
    public:
        void Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player) override;
    };

    namespace
    {
        void BuyCardsAI(FGameController &GameController, std::shared_ptr<FPlayer> &Player);
    }

}


#endif
