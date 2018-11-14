//
// Created by oscar on 13/11/18.
//

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