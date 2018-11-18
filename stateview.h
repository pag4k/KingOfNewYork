// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef STATEVIEW_H
#define STATEVIEW_H

#include "observer.h"

namespace KingOfNewYork
{
    class FGame;
    class FSubject;
    class IObserverEvent;

    //A class that observes the game notifications.
    class FStateView : public IObserver
    {
    public:
        explicit FStateView(std::shared_ptr<FGame> Game);
        ~FStateView() override;
        void Update(const std::shared_ptr<FSubject> &Subject, const std::shared_ptr<IObserverEvent> &Event) override;
    private:
        std::shared_ptr<FGame> Game;
    };
}

#endif
