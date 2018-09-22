#include <iostream>

#include "diceroller.h"

int main()
{
    DiceRoller* diceRoller = new DiceRoller(6,3);
    DiceResult diceResult = diceRoller->BeginRolling();

    std::cin.get();
    //TEST
    return 0;
}