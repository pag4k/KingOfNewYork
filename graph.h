#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>

template <class T>
struct FEdge;

template <class T>
struct FVertex
{
    T Element;
    std::string Name;
    //TODO: Not sure I need that. It is a pointer to itself.
    std::shared_ptr<FVertex<T>> Location;
    std::vector<std::shared_ptr<FEdge<T>>> IncidentEdgeVector;
};

template <class T>
struct FEdge
{
    std::string Name;
    std::shared_ptr<FEdge<T>> Location;
    std::shared_ptr<FVertex<T>> Origin;
    std::shared_ptr<FVertex<T>> Destination;
    std::shared_ptr<FVertex<T>> IncidentOrigin;
    std::shared_ptr<FVertex<T>> IncidentDestination;
};

template<class T>
class FGraph
{
  public:
    FGraph() {}
    FGraph(std::string FileName)
    {
        std::ifstream InputStream;
        InputStream.open(FileName);

        if (InputStream.fail())
        {
            std::cout << "Could not open file: " << FileName << std::endl;
            return;
        }

        std::string Text;
        while (!std::getline(InputStream, Text).eof())
        {
            //std::cout << "-" << Text << "-" << std::endl;
            if (Text == "VERTEX")
            {
                while (!std::getline(InputStream, Text).eof())
                {
                    if (Text == "")
                    {
                        break;
                    }
                    else
                    {
                        std::shared_ptr<FVertex<T>> NewVertex = std::make_shared<FVertex<T>>();
                        std::size_t Position1 = Text.find(',');
                        NewVertex->Name = Text.substr(0, Position1);
                        NewVertex->Element.Name = Text.substr(0, Position1++);
                        std::size_t Position2 = Text.find(',', Position1);
                        NewVertex->Element.bStartingLocation = (Text.substr(Position1, Position2++ - Position1) == "StartingLocation");
                        std::size_t Position3 = Text.find(',', Position2);
                        std::cout << Text.substr(Position2, Position3 - Position2) << std::endl;
                        NewVertex->Element.bInManhattan = (Text.substr(Position2, Position3 - Position2) == "InManhattan");
                        //NewVertex->Level = 0;
                        InsertVertex(NewVertex);
                    }
                }
            }
            else if (Text == "EDGE")
            {
                while (!std::getline(InputStream, Text).eof())
                {
                    if (Text == "")
                    {
                        std::cout << "-"
                                  << "BREAK"
                                  << "-" << std::endl;

                        break;
                    }
                    //std::cout << "-" << Text << "-" << std::endl;

                    std::size_t Position = Text.find(':');

                    if (Position != std::string::npos)
                    {
                        std::string OriginName = Text.substr(0, Position);
                        std::shared_ptr<FVertex<T>> OriginVertex = GetVertexWithName(OriginName);
                        if (OriginVertex)
                        {
                            std::string EdgeNames = Text.substr(Position + 1);
                            //Checking if there is at least one comma.
                            if (Text.find(',') != std::string::npos)
                            {
                                std::size_t Previous = 0;
                                while (EdgeNames.find(',', Previous) != std::string::npos)
                                {
                                    std::size_t Current = EdgeNames.find(',', Previous);
                                    std::string DestinationName = EdgeNames.substr(Previous, Current - Previous);
                                    std::shared_ptr<FVertex<T>> DestinationVertex = GetVertexWithName(DestinationName);
                                    if (DestinationVertex)
                                    {
                                        std::shared_ptr<FEdge<T>> NewEdge = std::make_shared<FEdge<T>>();
                                        InsertEdge(OriginVertex, DestinationVertex, NewEdge);
                                    }

                                    if (EdgeNames.length() > Current)
                                    {
                                        Previous = Current + 1;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        InputStream.close();
    }

    ~FGraph() {} //Must add desctructor!

    const std::shared_ptr<FVertex<T>> EndVertices(const std::shared_ptr<FVertex<T>> CurrentEdge) const;
    const std::shared_ptr<FVertex<T>> Opposite(const std::shared_ptr<FVertex<T>> CurrentVertex, const std::shared_ptr<FEdge<T>> CurrentEdge) const;
    bool AreAdjacent(const std::shared_ptr<FVertex<T>> VertexA, const std::shared_ptr<FVertex<T>> VertexB) const;
    void Replace(std::shared_ptr<FVertex<T>> OldVertex, std::shared_ptr<FVertex<T>> NewVertex);
    void Replace(std::shared_ptr<FEdge<T>> OldEdge, std::shared_ptr<FEdge<T>> NewEdge);
    const std::shared_ptr<FVertex<T>> InsertVertex(std::shared_ptr<FVertex<T>> NewVertex)
    {
        if (NewVertex)
        {
            VertexVector.push_back(NewVertex);
            std::cout << "Added Vertex: " << NewVertex->Name << std::endl;
            return VertexVector.back();
        }
        return nullptr;
    }

    const std::shared_ptr<FEdge<T>> InsertEdge(std::shared_ptr<FVertex<T>> OriginVertex, std::shared_ptr<FVertex<T>> DestinationVertex, std::shared_ptr<FEdge<T>> NewEdge)
    {
        if (OriginVertex && DestinationVertex && NewEdge)
        {
            EdgeVector.push_back(NewEdge);
            std::shared_ptr<FEdge<T>> CreatedEdge = EdgeVector.back();
            CreatedEdge->Location = CreatedEdge;
            CreatedEdge->Origin = OriginVertex;
            CreatedEdge->Destination = DestinationVertex;
            OriginVertex->IncidentEdgeVector.push_back(CreatedEdge);
            DestinationVertex->IncidentEdgeVector.push_back(CreatedEdge);
            std::cout << "Added Node from " << OriginVertex->Name << " to " << DestinationVertex->Name << std::endl;
            return CreatedEdge;
        }
        return nullptr;
    }

    const std::shared_ptr<FVertex<T>> RemoveVertex(std::shared_ptr<FVertex<T>> CurrentVertex);
    const std::shared_ptr<FEdge<T>> RemoveEdge(std::shared_ptr<FEdge<T>> CurrentEdge);
    std::vector<std::shared_ptr<FVertex<T>>> &Vertices()
    {
        return VertexVector;
    }

    std::vector<std::shared_ptr<FEdge<T>>> &Edges();
    std::vector<std::shared_ptr<FEdge<T>>> &IncidentEdges(std::shared_ptr<FVertex<T>> CurrentVertex);

    std::shared_ptr<FVertex<T>> GetVertexWithName(std::string Name)
    {
        for (std::shared_ptr<FVertex<T>> &Vertex : VertexVector)
        {
            if (Vertex->Name == Name)
            {
                return Vertex;
            }
        }
        std::cout << "Could not find Vertex with name: " << Name << std::endl;
        return nullptr;
    }

  private:
    std::vector<std::shared_ptr<FVertex<T>>> VertexVector;
    std::vector<std::shared_ptr<FEdge<T>>> EdgeVector;
};

#endif