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

    int ElementCount() { return VertexVector.size(); }
    T &GetElement(int n) {
        assert(0 <= n && n < VertexVector.size());
        T &Element = VertexVector[n]->Element;
        return Element;
    }
    std::string &GetName(int n) { assert(0 <= n && n < VertexVector.size()); return VertexVector[n]->Name; }

    std::vector<int> GetNeighbours(int n)
    {
        assert(0 <= n && n < VertexVector.size());
        std::vector<int> Neighbours;
        for (FEdge *Edge : VertexVector[n]->IncidentEdgeVector)
        {
            Neighbours.push_back(GetIndexFromName(Opposite(VertexVector[n], Edge)->Name));
        }
        return Neighbours;
    }

    bool AreAdjacent(std::string Name1, std::string Name2)
    {
        return AreAdjacent(GetVertexWithName(Name1), GetVertexWithName(Name2));
    }

    T *InsertVertex(std::string VertexName)
    {
        if (VertexName == "")
        {
            std::cout << "Error: You need to provide a non-empy string for the vertex." << std::endl;
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
                return &Vertex->Element;
            }
        }
        FVertex *NewVertex = new FVertex;
        NewVertex->Name = VertexName;
        FVertex *InsertedVertex = InsertVertex(NewVertex);
        return &NewVertex->Element;
    }

    void InsertEdge(std::string OriginName, std::string DestinationName)
    {
        if (OriginName == "" || DestinationName == "")
        {
            std::cout << "Error: You need to provide non-empy strings for both ends of the edge." << std::endl;
            return;
        }
        FEdge *NewEdge = new FEdge;
        InsertEdge(GetVertexWithName(OriginName), GetVertexWithName(DestinationName), NewEdge);
    }

    int GetIndexFromName(std::string Name)
    {
        for (int i = 0; i < VertexVector.size(); ++i)
        {
            if (VertexVector[i]->Name == Name)
            {
                return i;
            }
        }
        std::cout << "Error: Could not find vertex with name: " << Name << std::endl;
        return -1;
    }

private:
    const FVertex * EndVertices(const FVertex * CurrentEdge) const;

    const FVertex * Opposite(const FVertex * CurrentVertex, const FEdge * CurrentEdge) const
    {
        if (CurrentVertex && CurrentEdge)
        {
            if (CurrentEdge->Origin && CurrentEdge->Origin == CurrentVertex)
            {
                return CurrentEdge->Destination;
            }
            else if (CurrentEdge->Destination && CurrentEdge->Destination == CurrentVertex)
            {
                return CurrentEdge->Origin;
            }
            else
            {
                //Should output Error somehow.
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }

    bool AreAdjacent(const FVertex * VertexA, const FVertex * VertexB) const
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
            return false;
        }
    }

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

    FVertex * GetVertexWithName(const std::string Name)
    {
        for (FVertex *Vertex : VertexVector)
        {
            if (Vertex->Name == Name)
            {
                return Vertex;
            }
        }
        std::cout << "Error: Could not find Vertex with name: " << Name << std::endl;
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