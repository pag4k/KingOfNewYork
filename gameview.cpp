// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "gameview.h"
#include "game.h"
#include "player.h"
#include "helper.h"

namespace KingOfNewYork
{
    FGameView::FGameView(std::shared_ptr<FGame> Game) : Game(Game)
    {
        for (auto& Player : Game->GetPlayers())
        {
            Player->Attach(this);
        }
    }

    FGameView::~FGameView()
    {
        //TODO: There might be some corner cases when a player dies.
        for (auto& Player : Game->GetPlayers())
        {
            Player->Detach(this);
        }
    }

    void FGameView::Update(const std::shared_ptr<FSubject> &Subject, const std::shared_ptr<IObserverEvent> &Event)
    {
        //TODO: Not sure if it will only observe players.
        auto Player = std::dynamic_pointer_cast<FPlayer>(Subject);
        assert(Player);

        switch (Event->ObserverEvent)
        {
            case EObserverEvent::StartTurnPhase:
            {
                auto StartTurnPhaseEvent = std::dynamic_pointer_cast<FStartTurnPhaseEvent>(Event);
                assert(StartTurnPhaseEvent);
                PrintHeader(Player->GetPlayerAndMonsterNames() + ": " + GetTurnPhaseString(StartTurnPhaseEvent->TurnPhase));
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
                    for (const std::unique_ptr<FCard> &Card : Player->GetCards()) {
                        if (Card)
                        {
                            PrintNormal(Card->GetCardInfo());
                        }
                    }

                    std::cout << "Tokens:" << std::endl;
                    for (int i = 0; i < TOKEN_TYPE_COUNT; ++i)
                    {
                        PrintNormal("\t-" + GetTokenTypeString(ETokenType(i)) + ": " + std::to_string(Player->GetTokenInventory()[i]));
                    }

                    PrintNormal("Energy cubes: " + std::to_string(Player->GetEnergyCubes()));
                    PrintNormal("Life points: " + std::to_string(Player->GetLifePoints()));
                    PrintNormal("Victory points: " + std::to_string(Player->GetVictoryPoints()));

                    if (Player->IsCelebrity())
                    {
                        PrintNormal(Player->GetPlayerAndMonsterNames() + " is a Superstar!");
                    }

                    if (Player->IsStatueOfLiberty())
                    {
                        PrintNormal(Player->GetPlayerAndMonsterNames() + " has help from the Status of Liberty!");
                    }

                    std::cout << std::endl;

                    if (Player->GetBorough()->IsCenter())
                    {
                        std::cout << "Since "
                                  << Player->GetPlayerAndMonsterNames()
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
                auto ChangeVictoryPointsEvent = std::dynamic_pointer_cast<FChangeVictoryPointsEvent>(Event);
                assert(ChangeVictoryPointsEvent);
                assert(ChangeVictoryPointsEvent->Delta != 0);
                if (ChangeVictoryPointsEvent->Delta > 0) {
                    std::cout << Player->GetPlayerAndMonsterNames()
                              << " earned "
                              << ChangeVictoryPointsEvent->Delta
                              << " Victory Points (new total: "
                              << ChangeVictoryPointsEvent->Total
                              << ")."
                              << std::endl;
                }
                else
                {
                    std::cout << Player->GetPlayerAndMonsterNames()
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
                auto ChangeEnergyCubesEvent = std::dynamic_pointer_cast<FChangeEnergyCubesEvent>(Event);
                assert(ChangeEnergyCubesEvent);
                assert(ChangeEnergyCubesEvent->Delta != 0);
                if (ChangeEnergyCubesEvent->Delta > 0) {
                    std::cout << Player->GetPlayerAndMonsterNames()
                              << " earned "
                              << ChangeEnergyCubesEvent->Delta
                              << " Energy Cubes (new total: "
                              << ChangeEnergyCubesEvent->Total
                              << ")."
                              << std::endl;
                }
                else
                {
                    std::cout << Player->GetPlayerAndMonsterNames()
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
                auto ChangeLifePointsEvent = std::dynamic_pointer_cast<FChangeLifePointsEvent>(Event);
                assert(ChangeLifePointsEvent);
                assert(ChangeLifePointsEvent->Delta != 0);
                if (ChangeLifePointsEvent->Delta > 0) {
                    std::cout << Player->GetPlayerAndMonsterNames()
                              << " earned "
                              << ChangeLifePointsEvent->Delta
                              << " Life Points (new total: "
                              << ChangeLifePointsEvent->Total
                              << ")."
                              << std::endl;
                }
                else
                {
                    std::cout << Player->GetPlayerAndMonsterNames()
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
                auto ChangeBoroughEvent = std::dynamic_pointer_cast<FChangeBoroughEvent>(Event);
                assert(ChangeBoroughEvent);
                assert(ChangeBoroughEvent->DestinationBorough);
                if (!ChangeBoroughEvent->OriginBorough)
                {
                    std::cout << Player->GetPlayerAndMonsterNames()
                              << " moved to "
                              << ChangeBoroughEvent->DestinationBorough->GetName()
                              << "."
                              << std::endl;
                }
                else if (ChangeBoroughEvent->OriginBorough == ChangeBoroughEvent->DestinationBorough)
                {
                    std::cout << Player->GetPlayerAndMonsterNames()
                              << " stayed in "
                              << ChangeBoroughEvent->OriginBorough->GetName()
                              << "."
                              << std::endl;
                }
                else
                {
                    std::cout << Player->GetPlayerAndMonsterNames()
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
                auto MoveInManhattanEvent = std::dynamic_pointer_cast<FMoveInManhattanEvent>(Event);
                assert(MoveInManhattanEvent);
                assert(MoveInManhattanEvent->DestinationLevel != -1);

                if (MoveInManhattanEvent->OriginLevel != MoveInManhattanEvent->DestinationLevel)
                {
                    std::cout << Player->GetPlayerAndMonsterNames()
                              << " moved from "
                              << CENTER_LEVEL_NAMES[MoveInManhattanEvent->OriginLevel]
                              << " Manhattan to "
                              << CENTER_LEVEL_NAMES[MoveInManhattanEvent->DestinationLevel]
                              << " Manhattan."
                              << std::endl;
                }
                else
                {
                    std::cout << Player->GetPlayerAndMonsterNames()
                              << " stayed in "
                              << CENTER_LEVEL_NAMES[MoveInManhattanEvent->OriginLevel]
                              << " Manhattan to "
                              << std::endl;
                }
                return;
            }
            case EObserverEvent::DeadPlayer:
            {
                auto DeadPlayerEvent = std::dynamic_pointer_cast<FDeadPlayerEvent>(Event);
                assert(DeadPlayerEvent);
                std::cout << Player->GetPlayerAndMonsterNames()
                          << " died!";
                if (Player == Game->GetCurrentPlayer())
                {
                    std::cout << " It's turn is over.";
                }
                std::cout << std::endl;
                Player->Detach(this);
                return;
            }
        }
        assert(true);
    }
}

