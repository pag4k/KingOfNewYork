// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H

#include <cassert>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <memory>

namespace KingOfNewYork
{
    template<typename T>
    class FGraph
    {
    private:
        struct FEdge;
        struct FVertex;
    public:
        FGraph() = default;

        ~FGraph()
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

        const unsigned long ElementCount() const { return VertexVector.size(); }

        std::shared_ptr<T> GetElement(int n)
        {
            assert(0 <= n && n < VertexVector.size());
            return VertexVector[n]->Element;
        }

        const std::string &GetName(const int n) const
        {
            assert(0 <= n && n < VertexVector.size());
            return VertexVector[n]->Name;
        }

        const std::vector<int> GetNeighbours(const int n) const
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

        const bool AreAdjacent(
            const std::string &Name1,
            const std::string &Name2) const
        {
            return AreAdjacent(
                GetVertexWithName(Name1),
                GetVertexWithName(Name2));
        }

        std::shared_ptr<T> InsertVertex(const std::string &VertexName)
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

        void RemoveVertex(const std::string &VertexName)
        {
            if (VertexName.empty())
            {
                std::cout << "Error: You need to provide a non-empy string."
                          << std::endl;
                return;
            }
            RemoveVertex(GetVertexWithName(VertexName));
        }

        void InsertEdge(
            const std::string &OriginName,
            const std::string &DestinationName)
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

        const int GetIndexFromName(const std::string Name) const
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

    private:
        void EndVertices(
            const FEdge * CurrentEdge,
            FVertex *OutOriginVertex,
            FVertex *OutDestinationVertex) const;

        const FVertex * Opposite(
            const FVertex * CurrentVertex,
            const FEdge * CurrentEdge) const
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

        const bool AreAdjacent(
            const FVertex * VertexA,
            const FVertex * VertexB) const
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

        void Replace(const FVertex *OldVertex, const FVertex *NewVertex);
        void Replace(const FEdge *OldEdge, const FEdge *NewEdge);

        FVertex *InsertVertex(FVertex *NewVertex)
        {
            if (NewVertex)
            {
                VertexVector.push_back(NewVertex);
                std::cout << "Added Vertex: " << NewVertex->Name << std::endl;
                return VertexVector.back();
            }
            std::cout << "Error: Invalid vertex."
                      << std::endl;
            return nullptr;
        }

        FEdge * InsertEdge(
            FVertex * OriginVertex,
            FVertex * DestinationVertex,
            FEdge * NewEdge)
        {
            if (OriginVertex && DestinationVertex && NewEdge)
            {
                EdgeVector.push_back(NewEdge);
                FEdge * CreatedEdge = EdgeVector.back();
                CreatedEdge->Origin = OriginVertex;
                CreatedEdge->Destination = DestinationVertex;
                OriginVertex->IncidentEdgeVector.push_back(CreatedEdge);
                DestinationVertex->IncidentEdgeVector.push_back(CreatedEdge);
                std::cout << "Added Node from "
                          << OriginVertex->Name
                          << " to "
                          << DestinationVertex->Name
                          << std::endl;
                return CreatedEdge;
            }
            std::cout << "Error: Invalid vertex and/or edge."
                      << std::endl;
            return nullptr;
        }

        const FVertex *RemoveVertex(FVertex *VertexToRemove)
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

        const FEdge * RemoveEdge(FEdge * CurrentEdge);

        FVertex *GetVertexWithName(const std::string Name) const
        {
            for (FVertex *Vertex : VertexVector)
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

        struct FVertex
        {
            FVertex() : Element(std::make_shared<T>()), Name("") {};
            std::shared_ptr<T> Element;
            std::string Name;
            std::vector<FEdge *> IncidentEdgeVector;
        };
    
        struct FEdge
        {
            FVertex * Origin;
            FVertex * Destination;
            FVertex * IncidentOrigin;
            FVertex * IncidentDestination;
        };

    std::vector<FVertex *> VertexVector;
    std::vector<FEdge *> EdgeVector;
    };

    
}

#endif
