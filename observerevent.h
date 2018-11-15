//
// Created by oscar on 15/11/18.
//

#ifndef OBSERVEREVENT_H
#define OBSERVEREVENT_H

#include <string>
#include "memory"
#include "common.h"

namespace KingOfNewYork
{
    class String;
    class FBorough;

    class IObserverEvent
    {
    public:
        IObserverEvent(EObserverEvent ObserverEvent, std::string Message)
                : ObserverEvent(ObserverEvent), Message(Message) {}
        virtual ~IObserverEvent() = default;
        EObserverEvent ObserverEvent;
        std::string Message;
    };

    class FStartTurnPhaseEvent: public IObserverEvent
    {
    public:
        FStartTurnPhaseEvent(EObserverEvent ObserverEvent, std::string Message, ETurnPhase TurnPhase)
                : IObserverEvent(ObserverEvent, Message), TurnPhase(TurnPhase) {}
        ETurnPhase TurnPhase;
    };

    class FChangeVictoryPointsEvent: public IObserverEvent
    {
    public:
        FChangeVictoryPointsEvent(EObserverEvent ObserverEvent, std::string Message, int Delta, int Total)
                : IObserverEvent(ObserverEvent, Message), Delta(Delta), Total(Total) {}
        int Delta;
        int Total;
    };


    class FChangeEnergyCubesEvent: public IObserverEvent
    {
    public:
        FChangeEnergyCubesEvent(EObserverEvent ObserverEvent, std::string Message, int Delta, int Total)
                : IObserverEvent(ObserverEvent, Message), Delta(Delta), Total(Total) {}
        int Delta;
        int Total;
    };


    class FChangeLifePointsEvent: public IObserverEvent
    {
    public:
        FChangeLifePointsEvent(EObserverEvent ObserverEvent, std::string Message, int Delta, int Total)
                : IObserverEvent(ObserverEvent, Message), Delta(Delta), Total(Total) {}
        int Delta;
        int Total;
    };

    class FChangeBoroughEvent: public IObserverEvent
    {
    public:
        FChangeBoroughEvent(EObserverEvent ObserverEvent, std::string Message, std::shared_ptr<FBorough> OriginBorough, std::shared_ptr<FBorough> DestinationBorough)
                : IObserverEvent(ObserverEvent, Message), OriginBorough(OriginBorough), DestinationBorough(DestinationBorough) {}
        std::shared_ptr<FBorough> OriginBorough;
        std::shared_ptr<FBorough> DestinationBorough;
    };

    class FMoveInManhattanEvent: public IObserverEvent
    {
    public:
        FMoveInManhattanEvent(EObserverEvent ObserverEvent, std::string Message, int OriginLevel, int DestinationLevel)
                : IObserverEvent(ObserverEvent, Message), OriginLevel(OriginLevel), DestinationLevel(DestinationLevel) {}
        int OriginLevel;
        int DestinationLevel;
    };

    class FDeadPlayerEvent: public IObserverEvent
    {
    public:
        FDeadPlayerEvent(EObserverEvent ObserverEvent, std::string Message) : IObserverEvent(ObserverEvent, Message) {}
    };

//    class FTurnResultEvent: public IObserverEvent
//    {
//    public:
//        FTurnResultEvent(EObserverEvent ObserverEvent, std::string Message) : IObserverEvent(ObserverEvent, Message) {}
//    };

}

#endif