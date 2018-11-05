COMP345 Assignment 2
====================

Due date: November 4, 2018
--------------------------

Written by: Pierre-Andre Gagnon - 40067198
------------------------------------------

**Design**

The design of this project is straightforward. Four categories of files can be identified:

Driver files

- main.cpp and assignment2.h are strictly used to demonstrate the state of the project for assignment 2.

Library files

- graph.h/cpp was implemented as an external dependency since it does not depend at all on the rest of the projet. To do so, it uses templates to be flexible. It should be noted that most of the functions in it are not used, but were included to have a fully functionnal graph. Also note that these files are a bit messy since the use of templates implied that functions definitions had to be included in the files using them. As such, the functions that are used are definded in the header file instead of the source file.

Game files

- borough.h contains the struct that is used as template parameter for the graph.
- card.h/cpp contains the FCard and FDeck classes.
- diceroller.h/cpp contains the FDice and FDiceRoller classes.
- game.h/cpp contains the FGame class.
- map.h/cpp contains the FMap class.
- player.h/cpp contains the FPlayer class.
- tile.h/cpp contains the FTile and FTileStack classes.

Other files

- common.h/cpp contains various constants and enums that are used in many classes.
- helper.h.cpp contains various functions to help manage input.

**Dependencies**

The project only uses the C++ Standard Library.

**How to build**

The command I use to build the project on my machine is:

    g++ main.cpp diceroller.cpp graph.cpp player.cpp game.cpp helper.cpp common.cpp card.cpp tile.cpp map.cpp borough.cpp -I. -g -o kingofnewyork

The flags are:

- -I. : To tell the compiler to search the directory which was current when the compiler was invoked for #include "file".
- -g : To enable debugging. 
- -o kingofnewyork : To indicate the output file of the compilation.

**Coding environment**

This project is being coded using VS Code on Manjaro Linux. It is compiled using the GNU C++ Compiler.

**Coding standard**

This project uses [Epic's coding standard](https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard) which is used for the Unreal Engine.