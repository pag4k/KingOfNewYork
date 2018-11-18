// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef ROLLDICESTRATEGY_H
#define ROLLDICESTRATEGY_H

#include "diceroller.h"

namespace KingOfNewYork
{
    //Interface for the various roll dice strategies.
    class IRollDiceStrategy

    {
    public:
        virtual void Execute(FDiceRoller &DiceRoller, int DiceCount, int RollCount, std::vector<EDiceFace> &OutDiceResult) = 0;
    };

    class HumanRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        void Execute(FDiceRoller &DiceRoller, int DiceCount, int RollCount, std::vector<EDiceFace> &OutDiceResult) override;
    };

    class AggressiveRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        void Execute(FDiceRoller &DiceRoller, int DiceCount, int RollCount, std::vector<EDiceFace> &OutDiceResult) override;
    };

    class ModerateRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        void Execute(FDiceRoller &DiceRoller, int DiceCount, int RollCount, std::vector<EDiceFace> &OutDiceResult) override;
    };

}

#endif
