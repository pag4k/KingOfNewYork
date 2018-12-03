// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef DICEVIEW_H
#define DICEVIEW_H

#include "precompiledheader.h"
#include "observer.h"

namespace KingOfNewYork
{
    class FGameController;
    class FSubject;

    //A class that observes the dice notifications.
    class FDiceView : public IObserver
    {
    public:
        explicit FDiceView(std::shared_ptr<FGameController> GameController);
        ~FDiceView() override;
        void Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event) override;
    private:
        std::shared_ptr<FGameController> GameController;
    };
}

#endif
