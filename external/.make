#!/usr/bin/perl

my $git = `which git`;
chomp $git;

die "Error: git not found.  Try installing Homebrew (https://brew.sh)\n" if $git =~ /^\s*$/;

if ($git) {
	if (!-d "midifile") {
		`$git clone https://github.com/craigsapp/midifile && cd midifile && make`;
	}

	if (!-d "humlib") {
		`$git clone https://github.com/craigsapp/humlib && cd humlib && make`;
	}
} 

