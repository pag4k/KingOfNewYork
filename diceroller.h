// ----------------------------------------------------------------------------
// COMP345 Assignment 2
// Due date: November 4, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <vector>
#include <string>
#include "common.h"

namespace KingOfNewYork
{
    struct FDiceResult;

    class FDiceRoller {
    public :
        FDiceRoller();
        const std::vector<EDiceFace> BeginRolling(const int DiceCount, const int RollCount) const;
    private :
        const EDiceFace RollDice(const int FaceNumber) const;
        mutable int RollHistory[FACE_ON_DICE_COUNT];
    };
}
