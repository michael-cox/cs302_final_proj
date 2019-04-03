PROGNAMES := brb2d
PROGS := $(addprefix bin/, $(PROGNAMES))
CXX := g++
CXXFLAGS := -lSDL2 -lSDL2_image -std=c++11

.PHONY: test test-clean all clean

all: $(PROGS)

bin/brb2d: src/window_object.hpp src/window_object.o src/game.o
	$(CXX) $(CXXFLAGS) src/game.o src/window_object.o -o bin/brb2d

src/window_object.o: src/window_object.hpp src/window_object.cpp
	$(CXX) $(CXXFLAGS) -c src/window_object.cpp -o src/window_object.o

src/game.o: src/game.cpp
	$(CXX) $(CXXFLAGS) -c src/game.cpp -o src/game.o

clean:
	rm -f $(PROGS)
	rm -f src/*.o

test:
	@$(MAKE) -C test

test-clean:
	@$(MAKE) -C test clean
