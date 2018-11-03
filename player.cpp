// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>

#include "player.h"
#include "helper.h"
#include "card.h"

namespace KingOfNewYork
{
    FPlayer::FPlayer(
        std::vector<std::string> &PlayerNames,
        bool bAvailableMonsters[])
    {
        PlayerName = "";
        EnterPlayerName(PlayerNames);
        MonsterName = EMonsterName::None;
        SelectMonster(bAvailableMonsters);
        Borough = nullptr;

        DiceRoller = FDiceRoller();


        for (int &Token : TokenInventory)
        {
            Token = 0;
        }

        EnergyCubes = 0;
        LifePoints = MAXIMUM_LIFE_POINTS;
        VictoryPoints = 0;

        bCelebrity = false;
        bStatueOfLiberty = false;
    }

    const std::string FPlayer::GetPlayerAndMonsterNames()
    {
        return GetPlayerName() + "(" + GetMonsterNameString(GetMonsterName()) + ")";
    }

    void FPlayer::TakeTurn(FMap &Map)
    {
        std::cout << GetPlayerAndMonsterNames()
                  << " turn:"
                  << std::endl;

        std::cout << "Roll dice phase. Press enter to start:"
                  << std::endl;

        std::cin.get();

        RollDice(BLACK_DICE_COUNT, MAXIMUM_ROLL);

        std::cout << "Resolve dice phase. Press enter to start:"
                  << std::endl;

        std::cin.get();

        ResolveDice();

        std::cout << "Move phase. Press enter to start:"
                  << std::endl;

        std::cin.get();

        Move(Map);

        std::cout << "Buy card phase. Press enter to start:"
                  << std::endl;

        std::cin.get();

        BuyCards();

        std::cout << "Turn over. Press enter to end."
                  << std::endl;

        std::cin.get();
    }

    void FPlayer::SetCelebrity(const bool bCelebrity)
    {
        this->bCelebrity = bCelebrity;
    }

    void FPlayer::RollDice(const int DiceCount, const int RollCount)
    {
        CurrentDiceResult = DiceRoller.BeginRolling(DiceCount, RollCount);
    }

    const int FPlayer::GetAttackCount() const
    {
        assert(!CurrentDiceResult.empty());
        int AttackCount = 0;
        for (EDiceFace DiceFace : CurrentDiceResult)
        {
            if (DiceFace == EDiceFace::Attack)
            {
                AttackCount++;
            }
        }
        return AttackCount;
    }

    void FPlayer::ResolveDice()
    {
        assert(!CurrentDiceResult.empty());
        int DiceSums[FACE_ON_DICE_COUNT];
        for (int &DiceSum : DiceSums) {
            DiceSum = 0;
        }
        for (EDiceFace DiceFace: CurrentDiceResult)
        {
            DiceSums[static_cast<int>(DiceFace)]++;
        }

        bool Done = false;
        do
        {
            std::cout << "### Resolve the dice ###" << std::endl;
            for (int i = 0; i < FACE_ON_DICE_COUNT; ++i)
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
            int Input = InputSingleDigit()-1;
            if (0 <= Input && Input <= FACE_ON_DICE_COUNT-1)
            {
                if (DiceSums[Input] > 0)
                {
                    std::cout << "Resolving "
                            << GetDiceFaceString(EDiceFace(Input))
                            << " dice:"
                            << std::endl;
                    switch (Input)
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
                        default:
                            assert(true);
                    }
                    Done = true;
                    for (int &DiceSum : DiceSums) {
                        if (DiceSum > 0)
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

    void FPlayer::Move(FMap &Map)
    {

    }

    void FPlayer::BuyCards()
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
        std::cout << "Monster: "
                  << GetMonsterNameString(MonsterName)
                  << std::endl;

        if (Borough)
        {
            std::cout << "Position: " << Borough->Name << std::endl;
        }

        DiceRoller.PrintRollHistory();

        std::cout << "Number of cards: " << Cards.size() << std::endl;
        for (const std::unique_ptr<FCard> &Card : Cards) {
            if (Card)
            {
                std::cout << "\t-"
                        << Card->GetName()
                        << std::endl;
            }
        }

        std::cout << "Tokens:" << std::endl;
        for (int i = 0; i < TOKEN_TYPE_COUNT; ++i)
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
        while (PlayerName.empty())
        {
            std::cout   << "Player "
                        << PlayerNames.size() + 1
                        << ", please enter your name:" << std::endl;
            std::cout << ">";
            bool bError = false;
            const std::string Input = InputString();
            if (Input.empty())
            {
                std::cout << "Invalid input, please try again."
                          << std::endl
                          << std::endl;
                continue;
            }
            for (const std::string &Name: PlayerNames)
            {
                if (Input == Name)
                {
                    std::cout << "Name already taken, please try again."
                              << std::endl
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
            for (int i = 0; i < MONSTER_COUNT; ++i)
            {
                if (bAvailableMonsters[i])
                {
                    std::cout << (i + 1)
                              << " "
                              << GetMonsterNameString(
                                    static_cast<EMonsterName>(i))
                              << std::endl;
                }
            }
            std::cout << ">";
            const int Input = InputSingleDigit();
            if (1 <= Input &&
                Input <= MONSTER_COUNT &&
                bAvailableMonsters[Input - 1])
            {
                MonsterName = static_cast<EMonsterName>(Input - 1);
                bAvailableMonsters[Input - 1] = false;
            }
            else
            {
                std::cout << "Invalid input, please try again."
                          << std::endl
                          << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void FPlayer::SelectStartingLocation(FMap &Map)
    {
        while (!Borough)
        {
            {
                std::cout << GetPlayerAndMonsterNames()
                          << ", please select your starting borough:"
                          << std::endl;
                for (int i = 0; i < Map.BoroughCount(); ++i)
                {
                    std::shared_ptr<FBorough> CurrentBorough = Map.GetBorough(i);
                    std::vector<std::shared_ptr<FPlayer>> &CurrentPlayers =
                        CurrentBorough->Players;
                    //TODO: This assumes that MAXIMUM_PLAYERS_IN_BOROUGH = 2.
                    if (CurrentPlayers.size() < MAXIMUM_PLAYERS_IN_BOROUGH &&
                        CurrentBorough->bStartingLocation)
                    {
                        std::cout << (i + 1)
                                  << ". "
                                  << CurrentBorough->Name
                                  << (CurrentPlayers.size() == 1 ?
                                      " (" +
                                      GetMonsterNameString(
                                          CurrentPlayers[0]->GetMonsterName()) +
                                      " is already there)" : "")
                                  << std::endl;
                    }
                }
                std::cout << ">";
                const int Input = InputSingleDigit();
                std::cout << std::endl;

                if (1 <= Input && Input <= Map.BoroughCount())
                {
                    std::shared_ptr<FBorough> SelectedBorough = Map.GetBorough(Input - 1);
                    std::vector<std::shared_ptr<FPlayer>> &SelectedPlayers =
                        SelectedBorough->Players;
                    if (SelectedPlayers.size() < MAXIMUM_PLAYERS_IN_BOROUGH &&
                        SelectedBorough->bStartingLocation)
                    {
                        //Removing player from prevous borough list.
                        if (Borough)
                        {
                            for (auto it = Borough->Players.begin();
                                 it != Borough->Players.end();
                                 ++it)
                            {
                                if (*it == shared_from_this())
                                {
                                    Borough->Players.erase(it);
                                }
                            }
                        }
                        //Setting player position to selected borough.
                        Borough = SelectedBorough;
                        //Put player in the borough player list.
                        SelectedBorough->Players.push_back(shared_from_this());
                    }
                    else
                    {
                        std::cout << "Invalid borough, please try again."
                                  << std::endl
                                  << std::endl;
                    }
                }
                else
                {
                    std::cout << "Invalid input, please try again."
                              << std::endl
                              << std::endl;
                }
            }
        }
    }

    const bool FPlayer::ResolveAttack(const int NumberOfDice)
    {
        assert(Borough != nullptr);
        if (Borough->bInManhattan)
        {
            std::cout << "Since you are in Manhattan, each Attack inflicts damage to all Monsters outside Manhattan:"
                      << std::endl;
                      //TODO: Need to add access to other players via the Game or something.
        }
        else
        {
            std::cout << "Since you are not in Manhattan, each Attack inflicts damage to all Monsters in Manhattan:"
                      << std::endl;
            //TODO: Need to add access to other players via the Game or something.
        }
        //COULD USE THE MAP!
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
            if (NumberOfDice >= DICE_FOR_CELEBRITY_COUNT)
            {
                bCelebrity = true;
                NewVictoryPoints = NumberOfDice -
                                   (DICE_FOR_CELEBRITY_COUNT - 1);
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
        //TODO: NOT SURE HOW TO DEAL WITH VICTORY.
        //WITH A SETTER OR A CHECK AFTER TURN.
        return true;
    }

    const bool FPlayer::ResolveDestruction(const int NumberOfDice)
    {
        assert(Borough != nullptr);
        bool bAllEmptyStack = true;
        int MinimumDurability = MAXIMUM_TILE_DURABILITY;
        for (std::unique_ptr<FTileStack> &TileStack : Borough->TileStacks)
        {
            if (!TileStack->IsEmpty() && TileStack->GetTopTileInfo()->GetDurability() < MinimumDurability)
            {
                bAllEmptyStack = false;
                MinimumDurability = TileStack->GetTopTileInfo()->GetDurability();
            }
        }
        if (bAllEmptyStack)
        {
            std::cout << "There are no buildings or units to destruct."
                      << std::endl;
            return true;
        }
        if (MinimumDurability > NumberOfDice)
        {
            std::cout << "You only have "
                      << NumberOfDice
                      << " dice left and the weakest building/unit has "
                      << MinimumDurability
                      << " durability. You cannot do anything."
                      << std::endl;
            return true;
        }
        int SelectedStack = -1;
        do {
            std::cout << "The following buildings/units are in your borough. Select the number of the one you want to destruct (you have "
                      << NumberOfDice
                      << " left):"
                      << std::endl;
            for (int i = 0; i < Borough->TileStacks.size(); ++i)
            {
                std::cout << (i + 1)
                          << ". "
                          << (Borough->TileStacks[i]->IsEmpty()
                             ? "Tile stack is empty"
                             : Borough->TileStacks[i]->GetTopTileInfo()->GetTileInfo())
                          << "."
                          << std::endl;
            }
            std::cout << ">";
            int Input = InputSingleDigit() - 1;
            if (0 <= Input && Input <= Borough->TileStacks.size() - 1)
            {
                if (Borough->TileStacks[Input]->IsEmpty())
                {
                    std::cout << "Tile stack is empty. Please try again."
                              << std::endl;
                }
                else{
                    if (Borough->TileStacks[Input]->GetTopTileInfo()->GetDurability() <= NumberOfDice)
                    {
                        SelectedStack = Input;
                    }
                    else
                    {
                        std::cout << "You need "
                                  << Borough->TileStacks[Input]->GetTopTileInfo()->GetDurability()
                                  << " destruction dice, but you only have "
                                  << NumberOfDice
                                  << ". Please try again."
                                  << std::endl;
                    }
                }
                
            }
            else
            {
                std::cout << "Invalid input. Please try again."
                          << std::endl;
            }
        } while (SelectedStack == -1);

        int NewNumberOfDice = NumberOfDice - Borough->TileStacks[SelectedStack]->GetTopTileInfo()->GetDurability();
        Borough->TileStacks[SelectedStack]->DestructTopTile();
        if (NewNumberOfDice > 0)
        {
            ResolveDestruction(NewNumberOfDice);
        }
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
