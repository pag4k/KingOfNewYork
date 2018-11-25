// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef CARD_H
#define CARD_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "common.h"
#include "subject.h"

namespace KingOfNewYork
{
    //This class will represent a single card in the game.
    class FCard: public FSubject
    {
    public:
        FCard() : Id(-1), Name(""), HowToPlay(EHowToPlay::None), EnergyCost(-1), Effect("") {}
        FCard(int Id, std::string &Name, EHowToPlay HowToPlay, int EnergyCost, std::string &Effect) :
            Id(Id), Name(std::move(Name)), HowToPlay(HowToPlay), EnergyCost(EnergyCost), Effect(std::move(Effect)) {}
        const int GetId() const { return Id; }
        const std::string &GetName() const { return Name; };
        EHowToPlay GetHowToPlay() const { return HowToPlay; };
        int GetEnergyCost() const { return EnergyCost; };
        const std::string &GetEffect() const { return Effect; };
        void Bought() const;
        void Display() const;
        void Use();
    private:
        int Id;
        std::string Name;
        EHowToPlay HowToPlay;
        int EnergyCost;
        std::string Effect;
    };

    //This class represents a deck of cards.
    //Note: The cards in it are unique_ptr and that they are handled as such.
    class FDeck{
    public:
        FDeck() = default;
        explicit FDeck(const std::string &FileName);
        void Shuffle();
        bool IsEmpty() const { return Deck.empty(); };
        std::unique_ptr<FCard> Draw();
        void AddCard(std::unique_ptr<FCard> &Card);
        std::vector<std::unique_ptr<FCard>> &GetCards() { return Deck; }
    private:
        void GenerateFromFile(const std::string &FileName);
        std::vector<std::unique_ptr<FCard>> Deck;
    };
}

#endif
