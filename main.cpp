// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include "assignment2.h"

using namespace KingOfNewYork;

int main(int argc, char* argv[])
{
    Path = argv[0];
    bool bIsRunning = true;
    while (bIsRunning)
    {
        std::cout << std::endl
                  << "COMP345 Assignment 2 driver program by Pierre-André Gagnon (40067198)."
                  << std::endl
                  << "Please enter the number corresponding to the part you want to test:"
                  << std::endl
                  << "1. Part 1: Game start."
                  << std::endl
                  << "2. Part 2: Game play: startup phase."
                  << std::endl
                  << "3. Part 3: Game play: main game loop."
                  << std::endl
                  << "4. Part 4: Main game loop: roll the dice and resolve the dice."
                  << std::endl
                  << "5. Part 5: Main game loop: Move."
                  << std::endl
                  << "6. Part 6: Main game loop: Buy Cards."
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
            case 6:
            {
                Part6();
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