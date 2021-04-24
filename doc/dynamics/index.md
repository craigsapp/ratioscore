---
title: "Dynamics"
permalink: /dynamics/index.html
layout: page
vim: ts=8:ft=html
---


<h2 data-sidebar="Inline"> Inline attack velocity </h2>

The default attack velocity for notes is MIDI value 64.  This can
be changed by adding `*vel:#`, where `#` is an integer between 1
and 127.  Here is an example of starting the attack velocities at
30 and then changing to 100 to make the notes louder:

{% include ratioscore.html id="vel" %}
<script type="application/x-ratioscore" id="vel">
**dtime	**ratio
*	*Ivioln
*	*ref:C4
*	*vel:30
1	1
1	9/8
1	5/4
1	4/3
1	3/2
*	*vel:100
1	5/3
1	15/8
1	2
1	15/8
1	2
*-	*-
</script>

Attack velocities can be locally modified by adding one or more `v` or `V` to 
decrease or increase the attack velocity.  By default `v` will decrease
the attack velocity by 10, and `V` will increase the velocity by 10.
In the following example, the attack velocities start at 10 and
increase by 10 to 100 at the last note.


{% include ratioscore.html id="vstep" %}
<script type="application/x-ratioscore" id="vstep">
**dtime	**ratio
*	*Ivioln
*	*ref:C4
*	*vel:50
1	vvvv1
1	vvv9/8
1	vv5/4
1	v4/3
1	3/2
1	V5/3
1	VV15/8
1	VVV2
1	VVVV15/8
1	VVVVV2
*-	*-
</script>

The volumne increment of `v` and `V` can be set with `*vstep:#`.  In the following
example each `v`/`V` adjusts the base velocity by 5 units instead of 10:

{% include ratioscore.html id="vstep2" %}
<script type="application/x-ratioscore" id="vstep2">
**dtime	**ratio
*	*Ivioln
*	*ref:C4
*	*vstep:5
1	vvvv1
1	vvv9/8
1	vv5/4
1	v4/3
1	3/2
1	V5/3
1	VV15/8
1	VVV2
1	VVVV15/8
1	VVVVV2
*-	*-
</script>



<h2 data-sidebar="Parallel"> Attack velocity tandem spine </h2>

For numeric control of attack velocity, a separate column entitled `**vel` can
be given to the right of the `**ratio` spine that it applies to.  If a `**vel`
spine is present after a `**ratio` spine, the inline velocity system is deactivated
in favor of the `**vel` spine method.

{% include ratioscore.html id="vel-spine" %}
<script type="application/x-ratioscore" id="vel-spine">
**dtime	**ratio	**vel
*MM180	*Ivioln	*
*	*ref:C4	*
1	1	10
1	9/8	20
1	5/4	30
1	4/3	40
1	3/2	50
1	5/3	60
1	15/8	70
1	2	80
1	15/8	90
1	2	100
*-	*-	*-
</script>

If there are null tokens (`.`) in the `**vel` spine, then the previous explicit
value will be used (or the default of `64` if there is no previous value.

{% include ratioscore.html id="vel-spine2" %}
<script type="application/x-ratioscore" id="vel-spine2">
**dtime	**ratio	**vel
*MM180	*Ivioln	*
*	*ref:C4	*
1	1	110
1	9/8	.
1	5/4	50
1	4/3	.
1	3/2	110
1	5/3	.
1	15/8	50
1	2	.
1	15/8	110
1	2	.
*-	*-	*-
</script>




