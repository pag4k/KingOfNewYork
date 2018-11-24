// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "cardview.h"
#include <algorithm>
#include "game.h"
#include "playercontroller.h"
#include "player.h"
#include "helper.h"

namespace KingOfNewYork
{
    FCardView::FCardView(std::shared_ptr<FGame> Game) : Game(Game)
    {
        for (const auto &Card: Game->GetDeck().GetCards()) Card->Attach(this);
    }

    FCardView::~FCardView()
    {
        for (const auto &Card: Game->GetDeck().GetCards()) Card->Detach(this);

        for (const auto &Card: Game->GetDiscardDeck().GetCards()) Card->Detach(this);

        for (auto& PlayerController : Game->GetPlayerControllers())
        {
            if (PlayerController->GetPlayer())
            {
                for (const auto &Card: PlayerController->GetPlayer()->GetCards()) Card->Detach(this);
            }
        }
    }

    void FCardView::Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event)
    {
        //TODO: Not sure if it will only observe players.
        const auto Card = std::dynamic_pointer_cast<const FCard>(Subject);
        assert(Card);

        switch (Event->ObserverEvent)
        {
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