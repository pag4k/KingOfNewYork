#include <vector>
#include <string>
#include <iostream>

struct FEdge;

struct FVertex
{
    std::string Name;
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
    FGraph(std::string FileName);
    ~FGraph() {}; //Must add desctructor!

    const FVertex *EndVertices(const FEdge *CurrentEdge) const;
    const FVertex *Opposite(const FVertex *CurrentVertex, const FEdge *CurrentEdge) const;
    bool AreAdjacent(const FVertex *VertexA, const FVertex *VertexB) const;
    void Replace(FVertex *OldVertex, FVertex *NewVertex);
    void Replace(FEdge *OldEdge, FEdge *NewEdge);
    const FVertex *InsertVertex(FVertex *NewVertex);
    const FEdge *InsertEdge(FVertex *VertexA, FVertex *VertexB, FEdge *NewEdge);
    const FVertex *RemoveVertex(FVertex *CurrentVertex);
    const FEdge *RemoveEdge(FEdge *CurrentEdge);
    const std::vector<FVertex *> &Vertices() const;
    const std::vector<FEdge *> &Edges() const;
    const std::vector<FEdge *> &IncidentEdges(const FVertex *CurrentVertex) const;

    FVertex *GetVertexWithName(std::string Name);

  private:
    std::vector<FVertex *> VertexVector;
    std::vector<FEdge *> EdgeVector;
};