//
// Created by oscar on 15/11/18.
//

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <memory>
#include "observer.h"

namespace KingOfNewYork
{
    class FGame;
    class FSubject;
    class IObserverEvent;

    class FGameView : public IObserver
    {
    public:
        explicit FGameView(std::shared_ptr<FGame> Game);
        ~FGameView() override;
        void Update(std::shared_ptr<FSubject> Subject, std::shared_ptr<IObserverEvent> Event) override;
    private:
        std::shared_ptr<FGame> Game;
    };
}

#endif
