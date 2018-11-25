// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
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
        RollHistory = std::vector<int>(FACE_ON_DICE_COUNT, 0);
    }

    std::vector<EDiceFace> FDiceRoller::BeginRolling(const int DiceCount) const
    {
        assert(0 <= DiceCount && DiceCount <= BLACK_DICE_COUNT + GREEN_DICE_COUNT);
        std::vector<EDiceFace> DiceResult(DiceCount, EDiceFace::None);
        return DiceResult;
    }

    void FDiceRoller::RollDice(const int DiceCount, std::vector<EDiceFace> &OutDiceResult) const
    {
        std::vector<bool> NewRoll;
        for (int i = 0; i < DiceCount; i++)
        {
            if (OutDiceResult[i] == EDiceFace::None)
            {
                NewRoll.push_back(true);
                OutDiceResult[i] = RollSingleDice(FACE_ON_DICE_COUNT);
            }
            else
            {
                NewRoll.push_back(false);
            }
        }
        Notify(shared_from_this(), std::make_shared<FRolledDiceEvent>(EObserverEvent::RolledDice, "", OutDiceResult, NewRoll));
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
