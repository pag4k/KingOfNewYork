// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "graph.h"

namespace KingOfNewYork
{
    template <typename T>
    void FGraph<T>::EndVertices(
        const FEdge *CurrentEdge,
        FVertex *OutOriginVertex,
        FVertex *OutDestinationVertex) const
    {
        if (CurrentEdge)
        {
            OutOriginVertex = CurrentEdge->Origin;
            OutDestinationVertex = CurrentEdge->Destination;
        }
        else
        {
            OutOriginVertex = nullptr;
            OutDestinationVertex = nullptr;
        }
    }

    template <typename T>
    void FGraph<T>::Replace(
        const FVertex * OldVertex,
        const FVertex * NewVertex)
    {
        if (OldVertex && NewVertex)
        {
            OldVertex->Name = NewVertex->Name;
        }
    }

    template <typename T>
    void FGraph<T>::Replace(
        const FEdge * OldEdge,
        const FEdge * NewEdge)
    {
        if (OldEdge && NewEdge)
        {
            //OldEdge->Name = NewEdge->Name;
        }
    }

    template <typename T>
    const typename FGraph<T>::FEdge *FGraph<T>::RemoveEdge(FEdge *EdgeToRemove)
    {
        if (EdgeToRemove)
        {
            //Remove references to origin
            if (EdgeToRemove->Origin)
            {
                FVertex *Origin = EdgeToRemove->Origin;
                for (auto it = Origin->IncidentEdgeVector.begin();
                     it != Origin->IncidentEdgeVector.end();
                     ++it)
                {
                    if (Opposite(Origin, *it))
                    {
                        Origin->IncidentEdgeVector.erase(it);
                        break;
                    }
                }
            }

            //Remove references to destination
            if (EdgeToRemove->Destination)
            {
                FVertex *Destination = EdgeToRemove->Destination;
                for (auto it = Destination->IncidentEdgeVector.begin();
                     it != Destination->IncidentEdgeVector.end();
                     ++it)
                {
                    if (Opposite(Destination, *it))
                    {
                        Destination->IncidentEdgeVector.erase(it);
                        break;
                    }
                }
            }

            //Delete the edge and its pointer in the edge list.
            for (auto it = EdgeVector.begin(); it != EdgeVector.end(); ++it)
            {
                if (*it == EdgeToRemove)
                {
                    delete *it;
                    EdgeVector.erase(it);
                    return *it;
                }
            }
        }

        std::cout << "Error: Invalid edge."
                  << std::endl;
        return nullptr;
    }
}
