
#These variables are used for the precompiled header
CORE_PCH_FILENAME = precompiledheader.h
CORE_PCH = $(CORE_PCH_FILENAME).gch

#OBJS specifies which files to compile as part of the project
OBJS = main.o diceroller.o player.o game.o helper.o common.o card.o tile.o map.o borough.o rolldicestrategy.o resolvedicestrategy.o movestrategy.o buycardsstrategy.o subject.o playerview.o gameview.o diceview.o cardview.o playercontroller.o gamecontroller.o

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -I. -std=c++17

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lstdc++fs

#OBJ_NAME specifies the name of our executable
OBJ_NAME = kingofnewyork

all: $(CORE_PCH) $(OBJS)
	$(CC) $(COMPILER_FLAGS) -o $(OBJ_NAME) $(OBJS) $(LINKER_FLAGS)

$(CORE_PCH): $(CORE_PCH_FILENAME)
	$(CC) $(COMPILER_FLAGS) -o $@ $<

%.o: %.cpp $(PCH_OUT)
	$(CC) $(COMPILER_FLAGS) -include $(CORE_PCH_FILENAME) -c -o $@ $<
