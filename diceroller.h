// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
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
        ~FDiceRoller(){};
        const std::vector<EDiceFace> BeginRolling() const
            { return BeginRolling(BLACK_DICE_COUNT, MAXIMUM_ROLL); }
        const std::vector<EDiceFace> BeginRolling(const int DiceCount, const int RollCount) const;
        void PrintRollHistory() const;
    private :
        const EDiceFace RollDice(const int FaceNumber) const;
        mutable int RollHistory[FACE_ON_DICE_COUNT];
    };
}
