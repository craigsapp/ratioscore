---
title: "Time"
permalink: /time/index.html
layout: page
vim: ts=8:ft=html
---

There are multiple ways to indicate time in a Ratioscore.   The
left-most timing spine (column) will be used to control time in the
score, with possibilities being:

| Spine&nbsp;heading&nbsp;&nbsp;&nbsp;&nbsp; | Meaning          |
| -------------- | -------------------------------------------- |
| `**time`       | Absoute time (nominally) in seconds.         |
| `**dtime`      | Delta time in seconds.                       |
| `**ms`         | Absolute time in milliseconds seconds.       |
| `**dms`        | Delta time in milliseconds seconds.          |
| `**recip`      | Musical time in divisions of a whole note.   |
| *none*         | No timeline: treat each data line as 1 second long.   |



<h2> **time </h2>

A `**time` spine gives the time in seconds to start notes on each
line.  Time values need to be sorted from low to high in the score.
Here is an example of playing a new note once every quarter second,
and then once every half second, then once every second:

{% include ratioscore.html id="time-example" %}
<script type="application/x-ratioscore" id="time-example">
**time	**ratio	**ratio	**ratio
*	*Ikoto	*Ikoto	*Ikoto
*	*ref:C3	*ref:C4	*ref:C5
0	1	.	.
0.25	.	1	.
0.5	.	.	1
0.75	2	.	.
1.25	.	2	.
1.75	.	.	2
2.25	3	.	.
3.25	.	3	.
4.25	.	.	3
5.25	0	.	.
6.25	.	0	.
7.25	.	.	0
*-	*-	*-	*-
</script>

If a note is still sounding by the end of the score, it will be
extended for one second before being turned off.



<h2> **dtime </h2>

The `**dtime` spine gives the time in seconds to wait until playint
the next line of the score.  Here is an example that produces the
same rhythms as the previous example using `**time`:

{% include ratioscore.html id="dtime-example" %}
<script type="application/x-ratioscore" id="dtime-example">
**dtime	**ratio	**ratio	**ratio
*	*Ikoto	*Ikoto	*Ikoto
*	*ref:C3	*ref:C4	*ref:C5
0.25	1	.	.
0.25	.	1	.
0.25	.	.	1
0.50	2	.	.
0.50	.	2	.
0.50	.	.	2
1.00	3	.	.
1.00	.	3	.
1.00	.	.	3
1.00	0	.	.
1.00	.	0	.
1.00	.	.	0
*-	*-	*-	*-
</script>



<h2> **ms </h2>

The `**ms` spine is similar to `**time`, but the units are milliseconds
(1000 millseconds equals one second).

{% include ratioscore.html id="ms-example" %}
<script type="application/x-ratioscore" id="ms-example">
**ms	**ratio	**ratio	**ratio
*	*Ikoto	*Ikoto	*Ikoto
*	*ref:C3	*ref:C4	*ref:C5
0	1	.	.
250	.	1	.
500	.	.	1
750	2	.	.
1250	.	2	.
1750	.	.	2
2250	3	.	.
3250	.	3	.
4250	.	.	3
5250	0	.	.
6250	.	0	.
7250	.	.	0
*-	*-	*-	*-
</script>



<h2> **dms </h2>

The `**dms` spine is similar to `**dtime`, but the units are delta
milliseconds.

{% include ratioscore.html id="dms-example" %}
<script type="application/x-ratioscore" id="dms-example">
**dms	**ratio	**ratio	**ratio
*	*Ikoto	*Ikoto	*Ikoto
*	*ref:C3	*ref:C4	*ref:C5
250	1	.	.
250	.	1	.
250	.	.	1
500	2	.	.
500	.	2	.
500	.	.	2
1000	3	.	.
1000	.	3	.
1000	.	.	3
1000	0	.	.
1000	.	0	.
1000	.	.	0
*-	*-	*-	*-
</script>


<h2> **recip </h2>

The `**recip` timeline describes time in terms of musical rhythms.
Numbers represent divisions of a whole note, such that `4` means a
quarter note, `8` a half note, `12` a triplet eight note and so on.
One or more augmentation dots can be added after the number, such
as `2.` for a dotted half note, or `20..` four a doubly-dotted
quintuplet sixteenth note.

{% include ratioscore.html id="recip-example" %}
<script type="application/x-ratioscore" id="recip-example">
**recip	**ratio	**ratio	**ratio
*	*Ikoto	*Ikoto	*Ikoto
*	*ref:C3	*ref:C4	*ref:C5
16	1	.	.
16	.	1	.
16	.	.	1
8	2	.	.
8	.	2	.
8	.	.	2
4	3	.	.
4	.	3	.
4	.	.	3
4	0	.	.
4	.	0	.
4	.	.	0
*-	*-	*-	*-
</script>

<h2 data-sidebar="Implicit"> Implicit time </h2>

If there is no timeline in the score, then an implicit `**dtime` is used, with each
data line in the score played for one second (plus any tempo changes).  Tempo changes
can be given in any `**ratio` or `**drum` spine.

{% include ratioscore.html id="implicit" %}
<script type="application/x-ratioscore" id="implicit">
**ratio	**ratio	**ratio
*Ikoto	*Ikoto	*Ikoto
*ref:C3	*ref:C4	*ref:C5
*MM240	*	*
1	.	.
.	1	.
.	.	1
2	.	.
.	2	.
.	.	2
*MM150	*	*
3	.	.
.	3	.
.	.	3
0	.	.
.	0	.
.	.	0
*-	*-	*-
</script>


<h2> Tempo </h2>

All time spines can be altered by tempo changes.  This will cause
time descriptions such as `**time`, `**dtime`, `**ms` and `**dms`
to no longer represent physical time.

Tempo changes are indicated by `*MM#`, where `#` is a floating-point
number of beats to perform in one minute (`MM` = "Maelzel's Metronome").
`*MM60` is the default tempo for a time spines, and is equal to one
beat per second.

{% include ratioscore.html id="tempo-example" %}
<script type="application/x-ratioscore" id="tempo-example">
**recip	**ratio	**ratio
*	*Iorgan	*Iclars
*	*ref:C3	*ref:C4
8	1	.
8	.	2/1
*MM68	*	*
8	3/2	.
8	.	4/3
*MM76	*	*
8	5/4	.
8	.	6/5
*MM82	*	*
8	7/6	.
8	.	8/7
*MM90	*	*
8	9/8	.
8	.	10/9
*MM98	*	*
8	11/10	.
8	.	12/11
*MM106	*	*
8	13/12	.
8	.	14/13
*MM114	*	*
8	15/14	.
8	.	16/15
*MM122	*	*
8	17/16	.
8	.	18/17
*MM130	*	*
8	19/18	.
8	.	20/19
*MM60	*	*
8	1	.
8	.	1
8	0	.
8	.	0
*-	*-	*-
</script>



<h2> Fractions </h2>

The `**time`, `**dtime`, `**ms`, and `**dms` timelines can use rational numbers in 
addition to floating point numbers.

{% include ratioscore.html id="fraction" %}
<script type="application/x-ratioscore" id="fraction">
**dtime	**ratio
*	*Iflt
*	*ref:A3
1/2	1
1/2	2
1/4	1
1/4	2
1/8	1
3/8	2
1/12	1
1/12	2
1/12	1
1/12	2
1/12	1
1/12	2
1	1
*-	*-
</script>
[Note: needs to be implemented]


For fractions that are larger than one, the integer part can be split from
the fractional part:

{% include ratioscore.html id="compound" %}
<script type="application/x-ratioscore" id="compound">
**time	**ratio
*	*Iflt
*	*ref:A3
0	1
1/2	2
1	1
1+1/4	2
1+1/2	1
1+5/8	2
1+6/8	1
2	2
2+1/12	1
2+2/12	2
2+3/12	1
2+4/12	2
2+5/12	1
*-	*-
</script>
[Note: needs to be implemented]


For `**recip` timelines, fractional values are reversed and a `%` character is used
instead of a slash.  For example, `4` and `4%1` both represent a quarter note, with the
denominator of the reciprocal fraction being 1 by default.  Triplet whole notes
are `3%2` (i.e., 3/2 = 1.5 triplet whole notes create a regular whole note).

{% include ratioscore.html id="recip-fraction" %}
<script type="application/x-ratioscore" id="recip-fraction">
**recip	**ratio
*	*Iclars
*MM120	*ref:C3
4	1
8	2
8	1
4	3
8	1
8	4
3%2	1
3%2	5
3%2	1
3	6
3	1
3	7
1	1
*-	*-
</script>

<h2> Barlines </h2>

[Move this to another documentaiton page about Humdrum file structure]

Barlines are indicated by placing an equals sign (`=`) in each column of the
score.  An optional measure number can follow the equals sign.  The divisions
of the score into measures does not have to be equal or metrical.

{% include ratioscore.html id="barlines-example" %}
<script type="application/x-ratioscore" id="barlines-example">
**dtime	**ratio
*	*Iflt
*	*ref:A3
=1	=1
1	1
2	3
1	2
=2	=2
0.5	3
0.5	2
1	7/2
2	2
=3	=3
2	8/5
1	3/2
1	1
=4	=4
3	11/10H
1	1_h
*-	*-
</script>



<h2 data-sidebar="Multiple"> Multiple timelines </h2>

Multiple timelines can be present in the Ratioscore, but only the leftmost one
will be used to perform the **ratio spines.


{% include ratioscore.html id="multiple" %}
<script type="application/x-ratioscore" id="multiple">
**recip	**recip	**ratio
*	*	*Iflt
*	*	*ref:A3
16	8	1
16	16	2
16	16	1
16	8	2
16	16	1
16	16	2
16	8	1
16	16	2
16	16	1
16	8	2
16	16	1
16	16	2
16	1	1
*-	*-	*-
</script>

In this case only the first `**dtime` spine will be used (constant
16th note rhythm).  To use the second timeline, add a filter line
to the score:

{% include ratioscore.html id="filter" %}
<script type="application/x-ratioscore" id="filter">
!!!filter: extract -s 2-$
**recip	**recip	**ratio
*	*	*Iflt
*	*	*ref:A3
16	8	1
16	16	2
16	16	1
16	8	2
16	16	1
16	16	2
16	8	1
16	16	2
16	16	1
16	8	2
16	16	1
16	16	2
16	1	1
*-	*-	*-
</script>

The filter line can be placed anywhere in the score (top, bottom,
middle).   The extract filter pulls out the spcified spines, which
are from the second spine to the end of the line in this case,
removing the first `**recip` spine.  This will perform the score
using a repeated 8-16-16 rhythm instead of the constant 16th notes.




