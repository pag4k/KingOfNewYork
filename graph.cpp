
#include "graph.h"

//template <class T>
//FGraph<T>::FGraph(std::string FileName)

template <class T>
const std::shared_ptr<FVertex<T>> FGraph<T>::EndVertices(const std::shared_ptr<FVertex<T>> CurrentEdge) const
{
    //I don't know how to return that because I can only return a pointer to an array.
    //const std::vector<Edge> Array[] = { CurrentEdge->Origin, CurrentEdge->Destination }
    //return Array;
    return nullptr;
}

//NOTE: I'm using this to know if an edge as this vertex. This is not the role of this method.
template <class T>
const std::shared_ptr<FVertex<T>> FGraph<T>::Opposite(const std::shared_ptr<FVertex<T>> CurrentVertex, const std::shared_ptr<FEdge<T>> CurrentEdge) const
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

template <class T>
bool FGraph<T>::AreAdjacent(const std::shared_ptr<FVertex<T>> VertexA, const std::shared_ptr<FVertex<T>> VertexB) const
{
    if (VertexA && VertexB)
    {
        //Not sure about what to return when it is itself.
        if (VertexA == VertexB)
        {
            return false;
        }

        for (const std::shared_ptr<FEdge<T>> &IncidentEdge : VertexA->IncidentEdgeVector)
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

template <class T>
void FGraph<T>::Replace(std::shared_ptr<FVertex<T>> OldVertex, std::shared_ptr<FVertex<T>> NewVertex)
{
    if (OldVertex && NewVertex)
    {
        OldVertex->Name = NewVertex->Name;
    }
}

template <class T>
void FGraph<T>::Replace(std::shared_ptr<FEdge<T>> OldEdge, std::shared_ptr<FEdge<T>> NewEdge)
{
    if (OldEdge && NewEdge)
    {
        OldEdge->Name = NewEdge->Name;
    }
}

//This function assumes that the Vertex has no Edge.
//template <class T>
//const std::shared_ptr<FVertex<T>> FGraph<T>::InsertVertex(std::shared_ptr<FVertex<T>> NewVertex)

//This function assumes that the Edge has no Vertex.
//template <class T>
//const std::shared_ptr<FEdge<T>> FGraph<T>::InsertEdge(std::shared_ptr<FVertex<T>> OriginVertex, std::shared_ptr<FVertex<T>> DestinationVertex, std::shared_ptr<FEdge<T>> NewEdge)

template <class T>
const std::shared_ptr<FVertex<T>> FGraph<T>::RemoveVertex(std::shared_ptr<FVertex<T>> VertexToRemove)
{
    if (VertexToRemove)
    {
        //Remove all pointers to that Vertex in the other Vertex IncidentEdgeVector.
        for (const std::shared_ptr<FVertex<T>> &OtherVertex : VertexVector)
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

template <class T>
const std::shared_ptr<FEdge<T>> FGraph<T>::RemoveEdge(std::shared_ptr<FEdge<T>> EdgeToRemove)
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

//template <class T>
//std::vector<std::shared_ptr<FVertex<T>>> &FGraph<T>::Vertices()

template <class T>
std::vector<std::shared_ptr<FEdge<T>>> &FGraph<T>::Edges()
{
    return EdgeVector; 
}

template <class T>
std::vector<std::shared_ptr<FEdge<T>>> &FGraph<T>::IncidentEdges(std::shared_ptr<FVertex<T>> CurrentVertex)
{
    return CurrentVertex->IncidentEdgeVector;
}

//template <class T>
//std::shared_ptr<FVertex<T>> FGraph<T>::GetVertexWithName(std::string Name)x
