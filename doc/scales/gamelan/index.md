---
title: "Ratioscore: Gamelan"
permalink: /doc/scales/gamelan/index.html
layout: default
vim: ts=8:ft=html
---

{% include ratioscore.html id="frequencies" %}
<script type="application/x-ratioscore" id="frequencies">
!! Measured frequencies of saron barung and Sarun demung from
!! Arizona State University Javanese Gamelan ensemble.
**dtime	**ratio
*	*I#14
!! Saron Barung (Slendro)
1	524.5z
1	600.3z
1	688z
1	803z
1	918.6z
1	1055.5z
1	0
!! Saron Demung (Slendro)
1	261.5z
1	301.5z
1	343.4z
1	399z
1	456.5z
1	524.5z
*-	*-
!! reference: https://thewinnower.com/papers/2861-an-analysis-of-a-gamelan-slendro-tuning
</script>

{% include ratioscore.html id="beating" %}
<script type="application/x-ratioscore" id="beating">
!! Beating comparison of the two instruments
**dtime	**ratio	**ratio	**difference
*MM30	*Iclars	*Iclars	*
!	!barung	!demung	!
1	524.5z	261.5z	1.5z
1	600.3z	301.5z	-2.7z
1	688.0z	343.4z	1.2z
1	803.0z	399.0z	5z
1	918.6z	456.5z	5.6z
1	1055.5z	524.5z	6.0z
*-	*-	*-	*-
!! Difference: comparison of first harmonic of barung to second harmonic of demung
</script>

{% include ratioscore.html id="just-slendro" tabsize="12" %}
<script type="application/x-ratioscore" id="just-slendro">
!! Derived just slendro scale
**dtime	**ratio	**ratio	**difference
*	*I#14	*I#14	*
*	*ref:261.5z	*	*
1	1/1	.	.
1	8/7	.	.
1	21/16	.	.
1	32/21	.	.
1	7/4	.	.
1	2/1	.	.
1	0	.	.
!! Measured frequencies:
1	.	261.5z	.
1	.	301.5z	.
1	.	343.4z	.
1	.	399z	.
1	.	456.5z	.
1	.	524.5z	.
1	0	.	.
!! Simultaneous comparison
1	1/1	261.5z	0c
1	8/7	301.5z	-4.59c
1	21/16	343.4z	-0.28c
1	32/21	399z	-0.68c
1	7/4	456.5z	+1.28c
1	2/1	524.5z	-1.49c
*-	*-	*-	*-
</script>



