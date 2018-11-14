// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <random>
#include <chrono>
#include "card.h"
#include "helper.h"

namespace KingOfNewYork
{
    void FCard::Print()
    {
        std::cout << "\tName: " << GetName() << std::endl
                  << "\tHow to Play: "
                  << GetHowToPlayString(GetHowToPlay()) << std::endl
                  << "\tEnergy Cost: " << GetEnergyCost() << std::endl
                  << "\tEffect: " << GetEffect() << std::endl;
    }

    FDeck::FDeck(const std::string &FileName)
    {
        GenerateFromFile(FileName);
    }

    std::unique_ptr<FCard> FDeck::Draw()
    {
        if (IsEmpty())
        {
            return nullptr;
        }
        else
        {
            std::unique_ptr<FCard> Card = std::move(Deck.back());
            Deck.pop_back();
            return Card;
        }
    }

    void FDeck::AddCard(std::unique_ptr<FCard> &Card)
    {
        assert(Card);
        Deck.push_back(std::move(Card));
    }


    void FDeck::Print() const
    { 
        for (const auto& Card : Deck)
        {

        }
    }

    void FDeck::Shuffle()
    {
        std::shuffle(Deck.begin(), Deck.end(), std::default_random_engine(
                static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count())));
    }

    void FDeck::GenerateFromFile(const std::string &FileName)
    {
        std::ifstream InputStream;
        InputStream.open(FileName);

        if (InputStream.fail())
        {
            std::cout << "Could not open file: " << FileName << std::endl;
            return;
        }

        std::string Text;
        int Id = -1;
        std::string Name;
        EHowToPlay HowToPlay = EHowToPlay::None;
        int EnergyCost = -1;
        std::string Effect;

        while (!std::getline(InputStream, Text).eof())
        {
            if (Text.substr(0,3) == "Id:")
            {
                if (Id != -1 &&
                    !Name.empty() &&
                    HowToPlay != EHowToPlay::None &&
                    EnergyCost != -1 &&
                    !Effect.empty())
                {
                    Deck.push_back(
                        std::make_unique<FCard>(
                            Id, Name, HowToPlay, EnergyCost, Effect));
                    if (ParseIntFromChar(Text[3]) >= 0 &&
                        ParseIntFromChar(Text[4]) >= 0)
                    {
                        Id = 10 * ParseIntFromChar(Text[3]) +
                              1 * ParseIntFromChar(Text[4]);
                    }
                    else
                    {
                        Id = -1;
                    }
                    Name = "";
                    EnergyCost = -1;
                    HowToPlay = EHowToPlay::None;
                    Effect = "";
                }
                else if (Deck.empty())
                {
                    Id = 10 * ParseIntFromChar(Text[3]) +
                          1 * ParseIntFromChar(Text[4]);
                }
                else
                {
                    std::cout << "There was a problem creating card: "
                            << Name
                            << std::endl;
                    Id = -1;
                    Name = "";
                    EnergyCost = -1;
                    HowToPlay = EHowToPlay::None;
                    Effect = "";
                }
            }
            else if (Text.substr(0,5) == "Name:")
            {
                Name = Text.substr(5, Text.length() - 5);
            }
            else if (Text.substr(0, 10) == "HowToPlay:")
            {
                std::string temp = Text.substr(10, Text.length() - 10);
                if (temp == GetHowToPlayString(EHowToPlay::Discard))
                {
                    HowToPlay = EHowToPlay::Discard;
                }
                else if (temp == GetHowToPlayString(EHowToPlay::Keep))
                {
                    HowToPlay = EHowToPlay::Keep;
                }
                else
                {
                    HowToPlay = EHowToPlay::None;
                }
            }
            else if (Text.substr(0, 11) == "EnergyCost:")
            {
                EnergyCost = ParseIntFromChar(Text[11]);
            }
            else if (Text.substr(0, 7) == "Effect:")
            {
                Effect = Text.substr(7, Text.length() - 7);
            }
            else if (Text.empty())
            {
                continue;
            }
            else
            {
                std::cout << "Error: Invalid line detected: "
                          << Text
                          << std::endl;
                Id = -1;
                Name = "";
                EnergyCost = -1;
                HowToPlay = EHowToPlay::None;
                Effect = "";
            }
        }

        if (Id != -1 &&
            !Name.empty() &&
            HowToPlay != EHowToPlay::None &&
            EnergyCost != -1 &&
            !Effect.empty())
        {
            Deck.push_back(
                std::make_unique<FCard>(
                    Id, Name, HowToPlay, EnergyCost, Effect));
        }

        InputStream.close();
    }
}
