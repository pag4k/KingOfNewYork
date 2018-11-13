
#include "helper.h"
#include "resolvedicestrategy.h"
#include "game.h"
//#include "map.h"
#include "player.h"

namespace KingOfNewYork
{
    void HumanResolveDiceStrategy::Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player)
    {
        assert(!Player->GetCurrentDiceResult().empty());
        int DiceSums[FACE_ON_DICE_COUNT];
        for (int &DiceSum : DiceSums) {
            DiceSum = 0;
        }
        for (EDiceFace DiceFace: Player->GetCurrentDiceResult())
        {
            DiceSums[static_cast<int>(DiceFace)]++;
        }

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
                            if (ResolveDestruction(Player, DiceSums[Input]))
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

    void AggressiveResolveDiceStrategy::Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player)
    {

    }

    void ModerateResolveDiceStrategy::Execute(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player)
    {

    }

    namespace
    {

        const bool ResolveAttack(FGame &Game, FMap &Map, std::shared_ptr<FPlayer> Player, const int NumberOfDice)
        {
            assert(Player->GetBorough() != nullptr);
            const bool bAttackCenter = !Player->GetBorough()->IsCenter();
            if (bAttackCenter)
            {
                std::cout << "Since you are not in Manhattan, each Attack inflicts damage to all Monsters in Manhattan:"
                          << std::endl;
                for (int i = 0; i < Map.BoroughCount(); ++i)
                {
                    if (Map.GetBorough(i)->IsCenter() && !Map.GetBorough(i)->GetConstPlayers().empty())
                    {
                        assert(Map.GetBorough(i)->GetConstPlayers().size() == 1);
                        std::shared_ptr<FPlayer> TargetPlayer = Map.GetBorough(i)->GetMutablePlayers().back();
                        TargetPlayer->TakeDamage(Game, NumberOfDice);

                        if (!TargetPlayer->IsAlive())
                        {
                            break;
                        }

                        std::cout << "Since "
                                  << TargetPlayer->GetPlayerAndMonsterNames()
                                  <<" was attacked while being in Manhattan, he/she may flee Manhattan. Please, let him/her select the borough to move to:"
                                  << std::endl;
                        std::string OldBorough = TargetPlayer->GetBorough()->GetName();
                        TargetPlayer->SelectBorough(Map, false, true);
                        if (OldBorough == TargetPlayer->GetBorough()->GetName())
                        {
                            std::cout << TargetPlayer->GetPlayerAndMonsterNames()
                                      << " stayed in "
                                      << TargetPlayer->GetBorough()->GetName()
                                      << "."
                                      << std::endl;
                        }
                        else
                        {
                            std::cout << TargetPlayer->GetPlayerAndMonsterNames()
                                      << " moved from "
                                      << OldBorough
                                      << " to "
                                      << TargetPlayer->GetBorough()->GetName()
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
                        for (std::shared_ptr<FPlayer> TargetPlayer : Map.GetBorough(i)->GetMutablePlayers())
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
                std::cout << "Earned "
                          << Player->EarnVictoryPoints(NewVictoryPoints)
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

        const bool ResolveDestruction(std::shared_ptr<FPlayer> Player, const int NumberOfDice)
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
                      << " and earned "
                      << Player->EarnMonsterResources(EMonsterResource(static_cast<int>(DestructedTile.GetTileType())/2), DestructedTile.GetReward())
                      << "."
                      << std::endl;
            int NewNumberOfDice = NumberOfDice - DestructedTile.GetDurability();
            if (NewNumberOfDice > 0)
            {
                ResolveDestruction(Player, NewNumberOfDice);
            }
            return true;
        }

        const bool ResolveEnergy(std::shared_ptr<FPlayer> Player, const int NumberOfDice)
        {
            assert(NumberOfDice>0);
            //EnergyCubes += NumberOfDice;
            std::cout   << "Earned "
                        << Player->EarnEnergyCubes(NumberOfDice)
                        << "."
                        << std::endl;
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
                //LifePoints += NumberOfDice;
                //LifePoints = (LifePoints > MAXIMUM_LIFE_POINTS ? 10 : LifePoints);
                std::cout << "Earned "
                          << Player->EarnLifePoints(NumberOfDice)
                          << "."
                          << std::endl;
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
                    for (int i = 0; i < Map.BoroughCount(); ++i)
                    {
                        int Damage = Map.GetBorough(i)->GetUnitCount();
                        for (std::shared_ptr<FPlayer> &Player : Map.GetBorough(i)->GetMutablePlayers()) {
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
