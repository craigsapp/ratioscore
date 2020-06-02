
FLAGS   = -O3 -std=c++11
INCDIRS = -Iexternal/humlib/include -Iexternal/midifile/include
LIBDIRS = -Lexternal/humlib/lib -Lexternal/midifile/lib
LIBS    = -lhumlib -lmidifile -lpugixml
BIN     = bin
SRC     = src

all: init
	@mkdir -p bin
	g++ $(INCDIRS) $(FLAGS) -o $(BIN)/ratioscore $(SRC)/ratioscore.cpp $(LIBDIRS) $(LIBS)


init:
	@if [ ! -d external/midifile ]; then \
		(cd external; make); \
	fi

test:
	bin/ratioscore tests/test1.txt

