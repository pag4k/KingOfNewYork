#include <iostream>
#include <string>

#include "helper.h"
#include "common.h"
#include "diceroller.h"
#include "graph.h"
#include "game.h"
#include "card.h"

int main()
{
    bool bIsRunning = true;
    while (bIsRunning)
    {
        std::cout << std::endl
                  << "Write the number corresponding to what you want to test"
                  << std::endl
                  << "1. Generate the map and test it."
                  << std::endl
                  << "2. Test the dice roller."
                  << std::endl
                  << "3. Create a game."
                  << std::endl
                  << "4. Create a deck."
                  << std::endl
                  << "0. Exit program."
                  << std::endl
                  << ">";
        const int Input = InputSingleDigit();
        switch (Input)
        {
            case 0:
            {
                bIsRunning = false;
                break;
            }
            case 1:
            {
                std::cout << std::endl
                        << "Enter the name of the file to use to generate the graph:"
                        << std::endl
                        << ">";
                const std::string FileName = InputString();
                std::shared_ptr<FGraph> NewYorkGraph = std::make_shared<FGraph>(FileName);
                //delete NewYorkGraph;
                break;
            }
            case 2:
            {
                FDiceRoller CurrentDiceRoller;
                std::vector<EDiceFace> DiceResult = CurrentDiceRoller.BeginRolling();
                break;
            }
            case 3:
            {
                std::cout   << std::endl
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
                    std::shared_ptr<FGame> Game = std::make_shared<FGame>(NumberOfPlayer);
                    Game->Print();
                    //delete Game;
                }
                else
                {
                    std::cout   << "Invalid number of player. It has to be between "
                                << MINIMUM_NUMBER_OF_PLAYERS
                                << " and "
                                << MAXIMUM_NUMBER_OF_PLAYERS
                                << ". Please try again."
                                << std::endl;
                }
                break;
            }
            case 4:
            {
                FDeck Deck("cards.txt");
                Deck.Print();
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