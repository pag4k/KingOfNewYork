#include <fstream>
#include <iostream>

#include "map.h"

FMap::FMap(std::string FileName)
{
    std::ifstream InputStream;
    InputStream.open(FileName);

    if (InputStream.fail())
    {
        std::cout << "Error: Could not open file: " << FileName << std::endl;
        return;
    }

    std::string Text;
    while (!std::getline(InputStream, Text).eof())
    {
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
                    std::size_t Position1 = Text.find(',');
                    std::string Name = Text.substr(0, Position1++);
                    FBorough *Borough = Graph.InsertVertex(Name);
                    if (Borough)
                    {
                        Borough->Name = Name;
                        std::size_t Position2 = Text.find(',', Position1);
                        Borough->bStartingLocation = (Text.substr(Position1, Position2++ - Position1) == "StartingLocation");
                        std::size_t Position3 = Text.find(',', Position2);
                        Borough->bInManhattan = (Text.substr(Position2, Position3 - Position2) == "InManhattan");
                    }
                    else
                    {
                        std::cout << "Error: Could not create borough." << std::endl;
                        continue;
                    }

                }
            }
        }
        else if (Text == "EDGE")
        {
            while (!std::getline(InputStream, Text).eof())
            {
                if (Text == "")
                {
                    break;
                }
                std::size_t Position = Text.find(':');

                if (Position != std::string::npos)
                {
                    std::string OriginName = Text.substr(0, Position);
                    std::string EdgeNames = Text.substr(Position + 1);
                    //Checking if there is at least one comma.
                    if (Text.find(',') != std::string::npos)
                    {
                        std::size_t Previous = 0;
                        while (EdgeNames.find(',', Previous) != std::string::npos)
                        {
                            std::size_t Current = EdgeNames.find(',', Previous);
                            std::string DestinationName = EdgeNames.substr(Previous, Current - Previous);
                            Graph.InsertEdge(OriginName, DestinationName);
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

    std::cout << std::endl;
    InputStream.close();
}
