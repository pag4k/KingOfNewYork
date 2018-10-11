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
            { return BeginRolling(NUMBER_OF_DICE); }
        const std::vector<EDiceFace> BeginRolling(const int DiceNumber) const;
        void PrintRollHistory() const;
    private :
        const EDiceFace RollDice(const int FaceNumber) const;
        int MaximumRollCount;
        mutable int RollHistory[NUMBER_OF_FACES_ON_DICE];
    };
}
