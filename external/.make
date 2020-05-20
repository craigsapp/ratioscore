#!/usr/bin/perl

if (!-d "midifile") {
	`git clone https://github.com/craigsapp/midifile && cd midifile && make`;
}

if (!-d "humlib") {
	`git clone https://github.com/craigsapp/humlib && cd humlib && make`;
}

