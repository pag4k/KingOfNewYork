// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef CARDVIEW_H
#define CARDEFFECTVIEW_H

#include "observer.h"

namespace KingOfNewYork
{
    class FGameController;
    class FSubject;

    //A class that observes the card notifications.
    class FCardView : public IObserver
    {
    public:
        explicit FCardView(std::shared_ptr<FGameController> GameController);
        ~FCardView() override;
        void Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event) override;
    private:
        std::shared_ptr<FGameController> GameController;
    };
}

#endif
