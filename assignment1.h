#include <iostream>

#include "helper.h"
#include "graph.h"
#include "map.h"
#include "diceroller.h"
#include "game.h"

namespace KingOfNewYork
{
    void PrintNeighbours(const FGraph<int> &Graph, const std::string Name)
    {
        std::vector<int> Neighbours = Graph.GetNeighbours(Graph.GetIndexFromName(Name));
        if (Neighbours.size() == 0)
        {
            std::cout << Name << " as no neighbours!" << std::endl;
        }
        else
        {
            std::cout << Name << ": ";
            for (int i = 0; i < Neighbours.size(); ++i)
            {
                std::cout << Graph.GetName(Neighbours[i]);
                if (i != Neighbours.size() - 1)
                {
                    std::cout << ", ";
                }
                else
                {
                    std::cout << std::endl;
                }
            }
        }
    }

    void PrintAdjacent(const FGraph<int> &Graph, const std::string Name1, const std::string Name2)
    {
        std::cout   << "Is "
                    << Name1
                    << " adjancent with "
                    << Name2
                    << "? "
                    << (Graph.AreAdjacent(Name1, Name2) ? "Yes!" : "No!")
                    << std::endl;
    }

    void Part1()
    {
        std::cout << "Assignment 1: Part 1" << std::endl;
        {
            std::cout << "Creating graph of Western Europe" << std::endl;
            FGraph<int> Graph;

            std::cout << "Adding coutries:" << std::endl;
            Graph.InsertVertex("Portugal");
            Graph.InsertVertex("Spain");
            Graph.InsertVertex("Ireland");
            Graph.InsertVertex("Great Britain");
            Graph.InsertVertex("France");
            Graph.InsertVertex("Belgium");
            Graph.InsertVertex("Netherlands");
            Graph.InsertVertex("Luxembourg");
            Graph.InsertVertex("Swiss");
            Graph.InsertVertex("Germany");
            Graph.InsertVertex("Italy");
            Graph.InsertVertex("Austria");
            Graph.InsertVertex("Denmark");
            Graph.InsertVertex("Malta");

            std::cout << "Adding connections:" << std::endl;
            Graph.InsertEdge("Ireland", "Great Britain");
            Graph.InsertEdge("Portugal", "Spain");
            Graph.InsertEdge("France", "Spain");
            Graph.InsertEdge("France", "Belgium");
            Graph.InsertEdge("France", "Luxembourg");
            Graph.InsertEdge("France", "Germany");
            Graph.InsertEdge("France", "Swiss");
            Graph.InsertEdge("France", "Italy");
            Graph.InsertEdge("Belgium", "Netherlands");
            Graph.InsertEdge("Belgium", "Luxembourg");
            Graph.InsertEdge("Belgium", "Germany");
            Graph.InsertEdge("Netherlands", "Germany");
            Graph.InsertEdge("Luxembourg", "Germany");
            Graph.InsertEdge("Swiss", "Germany");
            Graph.InsertEdge("Swiss", "Austria");
            Graph.InsertEdge("Swiss", "Italy");
            Graph.InsertEdge("Germany", "Denmark");
            Graph.InsertEdge("Germany", "Austria");
            Graph.InsertEdge("Austria", "Italy");

            std::cout << "Showing neighbours:" << std::endl;
            PrintNeighbours(Graph, "Germany");
            PrintNeighbours(Graph, "Ireland");
            PrintNeighbours(Graph, "Malta");

            std::cout << "Checking adjacency:" << std::endl;
            PrintAdjacent(Graph, "France", "Italy");
            PrintAdjacent(Graph, "Denmark", "Portugal");
            PrintAdjacent(Graph, "Italy", "Swiss");
        }

        std::cout << std::endl;

        {
            std::cout << "Creating graph of broken map:" << std::endl;
            FGraph<int> Graph;
            
            std::cout << "Adding coutries:" << std::endl;
            Graph.InsertVertex("Brazil");
            std::cout << "Trying to add a vertex with no name:" << std::endl;
            Graph.InsertVertex("");
            Graph.InsertVertex("Argentina");

            std::cout << "Adding connections:" << std::endl;
            Graph.InsertEdge("Brazil", "Argentina");
            std::cout << "Trying to add a edge to a vertex that is not in the graph:" << std::endl;
            Graph.InsertEdge("Argentina", "Australia");
            std::cout << "Trying to add a edge to a vertex with no name:" << std::endl;
            Graph.InsertEdge("Argentina", "");
        }

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
}