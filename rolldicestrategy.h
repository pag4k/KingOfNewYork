#ifndef ROLLDICESTRATEGY_H
#define ROLLDICESTRATEGY_H

#include "diceroller.h"

namespace KingOfNewYork
{
    class IRollDiceStrategy
    {
    public:
        virtual std::vector<EDiceFace> Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount) = 0;
      //virtual void ResolveDice() = 0;
      //virtual void Move() = 0;
      //virtual void BuyCards() = 0;
    };

    class HumanRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        std::vector<EDiceFace> Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount);
    };

    class AggressiveRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        std::vector<EDiceFace> Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount);
    };

    class ModerateRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        std::vector<EDiceFace> Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount);
    };

}

#endif
