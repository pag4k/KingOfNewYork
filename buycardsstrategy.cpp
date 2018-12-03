// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "buycardsstrategy.h"
#include "gamecontroller.h"
#include "helper.h"

namespace KingOfNewYork
{
    void HumanBuyCardsStrategy::Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player)
    {
        auto &Game = GameController.GetGame();
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
                if (GameController.DistributeCard())
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

    void AggressiveBuyCardsStrategy::Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player)
    {
        BuyCardsAI(GameController, Player);
    }

    void ModerateBuyCardsStrategy::Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player)
    {
        BuyCardsAI(GameController, Player);
    }

    namespace
    {
        void BuyCardsAI(FGameController &GameController, std::shared_ptr<FPlayer> &Player)
        {
            auto &Game = GameController.GetGame();
            auto &AvailableCards = Game.GetAvailableCards();

            while (Player->GetEnergyCubes() > 0)
            {
                auto CheapestCardIt = std::min_element(AvailableCards.begin(), AvailableCards.end(),
                                                       [](const auto &CardA, const auto &CardB) { return CardA->GetEnergyCost() < CardB->GetEnergyCost(); });
                if (CheapestCardIt != AvailableCards.end() && (*CheapestCardIt)->GetEnergyCost() <= Player->GetEnergyCubes())
                {
                    auto Index = static_cast<int>(std::distance(AvailableCards.begin(), CheapestCardIt));
                    assert(0 <= Index && Index <= AvailableCards.size());
                    Player->BuyCard(Game.GetCard(Index));
                }
                else
                {
                    break;
                }
            }
        }
    }

}

