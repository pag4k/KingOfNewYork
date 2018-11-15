//
// Created by oscar on 15/11/18.
//

#include "stateview.h"
#include "game.h"


namespace KingOfNewYork
{
    FStateView::FStateView(std::shared_ptr<FGame> Game) : Game(Game)
    {
        Game->Attach(this);
    }

    FStateView::~FStateView()
    {
        Game->Detach(this);
    }

    void FStateView::Update(std::shared_ptr<FSubject> Subject, std::shared_ptr<IObserverEvent> Event)
    {

    }
}


