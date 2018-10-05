#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>

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
    std::vector<FPlayer *> Players;
    //END OF VERTEX DATA
    //TODO: Not sure I need that. It is a pointer to itself.
    FVertex *Location;
    std::vector<FEdge *> IncidentEdgeVector;
};

struct FEdge
{
    std::string Name;
    FEdge *Location;
    FVertex *Origin;
    FVertex *Destination;
    FVertex *IncidentOrigin;
    FVertex *IncidentDestination;
};

class FGraph
{
  public:
    FGraph() {}
    FGraph(std::string FileName);
    ~FGraph() {} //Must add desctructor!

    const FVertex *EndVertices(const FEdge *CurrentEdge) const;
    const FVertex *Opposite(const FVertex *CurrentVertex, const FEdge *CurrentEdge) const;
    bool AreAdjacent(const FVertex *VertexA, const FVertex *VertexB) const;
    void Replace(FVertex *OldVertex, FVertex *NewVertex);
    void Replace(FEdge *OldEdge, FEdge *NewEdge);
    const FVertex *InsertVertex(FVertex *NewVertex);
    const FEdge *InsertEdge(FVertex *VertexA, FVertex *VertexB, FEdge *NewEdge);
    const FVertex *RemoveVertex(FVertex *CurrentVertex);
    const FEdge *RemoveEdge(FEdge *CurrentEdge);
    std::vector<FVertex *> &Vertices();
    std::vector<FEdge *> &Edges();
    std::vector<FEdge *> &IncidentEdges(FVertex *CurrentVertex);

    FVertex *GetVertexWithName(std::string Name);

  private:
    std::vector<FVertex *> VertexVector;
    std::vector<FEdge *> EdgeVector;
};

#endif