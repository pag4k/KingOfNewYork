// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "map.h"

namespace KingOfNewYork
{
    FMap::FMap(const std::string &FileName)
    {
        bIsValid = LoadMap(FileName);
        if (bIsValid)
        {
            std::cout << "Map succesfully loaded." << std::endl;
        }
        else
        {
            std::cout << "Error: Map was not loaded." << std::endl;
        }
    }

    bool FMap::LoadMap(const std::string &FileName)
    {
        std::ifstream InputStream;
        InputStream.open(FileName);

        if (InputStream.fail())
        {
            std::cout << "Error: Could not open file: "
                      << FileName
                      << std::endl;
            return false;
        }

        std::string Text;
        while (!std::getline(InputStream, Text).eof())
        {
            if (Text == "VERTEX")
            {
                while (!std::getline(InputStream, Text).eof())
                {
                    if (Text.empty())
                    {
                        break;
                    }
                    else
                    {
                        std::size_t Position1 = Text.find(',');
                        std::string Name = Text.substr(0, Position1++);
                        std::shared_ptr<FBorough> Borough = Graph.InsertVertex(Name);
                        if (Borough)
                        {
                            Borough->SetName(Name);
                            std::size_t Position2 = Text.find(',', Position1);
                            Borough->SetStartingLocation(Text.substr(Position1, Position2++ - Position1) == "StartingLocation");
                            std::size_t Position3 = Text.find(',', Position2);
                            Borough->SetCenter(Text.substr(Position2, Position3 - Position2) == "Center");
                            Boroughs.push_back(Borough);
                        }
                        else
                        {
                            std::cout << "Error: Could not create borough."
                                      << std::endl;
                            return false;
                        }
                    }
                }
            }
            else if (Text == "EDGE")
            {
                while (!std::getline(InputStream, Text).eof())
                {
                    if (Text.empty())
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
        return true;
    }

    std::shared_ptr<FBorough> FMap::GetCenterBorough()
    {
        auto BoroughIt = std::find_if(GetMutableBoroughs().begin(), GetMutableBoroughs().end(),
                                   [](const auto &Borough){ return Borough->IsCenter(); });
        if (BoroughIt == GetMutableBoroughs().end())
        {
            return nullptr;
        }
        else
        {
            return *BoroughIt;
        }

    }
}
