#include <string>
#include <vector>
#include "common.h"

struct FVertex;
class FDiceRoller;
class FCard;

class FPlayer
{
public:
  FPlayer(std::vector<std::string> *PlayerNames, bool bAvailableMonsters[], std::vector<FVertex *> &Vertices);
  ~FPlayer();

  std::string GetPlayerName() const { return PlayerName; }
  EMonsterName GetMonsterName() const { return MonsterName; }
  bool GetCelebrity() const { return bCelebrity; }
  bool SetCelebrity(const bool bCelebrity) { this->bCelebrity = bCelebrity; }

  void RollDice();
  void ResolveDice();
  void Move();
  void BuyCards();

  void PrintShort();
  void PrintLong();

private :
    void EnterPlayerName(std::vector<std::string> *PlayerNames);
    void SelectMonster(bool AvailableMonsters[]);
    void SelectStartingLocation(std::vector<FVertex *> &Vertices);
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
    std::vector<EDiceFace> CurrentDiceResult;
    int TokenInventory[NUMBER_OF_TOKEN_TYPE];
    std::vector<FCard *> Cards;
    int EnergyCubes;
    int LifePoints;
    int VictoryPoints;

    bool bCelebrity;
    bool bStatueOfLiberty;

    //TODO: ADD CARD BUYING CODE.
};