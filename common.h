// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef COMMON_H
#define COMMON_H

#include <string>

namespace KingOfNewYork
{
    const std::string MAP_PATH = "map/";

    //This files contains contants, enums declaration and functions.
    const int MINIMUM_PLAYER = 2;
    const int MAXIMUM_PLAYER = 6;

    const int MAXIMUM_PLAYERS_IN_BOROUGH = 2;

    const int MAXIMUM_MONSTERS_IN_CENTER = 1;
    const int LEVEL_IN_CENTER_COUNT = 3;
    const std::string CENTER_LEVEL_NAMES[LEVEL_IN_CENTER_COUNT+1] =
            {"INVALID", "Lower", "Midtown", "Upper"};
    const int ENTER_CENTER_VICTORY_POINT_REWARD = 1;
    const int CENTER_VICTORY_POINT_REWARDS[LEVEL_IN_CENTER_COUNT+1] = {0, 1, 2, 2};
    const int CENTER_ENERGY_CUBE_REWARDS[LEVEL_IN_CENTER_COUNT+1] = {0, 1, 1, 2};

    const int TILESTACK_IN_BOROUGH_COUNT = 3;

    const int BLACK_DICE_COUNT = 6;
    const int GREEN_DICE_COUNT = 2;
    const int MAXIMUM_ROLL = 3;

    const int ENERGY_CUBE_FOR_NEW_CARDS_COUNT = 2;

    const int MONSTER_COUNT = 6;
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

    const int FACE_ON_DICE_COUNT = 6;
    const int DICE_FOR_CELEBRITY_COUNT = 3;
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
    const int TOKEN_TYPE_COUNT = 4;

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

    const int MAXIMUM_TILE_DURABILITY = 4;
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

    int const MAXIMUM_ENERGY_CUBES = 40; //TODO: Get the right amount.
    int const MAXIMUM_LIFE_POINTS = 10;
    int const VICTORY_POINTS_TO_WIN_COUNT = 20;
    int const STATUS_OF_LIBERTY_VICTORY_POINTS = 3;
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