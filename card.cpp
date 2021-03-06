// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------


#include "card.h"
#include "helper.h"

namespace KingOfNewYork
{
    FDeck::FDeck(const std::string &FileName)
    {
        GenerateFromFile(FileName);
    }

    void FCard::Bought() const
    {
        std::shared_ptr<FCard> ShareCardCopyPointer = std::make_shared<FCard>(*this);
        ShareCardCopyPointer->ClearObserverListPointer();
        Notify(ShareCardCopyPointer, std::make_shared<FBoughtCardEvent>(EObserverEvent::BoughtCard, ""));
    }

    void FCard::Display() const
    {
        std::shared_ptr<FCard> ShareCardCopyPointer = std::make_shared<FCard>(*this);
        ShareCardCopyPointer->ClearObserverListPointer();
        Notify(ShareCardCopyPointer, std::make_shared<FDisplayCardEvent>(EObserverEvent::DisplayCard, ""));
    }

    void FCard::Use()
    {
        std::shared_ptr<FCard> ShareCardCopyPointer = std::make_shared<FCard>(*this);
        ShareCardCopyPointer->ClearObserverListPointer();
        Notify(ShareCardCopyPointer, std::make_shared<FUsedCardEvent>(EObserverEvent::UsedCard, ""));
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
                if (Id != -1 && !Name.empty() && HowToPlay != EHowToPlay::None && EnergyCost != -1 && !Effect.empty())
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
                EnergyCost = 10 * ParseIntFromChar(Text[11]) + 1 * ParseIntFromChar(Text[12]);
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

        if (Id != -1 && !Name.empty() && HowToPlay != EHowToPlay::None && EnergyCost != -1 && !Effect.empty())
        {
            Deck.push_back(std::make_unique<FCard>(Id, Name, HowToPlay, EnergyCost, Effect));
        }

        InputStream.close();
    }
}
