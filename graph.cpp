#include "graph.h"

template <class T>
const typename FGraph<T>::FVertex *FGraph<T>::EndVertices(const FVertex *CurrentEdge) const
{
    //I don't know how to return that because I can only return a pointer to an array.
    //const std::vector<Edge> Array[] = { CurrentEdge->Origin, CurrentEdge->Destination }
    //return Array;
    return nullptr;
}

//NOTE: I'm using this to know if an edge as this vertex. This is not the role of this method.
template <class T>
const typename FGraph<T>::FVertex *FGraph<T>::Opposite(const FVertex *CurrentVertex, const FEdge *CurrentEdge) const
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
bool FGraph<T>::AreAdjacent(const FVertex * VertexA, const FVertex * VertexB) const
{
    if (VertexA && VertexB)
    {
        //Not sure about what to return when it is itself.
        if (VertexA == VertexB)
        {
            return false;
        }

        for (const FEdge * &IncidentEdge : VertexA->IncidentEdgeVector)
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
void FGraph<T>::Replace(FVertex * OldVertex, FVertex * NewVertex)
{
    if (OldVertex && NewVertex)
    {
        OldVertex->Name = NewVertex->Name;
    }
}

template <class T>
void FGraph<T>::Replace(FEdge * OldEdge, FEdge * NewEdge)
{
    if (OldEdge && NewEdge)
    {
        OldEdge->Name = NewEdge->Name;
    }
}

template <class T>
const typename FGraph<T>::FVertex *FGraph<T>::RemoveVertex(FVertex *VertexToRemove)
{
    if (VertexToRemove)
    {
        //Remove all pointers to that Vertex in the other Vertex IncidentEdgeVector.
        for (const auto OtherVertex : VertexVector)
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
                delete *it;
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
                delete *it;
                VertexVector.erase(it);
                return *it;
            }
        }
    }

    return nullptr;
}

template <class T>
const typename FGraph<T>::FEdge *FGraph<T>::RemoveEdge(FEdge *EdgeToRemove)
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
                delete *it;
                EdgeVector.erase(it);
                return *it;
            }
        }
    }

    return nullptr;
}

template <class T>
std::vector<typename FGraph<T>::FVertex *> &FGraph<T>::Vertices()
{
    return VertexVector;
}

template <class T>
std::vector<typename FGraph<T>::FEdge *> &FGraph<T>::Edges()
{
    return EdgeVector; 
}

template <class T>
std::vector<typename FGraph<T>::FEdge *> &FGraph<T>::IncidentEdges(FVertex * CurrentVertex)
{
    return CurrentVertex->IncidentEdgeVector;
}

//template <class T>
//typename FGraph<T>::FVertex *FGraph<T>::GetVertexWithName(std::string Name)
