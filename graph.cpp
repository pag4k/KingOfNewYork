// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "graph.h"

namespace KingOfNewYork
{
    template<typename T>
    FGraph<T>::~FGraph<T>()
    {
        for (FEdge *Edge : EdgeVector)
        {
            delete Edge;
        }
        for (FVertex *Vertex : VertexVector)
        {
            delete Vertex;
        }
        EdgeVector.clear();
        VertexVector.clear();
    }

    template<typename T>
    const std::string &FGraph<T>::GetName(const int n) const
    {
        assert(0 <= n && n < VertexVector.size());
        return VertexVector[n]->Name;
    }

    template<typename T>
    std::shared_ptr<T> FGraph<T>::GetElement(int n)
    {
        assert(0 <= n && n < VertexVector.size());
        return VertexVector[n]->Element;
    }

    template<typename T>
    std::vector<int> FGraph<T>::GetNeighbours(const int n) const
    {
        assert(0 <= n && n < VertexVector.size());
        //Using a set to make sure there are not duplicates.
        std::set<int> NeighbourSet;
        for (FEdge *Edge : VertexVector[n]->IncidentEdgeVector)
        {
            NeighbourSet.insert(
                    GetIndexFromName(Opposite(VertexVector[n], Edge)->Name));
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
        return AreAdjacent(
                GetVertexWithName(Name1),
                GetVertexWithName(Name2));
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
        for (FVertex *Vertex: VertexVector)
        {
            if (Vertex->Name == VertexName)
            {
                std::cout   << "Error: There is already a vertex named: "
                            << VertexName
                            << "."
                            << std::endl;
                return nullptr;
            }
        }
        auto *NewVertex = new FVertex;
        NewVertex->Name = VertexName;
        FVertex *InsertedVertex = InsertVertex(NewVertex);
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
    int FGraph<T>::GetIndexFromName(const std::string &Name) const
    {
        for (int i = 0; i < VertexVector.size(); ++i)
        {
            if (VertexVector[i]->Name == Name)
            {
                return i;
            }
        }
        std::cout << "Error: Could not find vertex with name: "
                  << Name
                  << std::endl;
        return -1;
    }

    template<typename T>
    typename FGraph<T>::FVertex * FGraph<T>::Opposite(FGraph<T>::FVertex const* CurrentVertex, FGraph<T>::FEdge const* CurrentEdge) const
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
    bool FGraph<T>::AreAdjacent(FVertex const* VertexA, FVertex const* VertexB) const
    {
        if (VertexA && VertexB)
        {
            for (const FEdge *IncidentEdge : VertexA->IncidentEdgeVector)
            {
                if (Opposite(VertexA, IncidentEdge) == VertexB)
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            std::cout << "Error: Invalid vertices."
                      << std::endl;
            return false;
        }
    }

    template<typename T>
    typename FGraph<T>::FVertex *FGraph<T>::InsertVertex(FGraph<T>::FVertex *NewVertex)
    {
        if (NewVertex)
        {
            VertexVector.push_back(NewVertex);
            return VertexVector.back();
        }
        std::cout << "Error: Invalid vertex."
                  << std::endl;
        return nullptr;
    }

    template<typename T>
    typename FGraph<T>::FEdge *FGraph<T>::InsertEdge(FGraph<T>::FVertex * OriginVertex, FGraph<T>::FVertex * DestinationVertex, FGraph<T>::FEdge * NewEdge)
    {
        if (OriginVertex && DestinationVertex && NewEdge)
        {
            EdgeVector.push_back(NewEdge);
            FEdge * CreatedEdge = EdgeVector.back();
            CreatedEdge->Origin = OriginVertex;
            CreatedEdge->Destination = DestinationVertex;
            OriginVertex->IncidentEdgeVector.push_back(CreatedEdge);
            DestinationVertex->IncidentEdgeVector.push_back(CreatedEdge);
            return CreatedEdge;
        }
        std::cout << "Error: Invalid vertex and/or edge."
                  << std::endl;
        return nullptr;
    }

    template<typename T>
    typename FGraph<T>::FVertex *FGraph<T>::RemoveVertex(FGraph<T>::FVertex *VertexToRemove)
    {
        if (VertexToRemove)
        {
            //Remove pointers to that vertex in the other IncidentEdgeVector.
            for (const auto OtherVertex : VertexVector)
            {
                if (AreAdjacent(VertexToRemove, OtherVertex))
                {
                    for (auto it = OtherVertex->IncidentEdgeVector.begin();
                         it != OtherVertex->IncidentEdgeVector.end();
                         ++it)
                    {
                        if (Opposite(OtherVertex, *it) == VertexToRemove)
                        {
                            OtherVertex->IncidentEdgeVector.erase(it);
                            break;
                        }
                    }
                }
            }

            //Deleting incident edges and their pointers in the edge list.
            int RemovedEdgeCount = 0;
            for (auto it = EdgeVector.begin(); it != EdgeVector.end();)
            {
                FEdge *CurrentEdge = *it;
                if (CurrentEdge->Origin == VertexToRemove ||
                    CurrentEdge->Destination == VertexToRemove)
                {
                    RemovedEdgeCount++;
                    delete CurrentEdge;
                    EdgeVector.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            //Clearing the the incident edge list.
            assert(VertexToRemove->IncidentEdgeVector.size() ==
                   RemovedEdgeCount);
            VertexToRemove->IncidentEdgeVector.clear();

            //Delete the vertex and its pointer in the vertex list.
            for (auto it = VertexVector.begin(); it != VertexVector.end(); ++it)
            {
                if (*it == VertexToRemove)
                {
                    std::cout << "Removing vertex:"
                              << VertexToRemove->Name
                              << "."
                              << std::endl;
                    delete *it;
                    VertexVector.erase(it);
                    return *it;
                }
            }
        }

        std::cout << "Error: Invalid vertex."
                  << std::endl;
        return nullptr;
    }

    template<typename T>
    typename FGraph<T>::FVertex *FGraph<T>::GetVertexWithName(const std::string &Name) const
    {
        for (FGraph<T>::FVertex *Vertex : VertexVector)
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
    void FGraph<T>::EndVertices(FEdge const* CurrentEdge, FVertex const* OutOriginVertex, FVertex const* OutDestinationVertex) const
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
    void FGraph<T>::Replace(FVertex const* OldVertex, FVertex const* NewVertex)
    {
        if (OldVertex && NewVertex)
        {
            OldVertex->Name = NewVertex->Name;
        }
    }

    template <typename T>
    void FGraph<T>::Replace(FEdge const* OldEdge, FEdge const* NewEdge)
    {
        if (OldEdge && NewEdge)
        {
            //OldEdge->Name = NewEdge->Name;
        }
    }

    template <typename T>
    typename FGraph<T>::FEdge *FGraph<T>::RemoveEdge(FEdge *EdgeToRemove)
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
