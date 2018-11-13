// ----------------------------------------------------------------------------
// COMP345 Assignment 2
// Due date: November 4, 2018
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

        RollDiceStrategy = new HumanRollDiceStrategy();
        ResolveDiceStrategy = new HumanResolveDiceStrategy;
        MoveStrategy = new HumanMoveStrategy;
        BuyCardsStrategy = new HumanBuyCardsStrategy;
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
        RollDice(BLACK_DICE_COUNT, MAXIMUM_ROLL);

        PrintHeader(GetPlayerAndMonsterNames() + " resolve dice phase");
        ResolveDice(Game, Map);

        Game.CheckDeadPlayer();
        if (!bAlive)
        {
            PrintHeader(GetPlayerAndMonsterNames() + " died, so its turn is over");
            return;
        }

        PrintHeader(GetPlayerAndMonsterNames() + " move phase");
        Move(Map);

        PrintHeader(GetPlayerAndMonsterNames() + " buy cards phase");
        BuyCards(Game);

        PrintHeader(GetPlayerAndMonsterNames() + " turn over");
    }

    void FPlayer::BuyCard(std::unique_ptr<FCard> Card)
    {
        Cards.push_back(std::move(Card));
    }

    void FPlayer::RollDice(const int DiceCount, const int RollCount)
    {
        CurrentDiceResult = RollDiceStrategy->Execute(DiceRoller, DiceCount, RollCount);
    }

    const int FPlayer::GetAttackCount() const
    {
        assert(!CurrentDiceResult.empty());
        int AttackCount = 0;
        for (EDiceFace DiceFace : CurrentDiceResult)
        {
            if (DiceFace == EDiceFace::Attack)
            {
                AttackCount++;
            }
        }
        return AttackCount;
    }

    void FPlayer::ResolveDice(FGame &Game, FMap &Map)
    {
        ResolveDiceStrategy->Execute(Game, Map, shared_from_this());
    }

    void FPlayer::Move(FMap &Map)
    {
        MoveStrategy->Execute(Map, shared_from_this());
    }

    void FPlayer::BuyCards(FGame &Game)
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
        SelectBorough(Map, true, false);

    }

    void FPlayer::SelectBorough(FMap &Map, const bool bOnlyStartingLocation, const bool bIncludeCenter)
    {
        int bDone = false;
        while (!bDone)
        {
            for (int i = 0; i < Map.BoroughCount(); ++i)
            {
                std::shared_ptr<FBorough> CurrentBorough = Map.GetBorough(i);
                const std::vector<std::shared_ptr<FPlayer>> &CurrentPlayers =
                        CurrentBorough->GetConstPlayers();
                const int Offset = CurrentBorough == Borough ? 1 : 0;
                if (CurrentPlayers.size() - Offset < MAXIMUM_PLAYERS_IN_BOROUGH &&
                        (!bOnlyStartingLocation || CurrentBorough->IsStartingLocation()) &&
                        (!CurrentBorough->IsCenter() || bIncludeCenter))
                {
                    std::cout << (i + 1)
                              << ". "
                              << CurrentBorough->GetName();
                    if (CurrentPlayers.size() > 0)
                    {
                        std::cout << " (already there: ";
                        for (int j = 0; j < CurrentPlayers.size(); ++j)
                        {
                            if (CurrentPlayers[j] == shared_from_this())
                            {
                                std::cout << "you";
                            }
                            else
                            {
                                std::cout << CurrentPlayers[j]->GetPlayerAndMonsterNames();
                            }
                            std::cout << (j + 1 != CurrentPlayers.size() ? ", " : ")");
                        }
                    }
                    std::cout << std::endl;
                }
            }
            std::cout << ">";
            const int Input = InputSingleDigit();
            std::cout << std::endl;

            if (1 <= Input && Input <= Map.BoroughCount())
            {
                std::shared_ptr<FBorough> SelectedBorough = Map.GetBorough(Input - 1);
                const std::vector<std::shared_ptr<FPlayer>> &SelectedPlayers =
                        SelectedBorough->GetConstPlayers();
                if (SelectedPlayers.size() < MAXIMUM_PLAYERS_IN_BOROUGH &&
                        (!bOnlyStartingLocation || SelectedBorough->IsStartingLocation()))
                {
                    bDone = true;
                    MoveTo(SelectedBorough);
                }
                else
                {
                    std::cout << "Invalid borough, please try again."
                              << std::endl
                              << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid input, please try again."
                          << std::endl
                          << std::endl;
            }
        }
    }

    void FPlayer::MoveTo(std::shared_ptr<FBorough> NewBorough)
    {
        assert(NewBorough);
        if (Borough == NewBorough)
        {
            return;
        }
        //Removing player from previous borough list.
        if (Borough)
        {
            bool Erased = false;
            for (auto it = Borough->GetConstPlayers().begin();
                 it != Borough->GetConstPlayers().end();
                 ++it)
            {
                if (*it == shared_from_this())
                {
                    Borough->GetMutablePlayers().erase(it);
                    Erased = true;
                    break;
                }
            }
            assert(Erased);
        }
        //Setting player position to selected borough.
        Borough = NewBorough;
        //Put player in the borough player list.
        Borough->GetMutablePlayers().push_back(shared_from_this());
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
