PROG = $(addprefix bin/, window image)
CXX = g++
CXXFLAGS = -lSDL2 -std=c++11

.PHONY: clean all

all: $(PROG)

$(PROG): src/%.o: src/%.cpp:
	$(CXX) -c $(CXXFLAGS) src/$< -o $@

clean:
	rm -f $(PROG)
