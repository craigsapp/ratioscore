---
title: "Ratioscore: Bohlen-Pierce scale"
permalink: /doc/scales/bohlen-pierce/index.html
layout: default
vim: ts=8:ft=html
---

Thirteen divisions of the third harmonic.

{% include ratioscore.html id="bohlen-pierce-scale" %}
<script type="application/x-ratioscore" id="bohlen-pierce-scale">
!!!OTL: Equal-tempered Bohlen-Pierce scale
**dtime	**ratio
*MM144	*Iclars
*	*ref:C3
1	3^(0/13)
1	3^(1/13)
1	3^(2/13)
1	3^(3/13)
1	3^(4/13)
1	3^(5/13)
1	3^(6/13)
1	3^(7/13)
1	3^(8/13)
1	3^(9/13)
1	3^(10/13)
1	3^(11/13)
1	3^(12/13)
2	3^(13/13)
*-	*-
</script>

Just intonation variant:

{% include ratioscore.html id="just-bohlen-pierce-scale" %}
<script type="application/x-ratioscore" id="just-bohlen-pierce-scale">
!!!OTL: Just Bohlen-Pierce scale
**dtime	**ratio
*MM144	*Iclars
*	*ref:C3
1	1
1	27/25
1	25/21
1	9/7
1	7/5
1	75/49
1	5/3
1	9/5
1	49/25
1	15/7
1	7/3
1	63/25
1	25/9
2	3/1
*-	*-
</script>

Playing both just and equal-tempered versions together to hear
tunning differences (as beats):

{% include ratioscore.html id="both-bohlen-pierce-scale" tabsize="12" %}
<script type="application/x-ratioscore" id="both-bohlen-pierce-scale">
!!!OTL: Bohlen-Pierce scales (just and equal-tempered)
**dtime	**ratio	**ratio	**difference
*	*Iclars	*Iclars	*
*	*ref:C3	*ref:C3	*
1	1	3^(0/13)	0.00c
1	27/25	3^(1/13)	13.06c
1	25/21	3^(2/13)	-9.24c
1	9/7	3^(3/13)	3.83c
1	7/5	3^(4/13)	2.71c
1	75/49	3^(5/13)	-5.41c
1	5/3	3^(6/13)	-6.53c
1	9/5	3^(7/13)	6.53c
1	49/25	3^(8/13)	5.42c
1	15/7	3^(9/13)	-2.70c
1	7/3	3^(10/13)	-3.82c
1	63/25	3^(11/13)	9.24c
1	25/9	3^(12/13)	-13.06c
2	3/1	3^(13/13)	0.00c
*-	*-	*-	*-

</script>

See <a target="_blank" href="https://en.wikipedia.org/wiki/Bohlen%E2%80%93Pierce_scale">Wikipedia entry for the Bohlen-Pierce</a> scale.



