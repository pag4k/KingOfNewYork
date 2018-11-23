// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <memory>
#include "observer.h"

namespace KingOfNewYork
{
    class FGame;
    class FSubject;
    class IObserverEvent;

    //A class that observes the player notifications.
    class FPlayerView : public IObserver
    {
    public:
        explicit FPlayerView(std::shared_ptr<FGame> Game);
        ~FPlayerView() override;
        void Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event) override;
    private:
        std::shared_ptr<FGame> Game;
    };
}

#endif
