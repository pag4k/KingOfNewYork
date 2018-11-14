// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include <algorithm>

#include "game.h"
#include "player.h"
#include "helper.h"

namespace KingOfNewYork
{
    FPlayer::FPlayer(
        std::vector<std::string> &PlayerNames,
        bool bAvailableMonsters[])
    {
        PlayerName = "";
        EnterPlayerName(PlayerNames);
        MonsterName = EMonsterName::None;
        SelectMonster(bAvailableMonsters);
        Borough = nullptr;
        LevelInCenter = 0;
        DiceRoller = FDiceRoller();


        for (int &Token : TokenInventory)
        {
            Token = 0;
        }

        bAlive = true;
        EnergyCubes = 0;
        LifePoints = MAXIMUM_LIFE_POINTS;
        VictoryPoints = 0;

        bCelebrity = false;
        bStatueOfLiberty = false;

        RollDiceStrategy = new AggressiveRollDiceStrategy();
        ResolveDiceStrategy = new AggressiveResolveDiceStrategy;
        MoveStrategy = new AggressiveMoveStrategy;
        BuyCardsStrategy = new AggressiveBuyCardsStrategy;
    }

    FPlayer::~FPlayer()
    {
        delete RollDiceStrategy;
        delete ResolveDiceStrategy;
        delete MoveStrategy;
        delete BuyCardsStrategy;

        RollDiceStrategy = nullptr;
        ResolveDiceStrategy = nullptr;
        MoveStrategy = nullptr;
        BuyCardsStrategy = nullptr;
    }

    const std::string FPlayer::GetPlayerAndMonsterNames()
    {
        return GetPlayerName() + "(" + GetMonsterNameString(GetMonsterName()) + ")";
    }

    void FPlayer::TakeTurn(FMap &Map, FGame &Game)
    {
        PrintHeader(GetPlayerAndMonsterNames() + " turn start");
        PrintLong();

        if (Borough->IsCenter())
        {
            std::cout << "Since you are in "
                      << CENTER_LEVEL_NAMES[LevelInCenter]
                      << " Manhattan, you earn "
                      << EarnVictoryPoints(CENTER_VICTORY_POINT_REWARDS[LevelInCenter])
                      << " and "
                      << EarnEnergyCubes(CENTER_ENERGY_CUBE_REWARDS[LevelInCenter])
                      << "."
                      << std::endl;
        }

        PrintHeader(GetPlayerAndMonsterNames() + " roll dice phase");
        std::vector<EDiceFace> DiceResult = DiceRoller.BeginRolling(BLACK_DICE_COUNT);

        RollDicePhase(BLACK_DICE_COUNT, MAXIMUM_ROLL, DiceResult);

        PrintHeader(GetPlayerAndMonsterNames() + " resolve dice phase");
        ResolveDicePhase(Game, Map, DiceResult);

        Game.CheckDeadPlayer();
        if (!bAlive)
        {
            PrintHeader(GetPlayerAndMonsterNames() + " died, so its turn is over");
            return;
        }

        PrintHeader(GetPlayerAndMonsterNames() + " move phase");
        MovePhase(Map);

        PrintHeader(GetPlayerAndMonsterNames() + " buy cards phase");
        BuyCardsPhase(Game);

        PrintHeader(GetPlayerAndMonsterNames() + " turn over");
    }

    std::vector<EDiceFace> FPlayer::RollStartDice(const int DiceCount)
    {
        std::vector<EDiceFace> DiceResult = DiceRoller.BeginRolling(DiceCount);
        DiceRoller.RollDice(DiceCount, DiceResult);
        return DiceResult;

    }

    void FPlayer::BuyCard(std::unique_ptr<FCard> Card)
    {
        Cards.push_back(std::move(Card));
    }

    void FPlayer::RollDicePhase(const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult)
    {
        RollDiceStrategy->Execute(DiceRoller, DiceCount, RollCount, OutDiceResult);
    }

    void FPlayer::ResolveDicePhase(FGame &Game, FMap &Map, std::vector<EDiceFace> &DiceResult)
    {
        ResolveDiceStrategy->Execute(Game, Map, shared_from_this(), DiceResult);
    }

    void FPlayer::MovePhase(FMap &Map)
    {
        MoveStrategy->Execute(Map, shared_from_this(), true, false);
    }

    void FPlayer::BuyCardsPhase(FGame &Game)
    {
        BuyCardsStrategy->Execute(Game, shared_from_this());
    }

    void FPlayer::PrintShort() const
    {
        std::cout   << "Name: " << PlayerName
                    << " Monster: " << GetMonsterNameString(MonsterName)
                    << std::endl;

    }

    void FPlayer::PrintLong() const
    {
        std::cout << "Current status: "
                  << std::endl;

        if (Borough)
        {
            if (Borough->IsCenter())
            {
                std::cout << "Position: "
                          << CENTER_LEVEL_NAMES[LevelInCenter]
                          << " Manhattan"
                          << std::endl;
            }
            else
            {
                std::cout << "Position: " << Borough->GetName() << std::endl;
            }
        }

        //DiceRoller.PrintRollHistory();

        std::cout << "Number of cards: " << Cards.size() << std::endl;
        for (const std::unique_ptr<FCard> &Card : Cards) {
            if (Card)
            {
                Card->Print();
            }
        }

        std::cout << "Tokens:" << std::endl;
        for (int i = 0; i < TOKEN_TYPE_COUNT; ++i)
        {
            std::cout << "\t-"
                    << GetTokenTypeString(ETokenType(i))
                    << ": "
                    << TokenInventory[i]
                    << std::endl;
        }

        std::cout << "Energy cubes: "
                << EnergyCubes
                << std::endl;

        std::cout << "Life points: "
                << LifePoints
                << std::endl;

        std::cout << "Victory points: "
                << VictoryPoints
                << std::endl;

        if (bCelebrity)
        {
            std::cout << GetMonsterNameString(MonsterName)
                    << "is a Superstar!"
                    << std::endl;
        }

        if (bStatueOfLiberty)
        {
            std::cout << GetMonsterNameString(MonsterName)
                    << " has help from the Status of Liberty!"
                    << std::endl;
        }

        std::cout << std::endl;
    }

    void FPlayer::EnterPlayerName(std::vector<std::string> &PlayerNames)
    {
        while (PlayerName.empty())
        {
            std::cout   << "Player "
                        << PlayerNames.size() + 1
                        << ", please enter your name:" << std::endl;
            std::cout << ">";
            bool bError = false;
            const std::string Input = InputString();
            if (Input.empty())
            {
                std::cout << "Invalid input, please try again."
                          << std::endl
                          << std::endl;
                continue;
            }
            for (const std::string &Name: PlayerNames)
            {
                if (Input == Name)
                {
                    std::cout << "Name already taken, please try again."
                              << std::endl
                              << std::endl;
                    bError = true;
                    break;
                }
            }
            if (!bError)
            {
                PlayerName = Input;
                PlayerNames.push_back(Input);
            }
        }
        std::cout << std::endl;
    }

    void FPlayer::SelectMonster(bool bAvailableMonsters[])
    {
        while (MonsterName == EMonsterName::None)
        {
            std::cout   << PlayerName
                        << ", please select your monster:" << std::endl;
            for (int i = 0; i < MONSTER_COUNT; ++i)
            {
                if (bAvailableMonsters[i])
                {
                    std::cout << (i + 1)
                              << " "
                              << GetMonsterNameString(
                                    static_cast<EMonsterName>(i))
                              << std::endl;
                }
            }
            std::cout << ">";
            const int Input = InputSingleDigit();
            if (1 <= Input &&
                Input <= MONSTER_COUNT &&
                bAvailableMonsters[Input - 1])
            {
                MonsterName = static_cast<EMonsterName>(Input - 1);
                bAvailableMonsters[Input - 1] = false;
            }
            else
            {
                std::cout << "Invalid input, please try again."
                          << std::endl
                          << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void FPlayer::SelectStartingLocation(FMap &Map)
    {
        std::cout << GetPlayerAndMonsterNames()
                  << ", please select your starting borough:"
                  << std::endl;

        Move(Map, true);
    }


    void FPlayer::TakeDamage(FGame &Game, const int Damage)
    {
        assert(Damage > 0);
        assert(bAlive);
        std::cout << GetPlayerAndMonsterNames()
                   << " loses "
                   << EarnLifePoints(-Damage)
                   << "."
                   << std::endl;
        if (LifePoints == 0)
        {
            bAlive = false;
            bStatueOfLiberty = false;
            bCelebrity = false;
            std::cout << GetPlayerAndMonsterNames()
                      << " died!"
                      << std::endl
                      << std::endl;
        }
    }

    void FPlayer::Move(FMap &Map, bool bOnlyStartingLocation)
    {
        MoveStrategy->Execute(Map, shared_from_this(), false, bOnlyStartingLocation);
    }


    const std::string FPlayer::EarnMonsterResources(const EMonsterResource MonsterResource, const int Number)
    {
        assert(Number != 0);
        switch (MonsterResource)
        {
            case EMonsterResource::EnergyCube:
                return EarnEnergyCubes(Number);
            case EMonsterResource::LifePoint:
                return EarnLifePoints(Number);
            case EMonsterResource::VictoryPoint:
                return EarnVictoryPoints(Number);
        }
        assert(true);
        return "ERROR";
    }

    const std::string FPlayer::EarnEnergyCubes(const int Number)
    {
        assert(Number != 0);
        EnergyCubes += Number;
        return std::to_string(std::abs(Number)) + " Energy Cubes (new total: " + std::to_string(EnergyCubes) + ")";
    }

    const std::string FPlayer::EarnLifePoints(const int Number)
    {
        assert(Number != 0);
        LifePoints += Number;
        LifePoints = std::clamp(LifePoints, 0, MAXIMUM_LIFE_POINTS);
        return std::to_string(std::abs(Number)) + " Life Points (new total: " + std::to_string(LifePoints) + ")";
    }

    const std::string FPlayer::EarnVictoryPoints(const int Number)
    {
        assert(Number != 0);
        VictoryPoints += Number;
        return std::to_string(std::abs(Number))+ " Victory Points (new total: " + std::to_string(VictoryPoints) + ")";
    }
}
