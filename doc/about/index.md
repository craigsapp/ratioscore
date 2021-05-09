---
title: "About"
permalink: /about/index.html
layout: page
vim: ts=3:ft=html
---

Ratioscores are designed to explore and test tunings for music
composition.  This website allows online editing and rendering of
the scores into MIDI and MP3 files, but you can also use the <a
target="_blank" href="https://github.com/craigsapp/ratioscore">command-line
converter<a/> for batch processing on your own computer.

The structure of a ratioscore is based on the <a target="_blank"
href="https://www.humdrum.org/guide/ch05">Humdrum file format<a/>:
time progresses downwards in the file, and columns (called <i>spines</i>
in Humdrum terminology) are used to encode multiple streams of
time-sequenced data in parallel, with each row representing a
simultaneity across all spines.  All <a href="/pitch">pitch</a>
data is stored in up to 15 `**ratio` spines, while the <a
href="/time">timeline</a> can be expressed in multiple formats
depending on the best one for your application.  <a
href="/drum">Percussion</a> can also be added to the score using
one or more `**drum` spines.  Other spine types will be ignored,
and can be used for general comments for example.

To get started, read the <a href="/pitch">pitch</a> and <a
href="/time">time</a> pages to observe how to represent time and
pitch.  Visit the <a href="/generator">score generator</a> page to
create an empty score to fill in with your own notes and timings.



<h2> Motivation </h2>

Ratioscore was designed as a composition prototyping system for
<i>The Answers</i> by <a target="_blank" href="https://juliezhu.net">Julie Zhu</a>.
Here is a performance of it
by the <a target="_blank" href="https://jackquartet.com">JACK
Quartet in December 2020</a>:

<style>
	iframe {
		position: absolute;
		top: 0;
		left: 0;
		width: 100%;
		height: 100%;
		align: center;
	}
</style>

<div style="margin-bottom:40px;">
  <div style="position:relative;padding-top:56.25%;">
    <iframe src="https://www.youtube.com/embed/Dx5l-9MUZ1o" frameborder="0" allowfullscreen></iframe>
  </div>
</div>


Below is the prototype for the final score (first minute of the
piece before dynamics, glissandos and articulations were added).
A clarinet sound is used below since it has less vibratio than the
string instruments in the MIDI player used to create the synthetic
performance.

{% include ratioscore.html id="quick-answers" height="600px" %}
<script type="application/x-ratioscore" id="quick-answers">
!!!COM: Zhu, Julie
!!!OTL: The Answers
!!!ONB: Prototype (unquantized time, no dynamics)
!!!ODT: 2020/12
**time	**ratio	**ratio	**ratio	**ratio
*	*Icello	*Iviola	*Ivioln	*Ivioln
*	*ref:C2	*ref:C2	*ref:C2	*ref:C2
4.231	.	.	27/8	.
6.182	2	.	.	.
7.441	.	.	3	.
9.337	.	3	.	.
9.502	.	.	.	63/6
9.521	.	.	.	7/2
11.522	.	.	6	.
13.571	.	.	.	7
13.958	.	.	9	.
14.814	.	.	6	.
15.358	.	.	.	12
15.457	1	.	.	.
15.567	.	.	27/2	.
16.487	.	.	.	63/4
17.037	.	.	9	.
17.459	.	.	.	63/8
17.776	.	.	27/2	.
18.162	.	.	.	27/2
18.476	.	.	.	18
19.854	.	.	16	.
20.038	.	2	.	.
20.223	.	.	.	21
20.594	.	.	12	.
20.837	.	.	.	27/2
22.064	.	.	18	.
22.103	.	.	.	27
22.11	.	.	.	9
22.816	.	.	27/4	.
23.334	.	.	.	14
23.673	.	.	12	.
24.066	3	.	.	.
25.108	.	.	.	21/2
25.499	9/4	.	.	.
26.108	.	.	8	.
28.582	.	.	.	6
28.589	.	.	.	6
30.19	.	.	9/2	.
32.294	.	4	.	.
33.399	.	.	4	.
34.39	4	.	.	.
39.386	.	4	.	.
40.957	.	6	.	.
41.006	6	.	.	.
42.579	.	.	3	.
44.052	4	.	.	.
46.319	.	.	.	7/2
46.863	.	9	.	.
48.399	6	.	.	.
49.075	.	.	6	.
51.153	.	7	.	.
52.73	.	.	9	.
52.766	.	.	.	7
54.239	.	9	.	.
54.303	.	.	27/2	.
54.608	.	.	.	12
55.508	.	.	.	63/4
55.961	7	.	.	.
57.06	.	.	27/2	.
57.609	.	.	9	.
57.746	.	.	.	18
58.098	.	.	.	27/2
58.979	.	.	.	63/8
59.194	.	.	16	.
59.495	.	.	.	21
*-	*-	*-	*-	*-

</script>

The Ratioscore was first converted into MIDI and then loaded into
Sibelius to quantize note durations into notatable rhythms and to
add <a target="_blank" href="https://www.plainsound.org/HEJI">HEJI
accidentals</a>.


<h2> Conference </h2>

Ratioscores will be presented at <a href="/tenor2021">TENOR 2021</a>.


<h2> Software and website </h2>

Ratioscores on this website are converted into MIDI files using <a
target="_blank" href="https://github.com/craigsapp/ratioscore">this
software</a>.  After converting into MIDI files, MP3s are generated
for this website using <a target="_blank"
href="http://timidity.sourceforge.net">timidity</a>, although any
MIDI syntheizer should work.

The software adjusts the tuning of each note with pitch-bend message
to allow for non-equal temperament pitches.  <a
href="glissandos">Glissandos</a> up to one octave are also possible,
with the convert automatically adjusting the pitch-bend depth to
accomodate the widest glissando in a part.

This website is hosted on Github and uses Jekyll for page templating.
<a target="_blank"
href="https://github.com/craigsapp/ratioscore/tree/gh-pages">Here</a> are
the source files for the website.  The Ratioscore to MIDI/MP3
conversion occurs on the server side using this <a target="_blank"
href="https://github.com/craigsapp/ratioscore/blob/gh-pages/_includes/cgi/ratioscore.pl">CGI
script</a>.

In the CGI script, the command `ratioscore -r` converts a Ratioscore
into a MIDI file, with the `-r` option outputting the MIDI file to standard
output (so that the CGI script does not need to store any intermediate files).

To convert to MIDI, the command is:

```bash
ratioscore -r -x630 | timidity - -m60000 --preserve-silence -Ow -o - | lame - -b64 -
```

This command first converts a Ratioscore to MID, then converts the
MIDI into a WAVE audio file, then the WAVE file is converted into
an MP3. Options:

<style>

span.command {
	white-space: pre;
}

table.command tr td {
	vertical-align: top;
}

</style>


<table class="command">
<tr><th>Command</th><th>Meaning</th></tr>
<tr><td><span class="command"><b>ratioscore</b> -r</span></td>
    <td> print MIDI file to standard output </td></tr>
<tr><td><span class="command">&nbsp;&nbsp;&nbsp; -x603</span></td>
     <td> limit output to 630 seconds. </td></tr>
<tr><td><span class="command"><b>timidity</b> -m60000</span></td>
     <td></td></tr>
<tr><td><span class="command">&nbsp;&nbsp;&nbsp; --preserve-silence</span></td>
     <td> keep any starting silence from the MIDI file. </td></tr>
<tr><td><span class="command">&nbsp;&nbsp;&nbsp; -Ow</span></td>
     <td> output as WAVE file. </td></tr>
<tr><td><span class="command">&nbsp;&nbsp;&nbsp; -o -</span></td>
     <td> output WAVE file to standard output. </td></tr>
<tr><td><span class="command"><b>lame</b> -</span></td>
     <td> Read from standard input </td></tr>
<tr><td><span class="command">&nbsp;&nbsp;&nbsp; -b64</span></td>
     <td> 64 kbits/second </td></tr>
<tr><td><span class="command">&nbsp;&nbsp;&nbsp; -</span></td>
     <td> print to standard output </td></tr>
</table>

<h2 data-sidebar="Bug&nbsp;reports"> Bug reports and feature requests </h2>

Bug reports and feature requests can be submitted to the <a
target="_blank" href="https://github.com/craigsapp/ratioscore/issues">Ratioscore repository</a> on Github.


