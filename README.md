ratioscore
===========

Ratioscore is a program that converts a
[Humdrum](https://www.humdrum.org)-based textual score representing
musical intervals as ratios into a Standard MIDI file, using
pitch-bend messages to tune notes out of equal temperament, allowing
playback of just intervals with any MIDI player.

Downloading
===========

To download from github, type in a unix/linux terminal:

```bash
git clone https://github.com/craigsapp/ratioscore
```

This should download the source code into the current directory.  


Compiling
=========

To compile, enter the ratioscore directory and then type:

```bash
make
```

This will download and compile two external libraries, [midifile](https://github.com/craigsapp/midifile)
(for MIDI file parsing) and [humlib](https://github.com/craigsapp/humlib) (for Humdrum file
parsing).  The ratioscore program will be compiled and placed in the `bin` directory.  To
install in `/usr/local/bin`, allowing the ratioscore program to be run from any directory, type:

```bash
make install
```


Documentation
=============

The website https://ratioscore.humdrum.org serves as front-end for
the ratioscore program and provides documentation as well as online-rendering
of Ratioscores into MIDI and MP3 files.

Timidity and lame are used to create the MP3 files.  See the
[server-side CGI script](https://github.com/craigsapp/ratioscore/blob/gh-pages/_includes/cgi/ratioscore.pl)
if you want to interface to your preferred MIDI rendering software,
or to set up your own soundfonts with Timidity.  The website
uses [jekyll](https://jekyllrb.com) and is hosted on Github Pages
([source files](https://github.com/craigsapp/ratioscore/tree/gh-pages)).



