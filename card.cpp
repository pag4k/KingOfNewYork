#include <fstream>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include "card.h"
#include "helper.h"

FCard::FCard(int Id, std::string Name, EHowToPlay HowToPlay, int EnergyCost, std::string Effect)
{
    this->Id = Id;
    this->Name = Name;
    this->HowToPlay = HowToPlay;
    this->EnergyCost = EnergyCost;
    this->Effect = Effect;
}

FDeck::FDeck()
{

}

FDeck::FDeck(std::string FileName)
{
    GenerateFromFile(FileName);
}

std::unique_ptr<FCard> FDeck::Draw()
{
    assert(!IsEmpty());
    std::unique_ptr<FCard> Card = std::move(Deck.back());
    Deck.pop_back();
    return Card;
}

void FDeck::Print() const
{
    for (const auto& Card : Deck)
    {
        std::cout << "Id: " << Card->GetId() << std::endl
                  << "Name: " << Card->GetName() << std::endl
                  << "How to Play: " << GetHowToPlayString(Card->GetHowToPlay()) << std::endl
                  << "Energy Cost: " << Card->GetEnergyCost() << std::endl
                  << "Effect: " << Card->GetEffect() << std::endl;
    }
}

void FDeck::Shuffle()
{
    std::random_shuffle(Deck.begin(), Deck.end());
}

void FDeck::GenerateFromFile(std::string FileName)
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
    std::string Name = "";
    EHowToPlay HowToPlay = EHowToPlay::None;
    int EnergyCost = -1;
    std::string Effect = "";
    while (!std::getline(InputStream, Text).eof())
    {
        if (Text.substr(0,3) == "Id:")
        {
            if (Id != -1 &&
                Name != "" &&
                HowToPlay != EHowToPlay::None &&
                EnergyCost != -1 &&
                Effect != "")
            {
                Deck.push_back(std::make_unique<FCard>(Id, Name, HowToPlay, EnergyCost, Effect));
                if (ParseIntFromChar(Text[3]) >= 0 && ParseIntFromChar(Text[4]) >= 0)
                {
                    Id = 10 * ParseIntFromChar(Text[3]) + 1 * ParseIntFromChar(Text[4]);
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
                Id = 10 * ParseIntFromChar(Text[3]) + 1 * ParseIntFromChar(Text[4]);
            }
            else
            {
                std::cout << "There was a problem creating card: "
                          << Name
                          << std::endl;
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
        else if (Text == "")
        {
            continue;
        }
        else
        {
            //INVALID
        }
    }

    if (Id != -1 &&
        Name != "" &&
        HowToPlay != EHowToPlay::None &&
        EnergyCost != -1 &&
        Effect != "")
    {
        Deck.push_back(std::make_unique<FCard>(Id, Name, HowToPlay, EnergyCost, Effect));
    }

    InputStream.close();
}
