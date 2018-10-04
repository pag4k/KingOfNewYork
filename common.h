#ifndef COMMON_H
#define COMMON_H

#include <string>

const int MINIMUM_NUMBER_OF_PLAYERS = 2;
const int MAXIMUM_NUMBER_OF_PLAYERS = 6;

const int NUMBER_OF_DICE = 6;
const int NUMBER_OF_ROLLS = 3;

const int NUMBER_OF_MONSTERS = 6;
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
std::string GetMonsterNameString(EMonsterName MonsterName);

const int NUMBER_OF_FACES_ON_DICE = 6;
const int NUMBER_OF_DICE_FOR_CELEBRITY = 3;
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

std::string GetDiceFaceString(EDiceFace Face);

struct FDiceResult
{
    EDiceFace Dice[NUMBER_OF_FACES_ON_DICE];
};

const int NUMBER_OF_TOKENS = 4;
enum class ETokenType
{
    //None = -1,
    Carapace = 0,
    Jinx = 1,
    Souvenir = 2,
    Web = 3
};
std::string GetTokenTypeString(ETokenType TokenType);

struct FTokenInventory
{
    int Token[NUMBER_OF_TOKENS];
};

const int MAXIMUM_AVAILABLE_CARDS = 3; 
enum class EHowToPlay
{
    None = -1,
    Keep = 0,
    Discard = 1
};
std::string GetHowToPlayString(EHowToPlay HowToPlay);

enum class ETileType
{
    None = -1,
    //Energy
    PowerPlant = 0,
    Jet = 1,
    //Heal
    Hospital = 2,
    Infantry = 3,
    //Victory Points
    HighRise = 4,
    Tank = 5
};
std::string GetTileTypeString(ETileType TileType);

int const NUMBER_OF_MONSTER_RESOURCES = 3;
int const MAXIMUM_LIFE_POINTS = 10;
int const NUMBER_VICTORY_POINTS_TO_WIN = 20;
enum class EMonsterResource
{
    None = -1,
    EnergyCube = 0,
    LifePoint = 1,
    VictoryPoint = 2
};
std::string GetMonsterResourceString(EMonsterResource MonsterResource);

#endif