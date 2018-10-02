#include <iostream>

#include "player.h"
#include "common.h"
#include "helper.h"
#include "diceroller.h"

FPlayer::FPlayer(std::vector<std::string> *PlayerNames, bool bAvailableMonsters[])
{
    PlayerName = "";
    EnterPlayerName(PlayerNames);
    MonsterName = EMonsterName::None;
    SelectMonster(bAvailableMonsters);

    //NEED TO ADD POSITION

    DiceRoller = new FDiceRoller(NUMBER_OF_DICE, NUMBER_OF_ROLLS);
}

FPlayer::~FPlayer()
{
    delete DiceRoller;
    DiceRoller =  nullptr;
}

void FPlayer::EnterPlayerName(std::vector<std::string> *PlayerNames)
{
    while (PlayerName == "")
    {
        std::cout << "Please enter your name:" << std::endl;
        std::cout << ">";
        bool bError = false;
        const std::string Input = InputString();
        if (Input == "")
        {
            std::cout << "Invalid input, please try again." << std::endl
                      << std::endl;
            bError = true;
            continue;
        }
        for (std::string Name: *PlayerNames)
        {
            if (Input == Name)
            {
                std::cout << "Name already taken, please try again." << std::endl
                          << std::endl;
                bError = true;
                break;
            }
        }
        if (!bError)
        {
            PlayerName = Input;
            PlayerNames->push_back(Input);
        }
    }
}

void FPlayer::SelectMonster(bool bAvailableMonsters[])
{
    while (MonsterName == EMonsterName::None)
    {
        std::cout << "Please select your monster:" << std::endl;
        for (int i = 0; i < NUMBER_OF_MONSTERS; ++i)
        {
            if (bAvailableMonsters[i])
            {
                std::cout << (i + 1) << " " << GetMonsterName(static_cast<EMonsterName>(i)) << std::endl;
            }
        }
        std::cout << ">";
        const int Input = InputSingleDigit();
        if (1 <= Input && Input <= NUMBER_OF_MONSTERS && bAvailableMonsters[Input])
        {
            MonsterName = static_cast<EMonsterName>(Input - 1);
            bAvailableMonsters[Input - 1] = false;
        }
        else
        {
            std::cout << "Invalid input, please try again." << std::endl << std::endl;
        }
    }
}