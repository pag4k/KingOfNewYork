#include <iostream>

#include "player.h"
#include "helper.h"

FPlayer::FPlayer(std::vector<std::string> *PlayerNames, bool bAvailableMonsters[])
{
    PlayerName = "";
    EnterPlayerName(PlayerNames);
    MonsterName = EMonsterName::None;
    SelectMonster(bAvailableMonsters);

    //NEED TO ADD POSITION

    for (int i = 0; i < NUMBER_OF_TOKENS; ++i)
    {
        TokenInventory.Token[i] = 0;
    }

    EnergyCubes = 0;
    LifePoints = 10;
    VictoryPoints = 0;

    RollDice();
    ResolveDice();
}

FPlayer::~FPlayer()
{
    //delete DiceRoller;
    //DiceRoller = nullptr;
}

void FPlayer::RollDice()
{
    CurrentDiceResult = DiceRoller.BeginRolling();
}

void FPlayer::ResolveDice()
{
    int DiceSums[NUMBER_OF_FACES_ON_DICE];
    for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; ++i)
    {
        DiceSums[i] = 0;
    }
    for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; ++i)
    {
        DiceSums[static_cast<int>(CurrentDiceResult.Dice[i])]++;
    }
    for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; ++i)
    {
        std::cout << (i+1)
                  << ". "
                  << DiceSums[i]
                  << "x "
                  << GetDiceFaceString(EDiceFace(i))
                  << std::endl;
    }

    bool Done = false;
    do
    {
        std::cout << "Enter the number of the action you want to resolve:"
                  << std::endl
                  << ">";
        int Input = InputSingleDigit();
        if (0 <= Input && Input <= NUMBER_OF_FACES_ON_DICE)
        {
            
        }
        else
        {
            std::cout << "Invalid input!" << std::endl;
        }
    } while (!Done);


}

void FPlayer::Move()
{

}


void FPlayer::EnterPlayerName(std::vector<std::string> *PlayerNames)
{
    while (PlayerName == "")
    {
        std::cout   << "Player "
                    << PlayerNames->size() + 1
                    << ", please enter your name:" << std::endl;
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
        std::cout   << PlayerName
                    << ", please select your monster:" << std::endl;
        for (int i = 0; i < NUMBER_OF_MONSTERS; ++i)
        {
            if (bAvailableMonsters[i])
            {
                std::cout << (i + 1) << " " << GetMonsterNameString(static_cast<EMonsterName>(i)) << std::endl;
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