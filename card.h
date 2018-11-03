#ifndef CARD_H
#define CARD_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "common.h"

namespace KingOfNewYork
{
    //This class will represent a single card in the game.
    class FCard
    {
    public:
        FCard() :
            Id(-1),
            Name(""),
            HowToPlay(EHowToPlay::None),
            EnergyCost(-1),
            Effect("") {}
        FCard(int Id, std::string &Name, EHowToPlay HowToPlay, int EnergyCost, std::string &Effect) :
            Id(Id),
            Name(std::move(Name)),
            HowToPlay(HowToPlay),
            EnergyCost(EnergyCost),
            Effect(std::move(Effect)) {}
        const int GetId() const { return Id; }
        const std::string GetName() const { return Name; };
        const EHowToPlay GetHowToPlay() const { return HowToPlay; };
        const int GetEnergyCost() const { return EnergyCost; };
        const std::string GetEffect() const { return Effect; };
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
        FDeck() = default {}
        explicit FDeck(const std::string &FileName);
        void Shuffle();
        const unsigned int Size() const { return (unsigned int)Deck.size(); };
        const bool IsEmpty() const { return Deck.empty(); };
        std::unique_ptr<FCard> Draw();
        void Print() const;
    private:
        void GenerateFromFile(const std::string &FileName);
        std::vector<std::unique_ptr<FCard>> Deck;
    };
}

#endif
