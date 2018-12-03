// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "resolvedicestrategy.h"
#include "gamecontroller.h"
#include "helper.h"

namespace KingOfNewYork
{
    void HumanResolveDiceStrategy::Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player, std::vector<EDiceFace> &DiceResult)
    {
        auto &Game = GameController.GetGame();
        auto &Map = Game.GetMutableMap();
        std::vector<int> DiceSums = GetDiceSums(DiceResult);

        bool Done = false;
        do
        {
            if (!Player->IsAlive())
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
                    Done = true;
                    switch (Input)
                    {
                        case 0:
                            if (ResolveAttack(GameController, Player, DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 1:
                            if (ResolveCelebrity(GameController, Player, DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 2:
                            if (HumanResolveDestruction(Player, DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 3:
                            if (ResolveEnergy(Player, DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 4:
                            if (ResolveHeal(Player, DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 5:
                            if (ResolveOuch(GameController, Player, DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        default:
                            assert(true);
                    }
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

    void AggressiveResolveDiceStrategy::Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player, std::vector<EDiceFace> &DiceResult)
    {
        auto &Game = GameController.GetGame();
        auto &Map = Game.GetMutableMap();
        std::vector<int> DiceSums = GetDiceSums(DiceResult);

        //1. Celebrity
        if (DiceSums[1] > 0)
        {
            ResolveCelebrity(GameController, Player, DiceSums[1]);
            DiceSums[1] = 0;
        }

        //2. Energy
        if (DiceSums[3] > 0)
        {
            ResolveEnergy(Player, DiceSums[3]);
            DiceSums[3] = 0;
        }

        //3. Attack
        if (DiceSums[0] > 0)
        {
            ResolveAttack(GameController, Player, DiceSums[0]);
            DiceSums[0] = 0;
        }

        //4. Heal
        if (DiceSums[4] > 0)
        {
            ResolveHeal(Player, DiceSums[4]);
            DiceSums[4] = 0;
        }

        //5. Ouch
        if (DiceSums[5] > 0)
        {
            ResolveOuch(GameController, Player, DiceSums[5]);
            DiceSums[5] = 0;
        }

        if (!Player->IsAlive())
        {
            return;
        }

        //6. Destruction
        if (DiceSums[2] > 0)
        {
            AIResolveDestruction(Player, DiceSums[2], false);
            DiceSums[2] = 0;
        }
    }

    void ModerateResolveDiceStrategy::Execute(FGameController &GameController, std::shared_ptr<FPlayer> &Player, std::vector<EDiceFace> &DiceResult)
    {
        auto &Game = GameController.GetGame();
        auto &Map = Game.GetMutableMap();
        std::vector<int> DiceSums = GetDiceSums(DiceResult);

        //1. Celebrity
        if (DiceSums[1] > 0)
        {
            ResolveCelebrity(GameController, Player, DiceSums[1]);
            DiceSums[1] = 0;
        }

        //2. Energy
        if (DiceSums[3] > 0)
        {
            ResolveEnergy(Player, DiceSums[3]);
            DiceSums[3] = 0;
        }

        //3. Attack
        if (DiceSums[0] > 0)
        {
            ResolveAttack(GameController, Player, DiceSums[0]);
            DiceSums[0] = 0;
        }

        //4. Heal
        if (DiceSums[4] > 0)
        {
            ResolveHeal(Player, DiceSums[4]);
            DiceSums[4] = 0;
        }

        //5. Ouch
        if (DiceSums[5] > 0)
        {
            ResolveOuch(GameController, Player, DiceSums[5]);
            DiceSums[5] = 0;
        }

        if (!Player->IsAlive())
        {
            return;
        }

        //6. Destruction
        if (DiceSums[2] > 0)
        {
            AIResolveDestruction(Player, DiceSums[2], true);
            DiceSums[2] = 0;
        }
    }

    namespace
    {

        std::vector<int> GetDiceSums(std::vector<EDiceFace> &DiceResult)
        {
            std::vector<int> DiceSums(FACE_ON_DICE_COUNT, 0);
            for (EDiceFace DiceFace: DiceResult)
            {
                DiceSums[static_cast<int>(DiceFace)]++;
            }
            return  DiceSums;
        }

        bool ResolveAttack(FGameController &GameController, std::shared_ptr<FPlayer> &Player, int NumberOfDice)
        {
            PrintNormal("### Resolving " + std::to_string(NumberOfDice) + " Attack dice ###");
            assert(Player->GetMutableBorough() != nullptr);
            auto &Game = GameController.GetGame();
            auto &Map = Game.GetMutableMap();
            const bool bAttackCenter = !Player->GetMutableBorough()->IsCenter();
            if (Player->UseCard(22))
            {
                NumberOfDice *= 2;
            }

            if (bAttackCenter)
            {
                std::cout << "Since you are not in Manhattan, each Attack inflicts damage to all Monsters in Manhattan:"
                          << std::endl;
                for (const std::shared_ptr<FBorough> &Borough : Map.GetMutableBoroughs())
                {
                    if (Borough->IsCenter() && !Borough->GetConstPlayers().empty())
                    {
                        assert(Borough->GetConstPlayers().size() == MAXIMUM_MONSTERS_IN_CENTER);
                        std::shared_ptr<FPlayer> &TargetPlayer = Borough->GetMutablePlayers().back();
                        int BonusAttack = 0;
                        if (TargetPlayer->GetLifePoints() > Player->GetLifePoints() && Player->UseCard(23))
                        {
                            BonusAttack = 1;
                        }
                        TargetPlayer->TakeDamage(Game, NumberOfDice + BonusAttack);

                        if (!TargetPlayer->IsAlive())
                        {
                            break;
                        }

                        std::cout << "Since "
                                  << TargetPlayer->GetMonsterName()
                                  <<" was attacked while being in Manhattan, he/she may flee Manhattan."
                                  << std::endl;
                        auto &TargetPlayerController = GameController.GetPlayerController(TargetPlayer);
                        TargetPlayerController->Move(Map, false, false);
                        break;
                    }
                }
            }
            else
            {
                std::cout << "Since you are in Manhattan, each Attack inflicts damage to all Monsters outside Manhattan:"
                          << std::endl;
                for (const std::shared_ptr<FBorough> &Borough : Map.GetMutableBoroughs())
                {
                    if (!Borough->IsCenter())
                    {
                        auto TargetPlayers = Borough->GetMutablePlayers();
                        for (const std::shared_ptr<FPlayer> &TargetPlayer : TargetPlayers)
                        {
                            int BonusAttack = 0;
                            if (TargetPlayer->GetLifePoints() > Player->GetLifePoints() && Player->UseCard(23))
                            {
                                BonusAttack = 1;
                            }
                            TargetPlayer->TakeDamage(Game, NumberOfDice + BonusAttack);
                        }
                    }
                }
            }

            return true;
        }

        bool ResolveCelebrity(FGameController &GameController, std::shared_ptr<FPlayer> &Player, const int NumberOfDice)
        {
            PrintNormal("### Resolving " + std::to_string(NumberOfDice) + " Celebrity dice ###");
            int NewVictoryPoints = 0;
            if (Player->IsCelebrity())
            {
                NewVictoryPoints = NumberOfDice;
            }
            else
            {
                if (NumberOfDice >= DICE_FOR_CELEBRITY_COUNT)
                {
                    GameController.ChangeCelebrity(Player);
                    NewVictoryPoints = NumberOfDice - (DICE_FOR_CELEBRITY_COUNT - 1);
                }
            }
            if (NewVictoryPoints > 0)
            {
                Player->ChangeVictoryPoints(NewVictoryPoints);
            }
            else
            {
                std::cout << "You did not roll enough Celebrity to earn any Victory Points."
                          << std::endl;
            }
            return true;
        }

        int GetMinimumDurability(const std::shared_ptr<FBorough> &Borough)
        {
            auto &TileStacks = Borough->GetMutableTileStacks();
            auto &Units = Borough->GetUnits();
            int MinimumDurability = MAXIMUM_TILE_DURABILITY;

            for (const auto &TileStack : TileStacks)
            {
                if (!TileStack->IsEmpty() && TileStack->GetTopTile()->GetDurability() < MinimumDurability)
                {
                    MinimumDurability = TileStack->GetTopTile()->GetDurability();
                }
            }

            //const auto &MinUnit = std::min_element(Units.begin(), Units.end(),
            //                                       [](const auto &A, const auto &B){ return A->GetDurability() < B->GetDurability(); });


            for (const auto &Unit : Units)
            {
                if (Unit->GetDurability() < MinimumDurability)
                {
                    MinimumDurability = Unit->GetDurability();
                }
            }
            return MinimumDurability;
        }


        bool HumanResolveDestruction(std::shared_ptr<FPlayer> &Player, const int NumberOfDice)
        {
            PrintNormal("### Resolving " + std::to_string(NumberOfDice) + " Destruction dice ###");
            assert(Player->GetMutableBorough());
            auto &Borough = Player->GetMutableBorough();
            auto &TileStacks = Borough->GetMutableTileStacks();
            auto &Units = Borough->GetUnits();
            auto TileStackCount = static_cast<int>(std::count_if(TileStacks.begin(), TileStacks.end(),
                                                                [](const auto &TileStack) { return !TileStack->IsEmpty(); }));

            if (TileStackCount == 0 && Borough->GetUnitCount() == 0)
            {
                PrintNormal("There are no buildings or units to destruct.");
                return true;
            }

            const int MinimumDurability = GetMinimumDurability(Borough);

            if (MinimumDurability > NumberOfDice)
            {
                PrintNormal("You only have " +  std::to_string(NumberOfDice) + " dice left and the weakest building/unit has " + std::to_string(MinimumDurability) + " durability. You cannot do anything.");
                return true;
            }

            int Input = 0;
            int UsedDice = 0;

            while(Input > -TILESTACK_IN_BOROUGH_COUNT)
            {
                PrintNormal("The following buildings/units are in your borough. Select the number of the one you want to destruct (you have " + std::to_string(NumberOfDice) + " left):");
                for (int i = 0; i < TileStacks.size(); ++i)
                {
                    PrintList(i + 1, (TileStacks[i]->IsEmpty() ? "Tile stack is empty" : TileStacks[i]->GetTopTile()->GetTileInfo()) + ".");
                }
                for (int i = 0; i < Borough->GetUnitCount(); ++i)
                {
                    PrintList(i + static_cast<int>(TileStacks.size()) + 1, Units[i]->GetTileInfo() + ".");
                }

                std::cout << ">";
                Input = InputSingleDigit() - 1;
                if (0 <= Input && Input <= TileStacks.size() - 1)
                {
                    if (TileStacks[Input]->IsEmpty())
                    {
                        PrintNormal("Tile stack is empty. Please try again.");
                    }
                    else{
                        if (TileStacks[Input]->GetTopTile()->GetDurability() <= NumberOfDice)
                        {
                            UsedDice = TileStacks[Input]->GetTopTile()->GetDurability();
                            Player->DestroyBuilding(TileStacks[Input]);
                            break;
                        }
                        else
                        {
                            PrintNormal("You need " + std::to_string(TileStacks[Input]->GetTopTile()->GetDurability()) + " destruction dice, but you only have " + std::to_string(NumberOfDice) + ". Please try again.");
                        }
                    }
                }
                else if (TileStacks.size() <= Input && Input <= TileStacks.size() + Borough->GetUnitCount() - 1)
                {
                    Input -= TileStacks.size();
                    if (Units[Input]->GetDurability() <= NumberOfDice)
                    {
                        UsedDice = Units[Input]->GetDurability();
                        Player->DestroyUnit(Units[Input]);
                        break;
                    }
                    else
                    {
                        PrintNormal("You need " + std::to_string(Units[Input]->GetDurability()) + " destruction dice, but you only have " + std::to_string(NumberOfDice) + ". Please try again.");
                    }
                }
                else
                {
                        PrintNormal("Invalid input. Please try again.");
                }
            }

            int NewNumberOfDice = NumberOfDice - UsedDice;

            if (NewNumberOfDice > 0)
            {
                HumanResolveDestruction(Player, NewNumberOfDice);
            }
            return true;
        }

        bool AIResolveDestruction(std::shared_ptr<FPlayer> &Player, int NumberOfDice, bool bPrioritizeUnit)
        {
            PrintNormal("### Resolving " + std::to_string(NumberOfDice) + " Destruction dice ###");
            assert(Player->GetMutableBorough());
            auto &Borough = Player->GetMutableBorough();
            auto &TileStacks = Borough->GetMutableTileStacks();
            auto &Units = Borough->GetUnits();
            auto TileStackCount = static_cast<int>(std::count_if(TileStacks.begin(), TileStacks.end(),
                                                                [](const auto &TileStack) { return !TileStack->IsEmpty(); }));

            if (TileStackCount == 0 && Borough->GetUnitCount() == 0)
            {
                PrintNormal("There are no buildings or units to destruct.");
                return true;
            }

            const int MinimumDurability = GetMinimumDurability(Borough);

            if (MinimumDurability > NumberOfDice)
            {
                PrintNormal("You only have " +  std::to_string(NumberOfDice) + " dice left and the weakest building/unit has " + std::to_string(MinimumDurability) + " durability. You cannot do anything.");
                return true;
            }

            int Input = -1;

            if (bPrioritizeUnit)
            {
                for (int i = 0; i < Borough->GetUnitCount(); ++i)
                {
                    if (Units[i]->GetDurability() <= NumberOfDice)
                    {
                        Input = static_cast<int>(TileStacks.size()) + i;
                        break;
                    }
                }
                if (Input == -1)
                {
                    for (int i = 0; i < TileStacks.size(); ++i)
                    {
                        if (!TileStacks[i]->IsEmpty() && TileStacks[i]->GetTopTile()->GetDurability() <= NumberOfDice)
                        {
                            Input = i;
                            break;
                        }
                    }
                }
            }
            else
            {
                for (int i = 0; i < TileStacks.size(); ++i)
                {
                    if (!TileStacks[i]->IsEmpty() && TileStacks[i]->GetTopTile()->GetDurability() <= NumberOfDice)
                    {
                        Input = i;
                        break;
                    }
                }

                if (Input == -1)
                {
                    for (int i = 0; i < Borough->GetUnitCount(); ++i)
                    {
                        if (Units[i]->GetDurability() <= NumberOfDice)
                        {
                            Input = static_cast<int>(TileStacks.size()) + i;
                            break;
                        }
                    }
                }
            }

            assert(Input != -1);

            int UsedDice = 0;

            PrintNormal("The following buildings/units are in your borough (you have " + std::to_string(NumberOfDice) + " left):");
            for (int i = 0; i < TileStacks.size(); ++i)
            {
                PrintList(i + 1, (TileStacks[i]->IsEmpty() ? "Tile stack is empty" : TileStacks[i]->GetTopTile()->GetTileInfo()) + ".");
            }
            for (int i = 0; i < Borough->GetUnitCount(); ++i)
            {
                PrintList(i + static_cast<int>(TileStacks.size()) + 1, Units[i]->GetTileInfo() + ".");
            }

            if (0 <= Input && Input <= TileStacks.size() - 1)
            {
                UsedDice = TileStacks[Input]->GetTopTile()->GetDurability();
                Player->DestroyBuilding(TileStacks[Input]);
            }
            else if (TileStacks.size() <= Input && Input <= TileStacks.size() + Borough->GetUnitCount() - 1)
            {
                Input -= TileStacks.size();
                UsedDice = Units[Input]->GetDurability();
                Player->DestroyUnit(Units[Input]);
            }

            int NewNumberOfDice = NumberOfDice - UsedDice;

            if (NewNumberOfDice > 0)
            {
                AIResolveDestruction(Player, NewNumberOfDice, bPrioritizeUnit);
            }
            return true;
        }

        bool ResolveEnergy(std::shared_ptr<FPlayer> &Player, const int NumberOfDice)
        {
            PrintNormal("### Resolving " + std::to_string(NumberOfDice) + " Energy dice ###");
            assert(NumberOfDice>0);
            Player->ChangeEnergyCubes(NumberOfDice);
            return true;
        }

        bool ResolveHeal(std::shared_ptr<FPlayer> &Player, const int NumberOfDice)
        {
            PrintNormal("### Resolving " + std::to_string(NumberOfDice) + " Heal dice ###");
            assert(NumberOfDice > 0);
            if (Player->GetMutableBorough()->IsCenter())
            {
                std::cout << "Since you are in Manhattan, you cannot use Heal rolls to heal."
                          << std::endl;
            }
            else
            {
                Player->ChangeLifePoints(NumberOfDice);
            }
            return true;
        }

        bool ResolveOuch(FGameController &GameController, std::shared_ptr<FPlayer> &Player, const int NumberOfDice)
        {
            PrintNormal("### Resolving " + std::to_string(NumberOfDice) + " Ouch dice ###");
            assert(NumberOfDice > 0);
            auto &Game = GameController.GetGame();
            auto &Map = Game.GetMutableMap();

            switch (NumberOfDice)
            {
                case 1:
                {
                    std::cout << "Since you rolled 1 Ouch, the Units in your borough attack you; you suffer 1 damage per Unit tile in your borough."
                              << std::endl;
                    int Damage = Player->GetMutableBorough()->GetUnitCount();
                    int FinalDamage = Damage;
                    if (Player->UseCard(18))
                    {
                        FinalDamage--;
                    }

                    if (FinalDamage > 0)
                    {
                        Player->TakeDamage(Game, Damage);
                    }
                    break;
                }
                case 2:
                {
                    std::cout << "Since you rolled 2 Ouch, the Units in your borough attack all the Monsters in your borough; each Monster in your borough suffers 1 damage per Unit tile in your borough."
                              << std::endl;
                    int Damage = Player->GetMutableBorough()->GetUnitCount();
                    auto TargetPlayers = Player->GetMutableBorough()->GetMutablePlayers();
                    for (const std::shared_ptr<FPlayer> &TargetPlayer : TargetPlayers)
                    {
                        int FinalDamage = Damage;
                        if (TargetPlayer == Player && Player->UseCard(18))
                        {
                            FinalDamage--;
                        }

                        if (FinalDamage > 0)
                        {
                            TargetPlayer->TakeDamage(Game, Damage);
                        }
                    }
                    break;
                }
                default:
                {
                    std::cout << "Since you rolled 3 Ouch or more, all Units in the entire city attack; each Monster suffers 1 damage per Unit tile in his borough."
                              << std::endl;
                    for (const auto &Borough : Map.GetMutableBoroughs())
                    {
                        int Damage = Borough->GetUnitCount();
                        auto TargetPlayers = Borough->GetMutablePlayers();
                        for (const std::shared_ptr<FPlayer> &TargetPlayer : TargetPlayers)
                        {
                            //Do the check inside the loop to make sure the Status of Liberty is properly removed.
                            if (Damage > 0) {
                                TargetPlayer->TakeDamage(Game, Damage);
                            }
                        }
                    }
                    GameController.ChangeStatueOfLiberty(Player);
                }
            }

            return true;
        }
    }
}
