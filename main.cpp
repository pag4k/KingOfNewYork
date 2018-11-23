// ----------------------------------------------------------------------------
// COMP345 Assignment 3
// Due date: November 18, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include "game.h"
#include "helper.h"
#include "gameview.h"
#include "playerview.h"
#include "diceview.h"
#include "cardview.h"

using namespace KingOfNewYork;

    int main(int argc, char *argv[]) {
        Path = argv[0];
        std::cout << "COMP345 Assignment 3 driver program by Pierre-André Gagnon (40067198)."
                  << std::endl
                  << std::endl
                  << "Welcome to King of New York!"
                  << std::endl
                  << std::endl;

        std::shared_ptr<FGame> Game = std::make_shared<FGame>();

        FGameView GameView = FGameView(Game);
        FPlayerView PlayerView = FPlayerView(Game);
        FDiceView DiceView = FDiceView(Game);
        FCardView CardView = FCardView(Game);
        Game->StartupPhase();
        Game->StartMainPhase();

        std::cout << std::endl;

        return 0;
    }
