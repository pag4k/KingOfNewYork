// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <cassert>
#include <algorithm>
#include "game.h"

namespace KingOfNewYork
{
    FGame::FGame(std::unique_ptr<FMap> Map) : Map(std::move(Map))
    {
        AvailableCards = std::vector<std::unique_ptr<FCard>>(MAXIMUM_AVAILABLE_CARDS);
    }

    std::unique_ptr<FCard> FGame::GetCard(int Index) {
        assert(AvailableCards[Index]);
        std::unique_ptr<FCard> Card = std::move(AvailableCards[Index]);
        assert(AvailableCards[Index] == nullptr);
        AvailableCards[Index] = Deck.Draw();
        auto newEndIt = std::remove(AvailableCards.begin(), AvailableCards.end(), nullptr );
        AvailableCards.resize(static_cast<unsigned  long>(newEndIt - AvailableCards.begin()));
        return Card;
    }

    void FGame::ShowStatus() const
    {
        Notify(shared_from_this(), std::make_shared<FBetweenTurnsEvent>(EObserverEvent::BetweenTurns, ""));
    }

}
