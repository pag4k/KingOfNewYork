COMP345 Assignment 4
====================

Due date: December 3, 2018
--------------------------

Written by: Pierre-Andre Gagnon - 40067198
------------------------------------------

**Design**

The design of this project is partially based on the strategy pattern, the observer pattern, and MVC pattern.

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
- The playerview observer:
    - playerview.h/cpp: These files implement IObserver and are only used for notifications from players.
- The game as a subject:
    - The game notifies its observer at the beginning of each turn.
- The gameview observer:
    - stateview.h/cpp: These files implement Observer and are only used for notification from the game.
- The cards as subject:
    - The cards notify their observer when they are used.
- The cardview observer:
    - cardview.h/cpp: These files implement IObserver and are only used for notifications from cards.
- The diceroller as subject:
    - The dicerollers notify their observer when they are used.
- The diceview observer:
    - diceview.h/cpp: These files implement IObserver and are only used for notifications from dicerollers.

MVC pattern:
- While it is not implemented for all the projects, some classes have been separated in model and controller. This separate the behavior from the data and makes the code more modular.
- game.h/cpp and gamecontroller.h/cpp
    - The former only includes the game data while the latter take cares of the game setup and the game loop.
- player.h/cpp and playercontroller.h/cpp
    - The former only includes the player data while the latter take cares of player turns.
    - In a sense, the player is actually the monster been played and the player controller is the the actuel player.

Precompiler heard:
- This project uses a precompiler header, precompiledheader.h, to speed up compilation.
- It includes all references to the standard library since they are not expected to change often.

Other files:
- Driver file:
    - main.cpp is strictly used to start the game.
- Library files:
    - graph.h/cpp were implemented as an external dependency since it does not depend at all on the rest of the projet. To do so, it uses templates to be flexible. It should be noted that most of the functions in it are not used, but were included to have a fully functional graph.
- Game files:
    - borough.h contains FBorough class that is used as template parameter for the graph.
    - card.h/cpp contains the FCard and FDeck classes.
    - diceroller.h/cpp contains the FDice and FDiceRoller classes.
    - map.h/cpp contains the FMap class.
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

    make all
    
Details:

- -o kingofnewyork : To indicate the output file of the compilation.
- -std=c++17: To include c++17.
- -lstdc++fs: To include the fs (filesystem) library of the standard library.

**Coding environment**

This project is being coded using VS Code on Manjaro Linux. It is compiled using the GNU C++ Compiler.

**Coding standard**

This project uses [Epic's coding standard](https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard) which is used for the Unreal Engine.