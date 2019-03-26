PROGNAMES = window image
PROG = $(addprefix bin/, $(PROGNAMES))
SRC = $(addsuffix .cpp, $(addprefix src/, $(PROGNAMES)))
CXX = g++
CXXFLAGS = -lSDL2 -std=c++11

.PHONY: clean all

all: $(PROG)

$(PROG): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(PROG)
