#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.

#OBJS specifies which files to compile as part of the project
OBJS = main.cpp diceroller.cpp player.cpp game.cpp helper.cpp common.cpp card.cpp tile.cpp map.cpp borough.cpp rolldicestrategy.cpp resolvedicestrategy.cpp movestrategy.cpp buycardsstrategy.cpp subject.cpp gameview.cpp stateview.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
#-g to enable debugging
COMPILER_FLAGS = -I. -g -std=c++17

#LINKER_FLAGS specifies the libraries we're linking against
#LINKER_FLAGS = -lSDL2
LINKER_FLAGS = -lstdc++fs

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = kingofnewyork

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)