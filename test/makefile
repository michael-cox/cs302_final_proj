PROGNAMES = window image
HEADERNAMES = window_object
PROG = $(addprefix bin/, $(PROGNAMES))
HEADERS = $(addsuffix .hpp, $(addprefix src/, $(HEADERNAMES)))
SRC = $(addsuffix .cpp, $(addprefix src/, $(PROGNAMES)))
CXX = g++
CXXFLAGS = -lSDL2 -std=c++11

.PHONY: clean all

all: $(PROG)

$(PROG): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(PROG)
