// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include <assert.h>

#include "player.h"
#include "helper.h"
#include "card.h"

namespace KingOfNewYork
{
    FPlayer::FPlayer(std::vector<std::string> &PlayerNames, bool bAvailableMonsters[])
    {
        PlayerName = "";
        EnterPlayerName(PlayerNames);
        MonsterName = EMonsterName::None;
        SelectMonster(bAvailableMonsters);
        Position = nullptr;

        DiceRoller = FDiceRoller();

        for (int i = 0; i < NUMBER_OF_TOKEN_TYPE; ++i)
        {
            TokenInventory[i] = 0;
        }

        EnergyCubes = 0;
        LifePoints = MAXIMUM_LIFE_POINTS;
        VictoryPoints = 0;

        bCelebrity = false;
        bStatueOfLiberty = false;

        //PrintLong();

        //RollDice();
        //ResolveDice();
    }

    FPlayer::~FPlayer()
    {
        //delete DiceRoller;
        //DiceRoller = nullptr;
    }

    void FPlayer::RollDice()
    {
        CurrentDiceResult = DiceRoller.BeginRolling();
    }

    void FPlayer::ResolveDice()
    {
        assert(!CurrentDiceResult.empty());
        int DiceSums[NUMBER_OF_FACES_ON_DICE];
        for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; ++i)
        {
            DiceSums[i] = 0;
        }
        for (EDiceFace DiceFace: CurrentDiceResult)
        {
            DiceSums[static_cast<int>(DiceFace)]++;
        }

        bool Done = false;
        do
        {
            std::cout << "### Resolve the dice ###" << std::endl;
            for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; ++i)
            {
                std::cout << (i + 1)
                        << ". "
                        << DiceSums[i]
                        << "x "
                        << GetDiceFaceString(EDiceFace(i))
                        << std::endl;
            }
            std::cout << "Enter the number of the action you want to resolve:"
                    << std::endl
                    << ">";
            int Input = InputSingleDigit();
            if (0 <= Input && Input <= NUMBER_OF_FACES_ON_DICE)
            {
                if (DiceSums[Input] > 0)
                {
                    std::cout << "Resolving "
                            << GetDiceFaceString(EDiceFace(Input))
                            << " dice:"
                            << std::endl;
                    switch (Input + 1)
                    {
                        case 0:
                            if (ResolveAttack(DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 1:
                            if (ResolveCelebrity(DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 2:
                            if (ResolveDestruction(DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 3:
                            if (ResolveEnergy(DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 4:
                            if (ResolveHeal(DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 5:
                            if (ResolveOuch(DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                    }
                    Done = true;
                    for (int i = 0; i < NUMBER_OF_FACES_ON_DICE; ++i)
                    {
                        if (DiceSums[i] > 0)
                        {
                            Done = false;
                            break;
                        }
                    }
                }
                else
                {
                    std::cout   << "No "
                                << GetDiceFaceString(EDiceFace(Input))
                                << " dice to resolve."
                                << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid input!" << std::endl;
            }
        } while (!Done);


    }

    void FPlayer::Move()
    {

    }

    void FPlayer::PrintShort() const
    {
        std::cout   << "Name: " << PlayerName
                    << " Monster: " << GetMonsterNameString(MonsterName)
                    << std::endl;

    }

    void FPlayer::PrintLong() const
    {
        std::cout << "Name: " << PlayerName << std::endl;
        std::cout << "Monster: " << GetMonsterNameString(MonsterName) << std::endl;

        if (Position)
        {
            std::cout << "Position: " << Position->Name << std::endl;
        }

        DiceRoller.PrintRollHistory();

        std::cout << "Number of cards: " << Cards.size() << std::endl;
        for (int i = 0; i < Cards.size(); ++i)
        {
            if (Cards[i])
            {
                std::cout << "\t-"
                        << Cards[i]->GetName()
                        << std::endl;
            }
        }

        std::cout << "Tokens:" << std::endl;
        for (int i = 0; i < NUMBER_OF_TOKEN_TYPE; ++i)
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
        while (PlayerName == "")
        {
            std::cout   << "Player "
                        << PlayerNames.size() + 1
                        << ", please enter your name:" << std::endl;
            std::cout << ">";
            bool bError = false;
            const std::string Input = InputString();
            if (Input == "")
            {
                std::cout << "Invalid input, please try again." << std::endl
                        << std::endl;
                bError = true;
                continue;
            }
            for (std::string Name: PlayerNames)
            {
                if (Input == Name)
                {
                    std::cout << "Name already taken, please try again." << std::endl
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
            for (int i = 0; i < NUMBER_OF_MONSTERS; ++i)
            {
                if (bAvailableMonsters[i])
                {
                    std::cout << (i + 1) << " " << GetMonsterNameString(static_cast<EMonsterName>(i)) << std::endl;
                }
            }
            std::cout << ">";
            const int Input = InputSingleDigit();
            if (1 <= Input && Input <= NUMBER_OF_MONSTERS && bAvailableMonsters[Input-1])
            {
                MonsterName = static_cast<EMonsterName>(Input - 1);
                bAvailableMonsters[Input - 1] = false;
            }
            else
            {
                std::cout << "Invalid input, please try again." << std::endl << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void FPlayer::SelectStartingLocation(FMap &Map)
    {
        while (!Position)
        {
            {
                std::cout << PlayerName
                        << ", please select your starting borough:" << std::endl;
                for (int i = 0; i < Map.BoroughCount(); ++i)
                {
                    FBorough &CurrentBorough = Map.GetBorough(i);
                    if (CurrentBorough.Players.size() < MAXIMUM_PLAYERS_IN_BOROUGH && CurrentBorough.bStartingLocation)
                    {
                        std::cout << (i + 1)
                                << ". "
                                << CurrentBorough.Name
                                << (CurrentBorough.Players.size() == 1 ?
                                    " (" +
                                    GetMonsterNameString(CurrentBorough.Players[0]->GetMonsterName()) +
                                    " is already there)" : "")
                                << std::endl;
                    }
                }
                std::cout << ">";
                const int Input = InputSingleDigit();
                std::cout << std::endl;

                if (1 <= Input &&
                    Input <= Map.BoroughCount() &&
                    Map.GetBorough(Input - 1).Players.size() < MAXIMUM_PLAYERS_IN_BOROUGH &&
                    Map.GetBorough(Input - 1).bStartingLocation)
                {
                    //Removing player from prevous borough list.
                    if (Position)
                    {
                        for (auto it = Position->Players.begin(); it != Position->Players.end(); ++it)
                        {
                            if (*it == shared_from_this())
                            {
                                Position->Players.erase(it);
                            }
                        }
                    }
                    //Setting player position to selected borough.
                    Position = std::make_shared<FBorough>(Map.GetBorough(Input - 1));
                    //Put player in the borough player list.
                    Map.GetBorough(Input - 1).Players.push_back(shared_from_this());
                }
                else
                {
                    std::cout << "Invalid input, please try again." << std::endl
                            << std::endl;
                }
            }
        }
    }

    const bool FPlayer::ResolveAttack(const int NumberOfDice)
    {
        return true;
    }

    const bool FPlayer::ResolveCelebrity(const int NumberOfDice)
    {
        int NewVictoryPoints = 0;
        if (bCelebrity)
        {   
            NewVictoryPoints = NumberOfDice;
        }
        else
        {
            if (NumberOfDice >= NUMBER_OF_DICE_FOR_CELEBRITY)
            {
                bCelebrity = true;
                NewVictoryPoints = NumberOfDice - (NUMBER_OF_DICE_FOR_CELEBRITY - 1);
            }
        }
        VictoryPoints += NewVictoryPoints;
        std::cout << "Earned "
                << NewVictoryPoints
                << " victory point"
                << (NumberOfDice == 1 ? ". " : "s. ")
                << "New total: "
                << VictoryPoints
                << "."
                << std::endl;
        //TODO: NOT SURE HOW TO DEAL WITH VICTORY. WITH A SETTER OR A CHECK AFTER TURN.
        return true;
    }

    const bool FPlayer::ResolveDestruction(const int NumberOfDice)
    {
        return true;
    }

    const bool FPlayer::ResolveEnergy(const int NumberOfDice)
    {
        assert(NumberOfDice>0);
        EnergyCubes += NumberOfDice;
        std::cout   << "Earned "
                    << NumberOfDice
                    << " energy cube"
                    << (NumberOfDice == 1 ? ". " : "s. ")
                    << "New total: "
                    << EnergyCubes
                    << "."
                    << std::endl;
        return true;
    }

    const bool FPlayer::ResolveHeal(const int NumberOfDice)
    {
        assert(NumberOfDice > 0);
        LifePoints += NumberOfDice;
        LifePoints = (LifePoints > MAXIMUM_LIFE_POINTS ? 10 : LifePoints);
        std::cout << "Earned "
                << NumberOfDice
                << " life point"
                << (NumberOfDice == 1 ? ". " : "s. ")
                << "New total: "
                << LifePoints
                << "."
                << std::endl;
        return true;
    }

    const bool FPlayer::ResolveOuch(const int NumberOfDice)
    {
        return true;
    }
}
