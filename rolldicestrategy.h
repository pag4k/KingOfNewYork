#ifndef ROLLDICESTRATEGY_H
#define ROLLDICESTRATEGY_H

#include "diceroller.h"

namespace KingOfNewYork
{
    class IRollDiceStrategy

    {
    public:
        virtual void Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult) = 0;
    };

    class HumanRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        void Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult);
    };

    class AggressiveRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        void Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult);
    };

    class ModerateRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        void Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult);
    };

}

#endif
