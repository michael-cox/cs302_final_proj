PROG=test
OBJ=sdl_test.o
SRC=sdl_test.cpp
CXX=g++
CXXFLAGS= -lSDL2 -std=c++11

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJ)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c -o $(OBJ) $(SRC)

.PHONY: clean all

all: $(PROG)

clean:
	rm -f $(PROG) $(OBJ)
