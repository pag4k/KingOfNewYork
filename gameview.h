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
    class FGameView : public IObserver
    {
    public:
        explicit FGameView(std::shared_ptr<FGame> Game);
        ~FGameView() override;
        void Update(const std::shared_ptr<FSubject> &Subject, const std::shared_ptr<IObserverEvent> &Event) override;
    private:
        std::shared_ptr<FGame> Game;
    };
}

#endif
