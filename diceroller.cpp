// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <ctime>

#include "diceroller.h"
#include "common.h"

namespace KingOfNewYork
{
    FDiceRoller::FDiceRoller()
    {
        //Use current time as seed for the random generator.
        std::srand(std::time(nullptr));
        //this->DiceNumber = NUMBER_OF_DICE;
        this->RollNumber = NUMBER_OF_ROLLS;

        for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; i++)
        {
            RollHistory[i] = 0;
        }
    }

    const std::vector<EDiceFace> FDiceRoller::BeginRolling() const
    {
        return BeginRolling(NUMBER_OF_DICE);    
    }

    const std::vector<EDiceFace> FDiceRoller::BeginRolling(const int DiceNumber) const
    {
        assert(0 <= DiceNumber &&
                DiceNumber <= NUMBER_OF_DICE);
        int RollCount = 0;
        std::vector<EDiceFace> DiceResult;
        for (int i = 0; i < DiceNumber; i++)
        {
            DiceResult.push_back(EDiceFace::None);
        }
        while (RollCount < RollNumber)
        {
            std::cout   << "### Roll number "
                        << (RollCount + 1)
                        << " out of "
                        << (RollNumber)
                        << " ###"
                        << std::endl;

            for (int i = 0; i < DiceNumber; i++)
            {
                bool NewRoll = false;
                if (DiceResult[i] == EDiceFace::None)
                {
                    NewRoll = true;
                    DiceResult[i] = RollDice(NUMBER_OF_FACES_ON_DICE);
                }
                std::cout << (i + 1)
                        << ": "
                        << GetDiceFaceString(DiceResult[i])
                        << (NewRoll ? " (new roll)" : "")
                        << std::endl;
            }
            RollCount++;
            if (RollCount >= RollNumber) {
                break;
            }
            std::cout   << "#############################"
                        << std::endl;
            std::cout   << "Enter the numbers of the dice you want to reroll and"
                        << "press enter."
                        << std::endl;
            std::cout   << "Ex.: \"123\" (all other characters will be ignored)." << std::endl;
            std::cout << "Write nothing and press enter to end the rolling phase)." << std::endl;
            std::cout << "> ";
            std::string input;
            std::getline(std::cin, input);
            if (input == "")
            {
                std::cout << "Ending rolling phase..." << std::endl;
                break;
            }
            for (int i = 0; i < DiceNumber; i++)
            {
                if (input.find((char)(i+1+48)) != std::string::npos)
                {
                    DiceResult[i] = EDiceFace::None;
                }
            }
        }

        //PrintRollHistory();

        return DiceResult;
    }

    const EDiceFace FDiceRoller::RollDice(const int FaceNumber) const
    {
        assert(FaceNumber > 0);
        int Roll = std::rand() / ((RAND_MAX + 1u) / FaceNumber);
        assert(0 <= Roll && Roll <= FaceNumber - 1);
        RollHistory[Roll]++;
        return EDiceFace(Roll);
    }

    void FDiceRoller::PrintRollHistory() const
    {
        std::cout << "### Roll History ###" << std::endl;
        for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; i++)
        {
            std::cout << GetDiceFaceString(EDiceFace(i)) << ": " << RollHistory[i] << std::endl;
        }
        std::cout << "####################" << std::endl;
    }
}
