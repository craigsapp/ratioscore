

all:
	./.make

update:
	(cd midifile && git pull)
	(cd humlib && make update)
	(cd midifile && make library)
	(cd humlib && make library)

compile:
	(cd midifile && make library)
	(cd humlib && make library)


clean:
	rm -rf midifile
	rm -rf humlib

