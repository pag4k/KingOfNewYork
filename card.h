#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <memory>
#include "common.h"

class FCard
{
public:
  FCard(int Id, std::string Name, EHowToPlay HowToPlay, int EnergyCost, std::string Effect);
  int GetId() const { return Id; }
  std::string GetName() const { return Name; };
  EHowToPlay GetHowToPlay() const { return HowToPlay; };
  int GetEnergyCost() const { return EnergyCost; };
  std::string GetEffect() const { return Effect; };

private:
  int Id;
  std::string Name;
  EHowToPlay HowToPlay;
  int EnergyCost;
  std::string Effect;
};

class FDeck{
public:
    FDeck();
    FDeck(std::string FileName);
    void Shuffle();
    int Size() const { return Deck.size(); };
    bool IsEmpty() const { return Deck.empty(); };
    std::unique_ptr<FCard> Draw();
    void Print() const;

private:
    void GenerateFromFile(std::string FileName);
    std::vector<std::unique_ptr<FCard>> Deck;
};

#endif
