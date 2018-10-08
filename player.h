#include <string>
#include <vector>
#include <memory>
#include "common.h"
#include "diceroller.h"
#include "borough.h"
#include "map.h"

class FDiceRoller;
class FCard;

class FPlayer : public std::enable_shared_from_this<FPlayer>
{
public:
  FPlayer(std::vector<std::string> &PlayerNames, bool bAvailableMonsters[]);
  ~FPlayer();

  void SelectStartingLocation(FMap &Map);

  std::string GetPlayerName() const { return PlayerName; }
  EMonsterName GetMonsterName() const { return MonsterName; }
  bool GetCelebrity() const { return bCelebrity; }
  void SetCelebrity(const bool bCelebrity) { this->bCelebrity = bCelebrity; }

  void RollDice();
  void ResolveDice();
  void Move();
  void BuyCards();

  void PrintShort();
  void PrintLong();

private :
    void EnterPlayerName(std::vector<std::string> &PlayerNames);
    void SelectMonster(bool AvailableMonsters[]);
    bool ResolveAttack(const int NumberOfDice);
    bool ResolveCelebrity(const int NumberOfDice);
    bool ResolveDestruction(const int NumberOfDice);
    bool ResolveEnergy(const int NumberOfDice);
    bool ResolveHeal(const int NumberOfDice);
    bool ResolveOuch(const int NumberOfDice);

    std::string PlayerName;
    EMonsterName MonsterName;
    std::shared_ptr<FBorough> Position;
    FDiceRoller DiceRoller;
    std::vector<EDiceFace> CurrentDiceResult;
    int TokenInventory[NUMBER_OF_TOKEN_TYPE];
    std::vector<std::unique_ptr<FCard>> Cards;
    int EnergyCubes;
    int LifePoints;
    int VictoryPoints;

    bool bCelebrity;
    bool bStatueOfLiberty;

    //TODO: ADD CARD BUYING CODE.
};