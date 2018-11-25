// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "diceview.h"
#include "gamecontroller.h"
#include "game.h"
#include "playercontroller.h"
#include "player.h"
#include "diceroller.h"

namespace KingOfNewYork
{
    FDiceView::FDiceView(std::shared_ptr<FGameController> GameController) : GameController(GameController)
    {
        for (auto& PlayerController : GameController->GetPlayerControllers())
        {
            if (PlayerController->GetPlayer())
            {
                PlayerController->GetDiceRoller()->Attach(this);
            }
        }
    }

    FDiceView::~FDiceView()
    {
        for (auto& PlayerController : GameController->GetPlayerControllers())
        {
            if (PlayerController->GetPlayer())
            {
                PlayerController->GetDiceRoller()->Detach(this);
            }
        }
    }

    void FDiceView::Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event)
    {
        const auto DiceRoller = std::dynamic_pointer_cast<const FDiceRoller>(Subject);
        assert(DiceRoller);

        switch (Event->ObserverEvent)
        {
            case EObserverEvent::RolledDice:
            {
                const auto RolledDiceEvent = std::dynamic_pointer_cast<const FRolledDiceEvent>(Event);
                assert(RolledDiceEvent);

                for (int i = 0; i < RolledDiceEvent->DiceResult.size(); ++i)
                {
                    std::cout << (i + 1)
                              << ": "
                              << GetDiceFaceString(RolledDiceEvent->DiceResult[i])
                              << (RolledDiceEvent->NewRoll[i] ? " (new roll)" : "")
                              << std::endl;
                }
                return;

            }
            case EObserverEvent::RollingDone:
            {
                const auto RollingDoneEvent = std::dynamic_pointer_cast<const FRollingDoneEvent>(Event);
                assert(RollingDoneEvent);

            }
        }
        assert(true);
    }
}

