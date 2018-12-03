// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H

#include "precompiledheader.h"

namespace KingOfNewYork
{
    //A graph ADT with V for FVertex elements and E for FEdge elements.
    template<typename V, typename E>
    class FGraph
    {
        struct FEdge;
        struct FVertex
        {
            FVertex() : Element(std::make_shared<V>()), Name("") {};
            typename std::list<std::shared_ptr<FVertex>>::iterator Position;
            std::shared_ptr<V> Element;
            std::string Name;
            std::list<std::shared_ptr<FEdge>> IncidentEdgeList;
        };
        struct FEdge
        {
            FEdge() : Element(std::make_shared<E>()), Name("") {};
            typename std::list<std::shared_ptr<FEdge>>::iterator Position;
            std::shared_ptr<E> Element;
            std::string Name;
            std::shared_ptr<FVertex> Origin;
            std::shared_ptr<FVertex> Destination;
            typename std::list<std::shared_ptr<FEdge>>::iterator IncidentOrigin;
            typename std::list<std::shared_ptr<FEdge>>::iterator IncidentDestination;
        };

    public:
        std::set<std::shared_ptr<V>> GetNeighbours(const std::string &Name) const;
        bool AreAdjacent(const std::string &Name1, const std::string &Name2) const;
        std::shared_ptr<V> InsertVertex(const std::string &VertexName);
        void InsertEdge(const std::string &OriginName, const std::string &DestinationName);
        void RemoveVertex(const std::string &VertexName);
    private:
        std::shared_ptr<FVertex> GetVertexWithName(const std::string &Name) const;
        std::pair<std::shared_ptr<FVertex>,std::shared_ptr<FVertex>> EndVertices(std::shared_ptr<FEdge> CurrentEdge) const;
        std::shared_ptr<FVertex> Opposite(std::shared_ptr<FVertex> CurrentVertex, std::shared_ptr<FEdge> CurrentEdge) const;
        bool AreAdjacent(std::shared_ptr<FVertex> VertexA, std::shared_ptr<FVertex> VertexB) const;
        void Replace(std::shared_ptr<FVertex> Vertex, std::shared_ptr<V> NewElement);
        void Replace(std::shared_ptr<FEdge> Edge, std::shared_ptr<E> NewElement);
        std::shared_ptr<FVertex> InsertVertex(std::shared_ptr<FVertex> NewVertex);
        std::shared_ptr<FEdge> InsertEdge(std::shared_ptr<FVertex> OriginVertex, std::shared_ptr<FVertex> DestinationVertex, std::shared_ptr<FEdge> NewEdge);
        std::shared_ptr<V> RemoveVertex(std::shared_ptr<FVertex> VertexToRemove);
        std::shared_ptr<E> RemoveEdge(std::shared_ptr<FEdge> EdgeToRemove);
        std::list<std::shared_ptr<FVertex>> VertexList;
        std::list<std::shared_ptr<FEdge>> EdgeList;
    };
}
#include "graph.cpp"

#endif
