---
title: "Glissandos"
permalink: /glissandos/index.html
layout: page
vim: ts=8:ft=html
---

Glissandos are created by adding an `H` to the starting note of the
glissando, and an `h` on the ending note.  The maximum gliss interval
is one octave above/below the starting note of the glissando.  Glissandos
larger than that will not be rendered correctly due to General MIDI limitations
for pitch-bend depth.

{% include ratioscore.html id="glissando" %}
<script type="application/x-ratioscore" id="glissando">
**dtime	**ratio
*	*Iclars
*	*ref:C4
2	3/2H
1	4/3
2	3/2h
*-	*-
</script>


Adding an underscore to a note will prevent a glissando
from reattacking at that note.

{% include ratioscore.html id="sustain" %}
<script type="application/x-ratioscore" id="sustain">
**dtime	**ratio
*	*Iclars
*	*ref:C4
2	3/2H
1	_4/3
2	_3/2h
*-	*-
</script>

The underscore character can be placed before or after the ratio, and it can
also be used to indicate tied notes (useful for when representating standard
music notation more closely):

{% include ratioscore.html id="tied" %}
<script type="application/x-ratioscore" id="tied">
**dtime	**ratio	**ratio
*MM50	*Iclars	*Ikoto
*	*ref:C4	*ref:C4
*	*	*grate:10
1	5/4	11/5
0.2	5/4_	11/5H
0.2	.	16/7_
0.6	.	11/6_h
0.25	5/4_	11/5H
0.75	.	13/7_h
1	5/4_	11/5
*-	*-	*-
</script>


<h2 data-sidebar="Pitchbend"> Pitchbend update rate </h2>

When doing glissandos quickly on large intervals, the individual
pitchbend adjustments may become audible.  By default, pitchbend
updates for glissandos occur once every 50 milliseconds (and faster
or slower based on the tempo adjustments in the timeline).

The pitchbend update rate can be set by adding `*grate:#` (meaning
<i>glissando rate</i>), where `#` is a positive integer indicating
the update rate in units of milliseconds (but will be modified based
on tempo adjustments of the timeline).

In the following example, notice the graininess of the first
glissando.  This is fixed for the second one, where the update rate
is lowered from 50 ms to 10 ms.  For the third glissando, the update
rate is changed to 250 ms, which will update the pitchbend values
for the glissando once every quarter second.  Then the rate is set
to 1/5 and 1/10 of a second respectivly for the last two glissandos.


{% include ratioscore.html id="grate" %}
<script type="application/x-ratioscore" id="grate">
**dtime	**ratio
*	*Iclars
*	*ref:C4
1	1H
1	_2h
1	0
*	*grate:10
1	1H
1	_2h
1	0
*	*grate:250
1	1H
1	_2h
1	0
*	*grate:200
1	1H
1	_2h
1	0
*	*grate:100
1	1H
1	_2h
*-	*-
</script>


<h2 data-sidebar="Examples"> Other examples </h2>

Here is an example of starting at a 5/4 major third, and then glissandoing
to a 400c major third and back again, with and without the reference pitch:

{% include ratioscore.html id="justeq3" %}
<script type="application/x-ratioscore" id="justeq3">
**dtime	**ratio	**ratio
*	*I#71	*I#71
*	*ref:C5	*refC5
*	*vel:60	*vel:50
1	5/4H	0
1	_5/4	.
1	_400c	.
1	_400c	.
1	_5/4	.
1	_5/4h	.
1	5/4H	1
1	_5/4	.
1	_400c	.
1	_400c	.
1	_5/4	.
1	_5/4h	.
*-	*-	*-
</script>



Here is an example of glissandoing up and down a pythagorean comma from a note:

{% include ratioscore.html id="pgliss" %}
<script type="application/x-ratioscore" id="pgliss">
**dtime	**ratio	**ratio
*	*I#71	*I#71
*	*refF3	*ref:F3
*	*vel:50	*vel:60
1	0	3/2H
1	.	_3/2
1	.	_(3/2)*(3^12/2^19)
1	.	_(3/2)*(3^12/2^19)
1	.	_3/2
1	.	_3/2
1	.	_(3/2)/(3^12/2^19)
1	.	_(3/2)/(3^12/2^19)
1	.	_3/2h
1	3/2	3/2H
1	.	_3/2
1	.	_(3/2)*(3^12/2^19)
1	.	_(3/2)*(3^12/2^19)
1	.	_3/2
1	.	_3/2
1	.	_(3/2)/(3^12/2^19)
1	.	_(3/2)/(3^12/2^19)
1	.	_3/2
1	.	_3/2h
*-	*-	*-
</script>



Going from a unison to a first-inversion major triad and back again:

{% include ratioscore.html id="triad" %}
<script type="application/x-ratioscore" id="triad">
**dtime	**ratio	**ratio	**ratio
*	*I#71	*I#71	*I#71
*	*ref:C4	*ref:C4	*ref:C4
9	1H	1H	1H
1	3/2_	5/4_	2_
8	3/2_	5/4_	2_
1	1h_	1h_	1h_
*-	*-	*-	*-
</script>

Simulating vibrato:

{% include ratioscore.html id="vibrato" %}
<script type="application/x-ratioscore" id="vibrato">
**dtime	**ratio
*MM500	*I#71
*	*ref:C2
1	9H
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10_
1	9_
1	10h_
*-	*-

</script>



