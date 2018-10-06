#include <fstream>
#include <iostream>
#include <string>

#include "graph.h"

FGraph::FGraph(std::string FileName)
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
                    std::shared_ptr<FVertex> NewVertex = std::make_shared<FVertex>();
                    std::size_t Position1 = Text.find(',');
                    NewVertex->Name = Text.substr(0,Position1++);
                    std::size_t Position2 = Text.find(',', Position1);
                    NewVertex->bStartingLocation = (Text.substr(Position1, Position2++ - Position1) == "StartingLocation");
                    std::size_t Position3 = Text.find(',', Position2);
                    std::cout << Text.substr(Position2, Position3 - Position2) << std::endl;
                    NewVertex->bInManhattan = (Text.substr(Position2, Position3 - Position2) == "InManhattan");
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
                    std::cout << "-" << "BREAK" << "-" << std::endl;

                    break;
                }
                //std::cout << "-" << Text << "-" << std::endl;

                std::size_t Position = Text.find(':');

                if (Position != std::string::npos)
                {
                    std::string OriginName = Text.substr(0, Position);
                    std::shared_ptr<FVertex> OriginVertex = GetVertexWithName(OriginName);
                    if (OriginVertex)
                    {
                        std::string EdgeNames = Text.substr(Position+1);
                        //Checking if there is at least one comma.
                        if (Text.find(',') != std::string::npos)
                        {
                            std::size_t Previous = 0;
                            while (EdgeNames.find(',', Previous) != std::string::npos)
                            {
                                std::size_t Current = EdgeNames.find(',', Previous);
                                std::string DestinationName = EdgeNames.substr(Previous, Current - Previous);
                                std::shared_ptr<FVertex> DestinationVertex = GetVertexWithName(DestinationName);
                                if (DestinationVertex)
                                {
                                    std::shared_ptr<FEdge> NewEdge = std::make_shared<FEdge>();
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

const std::shared_ptr<FVertex> FGraph::EndVertices(const std::shared_ptr<FVertex> CurrentEdge) const
{
    //I don't know how to return that because I can only return a pointer to an array.
    //const std::vector<Edge> Array[] = { CurrentEdge->Origin, CurrentEdge->Destination }
    //return Array;
    return nullptr;
}

//NOTE: I'm using this to know if an edge as this vertex. This is not the role of this method.
const std::shared_ptr<FVertex> FGraph::Opposite(const std::shared_ptr<FVertex> CurrentVertex, const std::shared_ptr<FEdge> CurrentEdge) const
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

bool FGraph::AreAdjacent(const std::shared_ptr<FVertex> VertexA, const std::shared_ptr<FVertex> VertexB) const
{
    if (VertexA && VertexB)
    {
        //Not sure about what to return when it is itself.
        if (VertexA == VertexB)
        {
            return false;
        }

        for (const std::shared_ptr<FEdge> &IncidentEdge : VertexA->IncidentEdgeVector)
        {
            if (Opposite(VertexA, IncidentEdge))
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

void FGraph::Replace(std::shared_ptr<FVertex> OldVertex, std::shared_ptr<FVertex> NewVertex)
{
    if (OldVertex && NewVertex)
    {
        OldVertex->Name = NewVertex->Name;
    }
}

void FGraph::Replace(std::shared_ptr<FEdge> OldEdge, std::shared_ptr<FEdge> NewEdge)
{
    if (OldEdge && NewEdge)
    {
        OldEdge->Name = NewEdge->Name;
    }
}

//This function assumes that the Vertex has no Edge.
const std::shared_ptr<FVertex> FGraph::InsertVertex(std::shared_ptr<FVertex> NewVertex)
{
    if (NewVertex)
    {
        VertexVector.push_back(NewVertex);
        std::cout << "Added Vertex: " << NewVertex->Name << std::endl;
        return VertexVector.back();
    }
    return nullptr;
}

//This function assumes that the Edge has no Vertex.
const std::shared_ptr<FEdge> FGraph::InsertEdge(std::shared_ptr<FVertex> OriginVertex, std::shared_ptr<FVertex> DestinationVertex, std::shared_ptr<FEdge> NewEdge)
{
    if (OriginVertex && DestinationVertex && NewEdge)
    {
        EdgeVector.push_back(NewEdge);
        std::shared_ptr<FEdge> CreatedEdge = EdgeVector.back();
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

const std::shared_ptr<FVertex> FGraph::RemoveVertex(std::shared_ptr<FVertex> VertexToRemove)
{
    if (VertexToRemove)
    {
        //Remove all pointers to that Vertex in the other Vertex IncidentEdgeVector.
        for (const std::shared_ptr<FVertex> &OtherVertex : VertexVector)
        {
            if (AreAdjacent(VertexToRemove, OtherVertex))
            {
                for (auto it = OtherVertex->IncidentEdgeVector.begin(); it != OtherVertex->IncidentEdgeVector.end(); ++it)
                {
                    if (Opposite(OtherVertex, *it))
                    {
                        OtherVertex->IncidentEdgeVector.erase(it);
                        break;
                    }
                }
            }
        }

        //Deleting all the edges incident to this vertex and their pointers in the edge list.
        for (auto it = EdgeVector.begin(); it != EdgeVector.end(); )
        {
            if (Opposite(VertexToRemove, *it))
            {
                //delete *it;
                EdgeVector.erase(it);
            }
            else{
                ++it;
            }
            
        }

        //Clearing the the incident edge list.
        VertexToRemove->IncidentEdgeVector.clear();

        //Delete the vertex and its pointer in the vertex list.
        for (auto it = VertexVector.begin(); it != VertexVector.end(); ++it)
        {
            if (*it == VertexToRemove)
            {
                //delete *it;
                VertexVector.erase(it);
                return *it;
            }
        }
    }

    return nullptr;
}

const std::shared_ptr<FEdge> FGraph::RemoveEdge(std::shared_ptr<FEdge> EdgeToRemove)
{
    if (EdgeToRemove)
    {
        //Remove references to origin
        if (EdgeToRemove->Origin)
        {
            for (auto it = EdgeToRemove->Origin->IncidentEdgeVector.begin(); it != EdgeToRemove->Origin->IncidentEdgeVector.end(); ++it)
            {
                if (Opposite(EdgeToRemove->Origin, *it))
                {
                    EdgeToRemove->Origin->IncidentEdgeVector.erase(it);
                    break;
                }
            }
        }

        //Remove references to destination
        if (EdgeToRemove->Destination)
        {
            for (auto it = EdgeToRemove->Destination->IncidentEdgeVector.begin(); it != EdgeToRemove->Destination->IncidentEdgeVector.end(); ++it)
            {
                if (Opposite(EdgeToRemove->Destination, *it))
                {
                    EdgeToRemove->Destination->IncidentEdgeVector.erase(it);
                    break;
                }
            }
        }

        //Delete the edge and its pointer in the edge list.
        for (auto it = EdgeVector.begin(); it != EdgeVector.end(); ++it)
        {
            if (*it == EdgeToRemove)
            {
                //delete *it;
                EdgeVector.erase(it);
                return *it;
            }
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<FVertex>> &FGraph::Vertices()
{
    return VertexVector;
}

std::vector<std::shared_ptr<FEdge>> &FGraph::Edges()
{
    return EdgeVector; 
}

std::vector<std::shared_ptr<FEdge>> &FGraph::IncidentEdges(std::shared_ptr<FVertex> CurrentVertex)
{
    return CurrentVertex->IncidentEdgeVector;
}

std::shared_ptr<FVertex> FGraph::GetVertexWithName(std::string Name)
{
    for (std::shared_ptr<FVertex> &Vertex : VertexVector)
    {
        if (Vertex->Name == Name)
        {
            return Vertex;
        }
    }
    std::cout << "Could not find Vertex with name: " << Name << std::endl;
    return nullptr;
}
