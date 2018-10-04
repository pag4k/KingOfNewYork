#include <fstream>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include "card.h"
#include "helper.h"

FCard::FCard(std::string Name, int EnergyCost, EHowToPlay HowToPlay, std::string Effect)
{
    this->Name = Name;
    this->EnergyCost = EnergyCost;
    this->HowToPlay = HowToPlay;
    this->Effect = Effect;
}

FDeck::FDeck()
{
    GenerateFromFile("cards.txt");
}

bool FDeck::IsEmpty()
{
    return Deck.empty();
}

FCard *FDeck::Draw()
{
    assert(!IsEmpty());
    FCard *Card = Deck.back();
    Deck.pop_back();
    return Card;
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
    std::string Name = "";
    int EnergyCost = -1;
    EHowToPlay HowToPlay = EHowToPlay::None;
    std::string Effect = "";
    while (!std::getline(InputStream, Text).eof())
    {
        if (Text.substr(0,5) == "Name:")
        {
            if (Name != "" &&
                EnergyCost != -1 &&
                HowToPlay != EHowToPlay::None &&
                Effect != "")
            {
                Deck.push_back(new FCard(Name, EnergyCost, HowToPlay, Effect));
                Name = Text.substr(5, Text.length() - 5);
                EnergyCost = -1;
                HowToPlay = EHowToPlay::None;
                Effect = "";
            }
            else if (Deck.empty())
            {
                Name = Text.substr(5, Text.length() - 5);
            }
            else
            {
                std::cout   << "There was a problem creating card: "
                            << Name
                            << std::endl;
            }

        }
        else if (Text.substr(0, 11) == "EnergyCost:")
        {
            EnergyCost = ParseIntFromChar(Text[11]);
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

    if (Name != "" &&
        EnergyCost != -1 &&
        HowToPlay != EHowToPlay::None &&
        Effect != "")
    {
        Deck.push_back(new FCard(Name, EnergyCost, HowToPlay, Effect));
    }

    InputStream.close();
}
