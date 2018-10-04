#include <iostream>
#include <assert.h>

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

    bCelebrity = false;
    bStatueOfLiberty = false;

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

    bool Done = false;
    do
    {
        std::cout << "### Resolve the dice ###" << std::endl;
        for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; ++i)
        {
            std::cout << (i + 1)
                      << ". "
                      << DiceSums[i]
                      << "x "
                      << GetDiceFaceString(EDiceFace(i))
                      << std::endl;
        }
        std::cout << "Enter the number of the action you want to resolve:"
                  << std::endl
                  << ">";
        int Input = InputSingleDigit();
        if (0 <= Input && Input <= NUMBER_OF_FACES_ON_DICE)
        {
            if (DiceSums[Input] > 0)
            {
                std::cout << "Resolving "
                          << GetDiceFaceString(EDiceFace(Input))
                          << " dice:"
                          << std::endl;
                switch (Input + 1)
                {
                    case 0:
                        if (ResolveAttack(DiceSums[Input]))
                        {
                            DiceSums[Input] = 0;
                        }
                        break;
                    case 1:
                        if (ResolveCelebrity(DiceSums[Input]))
                        {
                            DiceSums[Input] = 0;
                        }
                        break;
                    case 2:
                        if (ResolveDestruction(DiceSums[Input]))
                        {
                            DiceSums[Input] = 0;
                        }
                        break;
                    case 3:
                        if (ResolveEnergy(DiceSums[Input]))
                        {
                            DiceSums[Input] = 0;
                        }
                        break;
                    case 4:
                        if (ResolveHeal(DiceSums[Input]))
                        {
                            DiceSums[Input] = 0;
                        }
                        break;
                    case 5:
                        if (ResolveOuch(DiceSums[Input]))
                        {
                            DiceSums[Input] = 0;
                        }
                        break;
                }
                Done = true;
                for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; ++i)
                {
                    if (DiceSums[i] > 0)
                    {
                        Done = false;
                        break;
                    }
                }
            }
            else
            {
                std::cout   << "No "
                            << GetDiceFaceString(EDiceFace(Input))
                            << " dice to resolve."
                            << std::endl;
            }
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

bool FPlayer::ResolveAttack(const int NumberOfDice)
{
    return true;
}

bool FPlayer::ResolveCelebrity(const int NumberOfDice)
{
    int NewVictoryPoints = 0;
    if (bCelebrity)
    {   
        NewVictoryPoints = NumberOfDice;
    }
    else
    {
        if (NumberOfDice >= NUMBER_OF_DICE_FOR_CELEBRITY)
        {
            bCelebrity = true;
            NewVictoryPoints = NumberOfDice - (NUMBER_OF_DICE_FOR_CELEBRITY - 1);
        }
    }
    VictoryPoints += NewVictoryPoints;
    std::cout << "Earned "
              << NewVictoryPoints
              << " victory point"
              << (NumberOfDice == 1 ? ". " : "s. ")
              << "New total: "
              << VictoryPoints
              << "."
              << std::endl;
    //TODO: NOT SURE HOW TO DEAL WITH VICTORY. WITH A SETTER OR A CHECK AFTER TURN.
    return true;
}

bool FPlayer::ResolveDestruction(const int NumberOfDice)
{
    return true;
}

bool FPlayer::ResolveEnergy(const int NumberOfDice)
{
    assert(NumberOfDice>0);
    EnergyCubes += NumberOfDice;
    std::cout   << "Earned "
                << NumberOfDice
                << " energy cube"
                << (NumberOfDice == 1 ? ". " : "s. ")
                << "New total: "
                << EnergyCubes
                << "."
                << std::endl;
    return true;
}

bool FPlayer::ResolveHeal(const int NumberOfDice)
{
    assert(NumberOfDice > 0);
    LifePoints += NumberOfDice;
    LifePoints = (LifePoints > MAXIMUM_LIFE_POINTS ? 10 : LifePoints);
    std::cout << "Earned "
              << NumberOfDice
              << " life point"
              << (NumberOfDice == 1 ? ". " : "s. ")
              << "New total: "
              << LifePoints
              << "."
              << std::endl;
    return true;
}

bool FPlayer::ResolveOuch(const int NumberOfDice)
{
    return true;
}