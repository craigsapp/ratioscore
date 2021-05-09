
FLAGS   = -O3 -std=c++11
INCDIRS = -Iexternal/humlib/include -Iexternal/midifile/include
LIBDIRS = -Lexternal/humlib/lib -Lexternal/midifile/lib
LIBS    = -lhumlib -lmidifile -lpugixml
BIN     = bin
SRC     = src

.PHONY: tests

all: compile

compile:
	(cd external; make)
	@mkdir -p bin
	g++ $(INCDIRS) $(FLAGS) -o $(BIN)/ratioscore $(SRC)/ratioscore.cpp $(LIBDIRS) $(LIBS)


install:
	sudo cp bin/ratioscore /usr/local/bin/ && strip /usr/local/bin/ratioscore


tests: test
test:
	@echo "Creating test MIDI files in the tests directory..."
	for i in tests/*.txt; do bin/ratioscore $$i; done

cleantests: cleantest
cleantest:
	@echo "Deleting MIDI files in tests directory..."
	rm -f tests/test[0-9][0-9][0-9].mid

update:
	(cd external; make update)
	git pull


