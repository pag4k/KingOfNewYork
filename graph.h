#include <vector>
#include <string>
#include <iostream>

struct Edge;

struct Vertex
{
    std::string Name;
    Vertex *Location;
    std::vector<Edge *> IncidentEdgeVector;
};

struct Edge
{
    std::string Name;
    Edge *Location;
    Vertex *Origin;
    Vertex *Destination;
    Vertex *IncidentOrigin;
    Vertex *IncidentDestination;
};

class Graph
{
  public:
    Graph(std::string FileName);
    ~Graph() {}; //Must add desctructor!

    const Vertex *EndVertices(const Edge *CurrentEdge) const;
    const Vertex *Opposite(const Vertex *CurrentVertex, const Edge *CurrentEdge) const;
    bool AreAdjacent(const Vertex *VertexA, const Vertex *VertexB) const;
    void Replace(Vertex *OldVertex, Vertex *NewVertex);
    void Replace(Edge *OldEdge, Edge *NewEdge);
    const Vertex *InsertVertex(Vertex *NewVertex);
    const Edge *InsertEdge(Vertex *VertexA, Vertex *VertexB, Edge *NewEdge);
    const Vertex *RemoveVertex(Vertex *CurrentVertex);
    const Edge *RemoveEdge(Edge *CurrentEdge);
    const std::vector<Vertex *> &Vertices() const;
    const std::vector<Edge *> &Edges() const;
    const std::vector<Edge *> &IncidentEdges(const Vertex *CurrentVertex) const;

    Vertex *GetVertexWithName(std::string Name);

  private:
    std::vector<Vertex *> VertexVector;
    std::vector<Edge *> EdgeVector;
};