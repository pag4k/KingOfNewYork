// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef OBSERVEREVENT_H
#define OBSERVEREVENT_H

#include "precompiledheader.h"
#include "common.h"

namespace KingOfNewYork
{
    //class String;
    class FBorough;
    class FTile;
    class FCard;

    //Interface for events that are used with the observer pattern.
    class IObserverEvent
    {
    public:
        IObserverEvent(const EObserverEvent ObserverEvent, const std::string &Message)
                : ObserverEvent(ObserverEvent), Message(Message) {}
        virtual ~IObserverEvent() = default;
        const EObserverEvent ObserverEvent;
        const std::string Message;
    };

    class FStartTurnPhaseEvent: public IObserverEvent
    {
    public:
        FStartTurnPhaseEvent(const EObserverEvent ObserverEvent, const std::string &Message, const ETurnPhase TurnPhase)
                : IObserverEvent(ObserverEvent, Message), TurnPhase(TurnPhase) {}
        const ETurnPhase TurnPhase;
    };

    class FChangeVictoryPointsEvent: public IObserverEvent
    {
    public:
        FChangeVictoryPointsEvent(const EObserverEvent ObserverEvent, const std::string &Message, const int Delta, const int Total)
                : IObserverEvent(ObserverEvent, Message), Delta(Delta), Total(Total) {}
        const int Delta;
        const int Total;
    };


    class FChangeEnergyCubesEvent: public IObserverEvent
    {
    public:
        FChangeEnergyCubesEvent(const EObserverEvent ObserverEvent, const std::string &Message, const int Delta, const int Total)
                : IObserverEvent(ObserverEvent, Message), Delta(Delta), Total(Total) {}
        const int Delta;
        const int Total;
    };


    class FChangeLifePointsEvent: public IObserverEvent
    {
    public:
        FChangeLifePointsEvent(const EObserverEvent ObserverEvent, const std::string &Message, const int Delta, const int Total)
                : IObserverEvent(ObserverEvent, Message), Delta(Delta), Total(Total) {}
        const int Delta;
        const int Total;
    };

    class FChangeBoroughEvent: public IObserverEvent
    {
    public:
        FChangeBoroughEvent(const EObserverEvent ObserverEvent, const std::string &Message, const std::shared_ptr<FBorough> &OriginBorough, const std::shared_ptr<FBorough> &DestinationBorough)
                : IObserverEvent(ObserverEvent, Message), OriginBorough(OriginBorough), DestinationBorough(DestinationBorough) {}
        const std::shared_ptr<FBorough> &OriginBorough;
        const std::shared_ptr<FBorough> &DestinationBorough;
    };

    class FMoveInManhattanEvent: public IObserverEvent
    {
    public:
        FMoveInManhattanEvent(const EObserverEvent ObserverEvent, const std::string &Message, const int OriginLevel, const int DestinationLevel)
                : IObserverEvent(ObserverEvent, Message), OriginLevel(OriginLevel), DestinationLevel(DestinationLevel) {}
        const int OriginLevel;
        const int DestinationLevel;
    };

    class FDestroyedTileEvent: public IObserverEvent
    {
    public:
        FDestroyedTileEvent(const EObserverEvent ObserverEvent, const std::string &Message, const std::unique_ptr<FTile> &Tile)
                : IObserverEvent(ObserverEvent, Message), Tile(Tile) {}
        const std::unique_ptr<FTile> &Tile;
    };

    class FSpawnedUnitEvent: public IObserverEvent
    {
    public:
        FSpawnedUnitEvent(const EObserverEvent ObserverEvent, const std::string &Message, const std::unique_ptr<FTile> &Tile)
                : IObserverEvent(ObserverEvent, Message), Tile(Tile) {}
        const std::unique_ptr<FTile> &Tile;
    };

    class FTakeSuperstarEvent: public IObserverEvent
    {
    public:
        FTakeSuperstarEvent(const EObserverEvent ObserverEvent, const std::string &Message) : IObserverEvent(ObserverEvent, Message) {}
    };

    class FDeadPlayerEvent: public IObserverEvent
    {
    public:
        FDeadPlayerEvent(const EObserverEvent ObserverEvent, const std::string &Message) : IObserverEvent(ObserverEvent, Message) {}
    };

    class FBetweenTurnsEvent: public IObserverEvent
    {
    public:
        FBetweenTurnsEvent(const EObserverEvent ObserverEvent, const std::string &Message) : IObserverEvent(ObserverEvent, Message) {}
    };

    class FRolledDiceEvent: public IObserverEvent
    {
    public:
        FRolledDiceEvent(const EObserverEvent ObserverEvent, const std::string &Message, const std::vector<EDiceFace> &DiceResult, const std::vector<bool> &NewRoll)
                : IObserverEvent(ObserverEvent, Message), DiceResult(DiceResult), NewRoll(NewRoll) {}
        const std::vector<EDiceFace> &DiceResult;
        const std::vector<bool> &NewRoll;
    };

    class FRollingDoneEvent: public IObserverEvent
    {
    public:
        FRollingDoneEvent(const EObserverEvent ObserverEvent, const std::string &Message) : IObserverEvent(ObserverEvent, Message) {}
    };

    class FBoughtCardEvent: public IObserverEvent
    {
    public:
        FBoughtCardEvent(const EObserverEvent ObserverEvent, const std::string &Message) : IObserverEvent(ObserverEvent, Message) {}
    };

    class FDisplayCardEvent: public IObserverEvent
    {
    public:
        FDisplayCardEvent(const EObserverEvent ObserverEvent, const std::string &Message) : IObserverEvent(ObserverEvent, Message) {}
    };

    class FUsedCardEvent: public IObserverEvent
    {
    public:
        FUsedCardEvent(const EObserverEvent ObserverEvent, const std::string &Message) : IObserverEvent(ObserverEvent, Message) {}
    };
}

#endif
