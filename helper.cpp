// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include <filesystem>
#include <cmath>
#include "helper.h"

namespace KingOfNewYork
{
    std::string Path;

    void PrintHeader(std::string Header)
    {
        AddPadding(Header, 80, '#');
        std::cout << std::endl
                  << Header
                  << std::endl;
    }

    void PrintNormal(std::string Message)
    {
        std::cout << Message
                  << std::endl;
    }

    void AddPadding(std::string &OutString, int OutputLength, char Symbol) {
        const unsigned long StringLength = OutString.length();
        if (StringLength + 4 > OutputLength)
        {
            return;
        }
        OutString = std::string((OutputLength - StringLength - 2)/2, Symbol) + " " + OutString + " " + std::string(
                static_cast<unsigned long>(std::ceil((OutputLength - StringLength - 2)/2.0)), Symbol);

    }

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

    const int ParseIntFromChar(char Char)
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
        int Position = (int)FullPath.length() - 1;
        while (FullPath[Position] != '/')
        {
            --Position;
            if (Position < 0)
            {
                return "";
            }
        }
        return FullPath.substr(static_cast<unsigned long>(Position + 1), FullPath.length() - Position);
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
