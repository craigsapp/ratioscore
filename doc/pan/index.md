---
title: "Ratioscore: panning"
permalink: /doc/pan/index.html
layout: default
vim: ts=8:ft=html
---

Each `**ratio` spine can be positioned in the stereo field with
panning instructions.  Stereo left is -1.0 and right is 1.0.

{% include ratioscore.html id="glissando" %}
<script type="application/x-ratioscore" id="glissando">
**dtime	**ratio	**ratio	**ratio	**ratio	**ratio
*	*Ifagot	*Iclars	*Icor	*I#24	*I#14
*	*ref:C2	*ref:C3	*ref:C3	*ref:C5	*ref:C3
*MM144	*pan:-1.0	*pan:-0.5	*pan:0	*pan:0.5	*pan:1.0
1	1	.	.	.	.
1	0	1	.	.	.
1	.	0	1	.	.
1	.	.	0	1	.
1	.	.	.	0	1
1	.	.	.	.	0
1	3/2	.	.	.	.
1	0	3/2	.	.	.
1	.	0	3/2	.	.
1	.	.	0	3/2	.
1	.	.	.	0	3/2
1	.	.	.	.	0
!! Reverse the panning direction from right to left:
*	*pan:1.0	*pan:0.5	*pan:0	*pan:-0.5	*pan:-1.0
1	(3/2)^2	.	.	.	.
1	0	(3/2)^2	.	.	.
1	.	0	(3/2)^2	.	.
1	.	.	0	(3/2)^2	.
1	.	.	.	0	(3/2)^2
*-	*-	*-	*-	*-	*-
</script>


