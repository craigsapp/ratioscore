---
title: "Pitch"
permalink: /pitch/index.html
layout: page
vim: ts=8:ft=html
---

Pitches are stored in `**ratio` spines (columns).  Each `**ratio`
spine will be converted into a track when outputting to a Standard
MIDI File, and only one note can be active in the spine/track at
any given time.  Pitches remain active in a spine until another one
is given further down in the spine, or if `0` is used to turn off
a pitch.  The duration of the pitch is controlled by a <a
href="/time">timeline</a> found in a separate spine.

Pitches can be represented in various units.  The basic representation
is a rational number, such as `3/2`, representing a just perfect
fifth above the reference pitch for the spine.  This can alternatively
be given as the floating-point number `1.5`, or as `701.955c` in
cent units. Mathematical expressions such as `(3/2)*(80/81)^(1/4)`
can be used to describe ratios, which in this case means a just
perfect fifth flattened by 1/4th of the syntonic comma.  Irrational
numbers for equal-temperament can use exponentiation, such as
`2^(7/12)`, which is equivalent to `700c` (700 cents) for an
equal-tempered perfect fifth).

Usually pitches are described as intervals compared to a reference
pitch, but they can also be given as specific frequencies, such as
`300z` for 300 Hz, or as a fractional MIDI note number, such as
`60.5m`, which represents an equal-tempered quarter-tone sharp above
middle C (using A-440Hz and equal-temperament as a an implicit
tuning reference for MIDI pitches).


<h2 data-sidebar="Reference"> Reference pitch </h2>

The reference pitch is specified in the form   `*ref:A4`, where
`A4` is the A above middle C.  A reference pitch is required for
pitches described as intervals (fractions, real numbers, including
mathematical expressions).  Frequency and MIDI number pitches do
not rely on a reference pitch.  

Below is an example of playing harmonics of three different 
references:


{% include ratioscore.html id="reference" %}
<script type="application/x-ratioscore" id="reference">
**dtime	**ratio	**ratio	**ratio
*MM240	*Iclars	*Iclars	*Iclars
*	*ref:C2	*ref:E3	*ref:G4
1	1	.	.
1	0	1	.
1	.	0	1
1	2	.	0
1	0	2	.
1	.	0	2
1	3	.	.
1	0	3	.
1	.	0	3
*-	*-	*-	*-
</script>

C4 (middle C) will be used as the reference pitch if none is given
in a ratio column.  The reference pitch can be tuned off of EQ/A440
by adding/subtracting a cent interval from the note name.  The cent
interval should should have the letter "c" following it:

{% include ratioscore.html id="cent-reference" tabsize="12" %}
<script type="application/x-ratioscore" id="cent-reference">
**dtime	**ratio	**ratio	**ratio
*MM240	*I#71	*I#70	*I#69
*	*ref:C2	*ref:C2-25c	*ref:C2+25.5c
1	1	.	.
1	.	1	.
1	0	0	1
1	2	.	0
1	.	2	.
1	0	0	2
1	3	.	0
1	.	3	.
1	0	0	3
*-	*-	*-	*-
</script>

Frequencies in Hertz can be used as a reference if the frequency has the letter "z" after it:

{% include ratioscore.html id="frequency-reference" tabsize="12" %}
<script type="application/x-ratioscore" id="frequency-reference">
**dtime	**ratio	**ratio	**ratio
*MM300	*Iclars	*Iclars	*Iclars
*	*ref:100z	*ref:200z	*ref:300z
1	1	.	.
1	0	1	.
1	.	0	1
1	2	.	0
1	0	2	.
1	.	0	2
1	3	.	0
1	0	3	.
1	.	0	3
*-	*-	*-	*-
</script>


The reference pitch may also change after the start of the score:

{% include ratioscore.html id="changing-reference" tabsize="12" %}
<script type="application/x-ratioscore" id="changing-reference">
**dtime	**ratio	**ratio	**ratio
*	*Iclars	*Iclars	*Iclars
*	*ref:100z	*ref:200z	*ref:300z
1	1	.	.
1	0	1	.
1	.	0	1
*	*ref:C2	*ref:C2-50c	*ref:C2+155.5c
1	2	.	0
1	0	2	.
1	.	0	2
*	*ref:C2	*ref:E3	*ref:G4
1	3	.	0
1	0	3	.
1	.	0	3
*-	*-	*-	*-
</script>




<h2> Harmonics </h2>

As illustrated in the above example, integer values are harmonics,
with `1` being the fundamental of the reference pitch, `2` being
an octave higher, and so on.  Rests are indicated by `0`.


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


<h2> Fractions </h2>

To get intervals between harmonics, rational numbers can be used,
such as `3/2` for a perfect fifth.  In the following example, `5/1`
is the 5th harmonic of the reference pitch (two octaves and a major
third), `5/2` is an octave lower (major tenth), `5/3` is a major
6th above the reference, `5/4` is a major third, and `5/5` is the
reference pitch. Also: `5/10` is an octave lower than the reference,
`5/8` is down a minor 6th, and `5/6` is down a minor third.


{% include ratioscore.html id="daipiyench" %}
<script type="application/x-ratioscore" id="daipiyench">
!!!OTL: Daipiyench
!!!COM: Sapp, Craig Stuart
!!!ODT: 2021/04/15
**dtime	**ratio	**ratio	**ratio
=0	=0	=0	=0
*MM325	*I#71	*I#71	*I#15
*	*ref:C4	*ref:C4	*ref:C2
*	*vel:55	*vel:55	*vel:50
=1	=1	=1	=1
1	.	.	5/5V
1	.	.	5/2
1	5/1v	.	.
1	.	5/5	.
1	5/2	.	5/1
1	.	5/2	.
1	5/3	.	.
1	.	.	5/4
1	5/4	.	.
1	.	5/1v	.
1	.	.	.
1	.	.	.
1	.	.	.
1	.	5/3	.
1	.	.	.
=2	=2	=2	=2
1	.	.	.
1	.	5/2	.
1	.	5/5	5/4
1	.	.	.
1	.	.	.
1	5/1v	.	5/3V
1	.	.	.
1	.	5/3	5/2
1	5/5	.	5/2
1	.	5/1v	.
1	.	.	.
1	.	.	5/5
1	5/2	.	.
1	.	5/1v	5/3
1	.	.	.
1	5/1v	.	5/3
1	.	.	.
1	5/4	.	.
1	.	5/1v	.
1	.	.	5/1
=3	=3	=3	=3
1	.	5/3	5/3V
1	5/1v	.	.
1	.	.	.
1	5/5	5/1v	5/3
1	.	5/2	.
1	5/3	.	5/8V
1	5/2	.	.
1	.	5/1v	5/2
1	.	.	.
1	.	5/4	5/4
=4	=4	=4	=4
1	.	.	.
1	5/4	.	.
1	.	.	5/1
1	5/5	5/5	5/5
1	.	5/3	5/2
=5	=5	=5	=5
1	5/5	.	5/2V
1	.	5/1v	.
1	.	.	.
1	.	.	5/5
1	5/2	.	.
1	.	5/4	5/3V
1	.	.	.
=6	=6	=6	=6
3	5/6	5/8	5/10
==	==	==	==
*-	*-	*-	*-
!!!filter: myank -m 0,1*2,3,4,2,3,1,2,3,2,1,4*2,5,4,3*2,2,1,2,3,4,5,4,5,6
</script>

<ul>
<li> See the <a href="/intervals">interval dictionary</a> for a list of various named ratios.</li>
<li> See the <a href="/grid">interval grid</a> page for uses of interval fractions.</a>
</ul>

<h2 data-sidebar="Floating-point"> Floating-point numbers </h2>

Ratios can be simplified into numbers containing fractional values after
a decimal point.


{% include ratioscore.html id="float" %}
<script type="application/x-ratioscore" id="float">
**dtime	**ratio	**ratio
*MM120	*Iclars	*Ivibra
*	*ref:C4	*ref:C4
1	1	.
1	0	1.0
1	9/8	0
1	0	1.125
1	5/4	0
1	0	1.25
1	4/3	0
1	0	1.333333
1	3/2	0
1	0	1.5
1	5/3	.
1	0	1.666667
1	15/8	0
1	0	1.875
1	2	0
2	0	2.0
*-	*-	*-
</script>


<h2> Exponents </h2>

Here is an example of exponent notation to generate 12-TET:

{% include ratioscore.html id="tet12" %}
<script type="application/x-ratioscore" id="tet12">
**dtime	**ratio
*	*Iclars
*MM240	*ref:F#3
1	2^(0/12)
1	2^(1/12)
1	2^(2/12)
1	2^(3/12)
1	2^(4/12)
1	2^(5/12)
1	2^(6/12)
1	2^(7/12)
1	2^(8/12)
1	2^(9/12)
1	2^(10/12)
1	2^(11/12)
1	2^(12/12)
*-	*-
</script>

<ul>
<li> See the <a href="/equal-temperament">Equal-temperament calculator</a> page.</li>
</ul>

<h2 data-sidebar="Expressions"> Mathematical expressions </h2>

When describing pitches as integers fractions and exponents, basic
mathematical operations can be used to express the ratio in a
factored form for clarity:


{% include ratioscore.html id="expression-example" %}
<script type="application/x-ratioscore" id="expression-example">
**dtime	**ratio
*	*Iclars
*	*ref:F#3
1	9/8
1	3*3/2*2*2
1	3^2/2^3
!! equal-tempered approximation to 9/8:
1	2^(2/12)
!! The colon is equivalent to a slash:
1	9:8
1	3*3:2*2*2
1	3^2:2^3
!! Spaces are ignored and can be used for alignment within a column:
1	9   : 8
1	3*3 : 2*2*2
1	3^2 : 2^3
!! Negative exponents:
1	2^-3 * 3^2
*-	*-
</script>

Note that multiplication has priority over division, so `3*3/2*2`
will be treated as `(3*3)/(2*2)` rather than `((3*3)/2)*2`.  Also note
that exponentiation has priority over multiplication.  Parentheses can be
used to control the operator priority, but the current parser is not
very advanced, so avoid complicated expressions.


<h2> Cents </h2>

Cents can be used instead of or in addition to fractions.  A
floating-point number followed by the letter `c` will be interpreted
as cents, and cents will be above (or below) the reference pitch.

Here is an example of playing an Equal-tempered C major scale at
the same time as C major in Just intonation (listen to the beating
when the two notes are less in tune):

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

Here is an example of a quarter-tone chromatic scale using cent intervals
relative to the reference pitch:

{% include ratioscore.html id="quarter-tone-cents" %}
<script type="application/x-ratioscore" id="quarter-tone-cents">
**dtime	**ratio
*MM180	*Iclars
*	*ref:C4
1	0c
1	50c
1	100c
1	150c
1	200c
1	250c
1	300c
1	350c
1	400c
1	450c
1	500c
1	550c
1	600c
1	650c
1	700c
1	750c
1	800c
1	850c
1	900c
1	950c
1	1000c
1	1050c
1	1100c
1	1150c
2	1200c
*-	*-
</script>


<h2 data-sidebar="MIDI"> MIDI key number </h2>

MIDI key numbers can be used in `**ratio` spines by following the key
number by the letter `m`.  A reference pitch is not needed if 
key numbers are used, since MIDI note 69.0 is assigned to the 
frequency 440 Hz and other integer values for MIDI keys are
assumed to be in equal temperament.

{% include ratioscore.html id="midikey" %}
<script type="application/x-ratioscore" id="midikey">
**dtime	**ratio	**ratio
*	*Iclars	*Iorgan
*MM180	*	*ref:261.63z
1	60m	.
1	0	0c
1	62m	0
1	0	200c
1	64m	0
1	0	400c
1	65m	0
1	0	500c
1	67m	0
1	0	700c
1	69m	0
1	0	900c
1	71m	0
1	0	1100c
2	72.5m	0
*-	*-	*-
</script>


Here is an example of quarter-tones using fractional MIDI key numbers:

{% include ratioscore.html id="quarter-tone" %}
<script type="application/x-ratioscore" id="quarter-tone">
**dtime	**ratio
*MM180	*Iclars
1	60.0m
1	60.5m
1	61.0m
1	61.5m
1	62.0m
1	62.5m
1	63.0m
1	63.5m
1	64.0m
1	64.5m
1	65.0m
1	65.5m
1	66.0m
1	66.5m
2	67.0m
*-	*-
</script>


<h2> Frequency </h2>

Specific frequencies can be used by appending a floating-point
number with the letter `z` (for "Hz"). If only frequencies are given
in a `**ratio` column, then the reference pitch is not necessary. 
Here is a C major scale in equal temperament using frequencies and
cents for comparison:

{% include ratioscore.html id="freq" %}
<script type="application/x-ratioscore" id="freq">
**dtime	**ratio	**ratio
*	*Iclars	*Iorgan
*MM180	*	*ref:261.63z
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


<h2> Symbols </h2>

See the <a href="/symbols">Symbols</a> page for a description of
giving arbitrary names to pitches.




