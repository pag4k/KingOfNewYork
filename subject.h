// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
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
        virtual void Notify(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event) const;
        FSubject();
        virtual ~FSubject();
    protected:
        virtual void ClearObserverListPointer() { Observers = nullptr; }
    private:
        std::list<IObserver*>* Observers;
    };

}

#endif
