// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include <algorithm>

#include "game.h"
#include "player.h"
#include "card.h"

namespace KingOfNewYork
{
    FPlayer::FPlayer(EMonsterName MonsterName) : MonsterName(MonsterName)
    {
        TurnPhase = ETurnPhase ::None;

        Borough = nullptr;
        LevelInCenter = 0;

        for (int i = 0; i < TOKEN_TYPE_COUNT; ++i)
        {
            TokenInventory.push_back(0);
        }

        bAlive = true;
        EnergyCubes = 100;
        LifePoints = MAXIMUM_LIFE_POINTS;
        VictoryPoints = 0;

        bCelebrity = false;
        bStatueOfLiberty = false;
        bVictorious = false;
    }

    void FPlayer::SetCelebrity(const bool bCelebrity)
    {
        if (!this->bCelebrity && bCelebrity && UseCard(36))
        {
            ChangeEnergyCubes(1);
        }
        this->bCelebrity = bCelebrity;
    }

    void FPlayer::DestroyBuilding(std::unique_ptr<FTileStack> &TileStack)
    {
        //Make a copy of the destroyed building for convenience
        std::unique_ptr<FTile> DestructedBuilding = std::make_unique<FTile>(*(TileStack->GetTopTile()));
        assert(DestructedBuilding->IsBuilding());

        Notify(shared_from_this(), std::make_shared<FDestroyedTileEvent>(EObserverEvent::DestroyedTile, "", DestructedBuilding));

        EarnMonsterResources(EMonsterResource(static_cast<int>(DestructedBuilding->GetTileType())/2), DestructedBuilding->GetReward());

        if (!bDestroyedBuilding && UseCard(24))
        {
            bDestroyedBuilding = true;
            ChangeVictoryPoints(1);
        }

        Borough->GetUnits().push_back(std::move(TileStack->DestructTopTile()));

        Notify(shared_from_this(), std::make_shared<FSpawnedUnitEvent>(EObserverEvent::SpawnedUnit, "", Borough->GetUnits().back()));
    }

    void FPlayer::DestroyUnit(std::unique_ptr<FTile> &DestroyedUnit)
    {
        //Make a copy of the destroyed unit for convenience
        std::unique_ptr<FTile> DestructedUnit = std::make_unique<FTile>(*(DestroyedUnit));
        assert(!DestructedUnit->IsBuilding());

        Notify(shared_from_this(), std::make_shared<FDestroyedTileEvent>(EObserverEvent::DestroyedTile, "", DestructedUnit));

        EarnMonsterResources(EMonsterResource(static_cast<int>(DestructedUnit->GetTileType())/2), DestructedUnit->GetReward());

        if (DestructedUnit->GetTileType() == ETileType::Infantry && UseCard(3))
        {
            ChangeLifePoints(1);
        }
        if (UseCard(53))
        {
            ChangeVictoryPoints(1);
        }

        std::vector<std::unique_ptr<FTile>> &Units = Borough->GetUnits();

        auto newEndIt = std::remove_if(Units.begin(), Units.end(), [&DestroyedUnit](auto &Unit) { return Unit == DestroyedUnit; });
        Units.resize(static_cast<unsigned  long>(newEndIt - Units.begin()));
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

    bool FPlayer::UseCard(int Id)
    {
        auto it = std::find_if(Cards.begin(), Cards.end(),
                               [&Id](const std::unique_ptr<FCard> &Card) { return Card->GetId() == Id; });
        if (it == Cards.end())
        {
            return false;
        }
        else
        {
            (*it)->Use();
            return true;
        }
    }

    void FPlayer::Died(FGame &Game)
    {
        auto &BoroughPlayers = GetMutableBorough()->GetMutablePlayers();
        auto ThisPlayer = shared_from_this();
        auto newEndIt = std::remove_if(BoroughPlayers.begin(), BoroughPlayers.end(), [&ThisPlayer](const auto &Player) { return Player == ThisPlayer; });
        BoroughPlayers.resize(static_cast<unsigned  long>(newEndIt - BoroughPlayers.begin()));
        for (auto &Card : Cards) Game.GetDiscardDeck().AddCard(Card);
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
            Notify(shared_from_this(), std::make_shared<FDeadPlayerEvent>(EObserverEvent::DeadPlayer, ""));
            Died(Game);
            return;

        }
        if (UseCard(29))
        {
            ChangeEnergyCubes(1);
        }
    }

    void FPlayer::Move(std::shared_ptr<FBorough> OldBorough, int OldLevelInCenter)
    {
        //std::shared_ptr<FBorough> OldBorough = Borough;
        //int OldLevelInCenter = LevelInCenter;
        //MoveStrategy->Execute(Map, shared_from_this(), bMovePhase, bOnlyStartingLocation);

        if (OldBorough && OldBorough->IsCenter() && Borough->IsCenter())
        {
            Notify(shared_from_this(), std::make_shared<FMoveInManhattanEvent>(EObserverEvent::MoveInManhattan, "", OldLevelInCenter, LevelInCenter));
        }
        else
        {
            Notify(shared_from_this(), std::make_shared<FChangeBoroughEvent>(EObserverEvent::ChangeBorough, "", OldBorough, Borough));
            if (OldBorough && !OldBorough->IsCenter() && Borough->IsCenter() && UseCard(58))
            {
                ChangeLifePoints(2);
            }
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
}
