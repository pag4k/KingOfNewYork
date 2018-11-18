// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef OBSERVEREVENT_H
#define OBSERVEREVENT_H

#include <string>
#include "memory"
#include "common.h"

namespace KingOfNewYork
{
    class String;
    class FBorough;

    //Interface for events that are used with the observer pattern.
    class IObserverEvent
    {
    public:
        IObserverEvent(const EObserverEvent &ObserverEvent, const std::string &Message)
                : ObserverEvent(ObserverEvent), Message(Message) {}
        virtual ~IObserverEvent() = default;
        EObserverEvent ObserverEvent;
        std::string Message;
    };

    class FStartTurnPhaseEvent: public IObserverEvent
    {
    public:
        FStartTurnPhaseEvent(const EObserverEvent &ObserverEvent, const std::string &Message, ETurnPhase TurnPhase)
                : IObserverEvent(ObserverEvent, Message), TurnPhase(TurnPhase) {}
        ETurnPhase TurnPhase;
    };

    class FChangeVictoryPointsEvent: public IObserverEvent
    {
    public:
        FChangeVictoryPointsEvent(const EObserverEvent &ObserverEvent, const std::string &Message, int Delta, int Total)
                : IObserverEvent(ObserverEvent, Message), Delta(Delta), Total(Total) {}
        int Delta;
        int Total;
    };


    class FChangeEnergyCubesEvent: public IObserverEvent
    {
    public:
        FChangeEnergyCubesEvent(const EObserverEvent &ObserverEvent, const std::string &Message, int Delta, int Total)
                : IObserverEvent(ObserverEvent, Message), Delta(Delta), Total(Total) {}
        int Delta;
        int Total;
    };


    class FChangeLifePointsEvent: public IObserverEvent
    {
    public:
        FChangeLifePointsEvent(const EObserverEvent &ObserverEvent, const std::string &Message, int Delta, int Total)
                : IObserverEvent(ObserverEvent, Message), Delta(Delta), Total(Total) {}
        int Delta;
        int Total;
    };

    class FChangeBoroughEvent: public IObserverEvent
    {
    public:
        FChangeBoroughEvent(const EObserverEvent &ObserverEvent, const std::string &Message, const std::shared_ptr<FBorough> &OriginBorough, const std::shared_ptr<FBorough> &DestinationBorough)
                : IObserverEvent(ObserverEvent, Message), OriginBorough(OriginBorough), DestinationBorough(DestinationBorough) {}
        std::shared_ptr<FBorough> OriginBorough;
        std::shared_ptr<FBorough> DestinationBorough;
    };

    class FMoveInManhattanEvent: public IObserverEvent
    {
    public:
        FMoveInManhattanEvent(const EObserverEvent &ObserverEvent, const std::string &Message, int OriginLevel, int DestinationLevel)
                : IObserverEvent(ObserverEvent, Message), OriginLevel(OriginLevel), DestinationLevel(DestinationLevel) {}
        int OriginLevel;
        int DestinationLevel;
    };

    class FDeadPlayerEvent: public IObserverEvent
    {
    public:
        FDeadPlayerEvent(const EObserverEvent &ObserverEvent, const std::string &Message) : IObserverEvent(ObserverEvent, Message) {}
    };

    class FBetweenTurnsEvent: public IObserverEvent
    {
    public:
        FBetweenTurnsEvent(const EObserverEvent &ObserverEvent, const std::string &Message) : IObserverEvent(ObserverEvent, Message) {}
    };
}

#endif