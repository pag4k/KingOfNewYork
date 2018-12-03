// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "diceroller.h"

namespace KingOfNewYork
{
    FDiceRoller::FDiceRoller(int FaceNumber) :
            MersenneTwisterEngine(std::mt19937(std::random_device()())),
            UniformeDistribution(std::uniform_int_distribution(0, FaceNumber-1))
    {
        RollHistory = std::vector<int>(FaceNumber, 0);
    }

    std::vector<EDiceFace> FDiceRoller::BeginRolling(int DiceCount) const
    {
        assert(0 <= DiceCount && DiceCount <= BLACK_DICE_COUNT + GREEN_DICE_COUNT);
        std::vector<EDiceFace> DiceResult(static_cast<unsigned long>(DiceCount), EDiceFace::None);
        return DiceResult;
    }

    void FDiceRoller::RollDice(const int DiceCount, std::vector<EDiceFace> &OutDiceResult)
    {
        std::vector<bool> NewRoll;
        for (int i = 0; i < DiceCount; i++)
        {
            if (OutDiceResult[i] == EDiceFace::None)
            {
                NewRoll.push_back(true);
                OutDiceResult[i] = RollSingleDice();
            }
            else
            {
                NewRoll.push_back(false);
            }
        }
        Notify(shared_from_this(), std::make_shared<FRolledDiceEvent>(EObserverEvent::RolledDice, "", OutDiceResult, NewRoll));
    }

    const EDiceFace FDiceRoller::RollSingleDice()
    {
        int Roll = UniformeDistribution(MersenneTwisterEngine);
        assert(0 <= Roll && Roll <= FACE_ON_DICE_COUNT - 1);
        RollHistory[Roll]++;
        return EDiceFace(Roll);
    }
}
