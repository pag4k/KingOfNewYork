// ----------------------------------------------------------------------------
// COMP345 Assignment 2
// Due date: November 4, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include <algorithm>

#include "game.h"
#include "player.h"
#include "helper.h"

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
        LevelInCenter = 0;
        DiceRoller = FDiceRoller();


        for (int &Token : TokenInventory)
        {
            Token = 0;
        }

        bAlive = true;
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

    void FPlayer::TakeTurn(FMap &Map, FGame &Game)
    {
        std::cout << GetPlayerAndMonsterNames()
                  << " turn:"
                  << std::endl;

        PrintLong();

        if (Borough->IsCenter())
        {
            std::cout << "Since you are in "
                      << CENTER_LEVEL_NAMES[LevelInCenter]
                      << " Manhattan, you earn "
                      << EarnVictoryPoints(CENTER_VICTORY_POINT_REWARDS[LevelInCenter])
                      << " and "
                      << EarnEnergyCubes(CENTER_ENERGY_CUBE_REWARDS[LevelInCenter])
                      << "."
                      << std::endl;
        }

        std::cout << GetPlayerAndMonsterNames()
                  << ": Roll dice phase. Press enter to start:"
                  << std::endl;

        std::cin.get();

        RollDice(BLACK_DICE_COUNT, MAXIMUM_ROLL);

        std::cout << GetPlayerAndMonsterNames()
                  << ": Resolve dice phase. Press enter to start:"
                  << std::endl;

        std::cin.get();

        ResolveDice(Game, Map);

        Game.CheckDeadPlayer();
        if (!bAlive)
        {
            return;
        }

        std::cout << GetPlayerAndMonsterNames()
                  << ": Move phase. Press enter to start:"
                  << std::endl;

        std::cin.get();

        Move(Map);

        std::cout << GetPlayerAndMonsterNames()
                  << ": Buy card phase. Press enter to start:"
                  << std::endl;

        std::cin.get();

        BuyCards(Game);

        std::cout << GetPlayerAndMonsterNames()
                  << ": Turn over. Press enter to end."
                  << std::endl;

        std::cin.get();
    }

    void FPlayer::SetCelebrity(const bool bCelebrity)
    {
        this->bCelebrity = bCelebrity;
    }

    void FPlayer::SetStatueOfLiberty(const bool bStatueOfLiberty) {
        if (bStatueOfLiberty)
        {
            assert(!this->bStatueOfLiberty);
            this->bStatueOfLiberty = bStatueOfLiberty;
            VictoryPoints += STATUS_OF_LIBERTY_VICTORY_POINTS;
        }
        else
        {
            assert(this->bStatueOfLiberty);
            this->bStatueOfLiberty = bStatueOfLiberty;
            VictoryPoints -= STATUS_OF_LIBERTY_VICTORY_POINTS;
        }
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

    void FPlayer::ResolveDice(FGame &Game, FMap &Map)
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
            Game.CheckDeadPlayer();
            if (!bAlive)
            {
                return;
            }

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
                            if (ResolveAttack(Game, Map, DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 1:
                            if (ResolveCelebrity(Game, DiceSums[Input]))
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
                            if (ResolveOuch(Game, Map, DiceSums[Input]))
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
        if (Borough->IsCenter())
        {
            std::cout << "Since you were already in Manhattan, you must advance to the next zone up there."
                      << std::endl;
            if (LevelInCenter < LEVEL_IN_CENTER_COUNT)
            {
                assert(0 < LevelInCenter && LevelInCenter < LEVEL_IN_CENTER_COUNT);
                LevelInCenter++;
                std::cout << "You moved from "
                          << CENTER_LEVEL_NAMES[LevelInCenter-1]
                          << " Manhattan to "
                          << CENTER_LEVEL_NAMES[LevelInCenter]
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
                std::string OldBorough = Borough->GetName();
                std::cout << "Since there is already "
                          << MAXIMUM_MONSTERS_IN_CENTER
                          << " Monsters in any zone of Manhattan, you have two options: You can move to any borough that doesn’t already have 2 Monsters in it (except Manhattan), or you can just stay in your borough. Please enter the number of the borough you want to move to:"
                          << std::endl;
                SelectBorough(Map, false, false);
                if (OldBorough == Borough->GetName())
                {
                    std::cout << "You stayed in "
                              << Borough->GetName()
                              << "."
                              << std::endl;
                }
                else
                {
                    std::cout << "You moved from "
                              << OldBorough
                              << " to "
                              << Borough->GetName()
                              << "."
                              << std::endl;
                }
            }
            else
            {
                std::string OldBorough = Borough->GetName();
                std::cout << "Since are less than "
                          << MAXIMUM_MONSTERS_IN_CENTER
                          << " Monsters in any zone of Manhattan, you must move there."
                          << "You earn "
                          << EarnVictoryPoints(ENTER_CENTER_VICTORY_POINT_REWARD)
                          << " for doing so."
                          << std::endl;
                MoveTo(CenterBorough);
                LevelInCenter = 1;
                std::cout << "You moved from "
                          << OldBorough
                          << " to "
                          << CENTER_LEVEL_NAMES[LevelInCenter]
                          << " Manhattan."
                          << std::endl;

            }
        }
    }

    void FPlayer::BuyCards(FGame &Game)
    {
        int Input;
        do {
            std::cout << "Please enter the number of the card you want to buy (or 0 to stop buying or 9 to spend "
                      << ENERGY_CUBE_FOR_NEW_CARDS_COUNT
                      << " Energy Cubes to discard the 3 available cards and reveal new ones). You currently have "
                      << EnergyCubes
                      << " Energy Cubes."
                      << std::endl;
            std::vector<std::unique_ptr<FCard>> &AvailableCards = Game.GetAvailableCards();
            for (int i = 0; i < AvailableCards.size(); ++i)
            {
                std::cout << (i+1);
                AvailableCards[i]->Print();
            }
            std::cout << ">";
            Input = InputSingleDigit();
            if (Input == 0)
            {
                break;
            }
            if (Input == 9 && EnergyCubes >= ENERGY_CUBE_FOR_NEW_CARDS_COUNT)
            {
                std::cout << "You spend "
                          << EarnEnergyCubes(-ENERGY_CUBE_FOR_NEW_CARDS_COUNT)
                          << " to get new card."
                          << std::endl;
                Game.DistributeCard();
                continue;
            }
            else if (Input == 9 && EnergyCubes < ENERGY_CUBE_FOR_NEW_CARDS_COUNT)
            {
                std::cout << "You do not have enough Energy Cubes to get new cards."
                          << std::endl;
                continue;
            }
            if (1 <= Input && Input <= MAXIMUM_AVAILABLE_CARDS)
            {
                if (AvailableCards[Input-1] && AvailableCards[Input-1]->GetEnergyCost() <= EnergyCubes)
                {
                    std::cout << "You bough "
                              << AvailableCards[Input-1]->GetName()
                              << " for "
                              << EarnEnergyCubes(-AvailableCards[Input-1]->GetEnergyCost())
                              << "."
                              << std::endl;
                    Cards.push_back(std::move(Game.GetCard(Input-1)));
                }
                else
                {
                    std::cout << "You cannot buy this card."
                              << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid input."
                          << std:: endl;
            }
        } while (Input != 0);

    }

    void FPlayer::PrintShort() const
    {
        std::cout   << "Name: " << PlayerName
                    << " Monster: " << GetMonsterNameString(MonsterName)
                    << std::endl;

    }

    void FPlayer::PrintLong() const
    {
        std::cout << "Current status: "
                  << std::endl;

        if (Borough)
        {
            if (Borough->IsCenter())
            {
                std::cout << "Position: "
                          << CENTER_LEVEL_NAMES[LevelInCenter]
                          << " Manhattan"
                          << std::endl;
            }
            else
            {
                std::cout << "Position: " << Borough->GetName() << std::endl;
            }
        }

        //DiceRoller.PrintRollHistory();

        std::cout << "Number of cards: " << Cards.size() << std::endl;
        for (const std::unique_ptr<FCard> &Card : Cards) {
            if (Card)
            {
                Card->Print();
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
        std::cout << GetPlayerAndMonsterNames()
                  << ", please select your starting borough:"
                  << std::endl;
        SelectBorough(Map, true, false);

    }

    void FPlayer::SelectBorough(FMap &Map, const bool bOnlyStartingLocation, const bool bIncludeCenter)
    {
        int bDone = false;
        while (!bDone)
        {
            for (int i = 0; i < Map.BoroughCount(); ++i)
            {
                std::shared_ptr<FBorough> CurrentBorough = Map.GetBorough(i);
                const std::vector<std::shared_ptr<FPlayer>> &CurrentPlayers =
                        CurrentBorough->GetConstPlayers();
                const int Offset = CurrentBorough == Borough ? 1 : 0;
                if (CurrentPlayers.size() - Offset < MAXIMUM_PLAYERS_IN_BOROUGH &&
                        (!bOnlyStartingLocation || CurrentBorough->IsStartingLocation()) &&
                        (!CurrentBorough->IsCenter() || bIncludeCenter))
                {
                    std::cout << (i + 1)
                              << ". "
                              << CurrentBorough->GetName();
                    if (CurrentPlayers.size() > 0)
                    {
                        std::cout << " (already there: ";
                        for (int j = 0; j < CurrentPlayers.size(); ++j)
                        {
                            if (CurrentPlayers[j] == shared_from_this())
                            {
                                std::cout << "you";
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
            std::cout << ">";
            const int Input = InputSingleDigit();
            std::cout << std::endl;

            if (1 <= Input && Input <= Map.BoroughCount())
            {
                std::shared_ptr<FBorough> SelectedBorough = Map.GetBorough(Input - 1);
                const std::vector<std::shared_ptr<FPlayer>> &SelectedPlayers =
                        SelectedBorough->GetConstPlayers();
                if (SelectedPlayers.size() < MAXIMUM_PLAYERS_IN_BOROUGH &&
                        (!bOnlyStartingLocation || SelectedBorough->IsStartingLocation()))
                {
                    bDone = true;
                    MoveTo(SelectedBorough);
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

    void FPlayer::MoveTo(std::shared_ptr<FBorough> NewBorough)
    {
        assert(NewBorough);
        if (Borough == NewBorough)
        {
            return;
        }
        //Removing player from previous borough list.
        if (Borough)
        {
            bool Erased = false;
            for (auto it = Borough->GetConstPlayers().begin();
                 it != Borough->GetConstPlayers().end();
                 ++it)
            {
                if (*it == shared_from_this())
                {
                    Borough->GetMutablePlayers().erase(it);
                    Erased = true;
                    break;
                }
            }
            assert(Erased);
        }
        //Setting player position to selected borough.
        Borough = NewBorough;
        //Put player in the borough player list.
        Borough->GetMutablePlayers().push_back(shared_from_this());
    }

    const bool FPlayer::ResolveAttack(FGame &Game, FMap &Map, const int NumberOfDice)
    {
        assert(Borough != nullptr);
        const bool bAttackCenter = !Borough->IsCenter();
        if (bAttackCenter)
        {
            std::cout << "Since you are not in Manhattan, each Attack inflicts damage to all Monsters in Manhattan:"
                      << std::endl;
            for (int i = 0; i < Map.BoroughCount(); ++i)
            {
                if (Map.GetBorough(i)->IsCenter() && !Map.GetBorough(i)->GetConstPlayers().empty())
                {
                    assert(Map.GetBorough(i)->GetConstPlayers().size() == 1);
                    std::shared_ptr<FPlayer> &Player = Map.GetBorough(i)->GetMutablePlayers().back();
                    Player->TakeDamage(Game, NumberOfDice);

                    if (!Player->IsAlive())
                    {
                        break;
                    }

                    std::cout << "Since "
                              << Player->GetPlayerAndMonsterNames()
                              <<" was attacked while being in Manhattan, he/she may flee Manhattan. Please, let him/her select the borough to move to:"
                              << std::endl;
                    std::string OldBorough = Player->Borough->GetName();
                    Player->SelectBorough(Map, false, true);
                    if (OldBorough == Player->Borough->GetName())
                    {
                        std::cout << Player->GetPlayerAndMonsterNames()
                                  << " stayed in "
                                  << Player->Borough->GetName()
                                  << "."
                                  << std::endl;
                    }
                    else
                    {
                        std::cout << Player->GetPlayerAndMonsterNames()
                                  << " moved from "
                                  << OldBorough
                                  << " to "
                                  << Player->Borough->GetName()
                                  << "."
                                  << std::endl;
                    }
                    break;
                }
            }
        }
        else
        {
            std::cout << "Since you are in Manhattan, each Attack inflicts damage to all Monsters outside Manhattan:"
                      << std::endl;
            for (int i = 0; i < Map.BoroughCount(); ++i)
            {
                if (!Map.GetBorough(i)->IsCenter())
                {
                    for (std::shared_ptr<FPlayer> &Player : Map.GetBorough(i)->GetMutablePlayers())
                    {
                        Player->TakeDamage(Game, NumberOfDice);
                    }
                }
            }
        }

        return true;
    }

    const bool FPlayer::ResolveCelebrity(FGame &Game, const int NumberOfDice)
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
                for (std::shared_ptr<FPlayer> &Player : Game.GetPlayers())
                {
                    Player->SetCelebrity(false);
                }
                SetCelebrity(true);
                std::cout << "You are now a Celebrity!"
                          << std::endl;
                NewVictoryPoints = NumberOfDice -
                                   (DICE_FOR_CELEBRITY_COUNT - 1);
            }
        }
        //VictoryPoints += NewVictoryPoints;
        if (NewVictoryPoints > 0)
        {
            std::cout << "Earned "
                      << EarnVictoryPoints(NewVictoryPoints)
                      << "."
                      << std::endl;
        }
        else
        {
            std::cout << "You did not roll enough Celebrity to earn any Victory Points."
                      << std::endl;
        }
        return true;
    }

    const bool FPlayer::ResolveDestruction(const int NumberOfDice)
    {
        assert(Borough != nullptr);
        bool bAllEmptyStack = true;
        int MinimumDurability = MAXIMUM_TILE_DURABILITY;
        for (const std::unique_ptr<FTileStack> &TileStack : Borough->GetConstTileStacks())
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
            for (int i = 0; i < Borough->GetConstTileStacks().size(); ++i)
            {
                std::cout << (i + 1)
                          << ". "
                          << (Borough->GetConstTileStacks()[i]->IsEmpty()
                             ? "Tile stack is empty"
                             : Borough->GetConstTileStacks()[i]->GetTopTileInfo()->GetTileInfo())
                          << "."
                          << std::endl;
            }
            std::cout << ">";
            int Input = InputSingleDigit() - 1;
            if (0 <= Input && Input <= Borough->GetConstTileStacks().size() - 1)
            {
                if (Borough->GetConstTileStacks()[Input]->IsEmpty())
                {
                    std::cout << "Tile stack is empty. Please try again."
                              << std::endl;
                }
                else{
                    if (Borough->GetConstTileStacks()[Input]->GetTopTileInfo()->GetDurability() <= NumberOfDice)
                    {
                        SelectedStack = Input;
                    }
                    else
                    {
                        std::cout << "You need "
                                  << Borough->GetConstTileStacks()[Input]->GetTopTileInfo()->GetDurability()
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

        //Make a copy of the tile for convenience.
        FTile DestructedTile = FTile(*(Borough->GetConstTileStacks()[SelectedStack]->GetTopTileInfo()));
        Borough->GetConstTileStacks()[SelectedStack]->DestructTopTile();
        std::cout << "Destructed "
                  << GetTileTypeString(DestructedTile.GetTileType())
                  << " and earned "
                  << EarnMonsterResources(EMonsterResource(static_cast<int>(DestructedTile.GetTileType())/2), DestructedTile.GetReward())
                  << "."
                  << std::endl;
        int NewNumberOfDice = NumberOfDice - DestructedTile.GetDurability();
        if (NewNumberOfDice > 0)
        {
            ResolveDestruction(NewNumberOfDice);
        }
        return true;
    }

    const bool FPlayer::ResolveEnergy(const int NumberOfDice)
    {
        assert(NumberOfDice>0);
        //EnergyCubes += NumberOfDice;
        std::cout   << "Earned "
                    << EarnEnergyCubes(NumberOfDice)
                    << "."
                    << std::endl;
        return true;
    }

    const bool FPlayer::ResolveHeal(const int NumberOfDice)
    {
        assert(NumberOfDice > 0);
        if (Borough->IsCenter())
        {
            std::cout << "Since you are in Manhattan, you cannot use Heal rolls to heal."
                      << std::endl;
        }
        else
        {
            //LifePoints += NumberOfDice;
            //LifePoints = (LifePoints > MAXIMUM_LIFE_POINTS ? 10 : LifePoints);
            std::cout << "Earned "
                      << EarnLifePoints(NumberOfDice)
                      << "."
                    << std::endl;
        }
        return true;
    }

    const bool FPlayer::ResolveOuch(FGame &Game, FMap &Map, const int NumberOfDice)
    {
        assert(NumberOfDice > 0);
        switch (NumberOfDice)
        {
            case 1:
            {
                std::cout << "Since you rolled 1 Ouch, the Units in your borough attack you; you suffer 1 damage per Unit tile in your borough."
                          << std::endl;
                int Damage = Borough->GetUnitCount();
                if (Damage > 0)
                {
                    TakeDamage(Game, Damage);
                }
                break;
            }
            case 2:
            {
                std::cout << "Since you rolled 2 Ouch, the Units in your borough attack all the Monsters in your borough; each Monster in your borough suffers 1 damage per Unit tile in your borough."
                          << std::endl;
                int Damage = Borough->GetUnitCount();
                if (Damage > 0)
                {
                    for (std::shared_ptr<FPlayer> &Player : Borough->GetMutablePlayers())
                    {
                            Player->TakeDamage(Game, Damage);
                    }
                }
                break;
            }
            default:
            {
                std::cout << "Since you rolled 3 Ouch or more, all Units in the entire city attack; each Monster suffers 1 damage per Unit tile in his borough."
                          << std::endl;
                for (int i = 0; i < Map.BoroughCount(); ++i)
                {
                    int Damage = Map.GetBorough(i)->GetUnitCount();
                    for (std::shared_ptr<FPlayer> &Player : Map.GetBorough(i)->GetMutablePlayers()) {
                        //Do the check inside the loop to make sure the Status of Liberty is properly removed.
                        if (Damage > 0) {
                            Player->TakeDamage(Game, Damage);
                        }
                        if (Player->GetStatueOfLiberty()) {
                            Player->SetStatueOfLiberty(false);
                        }
                    }
                }
                std::cout << "Moreover, you trigger a counterattack by the entire army, and you become the defender of the city: The Statue of Liberty comes to life and teams up with you."
                          << std::endl;
                SetStatueOfLiberty(true);
            }

        }

        return true;
    }

    void FPlayer::TakeDamage(FGame &Game, const int Damage)
    {
        assert(Damage > 0);
        assert(bAlive);
        std::cout << GetPlayerAndMonsterNames()
                   << " loses "
                   << EarnLifePoints(-Damage)
                   << "."
                   << std::endl;
        if (LifePoints == 0)
        {
            bAlive = false;
            bStatueOfLiberty = false;
            bCelebrity = false;
            std::cout << GetPlayerAndMonsterNames()
                      << " died!"
                      << std::endl
                      << std::endl;
        }
    }

    const std::string FPlayer::EarnMonsterResources(const EMonsterResource MonsterResource, const int Number)
    {
        assert(Number != 0);
        switch (MonsterResource)
        {
            case EMonsterResource::EnergyCube:
                return EarnEnergyCubes(Number);
            case EMonsterResource::LifePoint:
                return EarnLifePoints(Number);
            case EMonsterResource::VictoryPoint:
                return EarnVictoryPoints(Number);
        }
        assert(true);
        return "ERROR";
    }

    const std::string FPlayer::EarnEnergyCubes(const int Number)
    {
        assert(Number != 0);
        EnergyCubes += Number;
        return std::to_string(std::abs(Number)) + " Energy Cubes (new total: " + std::to_string(EnergyCubes) + ")";
    }

    const std::string FPlayer::EarnLifePoints(const int Number)
    {
        assert(Number != 0);
        LifePoints += Number;
        LifePoints = std::clamp(LifePoints, 0, MAXIMUM_LIFE_POINTS);
        return std::to_string(std::abs(Number)) + " Life Points (new total: " + std::to_string(LifePoints) + ")";
    }

    const std::string FPlayer::EarnVictoryPoints(const int Number)
    {
        assert(Number != 0);
        VictoryPoints += Number;
        return std::to_string(std::abs(Number))+ " Victory Points (new total: " + std::to_string(VictoryPoints) + ")";
    }
}
