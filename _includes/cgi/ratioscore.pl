#!/usr/bin/perl
##
## Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
## Creation Date: Sat 03 Apr 2021 01:32:58 PM PDT
## Last Modified: Sat 03 Apr 2021 09:12:27 PM PDT
## Filename:      /var/www/cgi-bin/ratioscore.pl
## Syntax:        Perl 5; CGI
## $Smake:        cp -f %f /var/www/cgi-bin/%b
## vim:           ts=3
##
## Description:   Convert Ratioscores into MIDI or MP3 files.
##                Backend for https://ratioscore.humdrum.org
##

use strict;
use IPC::Open2;
use CGI;
my $cgi_form = new CGI;

# Configuration variables:
my $basedir      = "/project/ratioscore";

# Command-line tools:
my $ratioscore = "$basedir/ratioscore/bin/ratioscore";
my $timidity   = "/usr/bin/timidity";
my $lame       = "/usr/bin/lame";

##########################################################################
##############################                            ###           ##
###############                                            ###############

my %OPTIONS;
$OPTIONS{'inputdata'}           = $cgi_form->param('inputdata');
$OPTIONS{'outputformat'}        = $cgi_form->param('outputformat');
# outputformat == "mid"   for MIDI
# outputformat == "mp3"   for MP3

if ($OPTIONS{'inputdata'} =~ /^\s*$/) {
	errorMessage("Error: no input score");
} elsif ($OPTIONS{'outputformat'} =~ /mid/i) {
	generateMidiFile();
} elsif ($OPTIONS{'outputformat'} =~ /mp3/i) {
	generateMp3File();
} else {
	printParameters();
}

exit(0);

###############                                            ###############
##############################                            ###           ##
##########################################################################

##############################
##
## generateMidiFile --
##

sub generateMidiFile {
	my $inputdata = $OPTIONS{"inputdata"};
	local (*READ, *WRITE);
	my $command = "$ratioscore -r";
	my $outputdata = "";
	my $pid = open2(\*READ, \*WRITE, "$command") or $outputdata = "ERROR";
	if ($outputdata ne "ERROR") {
		print WRITE $inputdata;
		close(WRITE);
		binmode(READ);
		my $udata;
		while (read(READ, $udata, 4096)) {
			$outputdata .= $udata
		}
	}

	if ($outputdata =~ /^MThd/) {
		print "Content-Type: audio/midi\n\n";
		print "$outputdata";
	} else {
		errorMessage($outputdata);
	}
}



##############################
##
## generateMp3File --
##

sub generateMp3File {
	my $inputdata = $OPTIONS{"inputdata"};
	local (*READ, *WRITE);
	my $command = "$ratioscore -r -x 630";
	$command   .= " | $timidity - -m60000 --preserve-silence -Ow -o -";
	$command   .= " | $lame - -b64 -";
	my $outputdata = "";
	my $pid = open2(\*READ, \*WRITE, "$command") or $outputdata = "ERROR";
	if ($outputdata ne "ERROR") {
		print WRITE $inputdata;
		close(WRITE);
		binmode(READ);
		my $udata;
		while (read(READ, $udata, 4096)) {
			$outputdata .= $udata
		}
	}

	if ($outputdata =~ /[^\t\n\x20-x7e]/) {
		print "Content-Type: audio/mpeg\n\n";
		print "$outputdata";
	} else {
		errorMessage("ERROR: " . $outputdata);
	}
}



##############################
##
## errorMessage --
##

sub errorMessage {
	my ($message) = @_;
	print "Content-Type: text/plain\n\n";
	print "$message\n";
}



##############################
##
## printParameters --
##

sub printParameters {
	my $output = "";
	my $name;
	my $value;
	foreach my $name ($cgi_form->param) {
		foreach my $value ($cgi_form->param($name)) {
			$output .= "$name ==\t$value\n";
		}
	}

	print "Content-Type: text/plain\n\n";
	print "CGI parameters:\n";
	print "$output\n";
}



