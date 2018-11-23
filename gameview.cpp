//
// Created by oscar on 15/11/18.
//

#include "gameview.h"
#include "game.h"
#include "player.h"

namespace KingOfNewYork
{
    FGameView::FGameView(std::shared_ptr<FGame> Game) : Game(Game)
    {
        Game->Attach(this);
    }

    FGameView::~FGameView()
    {
        Game->Detach(this);
    }

    void FGameView::Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event)
    {
        //TODO: Not sure if it will only observe the game.
        const auto GameSubject = std::dynamic_pointer_cast<const FGame>(Subject);
        assert(Game == GameSubject);

        switch (Event->ObserverEvent)
        {
            case EObserverEvent::BetweenTurns:
            {
                const auto BetweenTurnsEvent = std::dynamic_pointer_cast<const FBetweenTurnsEvent>(Event);
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
                            std::cout << TileStack->GetTopTile()->GetTileInfo()
                                      << std::endl;
                        }
                    }
                    for (const auto &Unit : Borough->GetUnits())
                    {
                        std::cout << Unit->GetTileInfo()
                                  << std::endl;
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
                            std::cout << Player->GetMonsterName()
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


