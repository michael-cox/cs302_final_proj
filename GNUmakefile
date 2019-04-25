CXX := g++
CXXFLAGS := -g -std=c++11 -lSDL2 -lSDL2_image
PROG := brb2d
SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
HEAD := $(wildcard src/*.hpp)

all: $(OBJ) $(HEAD)
	$(CXX) $(CXXFLAGS) $(OBJ) -o bin/$(PROG)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f bin/$(PROG) $(OBJ)
