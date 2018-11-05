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

    const std::vector<EDiceFace> FDiceRoller::BeginRolling(
        const int DiceCount, const int RollCount) const
    {
        assert(0 <= DiceCount && DiceCount <= BLACK_DICE_COUNT + GREEN_DICE_COUNT);

        int CurrentRollCount = 0;

        std::vector<EDiceFace> DiceResult;
        for (int i = 0; i < DiceCount; i++)
        {
            DiceResult.push_back(EDiceFace::None);
        }

        while (CurrentRollCount < RollCount)
        {
            std::cout << "### Roll number "
                      << (CurrentRollCount + 1)
                      << " out of "
                      << (RollCount)
                      << " ###"
                      << std::endl;

            for (int i = 0; i < DiceCount; i++)
            {
                bool NewRoll = false;
                if (DiceResult[i] == EDiceFace::None)
                {
                    NewRoll = true;
                    DiceResult[i] = RollDice(FACE_ON_DICE_COUNT);
                }
                std::cout << (i + 1)
                          << ": "
                          << GetDiceFaceString(DiceResult[i])
                          << (NewRoll ? " (new roll)" : "")
                          << std::endl;
            }

            CurrentRollCount++;
            if (CurrentRollCount >= RollCount)
            {
                break;
            }

            std::cout << "#############################"
                      << std::endl;
            std::cout << "Enter the numbers of the dice you want to reroll and"
                      << " press enter."
                      << std::endl;
            std::cout << "Ex.: \"123\" (all other characters will be ignored)."
                      << std::endl;
            std::cout << "Write nothing to end the rolling phase)."
                      << std::endl;
            std::cout << "> ";
            
            std::string input;
            std::getline(std::cin, input);
            if (input.empty())
            {
                std::cout << "Ending rolling phase..." << std::endl;
                break;
            }

            for (int i = 0; i < DiceCount; i++)
            {
                if (input.find((char)(i+1+48)) != std::string::npos)
                {
                    DiceResult[i] = EDiceFace::None;
                }
            }
        }
        
        return DiceResult;
    }

    const EDiceFace FDiceRoller::RollDice(const int FaceNumber) const
    {
        assert(1 <= FaceNumber && FaceNumber <= FACE_ON_DICE_COUNT);
        int Roll = std::rand() / ((RAND_MAX + 1u) / FaceNumber);
        assert(0 <= Roll && Roll <= FaceNumber - 1);
        RollHistory[Roll]++;
        return EDiceFace(Roll);
    }
}
