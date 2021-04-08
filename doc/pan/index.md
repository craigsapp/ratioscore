---
title: "Ratioscore: panning"
permalink: /doc/pan/index.html
layout: default
vim: ts=8:ft=html
---

Each `**ratio` spine can be positioned in the stereo field with
panning instructions.  Stereo left is -1.0 and right is 1.0.

{% include ratioscore.html id="glissando-example" %}
<script type="application/x-ratioscore" id="glissando-example">
**dtime	**ratio	**ratio	**ratio	**ratio	**ratio
*	*Iclars	*Iclars	*Iclars	*Iclars	*Iclars
*	*ref:C3	*ref:C3	*ref:C3	*ref:C3	*ref:C3
*MM180	*pan:-1.0	*pan:-0.5	*pan:0	*pan:0.5	*pan:1.0
1	1	.	.	.	.
1	0	1	.	.	.
1	.	0	1	.	.
1	.	.	0	1	.
1	.	.	.	0	1
1	3/2	.	.	.	0
1	0	3/2	.	.	.
1	.	0	3/2	.	.
1	.	.	0	3/2	.
1	.	.	.	0	3/2
1	(3/2)^2	.	.	.	0
1	0	(3/2)^2	.	.	.
1	.	0	(3/2)^2	.	.
1	.	.	0	(3/2)^2	.
1	.	.	.	0	(3/2)^2
*-	*-	*-	*-	*-	*-
</script>


