#include <string>
#include <vector>
#include "common.h"

struct FVertex;
class FDiceRoller;

class FPlayer
{
public:
  FPlayer(std::vector<std::string> *PlayerNames, bool bAvailableMonsters[]);
  ~FPlayer();

  void RollDice();
  void ResolveDice();
  void Move();

private:
  void EnterPlayerName(std::vector<std::string> *PlayerNames);
  void SelectMonster(bool AvailableMonsters[]);

  std::string PlayerName;
  EMonsterName MonsterName;
  FVertex *Position;
  FDiceRoller *DiceRoller;
  FDiceResult CurrentDiceResult;

};