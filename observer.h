// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------
#ifndef OBSERVER_H
#define OBSERVER_H

#include "observerevent.h"

namespace KingOfNewYork
{
    class FSubject;
    class IObserverEvent;

    //Interface for the observer pattern.
    class IObserver
    {
    public:
        virtual ~IObserver() = default;
        virtual void Update(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event) = 0;
    protected:
        IObserver() = default;
    };

}

#endif
