// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "gamecontroller.h"

#include "helper.h"

namespace KingOfNewYork
{
    FGameController::FGameController(): CurrentPlayer(-1)
    {
        if (InitializationPhase())
        {
            bIsValid = true;
        }
        else
        {
            std::cout << "Error: There was a problem during the initialization phase."
                      << std::endl;
            bIsValid = false;
        }
    }

    int FGameController::GetPlayerCount() const
    {
        return static_cast<int>(std::count_if(PlayerControllers.begin(), PlayerControllers.end(),
                                              [](const auto &PlayerController) { return PlayerController->GetPlayer() != nullptr; }));
    }

    std::unique_ptr<FPlayerController> &FGameController::GetPlayerController(const std::shared_ptr<FPlayer> &Player)
    {
        auto PlayerControllerIt = std::find_if(PlayerControllers.begin(), PlayerControllers.end(),
                                               [Player](const auto &PlayerController) { return PlayerController->GetPlayer() == Player; });
        assert(PlayerControllerIt != PlayerControllers.end());
        return *PlayerControllerIt;
    }

    void FGameController::ChangeCelebrity(std::shared_ptr<FPlayer> &NewCelebrityPlayer)
    {
        auto PlayerControllerIt = std::find_if(PlayerControllers.begin(), PlayerControllers.end(),
                                               [](const auto &PlayerController) { return PlayerController->GetPlayer() && PlayerController->GetPlayer()->IsCelebrity(); });
        if (PlayerControllerIt != PlayerControllers.end()) {
            auto &Player = (*PlayerControllerIt)->GetPlayer();
            if (Player == NewCelebrityPlayer) {
                return;
            }
            PrintNormal(Player->GetMonsterName() + " is no longer a Celebrity.");
            Player->SetCelebrity(false);
        }
        NewCelebrityPlayer->SetCelebrity(true);
        PrintNormal("You are now a Celebrity!");
    }

    void FGameController::ChangeStatueOfLiberty(std::shared_ptr<FPlayer> &NewStatueOfLibertyPlayer)
    {
        auto PlayerControllerIt = std::find_if(PlayerControllers.begin(), PlayerControllers.end(),
                                               [](auto &PlayerController) { return PlayerController->GetPlayer() && PlayerController->GetPlayer()->IsStatueOfLiberty(); });
        if (!(PlayerControllerIt == PlayerControllers.end()))
        {
            auto &Player = (*PlayerControllerIt)->GetPlayer();
            std::cout << "The Statue of Liberty no longer teams up with "
                      << Player->GetMonsterName()
                      << "."
                      << std::endl;
            Player->SetStatueOfLiberty(false);
            Player->ChangeVictoryPoints(-STATUS_OF_LIBERTY_VICTORY_POINTS);
        }

        std::cout << "Moreover, you trigger a counterattack by the entire army, and you become the defender of the city: The Statue of Liberty comes to life and teams up with you."
                  << std::endl;
        NewStatueOfLibertyPlayer->SetStatueOfLiberty(true);
        NewStatueOfLibertyPlayer->ChangeVictoryPoints(STATUS_OF_LIBERTY_VICTORY_POINTS);
    }

    void FGameController::StartupPhase()
    {
        DistributeCard();
        GetFirstPlayer();
        assert(CurrentPlayer != -1);
        SelectStartingBoroughs();
    }

    void FGameController::StartMainPhase()
    {
        MainPhase();
    }



    bool FGameController::DistributeCard()
    {
        if (Game->GetDeck().IsEmpty()) {
            return false;
        }
        auto &AvailableCards = Game->GetAvailableCards();
        for (std::unique_ptr<FCard> &Card : AvailableCards)
        {
            if (Card)
            {
                Game->GetDiscardDeck().AddCard(Card);
                assert(Card == nullptr);
            }
            Card = Game->GetDeck().Draw();
        }

        auto newEndIt = std::remove(AvailableCards.begin(), AvailableCards.end(), nullptr);
        //AvailableCards.erase(newEndIt);
        AvailableCards.resize(static_cast<unsigned  long>(newEndIt - AvailableCards.begin()));
        return true;
    }


    //PRIVATE METHODS

    bool FGameController::InitializationPhase()
    {
        Game = std::make_shared<FGame>(std::move(SelectMap()));
        if (!Game->GetConstMap().IsValid())
        {
            return false;
        }

        const int PlayerCount = PromptPlayerCount();

        if (PlayerCount == -1)
        {
            return false;
        }

        CreatePlayerControllers(PlayerCount);

        Game->GetDeck() = FDeck("cards.txt");
        Game->GetDeck().Shuffle();

        FTileStack TileStack = FTileStack("tiles.txt");
        TileStack.Shuffle();
        DistributeTiles(TileStack, Game->GetMutableMap());

        return true;
    }

    std::unique_ptr<FMap> FGameController::SelectMap()
    {
        bool isValid = false;
        std::vector<std::string> MapFiles = GetMapFiles(MAP_PATH);
        if (MapFiles.empty())
        {
            std::cout << std::endl
                      << "Error: No map files have been found."
                      << std::endl;
            return nullptr;
        }
        while (!isValid)
        {
            std::cout << std::endl
                      << "Please choose a map by entering its number (0 to exit):"
                      << std::endl;
            for (int  i = 0; i < MapFiles.size(); ++i)
            {
                std::cout << (i+1)
                          << ". "
                          << MapFiles[i]
                          << std::endl;
            }
            std::cout << ">";
            const int FileNumber = InputSingleDigit();
            if (FileNumber == 0)
            {
                return nullptr;
            }
            else if (1 <= FileNumber && FileNumber <= MapFiles.size())
            {
                std::unique_ptr<FMap> Map = std::make_unique<FMap>(MAP_PATH + MapFiles[FileNumber - 1]);
                if (Map->IsValid())
                {
                    isValid = true;
                    return Map;
                }
                else
                {
                    return nullptr;
                }
            }
            else
            {
                std::cout << std::endl
                          << "Error: Invalid input."
                          << std::endl;
            }
        }
        return nullptr;
    }

    bool FGameController::DistributeTiles(FTileStack &MasterTileStack, FMap &Map)
    {
        while (!MasterTileStack.IsEmpty())
        {
            for (const std::shared_ptr<FBorough> &Borough : Map.GetMutableBoroughs())
            {
                for (const std::unique_ptr<FTileStack> &CurrentTileStack : Borough->GetConstTileStacks())
                {
                    CurrentTileStack->AddTileOnTop(MasterTileStack.Draw());
                    if (MasterTileStack.IsEmpty())
                    {
                        return true;
                    }
                }
            }
        }
        return true;
    }

    int FGameController::PromptPlayerCount()
    {
        bool isValid = false;
        int PlayerCount = 0;
        while (!isValid)
        {
            std::cout << std::endl
                      << "Enter the number of player ("
                      << MINIMUM_PLAYER
                      << "-"
                      << MAXIMUM_PLAYER
                      << " or 0 to exit):"
                      << std::endl
                      << ">";
            PlayerCount = InputSingleDigit();
            if (PlayerCount == 0)
            {
                return -1;
            }
            else if (MINIMUM_PLAYER <= PlayerCount &&
                     PlayerCount <= MAXIMUM_PLAYER)
            {
                std::cout << std::endl;
                isValid = true;
            }
            else
            {
                std::cout << "Invalid number of player. It has to be between "
                          << MINIMUM_PLAYER
                          << " and "
                          << MAXIMUM_PLAYER
                          << ". Please try again."
                          << std::endl;
            }
        }
        return PlayerCount;
    }

    void FGameController::CreatePlayerControllers(int PlayerCount)
    {
        assert(MINIMUM_PLAYER <= PlayerCount && PlayerCount <= MAXIMUM_PLAYER);
        PlayerControllers.reserve(static_cast<unsigned long>(PlayerCount));
        std::unordered_set<std::string> PlayerNames;
        std::vector<bool> AvailableMonsters(MONSTER_COUNT, true);

        for (int i = 0; i < PlayerCount; ++i)
        {
            PlayerControllers.push_back(std::make_unique<FPlayerController>(PlayerNames, AvailableMonsters));
        }
    }

    void FGameController::GetFirstPlayer()
    {
        std::vector<bool> StillRolling(PlayerControllers.size(), true);

        std::cout << "In order to see who goes first, each player rolls the 6 black dice and the 2 green dice, and whoever rolls the most Attacks starts the game."
                  << std::endl;
        while (CurrentPlayer == -1)
        {
            int MaxAttack = -1;
            for (int i = 0; i < static_cast<int>(PlayerControllers.size()); ++i)
            {
                if (StillRolling[i])
                {
                    std::cout << PlayerControllers[i]->GetMonsterName()
                              << ": Press enter to roll the dice.";
                    InputString();
                    std::vector<EDiceFace> DiceResult = PlayerControllers[i]->RollStartDice(BLACK_DICE_COUNT + GREEN_DICE_COUNT);

                    const auto AttackCount = static_cast<int>(std::count_if(DiceResult.begin(), DiceResult.end(),
                                                                            [](const auto &DiceFace) { return DiceFace == EDiceFace::Attack; }));

                    std::cout << "Number of attacks: "
                              << AttackCount
                              << std::endl;
                    if (AttackCount > MaxAttack)
                    {
                        for (int j = 0; j < i; ++j)
                        {
                            StillRolling[j] = false;
                        }
                        StillRolling[i] = true;
                        MaxAttack = AttackCount;
                        CurrentPlayer = i;
                    }
                    else if (AttackCount == MaxAttack)
                    {
                        StillRolling[i] = true;
                        CurrentPlayer = -1;
                    }
                    else
                    {
                        StillRolling[i] = false;
                    }
                }
            }
            if (CurrentPlayer > -1)
            {
                std::cout << PlayerControllers[CurrentPlayer]->GetMonsterName()
                          << " has rolled the highest number of attacks ("
                          << MaxAttack
                          << ")."
                          << std::endl;
            }
            else
            {
                std::cout << "There is a tie! The tied players have to roll again."
                          << std::endl
                          << std::endl;
            }
        }
    }

    void FGameController::SelectStartingBoroughs()
    {
        std::cout << "Starting with the first player, and going clockwise: Place your Monster in the borough of your choice, except Manhattan. There can be no more than 2 Monsters in any borough."
                  << std::endl;
        for (int i = 0; i < PlayerControllers.size(); ++i)
        {
            PlayerControllers[CurrentPlayer]->SelectStartingLocation(Game->GetMutableMap());
            CurrentPlayer = (CurrentPlayer + 1) % static_cast<int>(PlayerControllers.size());
        }
    }

    void FGameController::MainPhase()
    {
        while (CheckVictoriousPlayer() == std::nullopt)
        {
            if (PlayerControllers[CurrentPlayer]->GetPlayer())
            {
                if (PlayerControllers[CurrentPlayer]->GetPlayer()->IsAlive())
                {
                    Game->ShowStatus();
                    PlayerControllers[CurrentPlayer]->TakeTurn(*this);
                }
                else
                {
                    PlayerControllers[CurrentPlayer]->RemovePlayer();
                }

            }
            CurrentPlayer = (CurrentPlayer + 1) % static_cast<int>(PlayerControllers.size());
        }
    }

    std::optional<std::shared_ptr<FPlayer>> FGameController::CheckVictoriousPlayer()
    {
        int PlayerCount = GetPlayerCount();
        if (PlayerCount == 0)
        {
            std::cout << "Everybody died! Nobody win!"
                      << std::endl;
            std::cin.get();
            exit(0);
        }
        else if (PlayerCount == 1)
        {
            auto PlayerControllerIt = std::find_if(PlayerControllers.begin(), PlayerControllers.end(),
                                                   [](const auto &PlayerController) { return PlayerController->GetPlayer(); });
            assert(PlayerControllerIt != PlayerControllers.end());
            std::cout << (*PlayerControllerIt)->GetMonsterName()
                      << " is the only one alive and has won the game!"
                      << std::endl;
            std::cin.get();
            exit(0);
        }

        auto PlayerControllerIt = std::find_if(PlayerControllers.begin(), PlayerControllers.end(),
                                               [](const auto &PlayerController) { return PlayerController->GetPlayer() && PlayerController->GetPlayer()->IsVictorious(); });
        if (PlayerControllerIt != PlayerControllers.end())
        {
            std::cout << (*PlayerControllerIt)->GetMonsterName()
                      << " has at least "
                      << VICTORY_POINTS_TO_WIN_COUNT
                      <<" Victory Points and has won the game!"
                      << std::endl;
            std::cin.get();
            exit(0);
        }

        return std::nullopt;
    }
}