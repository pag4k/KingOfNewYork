#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>

//FOR VERTEX DATA
#include "tile.h"
class FPlayer;
//END OF FOR VERTEX DATA

struct FEdge;

struct FVertex
{
    //VERTEX DATA. NOT REQUIRED FOR GRAPH!
    std::string Name;
    bool bStartingLocation;
    bool bInManhattan;
    //int Level;
    FTileStack TileStacks[NUMBER_OF_TILESTACKS_IN_BOROUGH];
    std::vector<std::shared_ptr<FPlayer>> Players;
    //END OF VERTEX DATA
    //TODO: Not sure I need that. It is a pointer to itself.
    std::shared_ptr<FVertex> Location;
    std::vector<std::shared_ptr<FEdge>> IncidentEdgeVector;
};

struct FEdge
{
    std::string Name;
    std::shared_ptr<FEdge> Location;
    std::shared_ptr<FVertex> Origin;
    std::shared_ptr<FVertex> Destination;
    std::shared_ptr<FVertex> IncidentOrigin;
    std::shared_ptr<FVertex> IncidentDestination;
};

class FGraph
{
  public:
    FGraph() {}
    FGraph(std::string FileName);
    ~FGraph() {} //Must add desctructor!

    const std::shared_ptr<FVertex> EndVertices(const std::shared_ptr<FVertex> CurrentEdge) const;
    const std::shared_ptr<FVertex> Opposite(const std::shared_ptr<FVertex> CurrentVertex, const std::shared_ptr<FEdge> CurrentEdge) const;
    bool AreAdjacent(const std::shared_ptr<FVertex> VertexA, const std::shared_ptr<FVertex> VertexB) const;
    void Replace(std::shared_ptr<FVertex> OldVertex, std::shared_ptr<FVertex> NewVertex);
    void Replace(std::shared_ptr<FEdge> OldEdge, std::shared_ptr<FEdge> NewEdge);
    const std::shared_ptr<FVertex> InsertVertex(std::shared_ptr<FVertex> NewVertex);
    const std::shared_ptr<FEdge> InsertEdge(std::shared_ptr<FVertex> VertexA, std::shared_ptr<FVertex> VertexB, std::shared_ptr<FEdge> NewEdge);
    const std::shared_ptr<FVertex> RemoveVertex(std::shared_ptr<FVertex> CurrentVertex);
    const std::shared_ptr<FEdge> RemoveEdge(std::shared_ptr<FEdge> CurrentEdge);
    std::vector<std::shared_ptr<FVertex>> &Vertices();
    std::vector<std::shared_ptr<FEdge>> &Edges();
    std::vector<std::shared_ptr<FEdge>> &IncidentEdges(std::shared_ptr<FVertex> CurrentVertex);

    std::shared_ptr<FVertex> GetVertexWithName(std::string Name);

  private:
    std::vector<std::shared_ptr<FVertex>> VertexVector;
    std::vector<std::shared_ptr<FEdge>> EdgeVector;
};

#endif