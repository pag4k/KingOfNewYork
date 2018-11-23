// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef DICEROLLER_H
#define DICEROLLER_H

#include <memory>
#include <vector>
#include <string>
#include "subject.h"
#include "common.h"

namespace KingOfNewYork
{
    //A class that handles the dice rolling for the FPlayer class.
    class FDiceRoller : public FSubject, public std::enable_shared_from_this<FDiceRoller>
    {
    public :
        FDiceRoller();
        std::vector<EDiceFace> BeginRolling(int DiceCount) const;
        void RollDice(int DiceCount, std::vector<EDiceFace> &OutDiceResult) const;
    private :
        const EDiceFace RollSingleDice(int FaceNumber) const;
        mutable std::vector<int> RollHistory;
    };
}

#endif
