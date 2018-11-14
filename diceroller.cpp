// ----------------------------------------------------------------------------
// COMP345 Assignment 2
// Due date: November 4, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include <cassert>
#include <ctime>

#include "diceroller.h"

namespace KingOfNewYork
{
    FDiceRoller::FDiceRoller()
    {
        //Use current time as seed for the random generator.
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        for (int &Face : RollHistory)
        {
            Face = 0;
        }
    }

    std::vector<EDiceFace> FDiceRoller::BeginRolling(const int DiceCount) const
    {
        assert(0 <= DiceCount && DiceCount <= BLACK_DICE_COUNT + GREEN_DICE_COUNT);

        std::vector<EDiceFace> DiceResult;
        for (int i = 0; i < DiceCount; i++)
        {
            DiceResult.push_back(EDiceFace::None);
        }

        return DiceResult;
    }

    void FDiceRoller::RollDice(const int DiceCount, std::vector<EDiceFace> &OutDiceResult) const
    {
        for (int i = 0; i < DiceCount; i++)
        {
            bool NewRoll = false;
            if (OutDiceResult[i] == EDiceFace::None)
            {
                NewRoll = true;
                OutDiceResult[i] = RollSingleDice(FACE_ON_DICE_COUNT);
            }
            std::cout << (i + 1)
                      << ": "
                      << GetDiceFaceString(OutDiceResult[i])
                      << (NewRoll ? " (new roll)" : "")
                      << std::endl;
        }
    }

    const EDiceFace FDiceRoller::RollSingleDice(const int FaceNumber) const
    {
        assert(1 <= FaceNumber && FaceNumber <= FACE_ON_DICE_COUNT);
        int Roll = std::rand() / ((RAND_MAX + 1u) / FaceNumber);
        assert(0 <= Roll && Roll <= FaceNumber - 1);
        RollHistory[Roll]++;
        return EDiceFace(Roll);
    }
}
