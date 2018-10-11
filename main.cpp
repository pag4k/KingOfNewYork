// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include "assignment1.h"
#include "helper.h"

using namespace KingOfNewYork;

int main()
{
    bool bIsRunning = true;
    while (bIsRunning)
    {
        std::cout << std::endl
                  << "COMP345 Assignment 1 driver program by Pierre-André Gagnon (40067198)."
                  << std::endl
                  << "Please enter the number corresponding to the part you want to test:"
                  << std::endl
                  << "1. Part 1: Maps."
                  << std::endl
                  << "2. Part 2: Map loader."
                  << std::endl
                  << "3. Part 3: Dice Roller."
                  << std::endl
                  << "4. Part 4: Player."
                  << std::endl
                  << "5. Part 5: Cards deck/Monster cards/Tokens/cubes/unit tiles."
                  << std::endl
                  << "0. Exit program."
                  << std::endl
                  << ">";
        const int Input = InputSingleDigit();
        std::cout << std::endl;
        switch (Input)
        {
            case 0:
            {
                bIsRunning = false;
                break;
            }
            case 1:
            {
                Part1();
                break;
            }
            case 2:
            {
                Part2();
                break;
            }
            case 3:
            {
                Part3();
                break;
            }
            case 4:
            {
                Part4();
                break;
            }
            case 5:
            {
                Part5();
                break;
            }
            default:
            {
                std::cout   << "Invalid input!"
                            << std::endl;
                break;
            }
        }
    }

    std::cin.get();

    return 0;
}