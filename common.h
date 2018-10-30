// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef COMMON_H
#define COMMON_H

#include <string>

namespace KingOfNewYork
{
    const std::string MAP_PATH = "map/";

    //This files contains contants, enums declaration and functions.
    const int MINIMUM_NUMBER_OF_PLAYERS = 2;
    const int MAXIMUM_NUMBER_OF_PLAYERS = 6;

    const int MAXIMUM_PLAYERS_IN_BOROUGH = 2;

    //TODO: I think part of the code assumes it is 2.
    const int MAXIMUM_PLAYERS_IN_MANHATTAN = 2;

    const int NUMBER_OF_TILESTACKS_IN_BOROUGH = 3;

    const int NUMBER_OF_DICE = 6;
    const int MAXIMUM_ROLL_COUNT = 3;

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
    const std::string GetMonsterNameString(const EMonsterName MonsterName);

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

    const std::string GetDiceFaceString(const EDiceFace Face);

    const int STARTING_TOKENS = 13;
    const int NUMBER_OF_TOKEN_TYPE = 4;

    enum class ETokenType {
        //None = -1,
        Carapace = 0,
        Jinx = 1,
        Souvenir = 2,
        Web = 3
    };
    const std::string GetTokenTypeString(const ETokenType TokenType);

    const int MAXIMUM_AVAILABLE_CARDS = 3; 
    enum class EHowToPlay
    {
        None = -1,
        Keep = 0,
        Discard = 1
    };
    const std::string GetHowToPlayString(const EHowToPlay HowToPlay);

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
    const std::string GetTileTypeString(const ETileType TileType);

    int const NUMBER_OF_MONSTER_RESOURCES = 3;
    int const MAXIMUM_ENERGY_CUBES = 40; //TODO: Get the right amount.
    int const MAXIMUM_LIFE_POINTS = 10;
    int const NUMBER_VICTORY_POINTS_TO_WIN = 20;
    enum class EMonsterResource
    {
        None = -1,
        EnergyCube = 0,
        LifePoint = 1,
        VictoryPoint = 2
    };
    const std::string GetMonsterResourceString(
        const EMonsterResource MonsterResource);
}

#endif