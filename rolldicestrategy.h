// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef ROLLDICESTRATEGY_H
#define ROLLDICESTRATEGY_H

#include <memory>
#include <vector>
#include "common.h"

namespace KingOfNewYork
{
    class FPlayer;
    class FDiceRoller;

    //Interface for the various roll dice strategies.
    class IRollDiceStrategy
    {
    public:
        virtual void Execute(std::shared_ptr<FDiceRoller> DiceRoller, std::shared_ptr<FPlayer> Player, int DiceCount, int RollCount, std::vector<EDiceFace> &OutDiceResult) = 0;
    };

    class HumanRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        void Execute(std::shared_ptr<FDiceRoller> DiceRoller, std::shared_ptr<FPlayer> Player, int DiceCount, int RollCount, std::vector<EDiceFace> &OutDiceResult) override;
    };

    class AggressiveRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        void Execute(std::shared_ptr<FDiceRoller> DiceRoller, std::shared_ptr<FPlayer> Player, int DiceCount, int RollCount, std::vector<EDiceFace> &OutDiceResult) override;
    };

    class ModerateRollDiceStrategy : public IRollDiceStrategy
    {
    public:
        void Execute(std::shared_ptr<FDiceRoller> DiceRoller, std::shared_ptr<FPlayer> Player, int DiceCount, int RollCount, std::vector<EDiceFace> &OutDiceResult) override;
    };

    namespace
    {
        void PostRolling(std::shared_ptr<FPlayer> Player, std::vector<EDiceFace> &OutDiceResult);
    }

}

#endif
