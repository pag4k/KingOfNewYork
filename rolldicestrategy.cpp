#include "rolldicestrategy.h"


namespace KingOfNewYork
{
    std::vector<EDiceFace> HumanRollDiceStrategy::Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount)
    {
        return DiceRoller.BeginRolling(DiceCount, RollCount);
    }

    std::vector<EDiceFace> AggressiveRollDiceStrategy::Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount)
    {

    }

    std::vector<EDiceFace> ModerateRollDiceStrategy::Execute(FDiceRoller &DiceRoller, const int DiceCount, const int RollCount)
    {

    }
}
