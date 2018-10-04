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
    void Shuffle();
    bool IsEmpty();
    FCard Draw();

private:
    void GenerateFromFile(std::string FileName);
    std::vector<FCard> Cards;
};