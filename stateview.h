//
// Created by oscar on 15/11/18.
//

#ifndef STATEVIEW_H
#define STATEVIEW_H

#include "observer.h"

namespace KingOfNewYork
{
    class FGame;
    class FSubject;
    class IObserverEvent;

    class FStateView : public IObserver
    {
    public:
        explicit FStateView(std::shared_ptr<FGame> Game);
        ~FStateView() override;
        void Update(std::shared_ptr<FSubject> Subject, std::shared_ptr<IObserverEvent> Event) override;
    private:
        std::shared_ptr<FGame> Game;
    };
}

#endif
