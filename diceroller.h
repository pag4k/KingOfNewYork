// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef DICEROLLER_H
#define DICEROLLER_H

#include "precompiledheader.h"
#include "subject.h"
#include "common.h"

namespace KingOfNewYork
{
    //A class that handles the dice rolling for the FPlayer class.
    class FDiceRoller : public FSubject, public std::enable_shared_from_this<FDiceRoller>
    {
    public :
        explicit FDiceRoller(int FACE_ON_DICE_COUNT);
        std::vector<EDiceFace> BeginRolling(int DiceCount) const;
        void RollDice(int DiceCount, std::vector<EDiceFace> &OutDiceResult);
    private :
        const EDiceFace RollSingleDice();
        mutable std::vector<int> RollHistory;
        std::mt19937 MersenneTwisterEngine;
        std::uniform_int_distribution<> UniformeDistribution;
    };
}

#endif
