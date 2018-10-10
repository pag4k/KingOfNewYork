// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "graph.h"

namespace KingOfNewYork
{
    template <typename T>
    void FGraph<T>::EndVertices(const FEdge *CurrentEdge, FVertex *OutOriginVertex, FVertex *OutDestinationVertex) const
    {
        if (CurrentEdge)
        {
            OutOriginVertex = CurrentEdge.OriginVertex;
            OutDestinationVertex = CurrentEdge.DestinationVertex;
        }
        else
        {
            OutOriginVertex = nullptr;
            OutDestinationVertex = nullptr;
        }
    }

    template <typename T>
    void FGraph<T>::Replace(const FVertex * OldVertex, const FVertex * NewVertex)
    {
        if (OldVertex && NewVertex)
        {
            OldVertex->Name = NewVertex->Name;
        }
    }

    template <typename T>
    void FGraph<T>::Replace(const FEdge * OldEdge, const FEdge * NewEdge)
    {
        if (OldEdge && NewEdge)
        {
            OldEdge->Name = NewEdge->Name;
        }
    }

    template <typename T>
    const typename FGraph<T>::FVertex *FGraph<T>::RemoveVertex(FVertex *VertexToRemove)
    {
        if (VertexToRemove)
        {
            //Remove all pointers to that Vertex in the other Vertex IncidentEdgeVector.
            for (const auto OtherVertex : VertexVector)
            {
                if (AreAdjacent(VertexToRemove, OtherVertex))
                {
                    for (auto it = OtherVertex->IncidentEdgeVector.begin(); it != OtherVertex->IncidentEdgeVector.end(); ++it)
                    {
                        if (Opposite(OtherVertex, *it))
                        {
                            OtherVertex->IncidentEdgeVector.erase(it);
                            break;
                        }
                    }
                }
            }

            //Deleting all the edges incident to this vertex and their pointers in the edge list.
            for (auto it = EdgeVector.begin(); it != EdgeVector.end(); )
            {
                if (Opposite(VertexToRemove, *it))
                {
                    delete *it;
                    EdgeVector.erase(it);
                }
                else{
                    ++it;
                }
                
            }

            //Clearing the the incident edge list.
            VertexToRemove->IncidentEdgeVector.clear();

            //Delete the vertex and its pointer in the vertex list.
            for (auto it = VertexVector.begin(); it != VertexVector.end(); ++it)
            {
                if (*it == VertexToRemove)
                {
                    delete *it;
                    VertexVector.erase(it);
                    return *it;
                }
            }
        }

        return nullptr;
    }

    template <typename T>
    const typename FGraph<T>::FEdge *FGraph<T>::RemoveEdge(FEdge *EdgeToRemove)
    {
        if (EdgeToRemove)
        {
            //Remove references to origin
            if (EdgeToRemove->Origin)
            {
                for (auto it = EdgeToRemove->Origin->IncidentEdgeVector.begin(); it != EdgeToRemove->Origin->IncidentEdgeVector.end(); ++it)
                {
                    if (Opposite(EdgeToRemove->Origin, *it))
                    {
                        EdgeToRemove->Origin->IncidentEdgeVector.erase(it);
                        break;
                    }
                }
            }

            //Remove references to destination
            if (EdgeToRemove->Destination)
            {
                for (auto it = EdgeToRemove->Destination->IncidentEdgeVector.begin(); it != EdgeToRemove->Destination->IncidentEdgeVector.end(); ++it)
                {
                    if (Opposite(EdgeToRemove->Destination, *it))
                    {
                        EdgeToRemove->Destination->IncidentEdgeVector.erase(it);
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

        return nullptr;
    }

    template <typename T>
    std::vector<typename FGraph<T>::FVertex *> &FGraph<T>::Vertices()
    {
        return VertexVector;
    }

    template <typename T>
    std::vector<typename FGraph<T>::FEdge *> &FGraph<T>::Edges()
    {
        return EdgeVector; 
    }

    template <typename T>
    std::vector<typename FGraph<T>::FEdge *> &FGraph<T>::IncidentEdges(FVertex * CurrentVertex)
    {
        return CurrentVertex->IncidentEdgeVector;
    }
}
