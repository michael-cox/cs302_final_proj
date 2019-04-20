CXX := g++
CXXFLAGS := -std=c++11 -lSDL2 -lSDL2_image
PROG := brb2d
SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
CURRENTOBJ := src/game.o src/game_object.o src/image.o src/input.o src/menu.o
HEAD := $(wildcard src/*.hpp)
CURRENTHEAD := src/game_object.hpp src/image.hpp src/input.hpp src/menu.hpp

all: $(OBJ) $(HEAD)
	$(CXX) $(CXXFLAGS) $(OBJ) -o bin/$(PROG)

current: $(CURRENTOBJ) $(CURRENTHEAD)
	$(CXX) $(CXXFLAGS) $(CURRENTOBJ) -o bin/$(PROG)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(PROG) $(OBJ)
