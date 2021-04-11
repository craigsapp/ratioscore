---
title: "Ratioscore: filtering"
permalink: /doc/filters/index.html
layout: default
vim: ts=8:ft=html
---

Basic manipulations of Ratioscores can be embedded as filtering commands
within the score.  Filters are given on lines starting with `!!!filter:`
and then the actual filter.


<h2> Selecting/rearranging spines </h2>

The `extract` filter can be used to pull out specific spines (columns) of data, or
rearrange them before converting to MIDI/MP3s.  Here is an example where
only the first or second voice in the score are selected for performance:

{% include ratioscore.html id="full-example" %}
<script type="application/x-ratioscore" id="full-example">
**dtime	**ratio	**ratio
*MM300	*I#14	*I#24
*	*ref:C3	*ref:C2
1	1	0
1	2	1
1	3	2
1	4	3
1	5	4
1	6	5
1	7	6
1	8	7
1	9	8
1	10	9
1	11	10
1	12	11
1	13	12
1	14	13
1	15	14
1	16	15
1	17	16
*-	*-	*-
</script>

The line `!!!filter: extract -s 1,2` keeps the first two spines and removes
the third one when converting to MIDI/MP3:

{% include ratioscore.html id="first-part-example" %}
<script type="application/x-ratioscore" id="first-part-example">
!!!filter: extract -s 1,2
**dtime	**ratio	**ratio
*MM300	*I#14	*I#24
*	*ref:C3	*ref:C2
1	1	0
1	2	1
1	3	2
1	4	3
1	5	4
1	6	5
1	7	6
1	8	7
1	9	8
1	10	9
1	11	10
1	12	11
1	13	12
1	14	13
1	15	14
1	16	15
1	17	16
*-	*-	*-
</script>


And the line `!!!filter: extract -s 1,3` keeps the first and last spines and removes
the middle one:

{% include ratioscore.html id="second-part-example" %}
<script type="application/x-ratioscore" id="second-part-example">
!!!filter: extract -s 1,3
**dtime	**ratio	**ratio
*MM300	*I#14	*I#24
*	*ref:C3	*ref:C2
1	1	0
1	2	1
1	3	2
1	4	3
1	5	4
1	6	5
1	7	6
1	8	7
1	9	8
1	10	9
1	11	10
1	12	11
1	13	12
1	14	13
1	15	14
1	16	15
1	17	16
*-	*-	*-
</script>


It is possible to include multiple alternate timelines in a score, and
then user the `extract` filter to choose one of them.  The following 
example contains two timelines, with the first one chosen by default:

{% include ratioscore.html id="first-timeline-example" %}
<script type="application/x-ratioscore" id="first-timeline-example">
**dtime	**dtime	**ratio
*MM100	*MM300	*I#24
*	*	*ref:C2
1	1	0
1	1	1
1	2	2
1	3	3
1	2	4
1	1	5
1	2	6
1	3	7
1	2	8
1	1	9
1	2	10
1	3	11
1	2	12
1	1	13
1	2	14
1	3	15
1	4	16
*-	*-	*-
</script>


Removing the first spine will cause the second spine to be used as the timeline:


{% include ratioscore.html id="second-timeline-example" %}
<script type="application/x-ratioscore" id="second-timeline-example">
!!!filter: extract -s 2-$
**dtime	**dtime	**ratio
*MM100	*MM300	*I#24
*	*	*ref:C2
1	1	0
1	1	1
1	2	2
1	3	3
1	2	4
1	1	5
1	2	6
1	3	7
1	2	8
1	1	9
1	2	10
1	3	11
1	2	12
1	1	13
1	2	14
1	3	15
1	4	16
*-	*-	*-
</script>



<h2> Rearranging measures </h2>

The `myank` filter can be used to mix an match measures.


{% include ratioscore.html id="myank-example" %}
<script type="application/x-ratioscore" id="myank-example">
**recip	**ratio
=0	=0
*MM200	*ref:C3
=1	=1
8	11
8	12
8	11
8	13
8	11
=2	=2
8	10
8	11
8	12
8	11
=3	=3
8	9
8	8
8	9
=4	=4
8	7
8	6
=	=
*-	*-
</script>



{% include ratioscore.html id="myank-expand-example" %}
<script type="application/x-ratioscore" id="myank-expand-example">
!!!filter: myank -m 0,3,3,2,1,2,2,3,2,1,3,2,4,2,1,4,2,2,3,1,4
**recip	**ratio
=0	=0
*MM200	*ref:C3
=1	=1
8	11
8	12
8	11
8	13
8	11
=2	=2
8	10
8	11
8	12
8	11
=3	=3
8	9
8	8
8	9
=4	=4
8	7
8	6
=	=
*-	*-
</script>

