// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "subject.h"
#include "observer.h"

namespace KingOfNewYork
{

    FSubject::FSubject()
    {
        Observers = new std::list<IObserver*>;
    }

    FSubject::~FSubject()
    {
        delete Observers;
    }

    void FSubject::Attach(IObserver* Observer)
    {
        Observers->push_back(Observer);
    }

    void FSubject::Detach(IObserver* Observer)
    {
        Observers->remove(Observer);
    }

    void FSubject::Notify(const std::shared_ptr<const FSubject> &Subject, const std::shared_ptr<const IObserverEvent> &Event) const
    {
        assert(Observers);
        if (Observers->empty())
        {
            return;
        }
        for (auto Observer : *Observers)
        {
            assert(Observer);
            Observer->Update(Subject, Event);
            //FIXME: This is not a good solution as since I'm not sure what happens if there is more than one element.
            if (Observers->empty())
            {
                break;
            }
        }
    }

}