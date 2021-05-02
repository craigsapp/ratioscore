---
title: "Bohlen-Pierce scale"
permalink: /bohlen-pierce/index.html
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
tuning differences (as beats):

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






<h2> &lambda; scale </h2>


{% include ratioscore.html id="lambda-scale-just" tabsize="12" %}
<script type="application/x-ratioscore" id="lambda-scale-just">
!!!OTL: &lambda; scale
**dtime	**ratio
*MM144	*Iclars
*	*ref:C3
1	C
1	D
1	E
1	F
1	G
1	H
1	J
1	A
1	B
1	C*3
*-	*-
!!!RDF**ratio: C = 1:1
!!!RDF**ratio: D = 25:21
!!!RDF**ratio: E = 9:7
!!!RDF**ratio: F = 7:5
!!!RDF**ratio: G = 5:3
!!!RDF**ratio: H = 9:5
!!!RDF**ratio: J = 15:7
!!!RDF**ratio: A = 7:3
!!!RDF**ratio: B = 25:9
</script>

Equal-tempered version:

{% include ratioscore.html id="lambda-scale-eq" tabsize="12" %}
<script type="application/x-ratioscore" id="lambda-scale-eq">
!!!OTL: &lambda; scale (equal temperament)
**dtime	**ratio
*MM144	*Iclars
*	*ref:C3
1	C
1	D
1	E
1	F
1	G
1	H
1	J
1	A
1	B
1	C*3
*-	*-
!!!RDF**ratio: C = 0c
!!!RDF**ratio: D = 301.85c
!!!RDF**ratio: E = 435.08c
!!!RDF**ratio: F = 582.51c
!!!RDF**ratio: G = 884.36c
!!!RDF**ratio: H = 1017.60c
!!!RDF**ratio: J = 1319.44c
!!!RDF**ratio: A = 1466.87c
!!!RDF**ratio: B = 1768.72c
</script>


Composition using lambda scale:

{% include ratioscore.html id="lambda-comp" tabsize="12" %}
<script type="application/x-ratioscore" id="lambda-comp">
!!!OTL: ໃບຂາວ
!!!COM: Sapp, Craig Stuart
!!!ODT: 2021/05/02
**dtime	**ratio	**ratio	**ratio
*MM144	*I#14	*Ixylo	*I#70
*	*ref:C3	*ref:C3	*ref:C3
*	*	*	*vel:50
1	C	.	.
1	.	E	.
1	.	.	G*3
1	.	.	.
1	0	0	.
1	.	.	H*3
1	.	.	J*3
1	.	.	H*3
1	C	J	G*3
1	.	.	0
1	.	A	.
1	B/3	B	.
1	A/3	C*3	.
1	0	.	.
1	.	.	E*3
1	.	.	F*3
1	.	.	E*3
1	.	.	D*3
1	G/3	B/3	.
1	.	.	.
1	.	.	F*3
1	A/3	C	E*3
1	.	.	.
1	.	.	.
1	A/3	C	E*3
1	A/3	C	E*3
1	.	.	.
1	A/3	F	A*3
1	.	.	.
1	C	F	B*3
1	.	.	.
1	C	E	A*3
1	.	.	.
1	C	E	G*3
1	.	.	.
1	0	0	.
1	.	.	H*3
1	.	.	J*3
1	.	.	H*3
1	.	B/3	G*3
1	.	C	F*3
1	.	B/3	.
1	.	A/3	E*3
1	.	J/3	.
1	.	.	.
1	F	.	F*3
1	G	.	.
1	F	.	G*3
1	E	.	.
1	D	F	.
1	C	G	H*3
1	A/3	F	.
1	B/3	E	.
1	A/3	D	J*3
1	D	E	.
1	E	F	A*3
1	D	G	.
1	F	A	B*3
1	.	.	.
4	E	G	C*9
*-	*-	*-	*-
!!!RDF**ratio: C = 1:1
!!!RDF**ratio: D = 25:21
!!!RDF**ratio: E = 9:7
!!!RDF**ratio: F = 7:5
!!!RDF**ratio: G = 5:3
!!!RDF**ratio: H = 9:5
!!!RDF**ratio: J = 15:7
!!!RDF**ratio: A = 7:3
!!!RDF**ratio: B = 25:9
</script>


