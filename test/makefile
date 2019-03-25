PROG=window image
OBJ=window_test.o image_test.o
SRC=window_test.cpp image_test.cpp
CXX=g++
CXXFLAGS= -lSDL2 -std=c++11

.PHONY: clean all

all: $(PROG)

window: src/window_test.o
	g++ $(CXXFLAGS) -o bin/window src/window_test.o

window_test.o: src/window_test.cpp
	g++ $(CXXFLAGS) -c -o src/window_test.o src/window_test.cpp

image: src/image_test.o
	g++ $(CXXFLAGS) -o bin/image src/image_test.o

image_test.o: src/image_test.cpp
	g++ $(CXXFLAGS) -c -o src/image_test.o src/image_test.cpp

clean:
	rm -f bin/$(PROG) src/$(OBJ)
