---
title: "Ratioscore: glissandos"
permalink: /doc/glissandos/index.html
layout: default
vim: ts=8:ft=html
---

Glissandos are created by adding an `H` to the starting note of the
glissando, and an `h` on the ending note.  The maximum gliss interval
is one octave above/below the starting note of the glissando.  Glissandos
larger than that will not be rendered correctly.

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


<h2> Pitchbend update rate for glissandos </h2>

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
1	0
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
1	0
*-	*-
</script>




