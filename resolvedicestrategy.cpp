// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "helper.h"
#include "resolvedicestrategy.h"
#include "game.h"
//#include "map.h"
#include "player.h"

namespace KingOfNewYork
{
    void HumanResolveDiceStrategy::Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, std::vector<EDiceFace> &DiceResult)
    {
        std::vector<int> DiceSums = GetDiceSums(DiceResult);

        bool Done = false;
        do
        {
            Game.CheckDeadPlayer();
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
                            if (ResolveAttack(Game, Map, Player, DiceSums[Input]))
                            {
                                DiceSums[Input] = 0;
                            }
                            break;
                        case 1:
                            if (ResolveCelebrity(Game, Player, DiceSums[Input]))
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
                            if (ResolveOuch(Game, Map, Player, DiceSums[Input]))
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

    void AggressiveResolveDiceStrategy::Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, std::vector<EDiceFace> &DiceResult)
    {
        std::vector<int> DiceSums = GetDiceSums(DiceResult);

        //1. Celebrity
        if (DiceSums[1] > 0)
        {
            ResolveCelebrity(Game, Player, DiceSums[1]);
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
            ResolveAttack(Game, Map, Player, DiceSums[0]);
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
            ResolveOuch(Game, Map, Player, DiceSums[5]);
            DiceSums[5] = 0;
        }

        if (!Player->IsAlive())
        {
            return;
        }

        //6. Destruction
        if (DiceSums[2] > 0)
        {
            AIResolveDestruction(Player, DiceSums[2]);
            DiceSums[2] = 0;
        }
    }

    void ModerateResolveDiceStrategy::Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, std::vector<EDiceFace> &DiceResult)
    {
        std::vector<int> DiceSums = GetDiceSums(DiceResult);

        //1. Celebrity
        if (DiceSums[1] > 0)
        {
            ResolveCelebrity(Game, Player, DiceSums[1]);
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
            ResolveAttack(Game, Map, Player, DiceSums[0]);
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
            ResolveOuch(Game, Map, Player, DiceSums[5]);
            DiceSums[5] = 0;
        }

        if (!Player->IsAlive())
        {
            return;
        }

        //6. Destruction
        if (DiceSums[2] > 0)
        {
            AIResolveDestruction(Player, DiceSums[2]);
            DiceSums[2] = 0;
        }
    }

    namespace
    {

        std::vector<int> GetDiceSums(std::vector<EDiceFace> &DiceResult)
        {
            std::vector<int> DiceSums(DiceResult.size(), 0);
            for (EDiceFace DiceFace: DiceResult)
            {
                DiceSums[static_cast<int>(DiceFace)]++;
            }
            return  DiceSums;
        }

        const bool ResolveAttack(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, const int NumberOfDice)
        {
            assert(Player->GetBorough() != nullptr);
            const bool bAttackCenter = !Player->GetBorough()->IsCenter();
            if (bAttackCenter)
            {
                std::cout << "Since you are not in Manhattan, each Attack inflicts damage to all Monsters in Manhattan:"
                          << std::endl;
                for (auto Borough : Map.GetBoroughs())
                {
                    if (Borough->IsCenter() && !Borough->GetConstPlayers().empty())
                    {
                        assert(Borough->GetConstPlayers().size() == MAXIMUM_MONSTERS_IN_CENTER);
                        std::shared_ptr<FPlayer> TargetPlayer = Borough->GetMutablePlayers().back();
                        TargetPlayer->TakeDamage(Game, NumberOfDice);

                        if (!TargetPlayer->IsAlive())
                        {
                            break;
                        }

                        std::cout << "Since "
                                  << TargetPlayer->GetPlayerAndMonsterNames()
                                  <<" was attacked while being in Manhattan, he/she may flee Manhattan. Please, let him/her select the borough to move to:"
                                  << std::endl;
                        TargetPlayer->Move(Map, false);
                        break;
                    }
                }
            }
            else
            {
                std::cout << "Since you are in Manhattan, each Attack inflicts damage to all Monsters outside Manhattan:"
                          << std::endl;
                for (auto Borough : Map.GetBoroughs())
                {
                    if (!Borough->IsCenter())
                    {
                        for (std::shared_ptr<FPlayer> TargetPlayer : Borough->GetMutablePlayers())
                        {
                            TargetPlayer->TakeDamage(Game, NumberOfDice);
                        }
                    }
                }
            }

            return true;
        }

        const bool ResolveCelebrity(FGame &Game, std::shared_ptr<FPlayer> Player, const int NumberOfDice)
        {
            int NewVictoryPoints = 0;
            if (Player->IsCelebrity())
            {
                NewVictoryPoints = NumberOfDice;
            }
            else
            {
                if (NumberOfDice >= DICE_FOR_CELEBRITY_COUNT)
                {
                    Game.ChangeCelebrity(Player);
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

        const bool HumanResolveDestruction(std::shared_ptr<FPlayer> Player, const int NumberOfDice)
        {
            assert(Player->GetBorough() != nullptr);
            bool bAllEmptyStack = true;
            int MinimumDurability = MAXIMUM_TILE_DURABILITY;
            for (const std::unique_ptr<FTileStack> &TileStack : Player->GetBorough()->GetConstTileStacks())
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
                for (int i = 0; i < Player->GetBorough()->GetConstTileStacks().size(); ++i)
                {
                    std::cout << (i + 1)
                              << ". "
                              << (Player->GetBorough()->GetConstTileStacks()[i]->IsEmpty()
                                  ? "Tile stack is empty"
                                  : Player->GetBorough()->GetConstTileStacks()[i]->GetTopTileInfo()->GetTileInfo())
                              << "."
                              << std::endl;
                }
                std::cout << ">";
                int Input = InputSingleDigit() - 1;
                if (0 <= Input && Input <= Player->GetBorough()->GetConstTileStacks().size() - 1)
                {
                    if (Player->GetBorough()->GetConstTileStacks()[Input]->IsEmpty())
                    {
                        std::cout << "Tile stack is empty. Please try again."
                                  << std::endl;
                    }
                    else{
                        if (Player->GetBorough()->GetConstTileStacks()[Input]->GetTopTileInfo()->GetDurability() <= NumberOfDice)
                        {
                            SelectedStack = Input;
                        }
                        else
                        {
                            std::cout << "You need "
                                      << Player->GetBorough()->GetConstTileStacks()[Input]->GetTopTileInfo()->GetDurability()
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
            FTile DestructedTile = FTile(*(Player->GetBorough()->GetConstTileStacks()[SelectedStack]->GetTopTileInfo()));
            Player->GetBorough()->GetConstTileStacks()[SelectedStack]->DestructTopTile();
            std::cout << "Destructed "
                      << GetTileTypeString(DestructedTile.GetTileType())
                      << "."
                      << std::endl;
            Player->EarnMonsterResources(EMonsterResource(static_cast<int>(DestructedTile.GetTileType())/2), DestructedTile.GetReward());

            int NewNumberOfDice = NumberOfDice - DestructedTile.GetDurability();
            if (NewNumberOfDice > 0)
            {
                HumanResolveDestruction(Player, NewNumberOfDice);
            }
            return true;
        }

        const bool AIResolveDestruction(std::shared_ptr<FPlayer> Player, const int NumberOfDice)
        {
            assert(Player->GetBorough() != nullptr);
            bool bAllEmptyStack = true;
            int SelectedStack = -1;
            for (int i = 0; i < Player->GetBorough()->GetConstTileStacks().size(); ++i)
            {
                if (!Player->GetBorough()->GetConstTileStacks()[i]->IsEmpty() &&
                        Player->GetBorough()->GetConstTileStacks()[i]->GetTopTileInfo()->GetDurability() <= NumberOfDice)
                {
                    bAllEmptyStack = false;
                    SelectedStack = i;
                    break;
                }
            }

            if (bAllEmptyStack)
            {
                std::cout << "There are no buildings or units to destruct."
                          << std::endl;
                return true;
            }

            std::cout << "The following buildings/units are in your borough:"
                      << std::endl;
            for (int i = 0; i < Player->GetBorough()->GetConstTileStacks().size(); ++i)
            {
                std::cout << (i + 1)
                          << ". "
                          << (Player->GetBorough()->GetConstTileStacks()[i]->IsEmpty()
                              ? "Tile stack is empty"
                              : Player->GetBorough()->GetConstTileStacks()[i]->GetTopTileInfo()->GetTileInfo())
                          << "."
                          << std::endl;
            }

            if (SelectedStack == -1)
            {
                std::cout << "No buildings can be deleted with "
                          << NumberOfDice
                          << " dice left."
                          << std::endl;
                return true;
            }

            //Make a copy of the tile for convenience.
            FTile DestructedTile = FTile(*(Player->GetBorough()->GetConstTileStacks()[SelectedStack]->GetTopTileInfo()));
            Player->GetBorough()->GetConstTileStacks()[SelectedStack]->DestructTopTile();
            std::cout << "Destructed "
                      << GetTileTypeString(DestructedTile.GetTileType())
                      << "."
                      << std::endl;
            Player->EarnMonsterResources(EMonsterResource(static_cast<int>(DestructedTile.GetTileType())/2), DestructedTile.GetReward());

            int NewNumberOfDice = NumberOfDice - DestructedTile.GetDurability();
            if (NewNumberOfDice > 0)
            {
                AIResolveDestruction(Player, NewNumberOfDice);
            }
            return true;
        }


        const bool ResolveEnergy(std::shared_ptr<FPlayer> Player, const int NumberOfDice)
        {
            assert(NumberOfDice>0);
            Player->ChangeEnergyCubes(NumberOfDice);
            return true;
        }

        const bool ResolveHeal(std::shared_ptr<FPlayer> Player, const int NumberOfDice)
        {
            assert(NumberOfDice > 0);
            if (Player->GetBorough()->IsCenter())
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

        const bool ResolveOuch(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, const int NumberOfDice)
        {
            assert(NumberOfDice > 0);
            switch (NumberOfDice)
            {
                case 1:
                {
                    std::cout << "Since you rolled 1 Ouch, the Units in your borough attack you; you suffer 1 damage per Unit tile in your borough."
                              << std::endl;
                    int Damage = Player->GetBorough()->GetUnitCount();
                    if (Damage > 0)
                    {
                        Player->TakeDamage(Game, Damage);
                    }
                    break;
                }
                case 2:
                {
                    std::cout << "Since you rolled 2 Ouch, the Units in your borough attack all the Monsters in your borough; each Monster in your borough suffers 1 damage per Unit tile in your borough."
                              << std::endl;
                    int Damage = Player->GetBorough()->GetUnitCount();
                    if (Damage > 0)
                    {
                        for (std::shared_ptr<FPlayer> &TargetPlayer : Player->GetBorough()->GetMutablePlayers())
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
                    for (auto Borough : Map.GetBoroughs())
                    {
                        int Damage = Borough->GetUnitCount();
                        for (std::shared_ptr<FPlayer> &Player : Borough->GetMutablePlayers()) {
                            //Do the check inside the loop to make sure the Status of Liberty is properly removed.
                            if (Damage > 0) {
                                Player->TakeDamage(Game, Damage);
                            }
                        }
                    }
                    Game.ChangeStatueOfLiberty(Player);
                }
            }

            return true;
        }
    }
}
