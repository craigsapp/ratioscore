---
title: "Symbol substitution"
permalink: /symbols/index.html
layout: page
vim: ts=8:ft=html
---

Here are examples of using symbols to give names to ratios.
Substitutions will be applied before interpreting the note, and
substitutions will be applied in the order they occur in the file.

{% include ratioscore.html id="rdf" %}
<script type="application/x-ratioscore" id="rdf">
!!!OTL: Just major scale
**recip	**ratio
*MM144	*I#75
*	*ref:C4
4	do
4	re
4	mi
4	fa
4	sol
4	la
4	ti
4	do*2
*-	*-
!!!RDF**ratio: do  = (1/1)
!!!RDF**ratio: re  = (9/8)
!!!RDF**ratio: mi  = (5/4)
!!!RDF**ratio: fa  = (4/3)
!!!RDF**ratio: sol = (3/2)
!!!RDF**ratio: la  = (5/3)
!!!RDF**ratio: ti  = (15/8)
</script>

In general parentheses should be used in the substitutions to make 
mathematical operations with symbols to behave as expected, such as `do*2`.



{% include ratioscore.html id="slendro" %}
<script type="application/x-ratioscore" id="slendro">
!!!OTL: Gamelan
**recip	**ratio
*MM144	*I#14
*	*ref:C4
4	ji
4	ro
4	lu
4	ma
4	nem
4	pi
*-	*-
!!!RDF**ratio: ji  = 1/1
!!!RDF**ratio: ro  = 8/7
!!!RDF**ratio: lu  = 21/16
!!!RDF**ratio: ma  = 32/21
!!!RDF**ratio: nem = 7/4
!!!RDF**ratio: pi  = 2/1
</script>


Quarter-comma meantone temperament:



{% include ratioscore.html id="qcmean" %}
<script type="application/x-ratioscore" id="qcmean">
!!!OTL: 1/4-comma meantone
**dtime	**ratio	**ratio	**ratio
*MM60	*Iclars	*Iclars	*Iclars
*	*ref:D3	*ref:D3	*ref:D3
1	p00	.	.
1	p02	.	.
1	p04	.	.
1	p05	.	.
1	p07	.	.
1	p09	.	.
1	p11	.	.
2	p12	.	.
1	0	.	.
1	p00	p04	p07
1	p02	p05	p09
1	p04	p07	p11
1	p05	p09	p12
1	p07	p11	p14
2	p08	p12	p15
*-	*-	*-	*-
!!!RDF**ratio: p00 = 1
!!!RDF**ratio: p01 = 76.0c
!!!RDF**ratio: p02 = 193.2c
!!!RDF**ratio: p03 = 310.3c
!!!RDF**ratio: p04 = 5/4
!!!RDF**ratio: p05 = 503.4c
!!!RDF**ratio: p06 = 579.5c
!!!RDF**ratio: p07 = 696.6c
!!!RDF**ratio: p08 = 25/16
!!!RDF**ratio: p09 = 889.7c
!!!RDF**ratio: p10 = 1006.8c
!!!RDF**ratio: p11 = 1082.9c
!!!RDF**ratio: p12 = 1200.0c
!!!RDF**ratio: p13 = 1276.0c
!!!RDF**ratio: p14 = 1393.2c
!!!RDF**ratio: p15 = 1510.3c
!!!RDF**
</script>






