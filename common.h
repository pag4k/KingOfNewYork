#ifndef COMMON_H
#define COMMON_H

#include <string>

const int MINIMUM_NUMBER_OF_PLAYERS = 2;
const int MAXIMUM_NUMBER_OF_PLAYERS = 6;
const int NUMBER_OF_FACES_ON_DICE = 6;
const int NUMBER_OF_MONSTERS = 6;

const int NUMBER_OF_DICE = 6;
const int NUMBER_OF_ROLLS = 3;

enum class EMonsterName
{
    None = -1,
    CaptainFish = 0,
    Draconis = 1,
    Kong = 2,
    Mantis = 3,
    Rob = 4,
    Sherrif = 5
};

enum class EDiceFace
{
    None = -1,
    Attack = 0,
    Celebrity = 1,
    Destruction = 2,
    Energy = 3,
    Heal = 4,
    Ouch = 5
};

struct FDiceResult
{
    EDiceFace Dice[NUMBER_OF_FACES_ON_DICE];
};

std::string GetMonsterName(EMonsterName MonsterName);
std::string GetFaceName(EDiceFace Face);

#endif