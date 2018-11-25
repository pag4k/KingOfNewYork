// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include <iostream>
#include "gamecontroller.h"
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

    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();

    if (GameController->IsValid())
    {
        FGameView GameView = FGameView(GameController);
        FPlayerView PlayerView = FPlayerView(GameController);
        FDiceView DiceView = FDiceView(GameController);
        FCardView CardView = FCardView(GameController);
        GameController->StartupPhase();
        GameController->StartMainPhase();
    }

    std::cout << std::endl;

    return 0;
}
