// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "graph.h"

#include <algorithm>

namespace KingOfNewYork
{
    template<typename T>
    FGraph<T>::~FGraph<T>()
    {
        for (FEdge *Edge : EdgeList)
        {
            delete Edge;
        }
        for (FVertex *Vertex : VertexList)
        {
            delete Vertex;
        }
        EdgeList.clear();
        VertexList.clear();
    }



    template<typename T>
    std::set<std::shared_ptr<T>> FGraph<T>::GetNeighbours(const std::string &Name) const
    {
        assert(0 <= n && n < VertexList.size());
        //Using a set to make sure there are not duplicates.
        std::set<int> NeighbourSet;
        for (FEdge *Edge : VertexList[n]->IncidentEdgeVector)
        {
            NeighbourSet.insert(GetIndexFromName(Opposite(VertexList[n], Edge)->Name));
        }
        std::vector<int> NeighbourVector;
        for (int Index : NeighbourSet)
        {
            NeighbourVector.push_back(Index);
        }

        return NeighbourVector;
    }

    template<typename T>
    bool FGraph<T>::AreAdjacent(const std::string &Name1, const std::string &Name2) const
    {
        return AreAdjacent(GetVertexWithName(Name1), GetVertexWithName(Name2));
    }

    template<typename T>
    std::shared_ptr<T> FGraph<T>::InsertVertex(const std::string &VertexName)
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

    template<typename T>
    void FGraph<T>::RemoveVertex(const std::string &VertexName)
    {
        if (VertexName.empty())
        {
            std::cout << "Error: You need to provide a non-empy string."
                      << std::endl;
            return;
        }
        RemoveVertex(GetVertexWithName(VertexName));
    }

    template<typename T>
    void FGraph<T>::InsertEdge(const std::string &OriginName, const std::string &DestinationName)
    {
        if (OriginName.empty() || DestinationName.empty())
        {
            std::cout << "Error: You need to provide two non-empy strings."
                      << std::endl;
            return;
        }
        auto *NewEdge = new FEdge;
        InsertEdge(
                GetVertexWithName(OriginName),
                GetVertexWithName(DestinationName),
                NewEdge);
    }

    template<typename T>
    std::shared_ptr<FVertex> FGraph<T>::Opposite(std::shared_ptr<FVertex> CurrentVertex, std::shared_ptr<FEdge> CurrentEdge) const
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

    template<typename T>
    bool FGraph<T>::AreAdjacent(std::shared_ptr<FVertex> VertexA, std::shared_ptr<FVertex> VertexB) const
    {
        if (VertexA && VertexB)
        {
            const auto &IncidentEdgeList = (VertexA->IncidentEdgeList.size() <= VertexB->IncidentEdgeList.size()) ? VertexA->IncidentEdgeList : VertexB->IncidentEdgeList;
            return std::any_of(IncidentEdgeList.begin(), IncidentEdgeList.end(),
                                   [](const auto &Edge) { return Opposite(VertexA, Edge) == VertexB; });
        }
        else
        {
            std::cout << "Error: Invalid vertices."
                      << std::endl;
            return false;
        }
    }

    template<typename T>
    std::shared_ptr<FVertex> FGraph<T>::InsertVertex(std::shared_ptr<FVertex> NewVertex)
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

    template<typename T>
    std::shared_ptr<FEdge> FGraph<T>::InsertEdge(std::shared_ptr<FVertex> OriginVertex, std::shared_ptr<FVertex> DestinationVertex, std::shared_ptr<FEdge> NewEdge)
    {
        if (OriginVertex && DestinationVertex && NewEdge)
        {
            NewEdge->Position = EdgeList.insert(EdgeList.end(), NewEdge);
            //EdgeList.push_back(NewEdge);
            //FEdge * CreatedEdge = EdgeList.back();
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

    template<typename T>
    std::shared_ptr<FVertex> FGraph<T>::RemoveVertex(std::shared_ptr<FVertex> VertexToRemove)
    {
        if (VertexToRemove)
        {
            //NOTE SURE ABOUT THAT
            auto EdgeListCopy = VertexToRemove->IncidentEdgeList;
            for (auto Edge : EdgeListCopy) RemoveEdge(Edge);

            //TODO: NOT SURE WHAT HAPPENS WITH THE INCIDENT LIST? IS IT DESTROYED BY REMOVING ALL EDGES?

            VertexList.erase(VertexToRemove->Position);

            return VertexToRemove->Element;
        }

        std::cout << "Error: Invalid vertex."
                  << std::endl;
        return nullptr;
    }

    template<typename T>
    std::shared_ptr<FVertex> FGraph<T>::GetVertexWithName(const std::string &Name) const
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

    template <typename T>
    std::pair<std::shared_ptr<FVertex>, std::shared_ptr<FVertex>> FGraph<T>::EndVertices(std::shared_ptr<FEdge> CurrentEdge) const
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

    template <typename T>
    void FGraph<T>::Replace(std::shared_ptr<FVertex> OldVertex, std::shared_ptr<FVertex> NewVertex)
    {
        if (OldVertex && NewVertex)
        {
            //TODO: DON'T I HAVE TO DO MORE HERE?
            OldVertex->Name = NewVertex->Name;
        }
    }

    template <typename T>
    void FGraph<T>::Replace(std::shared_ptr<FEdge> OldEdge, std::shared_ptr<FEdge> NewEdge)
    {
        if (OldEdge && NewEdge)
        {
            //TODO: DON'T I HAVE TO DO MORE HERE?
            //OldEdge->Name = NewEdge->Name;
        }
    }

    template <typename T>
    std::shared_ptr<FEdge> FGraph<T>::RemoveEdge(std::shared_ptr<FEdge> EdgeToRemove)
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

            //TODO: Should return element, but there is none.
            EdgeList.erase(EdgeToRemove->Position);
            return EdgeToRemove;
        }

        std::cout << "Error: Invalid edge."
                  << std::endl;
        return nullptr;
    }
}
