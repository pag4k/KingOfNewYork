// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "buycardsstrategy.h"
#include "helper.h"
#include "game.h"
#include "player.h"

namespace KingOfNewYork
{
    void HumanBuyCardsStrategy::Execute(FGame &Game, std::shared_ptr<FPlayer> Player)
    {
        int Input;
        do {
            std::vector<std::unique_ptr<FCard>> &AvailableCards = Game.GetAvailableCards();
            if (AvailableCards.empty())
            {
                std::cout << "There are no more cards."
                          << std::endl;
                break;
            }
            std::cout << "Please enter the number of the card you want to buy (or 0 to stop buying or 9 to spend "
                      << ENERGY_CUBE_FOR_NEW_CARDS_COUNT
                      << " Energy Cubes to discard the 3 available cards and reveal new ones). You currently have "
                      << Player->GetEnergyCubes()
                      << " Energy Cubes."
                      << std::endl;
            for (int i = 0; i < AvailableCards.size(); ++i)
            {
                std::cout << (i+1);
                //PrintNormal(AvailableCards[i]->GetCardInfo());

                AvailableCards[i]->Display();
            }
            std::cout << ">";
            Input = InputSingleDigit();
            if (Input == 0)
            {
                break;
            }
            if (Input == 9 && Player->GetEnergyCubes() >= ENERGY_CUBE_FOR_NEW_CARDS_COUNT)
            {
                if (Game.DistributeCard())
                {
                    Player->ChangeEnergyCubes(-ENERGY_CUBE_FOR_NEW_CARDS_COUNT);
                    std::cout << "You get new card."
                              << std::endl;
                }
                else
                {
                    std::cout << "There are no cards new cards."
                            << std::endl;
                }
                continue;
            }
            else if (Input == 9 && Player->GetEnergyCubes() < ENERGY_CUBE_FOR_NEW_CARDS_COUNT)
            {
                std::cout << "You do not have enough Energy Cubes to get new cards."
                          << std::endl;
                continue;
            }
            if (1 <= Input && Input <= AvailableCards.size())
            {
                if (AvailableCards[Input-1] && AvailableCards[Input-1]->GetEnergyCost() <= Player->GetEnergyCubes())
                {
                    std::cout << "You bough "
                              << AvailableCards[Input-1]->GetName()
                              << "."
                              << std::endl;
                    Player->ChangeEnergyCubes(-AvailableCards[Input - 1]->GetEnergyCost());

                    Player->BuyCard(Game.GetCard(Input-1));
                }
                else
                {
                    std::cout << "You cannot buy this card."
                              << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid input."
                          << std:: endl;
            }
        } while (Input != 0);
    }

    void AggressiveBuyCardsStrategy::Execute(FGame &Game, std::shared_ptr<FPlayer> Player)
    {

    }

    void ModerateBuyCardsStrategy::Execute(FGame &Game, std::shared_ptr<FPlayer> Player)
    {

    }

}

