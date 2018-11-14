// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "rolldicestrategy.h"
#include <iostream>

namespace KingOfNewYork
{
    void HumanRollDiceStrategy::Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult)
    {
        int CurrentRollCount = 0;

        while (CurrentRollCount < RollCount)
        {
            std::cout << "### Roll number "
                      << (CurrentRollCount + 1)
                      << " out of "
                      << (RollCount)
                      << " ###"
                      << std::endl;

            DiceRoller.RollDice(DiceCount, OutDiceResult);

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
                    OutDiceResult[i] = EDiceFace::None;
                }
            }
        }
    }

    void AggressiveRollDiceStrategy::Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult)
    {
        //focuses on attack or destruction during the role dice step
        int CurrentRollCount = 0;

        while (CurrentRollCount < RollCount)
        {
            std::cout << "### Roll number "
                      << (CurrentRollCount + 1)
                      << " out of "
                      << (RollCount)
                      << " ###"
                      << std::endl;

            DiceRoller.RollDice(DiceCount, OutDiceResult);

            CurrentRollCount++;
            if (CurrentRollCount >= RollCount)
            {
                break;
            }

            bool bReroll = false;
            for (int i = 0; i < DiceCount; i++)
            {
                if (OutDiceResult[i] != EDiceFace::Attack && OutDiceResult[i] != EDiceFace::Destruction)
                {
                    OutDiceResult[i] = EDiceFace::None;
                    bReroll = true;
                }
            }

            if (!bReroll)
            {
                std::cout << "Ending rolling phase..." << std::endl;
                break;
            }
        }

    }

    void ModerateRollDiceStrategy::Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult)
    {
        //focus on balancing the health, grabbing power-ups or storming Manhattan which quickly builds rewards
    }
}
