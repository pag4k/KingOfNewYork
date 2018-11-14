// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "helper.h"
#include "movestrategy.h"
//#include "game.h"
#include "map.h"
#include "player.h"

namespace KingOfNewYork
{
    void HumanMoveStrategy::Execute(FMap &Map, std::shared_ptr<FPlayer> Player, bool bMovePhase, bool bOnlyStartingLocation)
    {
        if (bMovePhase)
        {
            if (Player->GetBorough()->IsCenter())
            {
                ForceProgressInCenter(Map, Player);
            }
            else
            {
                std::shared_ptr<FBorough> CenterBorough = Map.GetCenterBorough();

                if (CenterBorough->GetPlayerCount() == MAXIMUM_MONSTERS_IN_CENTER)
                {
                    std::cout << "Since there is already "
                              << MAXIMUM_MONSTERS_IN_CENTER
                              << " Monsters in any zone of Manhattan, you have two options: You can move to any borough that doesn’t already have 2 Monsters in it (except Manhattan), or you can just stay in your borough. Please enter the number of the borough you want to move to:"
                              << std::endl;
                    HumanSelectBorough(Map, Player, false);
                }
                else
                {
                    ForceMoveToCenter(Map, Player);
                }
            }
        } else {
            HumanSelectBorough(Map, Player, bOnlyStartingLocation);
        }
    }

    void AggressiveMoveStrategy::Execute(FMap &Map, std::shared_ptr<FPlayer> Player, bool bMovePhase, bool bOnlyStartingLocation)
    {
        //Try to stay away from Manhattan
        if (bMovePhase)
        {
            if (Player->GetBorough()->IsCenter())
            {
                ForceProgressInCenter(Map, Player);
            }
            else
            {
                std::shared_ptr<FBorough> CenterBorough = Map.GetCenterBorough();

                if (CenterBorough->GetPlayerCount() == MAXIMUM_MONSTERS_IN_CENTER)
                {
                    std::cout << "Since there is already "
                              << MAXIMUM_MONSTERS_IN_CENTER
                              << " Monsters in any zone of Manhattan, "
                              << Player->GetPlayerAndMonsterNames()
                              <<" has two options: He/she can move to any borough that does not already have 2 Monsters in it (except Manhattan), or can just stay in his/her borough."
                              << std::endl;

                    AISelectBorough(Map, Player, false, false);
                }
                else
                {
                    ForceMoveToCenter(Map, Player);
                }
            }
        }
        else
        {
            AISelectBorough(Map, Player, bOnlyStartingLocation, false);
        }
    }

    void ModerateMoveStrategy::Execute(FMap &Map, std::shared_ptr<FPlayer> Player, bool bMovePhase, bool bOnlyStartingLocation)
    {
        //Try to stay in Manhattan

    }

    namespace
    {
        std::vector<std::shared_ptr<FBorough>> GetValidBorough(FMap &Map, std::shared_ptr<FPlayer> Player, bool bOnlyStartingLocation)
        {
            std::vector<std::shared_ptr<FBorough>> ValidBorough;
            for (int i = 0; i < Map.BoroughCount(); ++i)
            {
                std::shared_ptr<FBorough> CurrentBorough = Map.GetBorough(i);
                const std::vector<std::shared_ptr<FPlayer>> &CurrentPlayers =
                        CurrentBorough->GetConstPlayers();
                const int Offset = CurrentBorough == Player->GetBorough() ? 1 : 0;
                if (CurrentPlayers.size() - Offset < MAXIMUM_PLAYERS_IN_BOROUGH &&
                    (!bOnlyStartingLocation || CurrentBorough->IsStartingLocation()))
                {
                    ValidBorough.push_back(CurrentBorough);
                    std::cout << (i + 1)
                              << ". "
                              << CurrentBorough->GetName();
                    if (CurrentPlayers.size() > 0)
                    {
                        std::cout << " (already there: ";
                        for (int j = 0; j < CurrentPlayers.size(); ++j)
                        {
                            if (CurrentPlayers[j] == Player)
                            {
                                std::cout << "current player";
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
            return ValidBorough;
        }


        void HumanSelectBorough(FMap &Map, std::shared_ptr<FPlayer> Player, bool bOnlyStartingLocation)
        {
            int bDone = false;
            while (!bDone)
            {

                std::vector<std::shared_ptr<FBorough>> ValidBorough = GetValidBorough(Map, Player, bOnlyStartingLocation);

                std::cout << ">";
                const int Input = InputSingleDigit();
                std::cout << std::endl;

                if (1 <= Input && Input <= ValidBorough.size())
                {
                    bDone = true;
                    MoveTo(Player, ValidBorough[Input - 1]);
                }
                else
                {
                    std::cout << "Invalid input, please try again."
                              << std::endl
                              << std::endl;
                }
            }
        }

        void AISelectBorough(FMap &Map, std::shared_ptr<FPlayer> Player, bool bOnlyStartingLocation, bool bPreferManhattan)
        {
            std::vector<std::shared_ptr<FBorough>> ValidBorough = GetValidBorough(Map, Player, bOnlyStartingLocation);
            std::shared_ptr<FBorough> CenterBorough = Map.GetCenterBorough();
            if (bPreferManhattan)
            {
                if (Player->GetBorough() == nullptr)
                {
                    for (auto Borough : ValidBorough)
                    {
                        if (Borough != CenterBorough)
                        {
                            MoveTo(Player, Borough);
                            break;
                        }
                    }
                }
                else if (Player->GetBorough() == CenterBorough)
                {
                    //Do nothing.
                }
                else
                {
                    for (auto Borough : ValidBorough)
                    {
                        if (Borough == CenterBorough)
                        {
                            MoveTo(Player, Borough);
                            break;
                        }
                    }
                }
            }
            else
            {
                if (Player->GetBorough() == nullptr)
                {
                    for (auto Borough : ValidBorough)
                    {
                        if (Borough != CenterBorough)
                        {
                            MoveTo(Player, Borough);
                            break;
                        }
                    }
                }
                else if (Player->GetBorough() == CenterBorough)
                {
                    for (auto Borough : ValidBorough)
                    {
                        if (Borough != CenterBorough)
                        {
                            MoveTo(Player, Borough);
                            break;
                        }
                    }
                }
                else
                {
                    //Do nothing.
                }
            }
        }

        void MoveTo(std::shared_ptr<FPlayer> Player, std::shared_ptr<FBorough> NewBorough)
        {
            assert(NewBorough);
            if (Player->GetBorough() == NewBorough)
            {
                std::cout << Player->GetPlayerAndMonsterNames()
                          << " stayed in "
                          << Player->GetBorough()->GetName()
                          << "."
                          << std::endl;
                return;
            }

            std::shared_ptr<FBorough> OldBorough = Player->GetBorough();

            //Removing player from previous borough list.
            if (Player->GetBorough())
            {
                bool Erased = false;
                for (auto it = Player->GetBorough()->GetConstPlayers().begin();
                     it != Player->GetBorough()->GetConstPlayers().end();
                     ++it)
                {
                    if (*it == Player)
                    {
                        Player->GetBorough()->GetMutablePlayers().erase(it);
                        Erased = true;
                        break;
                    }
                }
                assert(Erased);
            }
            //Setting player position to selected borough.
            Player->SetBorough(NewBorough);
            //Put player in the borough player list.
            Player->GetBorough()->GetMutablePlayers().push_back(Player);

            if (OldBorough == nullptr)
            {
                std::cout << Player->GetPlayerAndMonsterNames()
                          << " moved to "
                          << Player->GetBorough()->GetName()
                          << "."
                          << std::endl;
            }
            else
            {
                std::cout << Player->GetPlayerAndMonsterNames()
                          << " moved from "
                          << OldBorough->GetName()
                          << " to "
                          << Player->GetBorough()->GetName()
                          << "."
                          << std::endl;
            }

        }

        void ForceMoveToCenter(FMap &Map, std::shared_ptr<FPlayer> Player)
        {
            std::string OldBorough = Player->GetBorough()->GetName();
            std::cout << "Since there are less than "
                      << MAXIMUM_MONSTERS_IN_CENTER
                      << " Monsters in any zone of Manhattan,"
                      << Player->GetPlayerAndMonsterNames()
                      <<" must move there."
                      << "He/she earns "
                      << Player->EarnVictoryPoints(ENTER_CENTER_VICTORY_POINT_REWARD)
                      << " for doing so."
                      << std::endl;
            MoveTo(Player, Map.GetCenterBorough());
            Player->SetLevelInCenter(1);
        }

        void ForceProgressInCenter(FMap &Map, std::shared_ptr<FPlayer> Player)
        {
            std::cout << "Since "
                      << Player->GetPlayerAndMonsterNames()
                      << " is already in Manhattan, he/she must advance to the next zone up there."
                      << std::endl;
            if (Player->GetLevelInCenter() < LEVEL_IN_CENTER_COUNT)
            {
                assert(0 < Player->GetLevelInCenter() && Player->GetLevelInCenter() < LEVEL_IN_CENTER_COUNT);
                Player->SetLevelInCenter(Player->GetLevelInCenter() + 1);
                std::cout << Player->GetPlayerAndMonsterNames()
                          << " moved from "
                          << CENTER_LEVEL_NAMES[Player->GetLevelInCenter()-1]
                          << " Manhattan to "
                          << CENTER_LEVEL_NAMES[Player->GetLevelInCenter()]
                          << " Manhattan."
                          << std::endl;
            }
            else
            {
                std::cout << "However, since"
                          << Player->GetPlayerAndMonsterNames()
                          << " is in Upper Manhattan, he/she no longer move during this phase."
                          << std::endl;
            }
        }

    }

}
