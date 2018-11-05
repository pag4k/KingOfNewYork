// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <cassert>
#include <iostream>

#include "game.h"
#include "player.h"
#include "helper.h"

namespace KingOfNewYork
{
    FGame::FGame()
    {
        if (!InitializationPhase())
        {
            std::cout << "Error: There was a problem during the initialization phase."
                      << std::endl;
        }
        if (!StartupPhase())
        {
            std::cout << "Error: There was a problem during the startup phase."
                      << std::endl;
        }
        MainPhase();
    }

    FGame::~FGame()
    {
        Players.clear();
        Superstar = nullptr;
        StatusOfLiberty = nullptr;
    }

    void FGame::Print() const
    {
        std::cout << "Number of players: " << static_cast<int>(Players.size()) << std::endl;
        for (const std::shared_ptr<FPlayer> &Player : Players)
        {
            std::cout << "\t-";
            Player->PrintShort();
        }
        
        std::cout << "Monster in Manhattam: ";
        if (PlayersInCenter.empty())
        {
            std::cout << "No one." << std::endl;
        }
        else
        {
            for (const std::shared_ptr<FPlayer> &Player : Players)
            {
                std::cout   << "\t-"
                            << GetMonsterNameString(Player->GetMonsterName())
                            << std::endl;
            }
        }

        std::cout   << "Superstar: "
                    << (Superstar ?
                        GetMonsterNameString(Superstar->GetMonsterName()) :
                        "No one")
                    << std::endl;
        std::cout << "Status of Liberty: "
                << (StatusOfLiberty ?
                    GetMonsterNameString(StatusOfLiberty->GetMonsterName()) :
                    "No one")
                << std::endl;

        std::cout << "Number of cards in deck: " << Deck.Size() << std::endl;
        std::cout << "Number of cards in discard deck: "
                  << DiscardDeck.Size()
                  << std::endl;

        std::cout << "Tokens left:" << std::endl;
        for (int i = 0; i < TOKEN_TYPE_COUNT; ++i)
        {
            std::cout   << "\t-"
                        << GetTokenTypeString(ETokenType(i))
                        << ": "
                        << TokenInventory[i]
                        << std::endl;
        }

        std::cout   << "Energy cubes left: "
                    << EnergyCubes
                    << std::endl;

        std::cout << "Available cards:" << std::endl;
        for (const std::unique_ptr<FCard> &Card : AvailableCards)
        {
            if (Card)
            {
                std::cout << "\t-"
                        << Card->GetName()
                        << std::endl;
            }
            
        }
    }

    void FGame::ShuffleAndPrintDeck()
    {
        Deck.Shuffle();
        Deck.Print();
    }

    std::unique_ptr<FCard> FGame::GetCard(const int Index) {
        assert(AvailableCards[Index]);
        std::unique_ptr<FCard> Card = std::move(AvailableCards[Index]);
        assert(AvailableCards[Index] == nullptr);
        AvailableCards[Index] = Deck.Draw();
        if (AvailableCards[Index])
        {
            std::cout << "New card available:"
                      << std::endl;
            AvailableCards[Index]->Print();

        }
        return Card;
    }

    const bool FGame::InitializationPhase()
    {
        if (!SelectMap())
        {
            return false;
        }

        const int PlayerCount = GetPlayerCount();

        if (PlayerCount == -1)
        {
            return false;
        }

        CreatePlayers(PlayerCount);

        Superstar = nullptr;
        StatusOfLiberty = nullptr;

        Deck = FDeck("cards.txt");
        Deck.Shuffle();
        for (int i = 0; i < MAXIMUM_AVAILABLE_CARDS; ++i)
        {
            AvailableCards.push_back(nullptr);
        }
        DistributeCard();

        FTileStack TileStack = FTileStack("tiles.txt");
        TileStack.Shuffle();
        DistributeTiles(TileStack);

        for (int &Token : TokenInventory)
        {
            Token = STARTING_TOKENS;
        }

        EnergyCubes = MAXIMUM_ENERGY_CUBES;
        return true;
    }

    void FGame::DistributeCard()
    {
        for (std::unique_ptr<FCard> &Card : AvailableCards)
        {
            if (Card)
            {
                DiscardDeck.AddCard(Card);
                assert(Card == nullptr);
            }
            Card = Deck.Draw();
        }

    }

    const bool FGame::DistributeTiles(FTileStack &MasterTileStack)
    {
        assert(Map != nullptr);
        while (!MasterTileStack.IsEmpty())
        {
            for (int i = 0; i < Map->BoroughCount(); ++i)
            {
                for (const std::unique_ptr<FTileStack> &CurrentTileStack : Map->GetBorough(i)->GetConstTileStacks())
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

    const bool FGame::SelectMap()
    {
        bool isValid = false;
        std::vector<std::string> MapFiles = GetMapFiles(MAP_PATH);
        if (MapFiles.empty())
        {
            std::cout << std::endl
                      << "Error: No map files have been found."
                      << std::endl;
            return false;
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
                return false;
            }
            else if (1 <= FileNumber && FileNumber <= MapFiles.size())
            {
                Map = std::make_shared<FMap>(MAP_PATH + MapFiles[FileNumber - 1]);
                if (Map->IsValid())
                {
                    isValid = true;
                }
                else
                {
                    //TODO: Not sure if I need that. I think it should force the
                    //cleaning of the memory since at that point, it is the only pointer to map.
                    Map.reset();
                    Map = nullptr;
                }
            }
            else
            {
                std::cout << std::endl
                          << "Error: Invalid input."
                          << std::endl;
            }
        }
        return true;
    }

    const int FGame::GetPlayerCount()
    {
        bool isValid = false;
        int PlayerCount;
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

    void FGame::CreatePlayers(const int PlayerCount)
    {
        assert(MINIMUM_PLAYER <= PlayerCount &&
               PlayerCount <= MAXIMUM_PLAYER);
        Players.reserve(static_cast<unsigned long>(PlayerCount));
        std::vector<std::string> PlayerNames;
        PlayerNames.reserve(static_cast<unsigned long>(PlayerCount));
        bool bAvailableMonsters[MONSTER_COUNT];
        for (bool &bAvailableMonster : bAvailableMonsters)
        {
            bAvailableMonster = true;
        }

        for (int i = 0; i < PlayerCount; ++i)
        {
            Players.push_back(
                std::make_shared<FPlayer>(
                    PlayerNames, bAvailableMonsters));
            //Players.back()->PrintLong();
        }
    }

    const bool FGame::StartupPhase()
    {
        GetFirstPlayer();

        if (CurrentPlayer == -1)
        {
            return false;
        }

        SelectStartingBoroughs();
        return true;
    }

    void FGame::GetFirstPlayer()
    {
        std::vector<bool> StillRolling;
        for (int i = 0; i < static_cast<int>(Players.size()); ++i)
        {
            StillRolling.push_back(true);
        }

        std::cout << "In order to see who goes first, each player rolls the 6 black dice and the 2 green dice, and whoever rolls the most Attacks starts the game."
                  << std::endl;
        while (CurrentPlayer == -1)
        {
            int MaxAttack = -1;
            for (int i = 0; i < static_cast<int>(Players.size()); ++i)
            {
                if (StillRolling[i])
                {
                    std::cout << Players[i]->GetPlayerAndMonsterNames()
                              << ": Press enter to roll the dice.";
                    std::string Trash;
                    std::getline(std::cin, Trash);
                    Players[i]->RollDice(BLACK_DICE_COUNT + GREEN_DICE_COUNT, 1);
                    int AttackCount = Players[i]->GetAttackCount();
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
                std::cout << Players[CurrentPlayer]->GetPlayerAndMonsterNames()
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

    void FGame::SelectStartingBoroughs()
    {
        std::cout << "Starting with the first player, and going clockwise: Place your Monster in the borough of your choice, except Manhattan. There can be no more than 2 Monsters in any borough."
                  << std::endl;
        for (int i = 0; i < Players.size(); ++i)
        {
            Players[CurrentPlayer]->SelectStartingLocation(*Map);
            CurrentPlayer = (CurrentPlayer + 1) % static_cast<int>(Players.size());
        }
        //CurrentPlayer = (CurrentPlayer + 1) % static_cast<int>(Players.size());
    }

    void FGame::MainPhase()
    {
        while (VictoriousPlayer() == nullptr)
        {
            Players[CurrentPlayer]->TakeTurn(*Map, *this);
            CurrentPlayer = (CurrentPlayer + 1) % static_cast<int>(Players.size());
        }
    }

    void FGame::CheckDeadPlayer()
    {
        bool bNewDead = true;
        while (bNewDead)
        {
            bNewDead = false;
            bool bDeadAfterCurrent = true;
            for (auto it = Players.begin(); it != Players.end(); ++it)
            {
                std::shared_ptr<FPlayer> Player = *it;
                if (!Player->IsAlive())
                {
                    if (bDeadAfterCurrent)
                    {
                        CurrentPlayer--;
                    }
                    CleanDeadPlayer(Player);
                    Players.erase(it);
                    bNewDead = true;
                    break;
                }
                if (Player == Players[CurrentPlayer])
                {
                    bDeadAfterCurrent = false;
                }

            }
        }

    }

    void FGame::CleanDeadPlayer(std::shared_ptr<FPlayer> DeadPlayer)
    {
        assert(DeadPlayer);
        if (static_cast<int>(Players.size()) == 1)
        {
            std::cout << "Everybody died! Nobody win!"
                      << std::endl;
            std::cin.get();
            exit(0);
        }
        //Remove player from Borough
        for (auto it = DeadPlayer->GetBorough()->GetConstPlayers().begin();
             it != DeadPlayer->GetBorough()->GetConstPlayers().end();
             ++it)
        {
            if (*it == DeadPlayer)
            {
                DeadPlayer->GetBorough()->GetMutablePlayers().erase(it);
                break;
            }
        }
    }

    std::shared_ptr<FPlayer> FGame::VictoriousPlayer()
    {
        if (static_cast<int>(Players.size()) == 1)
        {
            std::cout << Players[0]->GetPlayerAndMonsterNames()
                      << " is the only one alive and has won the game!"
                      << std::endl;
            std::cin.get();
            exit(0);
        }
        for (std::shared_ptr<FPlayer> &Player : Players)
        {
            if (Player->IsVictorious())
            {
                std::cout << Player->GetPlayerAndMonsterNames()
                          << " has at least "
                          << VICTORY_POINTS_TO_WIN_COUNT
                          <<" Victory Points and has won the game!"
                          << std::endl;
                std::cin.get();
                exit(0);
            }
        }
        return nullptr;
    }
}
