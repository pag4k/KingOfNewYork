// ----------------------------------------------------------------------------
// COMP345 Assignment 1
// Due date: October 12, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include <filesystem>

#include "helper.h"0

namespace KingOfNewYork
{
    std::string Path;
    //If invalid, returns -1.
    const int InputSingleDigit()
    {
        std::string Input;
        std::getline(std::cin, Input);
        if (Input.length() == 1)
        {
            return ParseIntFromChar(Input[0]);
        }
        else
        {
            return -1;
        }
    }

    const std::string InputString()
    {
        std::string Input;
        std::getline(std::cin, Input);
        return Input;
    }

    const int ParseIntFromChar(const char Char)
    {
        int Digit = (int)Char - 48;
        if (0 <= Digit && Digit <= 9)
        {
            return Digit;
        }
        else
        {
            return -1;
        }
    }

    std::string GetFileName(const std::string &FullPath)
    {
        int Position = FullPath.length() - 1;
        while (FullPath[Position] != '/')
        {
            --Position;
            if (Position < 0)
            {
                return "";
            }
        }
        return FullPath.substr(Position + 1, FullPath.length() - Position);
    }

    const std::vector<std::string> GetMapFiles(const std::string &Folder)
    {
        std::vector<std::string> MapFiles;
        //TODO: Not sure if this will work on Windows because of the /
        for (auto &p : std::filesystem::directory_iterator(Path.substr(0, Path.length() - GetFileName(Path).length()) + Folder))
        {
            MapFiles.push_back(GetFileName(p.path().string()));
        }
        return MapFiles;
    }
}
