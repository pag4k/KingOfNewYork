// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "precompiledheader.h"
#include "observer.h"

namespace KingOfNewYork
{
    class FGameController;
    class FSubject;
    class IObserverEvent;

    //A class that observes the player notifications.
    class FPlayerView : public IObserver
    {
    public:
        explicit FPlayerView(std::shared_ptr<FGameController> GameController);
        ~FPlayerView() override;
        void Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event) override;
    private:
        std::shared_ptr<FGameController> GameController;
    };
}

#endif
