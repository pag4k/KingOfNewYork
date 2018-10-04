#include <string>
#include <vector>
#include "common.h"

struct FVertex;
class FDiceRoller;
class FCard;

class FPlayer
{
public:
    FPlayer(std::vector<std::string> *PlayerNames, bool bAvailableMonsters[]);
    ~FPlayer();

    bool GetCelebrity() const { return bCelebrity; }
    bool SetCelebrity(const bool bCelebrity) { this->bCelebrity = bCelebrity; }

    void RollDice();
    void ResolveDice();
    void Move();
    void BuyCards();

private :
    void EnterPlayerName(std::vector<std::string> *PlayerNames);
    void SelectMonster(bool AvailableMonsters[]);
    bool ResolveAttack(const int NumberOfDice);
    bool ResolveCelebrity(const int NumberOfDice);
    bool ResolveDestruction(const int NumberOfDice);
    bool ResolveEnergy(const int NumberOfDice);
    bool ResolveHeal(const int NumberOfDice);
    bool ResolveOuch(const int NumberOfDice);

    std::string PlayerName;
    EMonsterName MonsterName;
    FVertex *Position;
    FDiceRoller *DiceRoller;
    FDiceResult CurrentDiceResult;
    FTokenInventory TokenInventory;
    std::vector<FCard *> Cards;
    int EnergyCubes;
    int LifePoints;
    int VictoryPoints;
    bool bCelebrity;
    bool bStatueOfLiberty;

};