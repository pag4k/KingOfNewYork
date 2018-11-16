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
#include "observerevent.h"

namespace KingOfNewYork
{
    FPlayer::FPlayer(std::vector<std::string> &PlayerNames, bool bAvailableMonsters[])
    {
        PlayerName = "";
        EnterPlayerName(PlayerNames);
        MonsterName = EMonsterName::None;
        SelectMonster(bAvailableMonsters);
        SelectStrategy();
        TurnPhase = ETurnPhase ::None;
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
        SetTurnPhase(ETurnPhase::StartTurn);
        StartPhase();

        SetTurnPhase(ETurnPhase::RollDice);
        std::vector<EDiceFace> DiceResult = DiceRoller.BeginRolling(BLACK_DICE_COUNT);
        RollDicePhase(BLACK_DICE_COUNT, MAXIMUM_ROLL, DiceResult);

        SetTurnPhase(ETurnPhase::ResolveDice);
        ResolveDicePhase(Game, Map, DiceResult);

        Game.CheckDeadPlayer();
        if (!bAlive)
        {
            return;
        }

        SetTurnPhase(ETurnPhase::Move);
        MovePhase(Map);

        SetTurnPhase(ETurnPhase::BuyCards);
        BuyCardsPhase(Game);

        SetTurnPhase(ETurnPhase::EndTurn);
        SetTurnPhase(ETurnPhase::None);
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

    void FPlayer::SetTurnPhase(ETurnPhase NewTurnPhae)
    {
        this->TurnPhase = NewTurnPhae;
        if (TurnPhase != ETurnPhase::None)
        {
            Notify(shared_from_this(), std::make_shared<FStartTurnPhaseEvent>(EObserverEvent::StartTurnPhase, "", TurnPhase));
        }
    }

    void FPlayer::StartPhase()
    {
        if (Borough->IsCenter())
        {
            std::cout << "Since you are in "
                      << CENTER_LEVEL_NAMES[LevelInCenter]
                      << " Manhattan, you get the following:"
                      << std::endl;
            ChangeVictoryPoints(CENTER_VICTORY_POINT_REWARDS[LevelInCenter]);
            ChangeEnergyCubes(CENTER_ENERGY_CUBE_REWARDS[LevelInCenter]);
        }
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

    void FPlayer::SelectStrategy()
    {
        while (RollDiceStrategy == nullptr)
        {
            std::cout   << GetPlayerAndMonsterNames()
                        << ", please select your strategy:"
                        << std::endl
                        << "1. Human control"
                        << std::endl
                        << "2. Aggressive AI"
                        << std::endl
                        << "3. Moderate AI"
                        << std::endl;
            std::cout << ">";
            const int Input = InputSingleDigit();
            if (1 <= Input && Input <= 3)
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
        ChangeLifePoints(-Damage);
        if (LifePoints == 0)
        {
            bAlive = false;
            bStatueOfLiberty = false;
            bCelebrity = false;
            //TODO: WRONG PLACE TO PUT THIS!
            Notify(shared_from_this(), std::make_shared<FDeadPlayerEvent>(EObserverEvent::DeadPlayer, ""));
        }
    }

    void FPlayer::Move(FMap &Map, bool bOnlyStartingLocation)
    {
        std::shared_ptr<FBorough> OldBorough = Borough;
        int OldLevelInCenter = LevelInCenter;
        MoveStrategy->Execute(Map, shared_from_this(), false, bOnlyStartingLocation);
        if (OldBorough && OldBorough->IsCenter() && Borough->IsCenter())
        {
            Notify(shared_from_this(), std::make_shared<FMoveInManhattanEvent>(EObserverEvent::MoveInManhattan, "", OldLevelInCenter, LevelInCenter));
        }
        else
        {
            Notify(shared_from_this(), std::make_shared<FChangeBoroughEvent>(EObserverEvent::ChangeBorough, "", OldBorough, Borough));
        }
    }


    void FPlayer::EarnMonsterResources(const EMonsterResource MonsterResource, const int Number)
    {
        assert(Number != 0);
        switch (MonsterResource)
        {
            case EMonsterResource::EnergyCube:
                ChangeEnergyCubes(Number);
                break;
            case EMonsterResource::LifePoint:
                ChangeLifePoints(Number);
                break;
            case EMonsterResource::VictoryPoint:
                ChangeVictoryPoints(Number);
                break;
        }
        assert(true);
    }

    void FPlayer::ChangeEnergyCubes(int Number)
    {
        assert(Number != 0);
        EnergyCubes += Number;
        Notify(shared_from_this(), std::make_shared<FChangeEnergyCubesEvent>(EObserverEvent::ChangeEnergyCubes, "", Number, EnergyCubes));
    }

    void FPlayer::ChangeLifePoints(int Number)
    {
        assert(Number != 0);
        LifePoints += Number;
        LifePoints = std::clamp(LifePoints, 0, MAXIMUM_LIFE_POINTS);
        Notify(shared_from_this(), std::make_shared<FChangeLifePointsEvent>(EObserverEvent::ChangeLifePoints, "", Number, LifePoints));
    }

    void FPlayer::ChangeVictoryPoints(int Number)
    {
        assert(Number != 0);
        VictoryPoints += Number;
        Notify(shared_from_this(), std::make_shared<FChangeVictoryPointsEvent>(EObserverEvent::ChangeVictoryPoints, "", Number, VictoryPoints));

    }
//
//    void FPlayer::SetTurnResult(std::string Message) {
//        Notify(shared_from_this(), std::make_shared<FTurnResultEvent>(EObserverEvent::TurnResult, Message));
//    }
}
