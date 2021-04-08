---
title: "Ratioscore: representing pitch"
permalink: /doc/pitch/index.html
layout: default
vim: ts=8:ft=html
---

Notes are created in a Ratioscore by adding fractions in `**ratio`
spines (columns) to a <a href="/doc/timeline">timeline</a>.  The
fractions are used to calculate the pitch of the note by multiplying
the frequency of the reference pitch.  For example of the reference
pitch is A4 (=440Hz), then the fraction `3/2` will generate the
frequency 660 Hz.


<h2> Reference pitch </h2>

The reference pitch is specified in the form   `*ref:A4`, where
`A4` is the A above middle C.  Here is an example:


{% include ratioscore.html id="reference-example" %}
<script type="application/x-ratioscore" id="reference-example">
**dtime	**ratio	**ratio	**ratio
*	*Iclars	*Iclars	*Iclars
*	*ref:C2	*ref:E3	*ref:G4
0.25	1	.	.
0.25	.	1	.
0.25	.	.	1
0.25	2	.	.
0.25	.	2	.
0.25	.	.	2
0.25	3	.	.
0.25	.	3	.
0.25	.	.	3
0.25	0	.	.
0.25	.	0	.
0.25	.	.	0
*-	*-	*-	*-
</script>

C4 (middle C) will be used as the reference pitch if none is given
for any ratio column.


<h2> Harmonics </h2>

As illustrated in the above example, integer values are harmonics, with `1` being the 
fundamental of the reference pitch, `2` being an octave higher, and so on.  Rests are
indicated by `0`.


{% include ratioscore.html id="harmonics-example" %}
<script type="application/x-ratioscore" id="harmonics-example">
**dtime	**ratio
*	*Iclars
*MM400	*ref:C2
4	1
3	2
2	3
1	4
1	5
1	6
1	7
1	8
1	9
1	10
1	11
1	12
1	13
1	14
1	15
1	16
1	17
2	18
3	19
4	20
*-	*-
</script>


<h2> Ratios </h2>

To get pitches between harmonics, ratios can be used:



{% include ratioscore.html id="ratios-example" %}
<script type="application/x-ratioscore" id="ratios-example">
**dtime	**ratio	**ratio	**ratio	**ratio
*	*Iorgan	*Iclars	*Ikoto	*Iflt
*MM300	*ref:C2	*ref:C3	*ref:C4	*ref:C5
1	1	2/2	3/3	5/5
1	2	3/2	4/3	6/5
1	3	4/2	5/3	7/5
1	4	5/2	6/3	8/5
1	5	6/2	7/3	9/5
1	6	7/2	8/3	10/5
1	7	8/2	9/3	11/5
1	8	9/2	10/3	12/5
1	9	10/2	11/3	13/5
1	10	11/2	12/3	14/5
1	11	12/2	13/3	15/5
1	12	13/2	14/3	16/5
1	13	14/2	15/3	17/5
1	14	15/2	16/3	18/5
1	15	16/2	17/3	19/5
1	16	17/2	18/3	20/5
1	17	18/2	19/3	21/5
1	18	19/2	20/3	22/5
1	19	20/2	21/3	23/5
4	20	21/2	22/3	24/5
*-	*-	*-	*-	*-
</script>

See the <a href="/doc/intervals">interval dictionary</a> for a list of
various named ratios.


<h2> Cents </h2>

Cents can be used instead of or in addition to fractions.  A floating-point
number followed by the letter `c` will be interpreted as cents, and
cents will be above (or below) the reference pitch.

Here is an example of playing an Equal-tempered C major scale at the same
time as C major in Just intonation (listen to the beating when the
two notes are less in tune):

{% include ratioscore.html id="cents-example" %}
<script type="application/x-ratioscore" id="cents-example">
**dtime	**ratio	**ratio
*	*Iclars	*Iclars
*	*ref:C4	*ref:C4
1	0c	1
1	200c	9/8
1	400c	5/4
1	500c	4/3
1	700c	3/2
1	900c	5/3
1	1100c	15/8
2	1200c	2
*-	*-	*-
</script>


<h2> Frequency </h2>

Specific frequencies can be specified by appending a floating point
number with the letter `z` (for "Hz"). If only frequencies are given
for pitches, then the reference pitch is not necessary. 
Here is a C major scale in equal temperament using frequencies and
cents for comparison:

{% include ratioscore.html id="freq-example" %}
<script type="application/x-ratioscore" id="freq-example">
**dtime	**ratio	**ratio
*	*Iclars	*Iorgan
*MM180	*	*ref:C4
1	261.63z	.
1	0	0c
1	293.66z	0
1	0	200c
1	329.63z	0
1	0	400c
1	349.23z	0
1	0	500c
1	392.00z	0
1	0	700c
1	440.00z	0
1	0	900c
1	493.88z	0
1	0	1100c
2	523.25z	0
*-	*-	*-
</script>


