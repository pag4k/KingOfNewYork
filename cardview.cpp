// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "cardview.h"
#include "gamecontroller.h"
#include "helper.h"

namespace KingOfNewYork
{
    FCardView::FCardView(std::shared_ptr<FGameController> GameController) : GameController(GameController)
    {
        for (const auto &Card: GameController->GetGame().GetDeck().GetCards()) Card->Attach(this);
    }

    FCardView::~FCardView()
    {
        for (const auto &Card: GameController->GetGame().GetDeck().GetCards()) Card->Detach(this);

        for (const auto &Card: GameController->GetGame().GetDiscardDeck().GetCards()) Card->Detach(this);

        for (auto& PlayerController : GameController->GetPlayerControllers())
        {
            if (PlayerController->GetPlayer())
            {
                for (const auto &Card: PlayerController->GetPlayer()->GetCards()) Card->Detach(this);
            }
        }
    }

    void FCardView::Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event)
    {
        const auto Card = std::dynamic_pointer_cast<const FCard>(Subject);
        assert(Card);

        switch (Event->ObserverEvent)
        {
            case EObserverEvent::BoughtCard:
            {
                const auto BoughtCardEvent = std::dynamic_pointer_cast<const FBoughtCardEvent>(Event);
                assert(BoughtCardEvent);

                PrintNormal("Bought card: " + Card->GetName());
                return;
            }
            case EObserverEvent::DisplayCard:
            {
                const auto DisplayCardEvent = std::dynamic_pointer_cast<const FDisplayCardEvent>(Event);
                assert(DisplayCardEvent);

                PrintNormal("\tName: " + Card->GetName() +
                           "\n\tHow to Play: " + GetHowToPlayString(Card->GetHowToPlay()) +
                           "\n\tEnergy Cost: " + std::to_string(Card->GetEnergyCost()) +
                           "\n\tEffect: " + Card->GetEffect());
                return;
            }
            case EObserverEvent::UsedCard:
            {
                const auto UsedCardEvent = std::dynamic_pointer_cast<const FUsedCardEvent>(Event);
                assert(UsedCardEvent);

                PrintNormal("Used card: " + Card->GetName() + " -> " + Card->GetEffect());
                return;
            }
            default:
                assert(true);
        }
    }
}