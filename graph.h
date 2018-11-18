// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
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
    //A graph ADT.
    template<typename T>
    class FGraph
    {
        struct FEdge;
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

    public:
        FGraph() = default;
        ~FGraph();
        unsigned long ElementCount() const { return VertexVector.size(); }
        std::shared_ptr<T> GetElement(int n);
        const std::string &GetName(int n) const;
        std::vector<int> GetNeighbours(int n) const;
        bool AreAdjacent(const std::string &Name1, const std::string &Name2) const;
        std::shared_ptr<T> InsertVertex(const std::string &VertexName);
        void RemoveVertex(const std::string &VertexName);
        void InsertEdge(const std::string &OriginName, const std::string &DestinationName);
        int GetIndexFromName(const std::string &Name) const;
    private:
        void EndVertices(FEdge const* CurrentEdge, FVertex const* OutOriginVertex, FVertex const* OutDestinationVertex) const;
        FVertex * Opposite(FVertex const* CurrentVertex,FEdge const* CurrentEdge) const;
        bool AreAdjacent(FVertex const* VertexA, FVertex const* VertexB) const;
        void Replace(FVertex const* OldVertex, FVertex const* NewVertex);
        void Replace(FEdge const* OldEdge, FEdge const* NewEdge);
        FVertex *InsertVertex(FVertex *NewVertex);
        FEdge * InsertEdge(FVertex * OriginVertex, FVertex * DestinationVertex, FEdge * NewEdge);
        FVertex *RemoveVertex(FVertex *VertexToRemove);
        FEdge * RemoveEdge(FEdge * EdgeToRemove);
        FVertex *GetVertexWithName(const std::string &Name) const;
        std::vector<FVertex *> VertexVector;
        std::vector<FEdge *> EdgeVector;
    };
}
#include "graph.cpp"

#endif
