//
// Created by oscar on 15/11/18.
//

#ifndef OBSERVER_H
#define OBSERVER_H

#include "observerevent.h"

namespace KingOfNewYork
{
    class FSubject;
    class IObserverEvent;

    class IObserver
    {
    public:
        virtual ~IObserver() = default;
        virtual void Update(std::shared_ptr<FSubject> Subject, std::shared_ptr<IObserverEvent> Event) = 0;
    protected:
        IObserver() = default;
    };

}

#endif
