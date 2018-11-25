// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "playerview.h"
#include <algorithm>
#include "gamecontroller.h"
#include "playercontroller.h"
#include "game.h"
#include "player.h"
#include "helper.h"

namespace KingOfNewYork
{
    FPlayerView::FPlayerView(std::shared_ptr<FGameController> GameController) : GameController(GameController)
    {
        for (auto& PlayerController : GameController->GetPlayerControllers())
        {
            if (PlayerController->GetPlayer())
            {
                PlayerController->GetPlayer()->Attach(this);
            }
        }
    }

    FPlayerView::~FPlayerView()
    {
        for (auto& PlayerController : GameController->GetPlayerControllers())
        {
            if (PlayerController->GetPlayer())
            {
                PlayerController->GetPlayer()->Detach(this);
            }
        }
    }

    void FPlayerView::Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event)
    {
        //TODO: Not sure if it will only observe players.
        const auto Player = std::dynamic_pointer_cast<const FPlayer>(Subject);
        assert(Player);

        switch (Event->ObserverEvent)
        {
            case EObserverEvent::StartTurnPhase:
            {
                const auto StartTurnPhaseEvent = std::dynamic_pointer_cast<const FStartTurnPhaseEvent>(Event);
                assert(StartTurnPhaseEvent);
                PrintHeader(Player->GetMonsterName() + ": " + GetTurnPhaseString(StartTurnPhaseEvent->TurnPhase));
                if (StartTurnPhaseEvent->TurnPhase == ETurnPhase::StartTurn) {
                    assert(Player->GetBorough());
                    PrintHeader("Current Status");
                    if (Player->GetBorough()->IsCenter())
                    {
                        PrintNormal("Position: " + CENTER_LEVEL_NAMES[Player->GetLevelInCenter()] + " Manhattan");
                    }
                    else
                    {
                        PrintNormal("Position: " + Player->GetBorough()->GetName());
                    }

                    PrintNormal("Number of cards: " + std::to_string(Player->GetCards().size()));
                    for (const auto &Card : Player->GetCards()) Card->Display();

                    PrintNormal("Energy cubes: " + std::to_string(Player->GetEnergyCubes()));
                    PrintNormal("Life points: " + std::to_string(Player->GetLifePoints()));
                    PrintNormal("Victory points: " + std::to_string(Player->GetVictoryPoints()));

                    if (Player->IsCelebrity())
                    {
                        PrintNormal(Player->GetMonsterName() + " is a Superstar!");
                    }

                    if (Player->IsStatueOfLiberty())
                    {
                        PrintNormal(Player->GetMonsterName() + " has help from the Status of Liberty!");
                    }

                    std::cout << std::endl;

                    if (Player->GetBorough()->IsCenter())
                    {
                        std::cout << "Since "
                                  << Player->GetMonsterName()
                                  << " is in "
                                  << CENTER_LEVEL_NAMES[Player->GetLevelInCenter()]
                                  << " Manhattan, it gets the following:"
                                  << std::endl;
                    }
                }
                return;

            }
            case EObserverEvent::ChangeVictoryPoints:
            {
                const auto ChangeVictoryPointsEvent = std::dynamic_pointer_cast<const FChangeVictoryPointsEvent>(Event);
                assert(ChangeVictoryPointsEvent);
                assert(ChangeVictoryPointsEvent->Delta != 0);
                if (ChangeVictoryPointsEvent->Delta > 0) {
                    std::cout << Player->GetMonsterName()
                              << " earned "
                              << ChangeVictoryPointsEvent->Delta
                              << " Victory Points (new total: "
                              << ChangeVictoryPointsEvent->Total
                              << ")."
                              << std::endl;
                }
                else
                {
                    std::cout << Player->GetMonsterName()
                              << " lost "
                              << std::abs(ChangeVictoryPointsEvent->Delta)
                              << " Victory Points (new total: "
                              << ChangeVictoryPointsEvent->Total
                              << ")."
                              << std::endl;
                }
                return;
            }
            case EObserverEvent::ChangeEnergyCubes:
            {
                const auto ChangeEnergyCubesEvent = std::dynamic_pointer_cast<const FChangeEnergyCubesEvent>(Event);
                assert(ChangeEnergyCubesEvent);
                assert(ChangeEnergyCubesEvent->Delta != 0);
                if (ChangeEnergyCubesEvent->Delta > 0) {
                    std::cout << Player->GetMonsterName()
                              << " earned "
                              << ChangeEnergyCubesEvent->Delta
                              << " Energy Cubes (new total: "
                              << ChangeEnergyCubesEvent->Total
                              << ")."
                              << std::endl;
                }
                else
                {
                    std::cout << Player->GetMonsterName()
                              << " lost "
                              << std::abs(ChangeEnergyCubesEvent->Delta)
                              << " Energy Cubes (new total: "
                              << ChangeEnergyCubesEvent->Total
                              << ")."
                              << std::endl;
                }
                return;
            }
            case EObserverEvent::ChangeLifePoints:
            {
                const auto ChangeLifePointsEvent = std::dynamic_pointer_cast<const FChangeLifePointsEvent>(Event);
                assert(ChangeLifePointsEvent);
                assert(ChangeLifePointsEvent->Delta != 0);
                if (ChangeLifePointsEvent->Delta > 0) {
                    std::cout << Player->GetMonsterName()
                              << " earned "
                              << ChangeLifePointsEvent->Delta
                              << " Life Points (new total: "
                              << ChangeLifePointsEvent->Total
                              << ")."
                              << std::endl;
                }
                else
                {
                    std::cout << Player->GetMonsterName()
                              << " lost "
                              << std::abs(ChangeLifePointsEvent->Delta)
                              << " Life Points (new total: "
                              << ChangeLifePointsEvent->Total
                              << ")."
                              << std::endl;
                }
                return;
            }
            case EObserverEvent::ChangeBorough:
            {
                const auto ChangeBoroughEvent = std::dynamic_pointer_cast<const FChangeBoroughEvent>(Event);
                assert(ChangeBoroughEvent);
                assert(ChangeBoroughEvent->DestinationBorough);
                if (!ChangeBoroughEvent->OriginBorough)
                {
                    std::cout << Player->GetMonsterName()
                              << " moved to "
                              << ChangeBoroughEvent->DestinationBorough->GetName()
                              << "."
                              << std::endl;
                }
                else if (ChangeBoroughEvent->OriginBorough == ChangeBoroughEvent->DestinationBorough)
                {
                    std::cout << Player->GetMonsterName()
                              << " stayed in "
                              << ChangeBoroughEvent->OriginBorough->GetName()
                              << "."
                              << std::endl;
                }
                else
                {
                    std::cout << Player->GetMonsterName()
                              << " moved from "
                              << ChangeBoroughEvent->OriginBorough->GetName()
                              << " to "
                              << ChangeBoroughEvent->DestinationBorough->GetName()
                              << "."
                              << std::endl;
                }
                return;
            }
            case EObserverEvent::MoveInManhattan:
            {
                const auto MoveInManhattanEvent = std::dynamic_pointer_cast<const FMoveInManhattanEvent>(Event);
                assert(MoveInManhattanEvent);
                assert(MoveInManhattanEvent->DestinationLevel != -1);

                if (MoveInManhattanEvent->OriginLevel != MoveInManhattanEvent->DestinationLevel)
                {
                    std::cout << Player->GetMonsterName()
                              << " moved from "
                              << CENTER_LEVEL_NAMES[MoveInManhattanEvent->OriginLevel]
                              << " Manhattan to "
                              << CENTER_LEVEL_NAMES[MoveInManhattanEvent->DestinationLevel]
                              << " Manhattan."
                              << std::endl;
                }
                else
                {
                    std::cout << Player->GetMonsterName()
                              << " stayed in "
                              << CENTER_LEVEL_NAMES[MoveInManhattanEvent->OriginLevel]
                              << " Manhattan to "
                              << std::endl;
                }
                return;
            }
            case EObserverEvent::DestroyedTile:
            {
                const auto DestroyedTileEvent = std::dynamic_pointer_cast<const FDestroyedTileEvent>(Event);
                assert(DestroyedTileEvent);
                assert(DestroyedTileEvent->Tile);
                PrintNormal("Destructed tile: " + GetTileTypeString(DestroyedTileEvent->Tile->GetTileType()) + ".");
                return;
            }
            case EObserverEvent::SpawnedUnit:
            {
                const auto SpawnedUnitEvent = std::dynamic_pointer_cast<const FSpawnedUnitEvent>(Event);
                assert(SpawnedUnitEvent);
                assert(SpawnedUnitEvent->Tile);
                PrintNormal("Unit appeared: " + SpawnedUnitEvent->Tile->GetTileInfo() + ".");
                return;
            }
            case EObserverEvent::DeadPlayer:
            {
                const auto DeadPlayerEvent = std::dynamic_pointer_cast<const FDeadPlayerEvent>(Event);
                assert(DeadPlayerEvent);
                std::cout << Player->GetMonsterName()
                          << " died!";
                std::cout << std::endl;
                return;
            }
        }
        assert(true);
    }
}

