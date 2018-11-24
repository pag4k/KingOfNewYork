// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "playercontroller.h"

#include <iostream>
#include <algorithm>

#include "game.h"
#include "player.h"
#include "helper.h"
#include "diceroller.h"
#include "rolldicestrategy.h"
#include "resolvedicestrategy.h"
#include "movestrategy.h"
#include "buycardsstrategy.h"

namespace KingOfNewYork
{
    FPlayerController::FPlayerController(std::unordered_set<std::string> &PlayerNames, std::vector<bool> &AvailableMonsters) {
        Name = EnterPlayerName(PlayerNames);
        EMonsterName MonsterName = SelectMonster(AvailableMonsters);
        SelectStrategy();
        DiceRoller = std::make_shared<FDiceRoller>();
        Player = std::make_shared<FPlayer>(MonsterName);
    }

    FPlayerController::~FPlayerController()
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

    void FPlayerController::TakeTurn(FMap &Map, FGame &Game)
    {
        Player->SetTurnPhase(ETurnPhase::StartTurn);
        StartPhase();

        Player->SetTurnPhase(ETurnPhase::RollDice);
        std::vector<EDiceFace> DiceResult = DiceRoller->BeginRolling(BLACK_DICE_COUNT);
        RollDicePhase(BLACK_DICE_COUNT, MAXIMUM_ROLL, DiceResult);

        Player->SetTurnPhase(ETurnPhase::ResolveDice);
        ResolveDicePhase(Game, Map, DiceResult);

        Game.CheckDeadPlayer();
        if (!Player->IsAlive())
        {
            Player->Died(Game);
            Player == nullptr;
            return;
        }

        Player->SetTurnPhase(ETurnPhase::Move);
        MovePhase(Map);

        Player->SetTurnPhase(ETurnPhase::BuyCards);
        BuyCardsPhase(Game);

        Player->SetTurnPhase(ETurnPhase::EndTurn);
        Player->SetTurnPhase(ETurnPhase::None);
    }

    std::vector<EDiceFace> FPlayerController::RollStartDice(const int DiceCount)
    {
        std::vector<EDiceFace> DiceResult = DiceRoller->BeginRolling(DiceCount);
        DiceRoller->RollDice(DiceCount, DiceResult);
        return DiceResult;

    }

    void FPlayerController::Move(FMap &Map, bool bMovePhase, bool bOnlyStartingLocation)
    {
        const auto OldBorough = Player->GetBorough();
        const int OldLevelInCenter = Player->GetLevelInCenter();
        MoveStrategy->Execute(Map, Player, bMovePhase, bOnlyStartingLocation);
        Player->Move(OldBorough, OldLevelInCenter);
    }

    void FPlayerController::SelectStartingLocation(FMap &Map)
    {
        Move(Map, false, true);
    }

    std::string FPlayerController::EnterPlayerName(std::unordered_set<std::string> &PlayerNames)
    {
        std::string EnteredName = "";
        while (EnteredName.empty())
        {
            PrintNormal("Player " + std::to_string(PlayerNames.size() + 1) + ", please enter your name:");
            PrintChar('>');
            const std::string Input = InputString();
            if (Input.empty())
            {
                PrintNormal("Invalid input, please try again.");
                PrintNormal("");
                continue;
            }
            if (PlayerNames.count(Input))
            {
                PrintNormal("Name already taken, please try again.");
                PrintNormal("");
            }
            else
            {
                EnteredName = Input;
                PlayerNames.insert(Input);
            }
        }
        PrintNormal("");
        return EnteredName;
    }


    EMonsterName FPlayerController::SelectMonster(std::vector<bool> &AvailableMonsters)
    {
        EMonsterName MonsterName = EMonsterName::None;
        while (MonsterName == EMonsterName::None)
        {
            PrintNormal(Name + ", please select your monster:");
            for (int i = 0; i < AvailableMonsters.size(); ++i)
            {
                if (AvailableMonsters[i])
                {
                    PrintList(i + 1, GetMonsterNameString(static_cast<EMonsterName>(i)));
                }
            }
            PrintChar('>');
            const int Input = InputSingleDigit() - 1;
            if (0 <= Input && Input < AvailableMonsters.size() && AvailableMonsters[Input])
            {
                MonsterName = static_cast<EMonsterName>(Input);
                AvailableMonsters[Input] = false;
            }
            else
            {
                PrintNormal("Invalid input, please try again.");
                PrintNormal("");
            }
        }
        PrintNormal("");
        return MonsterName;
    }

    void FPlayerController::SelectStrategy()
    {
        while (RollDiceStrategy == nullptr)
        {
            PrintNormal(Name + ", please select your strategy:");
            PrintList(1, "Human control");
            PrintList(2, "Aggressive AI");
            PrintList(3, "Moderate AI");
            PrintChar('>');
            const int Input = InputSingleDigit() - 1;
            if (0 <= Input && Input < 3)
            {
                switch (Input)
                {
                    case 1:
                        RollDiceStrategy = new HumanRollDiceStrategy();
                        ResolveDiceStrategy = new HumanResolveDiceStrategy;
                        MoveStrategy = new HumanMoveStrategy;
                        BuyCardsStrategy = new HumanBuyCardsStrategy;
                        break;
                    case 2:
                        RollDiceStrategy = new AggressiveRollDiceStrategy();
                        ResolveDiceStrategy = new AggressiveResolveDiceStrategy;
                        MoveStrategy = new AggressiveMoveStrategy;
                        BuyCardsStrategy = new AggressiveBuyCardsStrategy;
                        break;
                    case 3:
                        RollDiceStrategy = new ModerateRollDiceStrategy();
                        ResolveDiceStrategy = new ModerateResolveDiceStrategy;
                        MoveStrategy = new ModerateMoveStrategy;
                        BuyCardsStrategy = new ModerateBuyCardsStrategy;
                        break;
                }
            }
            else
            {
                PrintNormal("Invalid input, please try again.");
                PrintNormal("");
            }
        }
        PrintNormal("");
    }

    void FPlayerController::StartPhase()
    {
        Player->SetDestroyedBuilding(false);
        if (Player->GetBorough()->IsCenter())
        {
            Player->ChangeVictoryPoints(CENTER_VICTORY_POINT_REWARDS[Player->GetLevelInCenter()]);
            Player->ChangeEnergyCubes(CENTER_ENERGY_CUBE_REWARDS[Player->GetLevelInCenter()]);
        }

        if (Player->GetBorough()->GetName() == "Queens" && Player->UseCard(12))
        {
            Player->ChangeEnergyCubes(1);
            Player->ChangeLifePoints(1);
        }

        if (Player->IsCelebrity() && Player->UseCard(36))
        {
            Player->ChangeEnergyCubes(1);
        }

        if (Player->UseCard(39))
        {
            Player->ChangeLifePoints(1);
        }
    }

    void FPlayerController::RollDicePhase(const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult)
    {
        RollDiceStrategy->Execute(DiceRoller, Player, DiceCount, RollCount, OutDiceResult);
    }

    void FPlayerController::ResolveDicePhase(FGame &Game, FMap &Map, std::vector<EDiceFace> &DiceResult)
    {
        ResolveDiceStrategy->Execute(Game, Map, Player, DiceResult);
    }

    void FPlayerController::MovePhase(FMap &Map)
    {
        Move(Map, true, false);
    }

    void FPlayerController::BuyCardsPhase(FGame &Game)
    {
        BuyCardsStrategy->Execute(Game, Player);
    }
}