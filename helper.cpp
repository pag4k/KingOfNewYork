#include <helper.h>

//If invalid, returns -1.
int InputSingleDigit()
{
    std::string Input;
    std::getline(std::cin, Input);
    if (Input.length() == 1)
    {
        char Char = Input[0];
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
    else
    {
        return -1;
    }
}

std::string InputString()
{
    std::string Input;
    std::getline(std::cin, Input);
    return Input;
}