#include "diceroller.h"

namespace KingOfNewYork
{
    class IRollDiceStrategy
    {
    public:
        virtual FDiceResult RollDice(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount) = 0;
      //virtual void ResolveDice() = 0;
      //virtual void Move() = 0;
      //virtual void BuyCards() = 0;
    };

    class HumanRollDice : public IRollDiceStrategy
    {
    public:
        FDiceResult RollDice(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount);
    };

    class AggressiveRollDice : public IRollDiceStrategy
    {
    public:
        FDiceResult RollDice(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount);
    };

    class ModerateRollDice : public IRollDiceStrategy
    {
    public:
        FDiceResult RollDice(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount);
    };

}
