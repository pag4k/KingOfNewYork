// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#ifndef HELPER_H
#define HELPER_H

#include "precompiledheader.h"

namespace KingOfNewYork
{
    extern std::string Path;
    void PrintHeader(std::string Header);
    void PrintNormal(std::string Message);
    void PrintList(int Number, std::string Message);
    void PrintChar(char Character);
    void AddPadding(std::string& OutString, int OutputLength, char Symbol);
    const int InputSingleDigit();
    const std::string InputString();
    const int ParseIntFromChar(char Char);
    std::string GetFileName(const std::string &FullPath);
    const std::vector<std::string> GetMapFiles(const std::string &Folder);
}

#endif
