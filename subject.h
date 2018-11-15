//
// Created by oscar on 15/11/18.
//

#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include <memory>
#include "observerevent.h"

namespace KingOfNewYork
{

    class IObserver;

    class FSubject
    {
    public:
        virtual void Attach(IObserver* Observer);
        virtual void Detach(IObserver* Observer);
        virtual void Notify(std::shared_ptr<FSubject> Subject, std::shared_ptr<IObserverEvent> Event);
        FSubject();
        virtual ~FSubject();
    private:
        std::list<IObserver*>* Observers;
    };

}

#endif
