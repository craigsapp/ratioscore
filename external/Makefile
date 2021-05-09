

all:
	./.make

update:
	(cd midifile && git pull)
	(cd humlib && make update)
	(cd midifile && make)
	(cd humlib && make)

compile:
	(cd midifile && make)
	(cd humlib && make)


clean:
	rm -rf midifile
	rm -rf humlib

