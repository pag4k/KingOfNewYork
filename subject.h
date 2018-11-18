// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include <memory>
#include "observerevent.h"

namespace KingOfNewYork
{
    class IObserver;

    //Base class for subjects in the observer pattern.
    class FSubject
    {
    public:
        virtual void Attach(IObserver* Observer);
        virtual void Detach(IObserver* Observer);
        virtual void DetachAll();
        virtual void Notify(const std::shared_ptr<FSubject> &Subject, const std::shared_ptr<IObserverEvent> &Event);
        FSubject();
        virtual ~FSubject();
    private:
        std::list<IObserver*>* Observers;
    };

}

#endif
