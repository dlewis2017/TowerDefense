#OBJS specifies which files to compile as part of the project
OBJS = main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAMES = main

#This is the target that compiles our executable
all: main

main: main.o Enemy.o Goblin.o Troll.o MapDirections.o
	$(CC) main.o Enemy.o Goblin.o Troll.o MapDirections.o $(COMPILER_FLAGS) $(LINKER_FLAGS) -o main

main.o: main.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c main.cpp

Enemy.o: Enemies/Enemy.cpp Enemies/Enemy.h MapDirections.cpp MapDirections.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Enemies/Enemy.cpp

Goblin.o: Enemies/Goblin.cpp Enemies/Goblin.h MapDirections.cpp MapDirections.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Enemies/Goblin.cpp

Troll.o: Enemies/Troll.cpp Enemies/Troll.h MapDirections.cpp MapDirections.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Enemies/Troll.cpp

MapDirections.o: MapDirections.cpp MapDirections.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c MapDirections.cpp

clean: 
	-rm *.o $(OBJ_NAMES)
