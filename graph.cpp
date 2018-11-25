// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "graph.h"

#include <algorithm>

namespace KingOfNewYork
{
    //PUBLIC METHODS

    template<typename V, typename E>
    std::set<std::shared_ptr<V>> FGraph<V,E>::GetNeighbours(const std::string &Name) const
    {
        std::shared_ptr<FVertex> Vertex = GetVertexWithName(Name);
        std::set<std::shared_ptr<V>> NeighbourSet;
        if (Vertex)
        {
            for (auto &Edge :  Vertex->IncidentEdgeList) NeighbourSet.insert(NeighbourSet.end(), Opposite(Vertex, Edge)->Element);
        }
        return NeighbourSet;
    }

    template<typename V, typename E>
    bool FGraph<V,E>::AreAdjacent(const std::string &Name1, const std::string &Name2) const
    {
        return AreAdjacent(GetVertexWithName(Name1), GetVertexWithName(Name2));
    }

    template<typename V, typename E>
    std::shared_ptr<V> FGraph<V,E>::InsertVertex(const std::string &VertexName)
    {
        if (VertexName.empty())
        {
            std::cout << "Error: You need to provide a non-empy string."
                      << std::endl;
            return nullptr;
        }
        if (std::any_of(VertexList.begin(), VertexList.end(),
                        [&VertexName](const auto &Vertex){ return Vertex->Name == VertexName;}))
        {
            std::cout   << "Error: There is already a vertex named: "
                        << VertexName
                        << "."
                        << std::endl;
            return nullptr;
        }
        auto NewVertex = std::make_shared<FVertex>();
        NewVertex->Name = VertexName;
        std::shared_ptr<FVertex> InsertedVertex = InsertVertex(NewVertex);
        return NewVertex->Element;
    }

    template<typename V, typename E>
    void FGraph<V,E>::InsertEdge(const std::string &OriginName, const std::string &DestinationName)
    {
        if (OriginName.empty() || DestinationName.empty())
        {
            std::cout << "Error: You need to provide two non-empy strings."
                      << std::endl;
            return;
        }
        auto NewEdge = std::make_shared<FEdge>();
        InsertEdge(GetVertexWithName(OriginName), GetVertexWithName(DestinationName), NewEdge);
    }

    template<typename V, typename E>
    void FGraph<V,E>::RemoveVertex(const std::string &VertexName)
    {
        if (VertexName.empty())
        {
            std::cout << "Error: You need to provide a non-empy string."
                      << std::endl;
            return;
        }
        RemoveVertex(GetVertexWithName(VertexName));
    }

    //PRIVATE METHODS

    template<typename V, typename E>
    std::shared_ptr<typename FGraph<V,E>::FVertex> FGraph<V,E>::GetVertexWithName(const std::string &Name) const
    {
        for (auto Vertex : VertexList)
        {
            if (Vertex->Name == Name)
            {
                return Vertex;
            }
        }
        std::cout << "Error: Could not find Vertex with name: "
                  << Name
                  << std::endl;
        return nullptr;
    }

    template<typename V, typename E>
    std::pair<std::shared_ptr<typename FGraph<V,E>::FVertex>, std::shared_ptr<typename FGraph<V,E>::FVertex>> FGraph<V,E>::EndVertices(std::shared_ptr<FEdge> CurrentEdge) const
    {
        if (CurrentEdge)
        {
            return std::make_pair(CurrentEdge->Origin, CurrentEdge->Destination);
        }
        else
        {
            return nullptr;
            //return std::make_pair(->Origin, CurrentEdge->Destination);
        }
    }

    template<typename V, typename E>
    std::shared_ptr<typename FGraph<V,E>::FVertex> FGraph<V,E>::Opposite(std::shared_ptr<FVertex> CurrentVertex, std::shared_ptr<FEdge> CurrentEdge) const
    {
        if (CurrentVertex && CurrentEdge)
        {
            if (CurrentEdge->Origin && CurrentEdge->Origin == CurrentVertex)
            {
                return CurrentEdge->Destination;
            }
            else if (CurrentEdge->Destination &&
                     CurrentEdge->Destination == CurrentVertex)
            {
                return CurrentEdge->Origin;
            }
            else
            {
                std::cout << "Error: The edge does not have this vertex."
                          << std::endl;
                return nullptr;
            }
        }
        else
        {
            std::cout << "Error: Invalid vertex and/or edge.."
                      << std::endl;
            return nullptr;
        }
    }

    template<typename V, typename E>
    bool FGraph<V,E>::AreAdjacent(std::shared_ptr<FVertex> VertexA, std::shared_ptr<FVertex> VertexB) const
    {
        if (VertexA && VertexB)
        {
            const auto &IncidentEdgeList = (VertexA->IncidentEdgeList.size() <= VertexB->IncidentEdgeList.size()) ? VertexA->IncidentEdgeList : VertexB->IncidentEdgeList;
            return std::any_of(IncidentEdgeList.begin(), IncidentEdgeList.end(),
                                   [this, &VertexA, &VertexB](const auto &Edge) { return Opposite(VertexA, Edge) == VertexB; });
        }
        else
        {
            std::cout << "Error: Invalid vertices."
                      << std::endl;
            return false;
        }
    }

    template<typename V, typename E>
    void FGraph<V,E>::Replace(std::shared_ptr<FVertex> Vertex, std::shared_ptr<V> NewElement)
    {
        if (Vertex)
        {
            Vertex->Element = NewElement;
        }
    }

    template<typename V, typename E>
    void FGraph<V,E>::Replace(std::shared_ptr<FEdge> Edge, std::shared_ptr<E> NewElement)
    {
        if (Edge)
        {
            Edge->Element = NewElement;
        }
    }

    template<typename V, typename E>
    std::shared_ptr<typename FGraph<V,E>::FVertex> FGraph<V,E>::InsertVertex(std::shared_ptr<FVertex> NewVertex)
    {
        if (NewVertex)
        {
            NewVertex->Position = VertexList.insert(VertexList.end(), NewVertex);
            return NewVertex;
        }
        std::cout << "Error: Invalid vertex."
                  << std::endl;
        return nullptr;
    }

    template<typename V, typename E>
    std::shared_ptr<typename FGraph<V,E>::FEdge> FGraph<V,E>::InsertEdge(std::shared_ptr<FVertex> OriginVertex, std::shared_ptr<FVertex> DestinationVertex, std::shared_ptr<FEdge> NewEdge)
    {
        if (OriginVertex && DestinationVertex && NewEdge)
        {
            NewEdge->Position = EdgeList.insert(EdgeList.end(), NewEdge);
            NewEdge->Origin = OriginVertex;
            NewEdge->Destination = DestinationVertex;
            NewEdge->IncidentOrigin = OriginVertex->IncidentEdgeList.insert(OriginVertex->IncidentEdgeList.end(), NewEdge);
            NewEdge->IncidentDestination = DestinationVertex->IncidentEdgeList.insert(DestinationVertex->IncidentEdgeList.end(), NewEdge);
            return NewEdge;
        }
        std::cout << "Error: Invalid vertex and/or edge."
                  << std::endl;
        return nullptr;
    }

    template<typename V, typename E>
    std::shared_ptr<V> FGraph<V,E>::RemoveVertex(std::shared_ptr<FVertex> VertexToRemove)
    {
        if (VertexToRemove)
        {
            //Making a copy of the list because it is modified by RemoveEdge.
            auto EdgeListCopy = VertexToRemove->IncidentEdgeList;
            for (auto Edge : EdgeListCopy) RemoveEdge(Edge);
            VertexList.erase(VertexToRemove->Position);
            return VertexToRemove->Element;
        }

        std::cout << "Error: Invalid vertex."
                  << std::endl;
        return nullptr;
    }

    template<typename V, typename E>
    std::shared_ptr<E> FGraph<V,E>::RemoveEdge(std::shared_ptr<FEdge> EdgeToRemove)
    {
        if (EdgeToRemove)
        {
            //Remove references to origin
            if (EdgeToRemove->Origin)
            {
                EdgeToRemove->Origin->IncidentEdgeList.erase(EdgeToRemove->IncidentOrigin);
                EdgeToRemove->Origin = nullptr;
            }

            //Remove references to destination
            if (EdgeToRemove->Destination)
            {
                EdgeToRemove->Destination->IncidentEdgeList.erase(EdgeToRemove->IncidentDestination);
                EdgeToRemove->Destination = nullptr;
            }

            EdgeList.erase(EdgeToRemove->Position);
            return EdgeToRemove->Element;
        }

        std::cout << "Error: Invalid edge."
                  << std::endl;
        return nullptr;
    }
}
