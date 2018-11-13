
//#include "helper.h"
#include "movestrategy.h"
//#include "game.h"
#include "map.h"
#include "player.h"

namespace KingOfNewYork
{
    void HumanMoveStrategy::Execute(FMap &Map, std::shared_ptr<FPlayer> Player)
    {
        if (Player->GetBorough()->IsCenter())
        {
            std::cout << "Since you were already in Manhattan, you must advance to the next zone up there."
                      << std::endl;
            if (Player->GetLevelInCenter() < LEVEL_IN_CENTER_COUNT)
            {
                assert(0 < Player->GetLevelInCenter() && Player->GetLevelInCenter() < LEVEL_IN_CENTER_COUNT);
                Player->SetLevelInCenter(Player->GetLevelInCenter() + 1);
                std::cout << "You moved from "
                          << CENTER_LEVEL_NAMES[Player->GetLevelInCenter()-1]
                          << " Manhattan to "
                          << CENTER_LEVEL_NAMES[Player->GetLevelInCenter()]
                          << " Manhattan."
                          << std::endl;
            }
            else
            {
                std::cout << "However, since you are in Upper Manhattan, you no longer move during this phase."
                          << std::endl;
            }
        }
        else
        {
            int MonsterInCenterCount = 0;
            std::shared_ptr<FBorough> CenterBorough = nullptr;
            for (int i = 0; i < Map.BoroughCount(); ++i) {
                if (Map.GetBorough(i)->IsCenter()) {
                    CenterBorough = Map.GetBorough(i);
                    MonsterInCenterCount = static_cast<int>(CenterBorough->GetConstPlayers().size());
                    break;
                }
            }
            assert(CenterBorough);
            if (MonsterInCenterCount == MAXIMUM_MONSTERS_IN_CENTER)
            {
                std::string OldBorough = Player->GetBorough()->GetName();
                std::cout << "Since there is already "
                          << MAXIMUM_MONSTERS_IN_CENTER
                          << " Monsters in any zone of Manhattan, you have two options: You can move to any borough that doesn’t already have 2 Monsters in it (except Manhattan), or you can just stay in your borough. Please enter the number of the borough you want to move to:"
                          << std::endl;
                Player->SelectBorough(Map, false, false);
                if (OldBorough == Player->GetBorough()->GetName())
                {
                    std::cout << "You stayed in "
                              << Player->GetBorough()->GetName()
                              << "."
                              << std::endl;
                }
                else
                {
                    std::cout << "You moved from "
                              << OldBorough
                              << " to "
                              << Player->GetBorough()->GetName()
                              << "."
                              << std::endl;
                }
            }
            else
            {
                std::string OldBorough = Player->GetBorough()->GetName();
                std::cout << "Since are less than "
                          << MAXIMUM_MONSTERS_IN_CENTER
                          << " Monsters in any zone of Manhattan, you must move there."
                          << "You earn "
                          << Player->EarnVictoryPoints(ENTER_CENTER_VICTORY_POINT_REWARD)
                          << " for doing so."
                          << std::endl;
                Player->MoveTo(CenterBorough);
                Player->SetLevelInCenter(1);
                std::cout << "You moved from "
                          << OldBorough
                          << " to "
                          << CENTER_LEVEL_NAMES[Player->GetLevelInCenter()]
                          << " Manhattan."
                          << std::endl;

            }
        }
    }

    void AggressiveMoveStrategy::Execute(FMap &Map, std::shared_ptr<FPlayer> Player)
    {

    }

    void ModerateMoveStrategy::Execute(FMap &Map, std::shared_ptr<FPlayer> Player)
    {

    }

}
