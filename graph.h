// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H

#include <cassert>
#include <list>
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
            typename std::list<std::shared_ptr<FVertex>>::iterator Position;
            std::shared_ptr<T> Element;
            std::string Name;
            std::list<std::shared_ptr<FEdge>> IncidentEdgeList;
        };
        struct FEdge
        {
            typename std::list<std::shared_ptr<FEdge>>::iterator Position;
            std::shared_ptr<FVertex> Origin;
            std::shared_ptr<FVertex> Destination;
            typename std::list<std::shared_ptr<FEdge>>::iterator IncidentOrigin;
            typename std::list<std::shared_ptr<FEdge>>::iterator IncidentDestination;
        };

    public:
        FGraph() = default;
        ~FGraph();
        unsigned long ElementCount() const { return VertexList.size(); }
        std::set<std::shared_ptr<T>> GetNeighbours(const std::string &Name) const;
        bool AreAdjacent(const std::string &Name1, const std::string &Name2) const;
        std::shared_ptr<T> InsertVertex(const std::string &VertexName);
        void RemoveVertex(const std::string &VertexName);
        void InsertEdge(const std::string &OriginName, const std::string &DestinationName);
    private:
        std::pair<std::shared_ptr<FVertex>,std::shared_ptr<FVertex>> EndVertices(std::shared_ptr<FEdge> CurrentEdge) const;
        std::shared_ptr<FVertex> Opposite(std::shared_ptr<FVertex> CurrentVertex, std::shared_ptr<FEdge> CurrentEdge) const;
        bool AreAdjacent(std::shared_ptr<FVertex> VertexA, std::shared_ptr<FVertex> VertexB) const;
        void Replace(std::shared_ptr<FVertex> OldVertex, std::shared_ptr<FVertex> NewVertex);
        void Replace(std::shared_ptr<FEdge> OldEdge, std::shared_ptr<FEdge> NewEdge);
        std::shared_ptr<FVertex> InsertVertex(std::shared_ptr<FVertex> NewVertex);
        std::shared_ptr<FEdge> InsertEdge(std::shared_ptr<FVertex> OriginVertex, std::shared_ptr<FVertex> DestinationVertex, std::shared_ptr<FEdge> NewEdge);
        std::shared_ptr<T> RemoveVertex(std::shared_ptr<FVertex> VertexToRemove);
        std::shared_ptr<T> RemoveEdge(std::shared_ptr<FEdge> EdgeToRemove);
        std::shared_ptr<FVertex> GetVertexWithName(const std::string &Name) const;
        std::list<std::shared_ptr<FVertex>> VertexList;
        std::list<std::shared_ptr<FEdge>> EdgeList;
    };
}
#include "graph.cpp"

#endif
