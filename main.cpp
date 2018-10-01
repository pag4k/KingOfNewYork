#include <iostream>

#include "diceroller.h"
#include "graph.h"
#include <string>

int main()
{
    while (true)
    {
        std::cout << std::endl
                  << "Write the number corresponding to what you want to test"
                  << std::endl
                  << "1. Generate the map and test it."
                  << std::endl
                  << "2. Test the dice roller."
                  << std::endl
                  << "0. Exit program."
                  << std::endl
                  << ">";
        std::string Text;
        std::getline(std::cin, Text);
        if (Text == "1")
        {
            std::cout << std::endl
                      << "Enter the name of the file to use to generate the graph:"
                      << std::endl
                      << ">";
            std::getline(std::cin, Text);
            Graph *NewYorkGraph = new Graph(Text);
            delete NewYorkGraph;
        }
        else if (Text == "2")
        {
            DiceRoller *CurrentDiceRoller = new DiceRoller(6, 3);
            DiceResult DiceResult = CurrentDiceRoller->BeginRolling();
            delete CurrentDiceRoller;
        }
        else if (Text == "0")
        {
            break;
        }
        else
        {
            std::cout << "Invalid input!"
                      << std::endl;
        }
    }

    std::cin.get();

    return 0;
}