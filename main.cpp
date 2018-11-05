// ----------------------------------------------------------------------------
// COMP345 Assignment 2
// Due date: November 4, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include <memory>
#include "game.h"
#include "helper.h"

using namespace KingOfNewYork;

    int main(int argc, char *argv[]) {
        Path = argv[0];
        std::cout << "COMP345 Assignment 2 driver program by Pierre-André Gagnon (40067198)."
                  << std::endl
                  << std::endl
                  << "Welcome to King of New York!"
                  << std::endl
                  << std::endl;

        std::shared_ptr<FGame> Game = std::make_shared<FGame>();
        //Game->Initialize();
        std::cout << std::endl;

        return 0;
    }
