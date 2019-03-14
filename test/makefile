PROG=window
OBJ=window_test.o
SRC=window_test.cpp
CXX=g++
CXXFLAGS= -lSDL2 -std=c++11

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) -o bin/$(PROG) src/$(OBJ)

$(OBJ): src/$(SRC)
	$(CXX) $(CXXFLAGS) -c -o src/$(OBJ) src/$(SRC)

.PHONY: clean all

all: $(PROG)

clean:
	rm -f bin/$(PROG) src/$(OBJ)
