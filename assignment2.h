#include <iostream>

#include "helper.h"
#include "graph.h"
#include "map.h"
#include "diceroller.h"
#include "game.h"

namespace KingOfNewYork
{
    void Part1()
    {
        PrintFiles("map/");

        std::cout << std::endl;
    }

    void Part2()
    {
        std::cout << std::endl
                << "Enter the name of the file to use to generate the map:"
                << std::endl
                << ">";
        const std::string FileName = InputString();
        FMap Map = FMap(FileName);
        if (Map.IsValid())
        {
            std::string CopyFileName = "Copy" + FileName;
            if (Map.SaveMap(CopyFileName))
            {
                std::cout << "Map succesfully saved to: "
                          << CopyFileName
                          << "."
                          << std::endl;
            }
            else
            {
                std::cout << "Error: Map was not saved." << std::endl;
            }
        }
    }

    void PrintDiceResult(const std::vector<EDiceFace> &DiceResult)
    {
        int DiceSums[NUMBER_OF_FACES_ON_DICE];
        for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; ++i)
        {
            DiceSums[i] = 0;
        }
        for (EDiceFace DiceFace : DiceResult)
        {
            DiceSums[static_cast<int>(DiceFace)]++;
        }
        std::cout << "Dice results:" << std::endl;
        for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; ++i)
        {
            std::cout << (i + 1)
                    << ". "
                    << DiceSums[i]
                    << "x "
                    << GetDiceFaceString(EDiceFace(i))
                    << std::endl;
        }
    }

    void Part3()
    {
        std::cout << "Creating first dice roller." << std::endl;
        FDiceRoller FirstDiceRoller;
        std::cout << "Creating second dice roller." << std::endl;
        FDiceRoller SecondDiceRoller;

        bool bContinue = true;
        while (bContinue)
        {
            std::cout << std::endl
                    << "Write the number corresponding to what you want to do"
                    << std::endl
                    << "1. Use first dice roller."
                    << std::endl
                    << "2. Use second dice roller."
                    << std::endl
                    << "3. See first dice roller roll history."
                    << std::endl
                    << "4. See second dice roller roll history."
                    << std::endl
                    << "0. Go back to main menu."
                    << std::endl
                    << ">";
            const int Input = InputSingleDigit();
            std::cout << std::endl;
            switch (Input)
            {
                case 0:
                {
                    bContinue = false;
                    break;
                }
                case 1:
                {
                    std::vector<EDiceFace> DiceResult = FirstDiceRoller.BeginRolling();
                    std::cout << std::endl;
                    PrintDiceResult(DiceResult);
                    break;
                }
                case 2:
                {
                    std::vector<EDiceFace> DiceResult = SecondDiceRoller.BeginRolling();
                    std::cout << std::endl;
                    PrintDiceResult(DiceResult);
                    break;
                }
                case 3:
                {
                    FirstDiceRoller.PrintRollHistory();
                    break;
                }
                case 4:
                {
                    SecondDiceRoller.PrintRollHistory();
                    break;
                }
            }
        }
    }

    void Part4()
    {
        std::cout << std::endl
                << "Enter the number of player ("
                << MINIMUM_NUMBER_OF_PLAYERS
                << "-"
                << MAXIMUM_NUMBER_OF_PLAYERS
                << "):"
                << std::endl
                << ">";
        const int NumberOfPlayer = InputSingleDigit();    
        if (MINIMUM_NUMBER_OF_PLAYERS <= NumberOfPlayer &&
            NumberOfPlayer <= MAXIMUM_NUMBER_OF_PLAYERS)
        {
            std::cout << std::endl;
            std::shared_ptr<FGame> Game = std::make_shared<FGame>(NumberOfPlayer);
        }
        else
        {
            std::cout << "Invalid number of player. It has to be between "
                    << MINIMUM_NUMBER_OF_PLAYERS
                    << " and "
                    << MAXIMUM_NUMBER_OF_PLAYERS
                    << ". Please try again."
                    << std::endl;
        }
    }

    void Part5()
    {
        std::shared_ptr<FGame> Game = std::make_shared<FGame>();
        if (!Game->IsValid())
        {
            return;
        }

        bool bContinue = true;
        while (bContinue)
        {
            std::cout << std::endl
                    << "Write the number corresponding to what you want to do"
                    << std::endl
                    << "1. See game status."
                    << std::endl
                    << "2. Shuffle and show deck."
                    << std::endl
                    << "3. Shuffle and show tile stack."
                    << std::endl
                    << "0. Go back to main menu."
                    << std::endl
                    << ">";
            const int Input = InputSingleDigit();
            std::cout << std::endl;
            switch (Input)
            {
                case 0:
                {
                    bContinue = false;
                    break;
                }
                case 1:
                {
                    Game->Print();
                    break;
                }
                case 2:
                {
                    Game->ShuffleAndPrintDeck();
                    break;
                }
                case 3:
                {
                    Game->ShuffleAndPrintTileStack();
                    break;
                }
            }
        }
    }

    void Part6()
    {
    }
}