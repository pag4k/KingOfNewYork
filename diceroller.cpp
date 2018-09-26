#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <ctime>

#include "diceroller.h"

DiceRoller::DiceRoller(int DiceNumber, int RollNumber)
{
    //Verify that both arguments are greater than zero.
    assert(DiceNumber > 0);
    assert(RollNumber > 0);
    //Use current time as seed for the random generator.
    std::srand(std::time(nullptr));
    this->DiceNumber = DiceNumber;
    this->RollNumber = RollNumber;

    for (int i = 0; i < FACE_NUMBER; i++)
    {
        RollHistory[i] = 0;
    }
}

DiceResult DiceRoller::BeginRolling()
{
    RollCount = 0;
    DiceResult DiceResult;
    for (int i = 0; i < DiceNumber; i++)
    {
        DiceResult.Dice[i] = DiceFace::None;
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
            if (DiceResult.Dice[i] == DiceFace::None)
            {
                NewRoll = true;
                DiceResult.Dice[i] = RollDice(FACE_NUMBER);
            }
            std::cout   << (i + 1)
                        << ": "
                        << GetFaceName(DiceResult.Dice[i])
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
                DiceResult.Dice[i] = DiceFace::None;
            }
        }
    }

    PrintRollHistory();

    return DiceResult;
}

DiceFace DiceRoller::RollDice(int FaceNumber)
{
    assert(FaceNumber > 0);
    int Roll = std::rand() / ((RAND_MAX + 1u) / FaceNumber);
    assert(0 <= Roll && Roll <= FaceNumber - 1);
    RollHistory[Roll]++;
    return DiceFace(Roll);
}

std::string DiceRoller::GetFaceName(DiceFace Face)
{
    std::string FaceName = "";
    switch(Face)
    {
    case DiceFace::Attack:
        FaceName = "Attack";
        break;
    case DiceFace::Celebrity:
        FaceName = "Celebrity";
        break;
    case DiceFace::Destruction:
        FaceName = "Destruction";
        break;
    case DiceFace::Energy:
        FaceName = "Energy";
        break;
    case DiceFace::Heal:
        FaceName = "Heal";
        break;
    case DiceFace::Ouch:
        FaceName = "Ouch";
        break;
    }
    assert(FaceName != "");
    return FaceName;
}

void DiceRoller::PrintRollHistory()
{
    std::cout << "### Roll History ###" << std::endl;
    for (int i = 0; i < FACE_NUMBER; i++)
    {
        std::cout << GetFaceName(DiceFace(i)) << ": " << RollHistory[i] << std::endl;
    }
}