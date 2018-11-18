//
// Created by oscar on 15/11/18.
//

#include "stateview.h"
#include "game.h"
#include "player.h"

namespace KingOfNewYork
{
    FStateView::FStateView(std::shared_ptr<FGame> Game) : Game(Game)
    {
        Game->Attach(this);
    }

    FStateView::~FStateView()
    {
        Game->Detach(this);
    }

    void FStateView::Update(const std::shared_ptr<FSubject> &Subject, const std::shared_ptr<IObserverEvent> &Event)
    {
        //TODO: Not sure if it will only observe the game.
        auto GameSubject = std::dynamic_pointer_cast<FGame>(Subject);
        assert(Game == GameSubject);

        switch (Event->ObserverEvent)
        {
            case EObserverEvent::BetweenTurns:
            {
                auto BetweenTurnsEvent = std::dynamic_pointer_cast<FBetweenTurnsEvent>(Event);
                assert(BetweenTurnsEvent);
                std::cout << std::endl;
                std::cout << "################################################################################" << std::endl;
                std::cout << "                              Current Game Status                               " << std::endl;
                std::cout << "################################################################################" << std::endl;
                for (const std::shared_ptr<FBorough> &Borough : Game->GetMap()->GetBoroughs())
                {
                    std::cout << Borough->GetName()
                              << ":"
                              << std::endl;
                    for (const auto& TileStack : Borough->GetConstTileStacks())
                    {
                        if (!TileStack->IsEmpty())
                        {
                            std::cout << TileStack->GetTopTileInfo()->GetTileInfo()
                                      << std::endl;
                        }
                    }
                    if (Borough->GetPlayerCount() == 0)
                    {
                        std::cout << "No players..."
                                  << std::endl;
                    }
                    else
                    {
                        for (const auto& Player : Borough->GetConstPlayers())
                        {
                            if (Borough->IsCenter())
                            {
                                std::cout << CENTER_LEVEL_NAMES[Player->GetLevelInCenter()]
                                          << " Manhattan: "
                                          << std::endl;
                            }
                            std::cout << Player->GetPlayerAndMonsterNames()
                                      << ": (Life Points: "
                                      << Player->GetLifePoints()
                                      << " Energy Cubes: "
                                      << Player->GetEnergyCubes()
                                      << " Victory Points: "
                                      << Player->GetVictoryPoints()
                                      << (Player->IsCelebrity() ? " Celebrity" : "")
                                      << (Player->IsStatueOfLiberty() ? "  Statue of Liberty" : "")
                                      << ")"
                                      << std::endl;
                        }
                    }
                    std::cout << std::endl;
                }
                std::cout << "################################################################################"
                          << std::endl;

                break;
            }
        }


    }
}


