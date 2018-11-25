// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "rolldicestrategy.h"
#include <algorithm>
#include "player.h"
#include "diceroller.h"
#include "helper.h"

namespace KingOfNewYork
{
    void HumanRollDiceStrategy::Execute(std::shared_ptr<FDiceRoller> DiceRoller, std::shared_ptr<FPlayer> Player, const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult)
    {
        int CurrentRollCount = 0;

        while (CurrentRollCount < RollCount)
        {
            std::cout << "### Roll number "
                      << (CurrentRollCount + 1)
                      << " out of "
                      << (RollCount)
                      << " ###"
                      << std::endl;

            DiceRoller->RollDice(DiceCount, OutDiceResult);

            CurrentRollCount++;
            if (CurrentRollCount >= RollCount)
            {
                break;
            }

            std::cout << "#############################"
                      << std::endl;
            std::cout << "Enter the numbers of the dice you want to reroll and"
                      << " press enter."
                      << std::endl;
            std::cout << "Ex.: \"123\" (all other characters will be ignored)."
                      << std::endl;
            std::cout << "Write nothing to end the rolling phase)."
                      << std::endl;
            std::cout << "> ";

            std::string input = InputString();
            if (input.empty())
            {
                break;
            }

            for (int i = 0; i < DiceCount; i++)
            {
                if (input.find((char)(i+1+48)) != std::string::npos)
                {
                    OutDiceResult[i] = EDiceFace::None;
                }
            }
        }
        PostRolling(Player, OutDiceResult);
    }

    void AggressiveRollDiceStrategy::Execute(std::shared_ptr<FDiceRoller> DiceRoller, std::shared_ptr<FPlayer> Player, const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult)
    {
        //focuses on attack or destruction during the role dice step
        int CurrentRollCount = 0;

        while (CurrentRollCount < RollCount)
        {
            std::cout << "### Roll number "
                      << (CurrentRollCount + 1)
                      << " out of "
                      << (RollCount)
                      << " ###"
                      << std::endl;

            DiceRoller->RollDice(DiceCount, OutDiceResult);

            CurrentRollCount++;
            if (CurrentRollCount >= RollCount)
            {
                break;
            }

            bool bReroll = false;
            for (int i = 0; i < DiceCount; i++)
            {
                if (OutDiceResult[i] != EDiceFace::Attack && OutDiceResult[i] != EDiceFace::Destruction)
                {
                    OutDiceResult[i] = EDiceFace::None;
                    bReroll = true;
                }
            }

            if (!bReroll)
            {
                std::cout << "Ending rolling phase..." << std::endl;
                break;
            }
        }
        PostRolling(Player, OutDiceResult);
    }

    void ModerateRollDiceStrategy::Execute(std::shared_ptr<FDiceRoller> DiceRoller, std::shared_ptr<FPlayer> Player, const int DiceCount, const int RollCount, std::vector<EDiceFace> &OutDiceResult)
    {
        //focus on balancing the health, grabbing power-ups or storming Manhattan which quickly builds rewards
        int CurrentRollCount = 0;

        while (CurrentRollCount < RollCount)
        {
            std::cout << "### Roll number "
                      << (CurrentRollCount + 1)
                      << " out of "
                      << (RollCount)
                      << " ###"
                      << std::endl;

            DiceRoller->RollDice(DiceCount, OutDiceResult);

            CurrentRollCount++;
            if (CurrentRollCount >= RollCount)
            {
                break;
            }

            bool bReroll = false;
            for (int i = 0; i < DiceCount; i++)
            {
                if (OutDiceResult[i] != EDiceFace::Ouch && OutDiceResult[i] != EDiceFace::Celebrity)
                {
                    OutDiceResult[i] = EDiceFace::None;
                    bReroll = true;
                }
            }

            if (!bReroll)
            {
                break;
            }
        }
        PostRolling(Player, OutDiceResult);
    }

    namespace
    {
        void PostRolling(std::shared_ptr<FPlayer> Player, std::vector<EDiceFace> &OutDiceResult)
        {
            bool bChanged = false;
            if (Player->UseCard(7))
            {
                OutDiceResult.push_back(EDiceFace::Attack);
                OutDiceResult.push_back(EDiceFace::Attack);
            }
            int DestructionCount = static_cast<int>(std::count_if(OutDiceResult.begin(), OutDiceResult.end(),
                                                                  [](const auto &DiceFace) { return DiceFace == EDiceFace::Destruction; } ));
            if (DestructionCount > 0 && DestructionCount % 2 == 0 && Player->UseCard(8))
            {
                switch (DestructionCount) {
                    case 2:
                        OutDiceResult.push_back(EDiceFace::Attack);
                        break;
                    case 4:
                        OutDiceResult.push_back(EDiceFace::Attack);
                        OutDiceResult.push_back(EDiceFace::Attack);
                        break;
                    case 6:
                        Player->SetVictorious();
                        break;
                }
            }
            if (Player->UseCard(11))
            {
                OutDiceResult.push_back(EDiceFace::Destruction);
            }
            bool bHasCelebrity = std::find(OutDiceResult.begin(), OutDiceResult.end(), EDiceFace::Celebrity) != OutDiceResult.end();
            if (bHasCelebrity && Player->UseCard(21))
            {
                Player->ChangeVictoryPoints(1);
            }
            int UnitCount = Player->GetBorough()->GetUnitCount();
            if (UnitCount >= 3 && Player->UseCard(28))
            {
                OutDiceResult.push_back(EDiceFace::Destruction);
                OutDiceResult.push_back(EDiceFace::Energy);
            }
        }
    }
}
