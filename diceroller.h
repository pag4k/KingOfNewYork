// ----------------------------------------------------------------------------
// COMP345 Assignment 2
// Due date: November 4, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef DICEROLLER_H
#define DICEROLLER_H

#include <vector>
#include <string>
#include "common.h"

namespace KingOfNewYork
{
    struct FDiceResult;

    class FDiceRoller {
    public :
        FDiceRoller();
        std::vector<EDiceFace> BeginRolling(const int DiceCount) const;
        void RollDice(const int DiceCount, std::vector<EDiceFace> &OutDiceResult) const;
    private :
        const EDiceFace RollSingleDice(const int FaceNumber) const;
        mutable int RollHistory[FACE_ON_DICE_COUNT];
    };
}

#endif
