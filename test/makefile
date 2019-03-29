PROG := window image keyTest
CXX := g++
CXXFLAGS := -lSDL2 -std=c++11

.PHONY: clean all

all: $(PROG)

window: src/window.cpp
	$(CXX) $(CXXFLAGS) -o bin/window $<

image: src/image.cpp
	$(CXX) $(CXXFLAGS) -o bin/image $<

keyTest: src/keyTest.cpp
	$(CXX) $(CXXFLAGS) -o bin/keyTest $<

clean:
	rm -f $(PROG)
