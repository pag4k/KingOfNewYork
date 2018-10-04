#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include "common.h"

class FCard
{
public:
    FCard(std::string Name, int EnergyCost, EHowToPlay HowToPlay, std::string Effect);
    std::string GetName() { return Name; };
    int GetEnergyCost() { return EnergyCost; };
    EHowToPlay GetHowToPlay() { return HowToPlay; };
    std::string GetEffect() { return Effect; };

  private:
    std::string Name;
    int EnergyCost;
    EHowToPlay HowToPlay;
    std::string Effect;
};

class FDeck{
public:
    FDeck();
    FDeck(std::string FileName);
    void Shuffle();
    int Size() const { return Deck.size(); };
    bool IsEmpty() const { return Deck.empty(); };
    FCard *Draw();
    void Print() const;

private:
    void GenerateFromFile(std::string FileName);
    std::vector<FCard *> Deck;
};

#endif
