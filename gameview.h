// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef STATEVIEW_H
#define STATEVIEW_H

#include "precompiledheader.h"
#include "observer.h"

namespace KingOfNewYork
{
    class FGameController;
    class FSubject;
    class IObserverEvent;

    //A class that observes the game notifications.
    class FGameView : public IObserver
    {
    public:
        explicit FGameView(std::shared_ptr<FGameController> GameController);
        ~FGameView() override;
        void Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event) override;
    private:
        std::shared_ptr<FGameController> GameController;
    };
}

#endif
