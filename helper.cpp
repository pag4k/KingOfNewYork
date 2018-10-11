// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include <helper.h>

namespace KingOfNewYork
{
    //If invalid, returns -1.
    const int InputSingleDigit()
    {
        std::string Input;
        std::getline(std::cin, Input);
        if (Input.length() == 1)
        {
            return ParseIntFromChar(Input[0]);
        }
        else
        {
            return -1;
        }
    }

    const std::string InputString()
    {
        std::string Input;
        std::getline(std::cin, Input);
        return Input;
    }

    const int ParseIntFromChar(const char Char)
    {
        int Digit = (int)Char - 48;
        if (0 <= Digit && Digit <= 9)
        {
            return Digit;
        }
        else
        {
            return -1;
        }
    }
}
