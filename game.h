// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include "precompiledheader.h"
#include "map.h"
#include "card.h"
#include "subject.h"

namespace KingOfNewYork
{
    //class FDeck;

    //The main class of the game that handles its basic functions.
    class FGame: public FSubject, public std::enable_shared_from_this<FGame>
    {
    public:
        explicit FGame(std::unique_ptr<FMap> Map);
        std::unique_ptr<FCard> GetCard(int Index);
        std::vector<std::unique_ptr<FCard>> &GetAvailableCards() { return AvailableCards; }
        const FMap &GetConstMap() const { return *Map; }
        FMap &GetMutableMap() { return *Map; }
        FDeck &GetDeck() { return Deck; }
        FDeck &GetDiscardDeck() { return DiscardDeck; }

        void ShowStatus() const;

    private:
        std::unique_ptr<FMap> Map;
        FDeck Deck;
        FDeck DiscardDeck;
        std::vector<std::unique_ptr<FCard>> AvailableCards;
    };
}

#endif
