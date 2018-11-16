//
// Created by oscar on 15/11/18.
//

#include "subject.h"
#include <cassert>
#include "observer.h"
#include <iostream>

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

    void FSubject::DetachAll()
    {
        Observers->clear();
    }

    void FSubject::Notify(std::shared_ptr<FSubject> Subject, std::shared_ptr<IObserverEvent> Event)
    {
        assert(Observers);
        //std::cout << Observers->size();
        for (auto Observer : *Observers)
        {
            assert(Observer);
            Observer->Update(Subject, Event);
            //FIXME: This is not a good solution as since I'm not sure what happens if there is more than one element.
            if (Observers->size() == 0)
            {
                break;
            }
        }
    }

}