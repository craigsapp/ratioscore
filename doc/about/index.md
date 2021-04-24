---
title: "About"
permalink: /about/index.html
layout: page
vim: ts=8:ft=html
---

Ratioscore was designed as a composition prototyping system for
<i>The Answers</i> by Julie Zhu.  Here is a performance of the final
work by the <a target="_blank" href="https://jackquartet.com">JACK
Quartet</a>:

<iframe width="800" height="600"
src="https://www.youtube.com/embed/Dx5l-9MUZ1o">
</iframe>


Below is the prototype for the final score (first minute of the
piece), before dynamics, glissandos and articulations were added.
A clarinet sound was used since it has less vibratio than the string
instruments in the MIDI player used to create the synthetic
performance.

{% include ratioscore.html id="quick-answers" height="600px" %}
<script type="application/x-ratioscore" id="quick-answers">
!!!COM: Zhu, Julie
!!!OTL: The Answers (prototype)
!!!ODT: 2020/12
**time	**ratio	**ratio	**ratio	**ratio
*	*Iclars	*Iclars	*Iclars	*Iclars
*	*ref:C2	*ref:C2	*ref:C2	*ref:C2
4.231	.	.	.	27/8
6.182	2	.	.	.
7.441	.	.	.	3
9.337	.	3	.	.
9.502	.	.	636	.
9.521	.	.	7/2	.
11.522	.	.	.	6
13.571	.	.	7	.
13.958	.	.	.	9
14.814	.	.	.	6
15.358	.	.	12	.
15.457	1	.	.	.
15.567	.	.	.	27/2
16.487	.	.	63/4	.
17.037	.	.	.	9
17.459	.	.	63/8	.
17.776	.	.	.	27/2
18.162	.	.	27/2	.
18.476	.	.	18	.
19.854	.	.	.	16
20.038	.	2	.	.
20.223	.	.	21	.
20.594	.	.	.	12
20.837	.	.	27/2	.
22.064	.	.	.	18
22.103	.	.	27	.
22.11	.	.	9	.
22.816	.	.	.	27/4
23.334	.	.	14	.
23.673	.	.	.	12
24.066	3	.	.	.
25.108	.	.	21/2	.
25.499	9/4	.	.	.
26.108	.	.	.	8
28.582	.	.	6	.
28.589	.	.	6	.
30.19	.	.	.	9/2
32.294	.	4	.	.
33.399	.	.	.	4
34.39	4	.	.	.
39.386	.	4	.	.
40.957	.	6	.	.
41.006	6	.	.	.
42.579	.	.	.	3
44.052	4	.	.	.
46.319	.	.	7/2	.
46.863	.	9	.	.
48.399	6	.	.	.
49.075	.	.	.	6
51.153	.	7	.	.
52.73	.	.	.	9
52.766	.	.	7	.
54.239	.	9	.	.
54.303	.	.	.	27/2
54.608	.	.	12	.
55.508	.	.	63/4	.
55.961	7	.	.	.
57.06	.	.	.	27/2
57.609	.	.	.	9
57.746	.	.	18	.
58.098	.	.	27/2	.
58.979	.	.	63/8	.
59.194	.	.	.	16
59.495	.	.	21	.
*-	*-	*-	*-	*-
</script>

The Ratioscore was first converted into MIDI and then loaded into
Sibelius to quantize the note durations into musical rhythms.


<h2> Conference </h2>

Ratioscores will be presented at <a href="/tenor2021">TENOR 2021</a>.


<h2> Software </h2>

Ratioscores on this website are converted into MIDI files with <a
target="_blank" href="https://github.com/craigsapp/ratioscore">this
software</a>.  After converting to MIDI, MP3s are generated for this
website using timidity.

<h2> Website </h2>

This website is hosted on Github and uses Jekyll for page templating.
<a target="_blank"
href="https://github.com/craigsapp/ratioscore/tree/gh-pages">Here</a> are
the source files for the website.

The Ratioscore to MIDI/MP3 conversion occurs on the server side
using this <a target="_blank"
href="https://github.com/craigsapp/ratioscore/blob/gh-pages/_includes/cgi/ratioscore.pl">CGI
script</a>.

In the CGI script, the command `ratioscore -r` converts a Ratioscore
into a MIDI file, with the `-r` option outputting the MIDI file to standard 
output (so that the CGI script does not need to store any intermediate files).

To convert to MIDI, the command is: `ratioscore -r -x630 | timidity - -m60000 --preserve-silence -Ow -o - | lame - -b64 -`.  This command
first converts a Ratioscore to MID, then converts the MIDI into a
WAVE audio file, then the WAVE file is converted into an MP3. Options:

* `ratioscore -r` print MIDI file to standard output
* `timidity -m60000` =
* `timidity --preserve-silence` = keep starting silence in the MIDI file.
* `timidity -Ow` = output as WAVE file.
* `timidity -o -` = output WAVE file to standard output.
* `lame -b64` =







