PROG := $(addprefix bin/, window image keyTest ssTest oopTest)
CXX := g++
CXXFLAGS := -lSDL2 -std=c++11

.PHONY: clean all

all: $(PROG)

bin/window: src/window.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

bin/image: src/image.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

bin/keyTest: src/keyTest.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

bin/ssTest: src/ssTest.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

bin/oopTest: src/oopTest.cpp src/window_object.hpp src/window_object.cpp
	$(CXX) $(CXXFLAGS) -c -o src/oopTest.o src/oopTest.cpp
	$(CXX) $(CXXFLAGS) -c -o src/window_object.o src/window_object.cpp
	$(CXX) $(CXXFLAGS) -o bin/oopTest src/window_object.o src/oopTest.o

clean:
	rm -f $(PROG)
