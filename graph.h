#ifndef GRAPH_H
#define GRAPH_H

#include <assert.h>
#include <vector>
#include <string>
#include <iostream>

template<class T>
class FGraph
{
private:
    struct FEdge;
    struct FVertex;
public:
    FGraph() {}
    ~FGraph() {
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

    ElementIterator Begin() { return ElementIterator(VertexVector[0]); }
    ElementIterator End() { return ElementIterator(VertexVector.back()); }
    int ElementCount() { return VertexVector.size(); }
    T &GetElement(int n) { assert(0 <= n && n < VertexVector.size()); return VertexVector[n]->Element; }
    std::vector<int> GetNeighbours(int n)
    {
        assert(0 <= n && n < VertexVector.size());
        std::vector<int> Neighbours;
        for (int i = 0; i < VertexVector.size(); ++i)
        {
            if (i == n)
            {
                continue;
            }
            if (AreAdjacent(VertexVector[i], VertexVector[n]))
            {
                Neighbours.push_back(i);
            }
        }
        return Neighbours;
    }

    T &InsertVertex(std::string VertexName)
    {
        for (FVertex *Vertex: VertexVector)
        {
            if (Vertex->Name == VertexName)
            {
                std::cout   << "Error: There is already a vertex named: "
                            << VertexName
                            << "."
                            << std::endl;
                return Vertex->Element;
            }
        }
        FVertex *NewVertex = new FVertex;
        NewVertex->Name = VertexName;
        return InsertVertex(NewVertex)->Element;
    }

    void InsertEdge(std::string OriginName, std::string DestinationName)
    {
        FEdge *NewEdge = new FEdge;
        InsertEdge(GetVertexWithName(OriginName), GetVertexWithName(DestinationName), NewEdge);
    }

private:
    const FVertex * EndVertices(const FVertex * CurrentEdge) const;
    const FVertex * Opposite(const FVertex * CurrentVertex, const FEdge * CurrentEdge) const;
    bool AreAdjacent(const FVertex * VertexA, const FVertex * VertexB) const;
    void Replace(FVertex * OldVertex, FVertex * NewVertex);
    void Replace(FEdge * OldEdge, FEdge * NewEdge);

    FVertex * InsertVertex(FVertex * NewVertex)
    {
        if (NewVertex)
        {
            VertexVector.push_back(NewVertex);
            std::cout << "Added Vertex: " << NewVertex->Name << std::endl;
            return VertexVector.back();
        }
        return nullptr;
    }

    FEdge * InsertEdge(FVertex * OriginVertex, FVertex * DestinationVertex, FEdge * NewEdge)
    {
        if (OriginVertex && DestinationVertex && NewEdge)
        {
            EdgeVector.push_back(NewEdge);
            FEdge * CreatedEdge = EdgeVector.back();
            //CreatedEdge->Location = CreatedEdge;
            CreatedEdge->Origin = OriginVertex;
            CreatedEdge->Destination = DestinationVertex;
            OriginVertex->IncidentEdgeVector.push_back(CreatedEdge);
            DestinationVertex->IncidentEdgeVector.push_back(CreatedEdge);
            std::cout << "Added Node from " << OriginVertex->Name << " to " << DestinationVertex->Name << std::endl;
            return CreatedEdge;
        }
        return nullptr;
    }

    const FVertex * RemoveVertex(FVertex * CurrentVertex);
    const FEdge * RemoveEdge(FEdge * CurrentEdge);

    std::vector<FVertex *> &Vertices();
    std::vector<FEdge *> &Edges();
    std::vector<FEdge *> &IncidentEdges(FVertex * CurrentVertex);

    FVertex * GetVertexWithName(std::string Name)
    {
        for (FVertex *&Vertex : VertexVector)
        {
            if (Vertex->Name == Name)
            {
                return Vertex;
            }
        }
        std::cout << "Could not find Vertex with name: " << Name << std::endl;
        return nullptr;
    }

    struct FVertex
    {
        T Element;
        std::string Name;
        //FVertex * Location;
        std::vector<FEdge *> IncidentEdgeVector;
    };
  
    struct FEdge
    {
        //FEdge * Location;
        FVertex * Origin;
        FVertex * Destination;
        FVertex * IncidentOrigin;
        FVertex * IncidentDestination;
    };

  std::vector<FVertex *> VertexVector;
  std::vector<FEdge *> EdgeVector;
};

#endif