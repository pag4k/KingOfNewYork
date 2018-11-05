// ----------------------------------------------------------------------------
// COMP345 Assignment 2
// Due date: November 4, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef HELPER_H
#define HELPER_H
#include <vector>
#include <string>

namespace KingOfNewYork
{
    extern std::string Path;

    const int InputSingleDigit();
    const std::string InputString();
    const int ParseIntFromChar(const char Char);
    std::string GetFileName(const std::string &FullPath);
    const std::vector<std::string> GetMapFiles(const std::string &Folder);
}

#endif
