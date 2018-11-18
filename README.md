COMP345 Assignment 3
====================

Due date: November 18, 2018
--------------------------

Written by: Pierre-Andre Gagnon - 40067198
------------------------------------------

**Design**

The design of this project is partially based on the strategy pattern and the observer pattern. This implies that most player behavior is handled with the former and that most of the "view" is handled by the latter.

Strategy pattern:
- Four player actions are handled by this patter:
    1. rolldicestrategy.h/cpp
    2. revolvedice.h/cpp
    3. movestrategy.h/cpp
    4. buycards.h/cpp
- In each case, the there are three available strategy:
    1. Human control: The game will prompt the user to choose his/her actions.
    2. Aggressive AI: The AI will try to stay away from Manhattan and roll as many Attack and Destruct to kill the other players.
    3. Moderate AI: The AI will try to stay in Manhattan and roll as many Celebrity and Ouch as possible to gain points.

Observer pattern:
- The way this design pattern is implemented, when a subject notifies its observers, it sends a reference to itself and an observer event.
- Many classes are used to implement this:
    - observer.h: This file contains the interface IObserver.
    - subject.h/cpp: These files contains the parent class of all subjects.
    - observerevent.h: This file contains the interface IObserverEvent and specific implementations for various events.
- The player as a subject:
    - The player notifies its observers every something important happens, most importantly the beginning of its phases and their outcomes.
    - There is only one observer that outputs to the console the notifications from the players.
- The gameview observer:
    - gameview.h/cpp: These files implement IObserver and are only used for notifications from players.
- The game as a subject:
    - The game notifies its observer at the beginning of each turn.
    - There is only one observer that outputs to the console the current state of the game.
- The stateview observer:
    - stateview.h/cpp: These files implement Observer and are only used for notification from the game to output the game state.

Other files:
- Driver file:
    - main.cpp is strictly used to start the game.
- Library files:
    - graph.h/cpp were implemented as an external dependency since it does not depend at all on the rest of the projet. To do so, it uses templates to be flexible. It should be noted that most of the functions in it are not used, but were included to have a fully functional graph.
- Game files:
    - borough.h contains FBorough class that is used as template parameter for the graph.
    - card.h/cpp contains the FCard and FDeck classes.
    - diceroller.h/cpp contains the FDice and FDiceRoller classes.
    - game.h/cpp contains the FGame class.
    - map.h/cpp contains the FMap class.
    - player.h/cpp contains the FPlayer class.
    - tile.h/cpp contains the FTile and FTileStack classes.
- Other files:
    - common.h/cpp contains various constants and enums that are used in many classes.
    - helper.h.cpp contains various functions to help manage input.

**Note about comments**

Since this project code is verbose and has long descriptive names, it did not appear essential to heavily comment it. As such, comments are mostly provided to explain parts that are not clear.

**Dependencies**

The project only uses the C++ Standard Library. It should, however, be noted that it uses some C++17 features. See the **How to build** section.

**How to build**

The command I use to build the project on my machine is:

    g++ main.cpp diceroller.cpp player.cpp game.cpp helper.cpp common.cpp card.cpp tile.cpp map.cpp borough.cpp rolldicestrategy.cpp resolvedicestrategy.cpp movestrategy.cpp buycardsstrategy.cpp subject.cpp gameview.cpp stateview.cpp -I. -g -std=c++17 -lstdc++fs -o kingofnewyork

The flags are:

- -I. : To tell the compiler to search the directory which was current when the compiler was invoked for #include "file".
- -g : To enable debugging. 
- -o kingofnewyork : To indicate the output file of the compilation.
- -std=c++17: To include c++17.
- -lstdc++fs: To include the fs (filesystem) library of the standard library.

**Coding environment**

This project is being coded using VS Code on Manjaro Linux. It is compiled using the GNU C++ Compiler.

**Coding standard**

This project uses [Epic's coding standard](https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard) which is used for the Unreal Engine.