---
title: "Symbol substitution"
permalink: /symbols/index.html
layout: page
vim: ts=8:ft=html
---

Here are examples of using symbols to give names to ratios.
Substitutions will be applied before interpreting the notes.
Substitutions will be applied in the order of longer strings first (such
as `sol` in the following example), then shorter strings.

{% include ratioscore.html id="rdf" %}
<script type="application/x-ratioscore" id="rdf">
!!!OTL: Just major scale
**recip	**ratio
*MM184	*Ixylo
*	*ref:C4
4	do
4	re
4	mi
4	fa
4	sol
4	la
4	ti
4	do*2
4	ti
4	la
4	sol
4	fa
4	mi
4	re
4	do
4	ti/2
2	do
*-	*-
!!!RDF**ratio: do  = 1/1
!!!RDF**ratio: re  = 9/8
!!!RDF**ratio: mi  = 5/4
!!!RDF**ratio: fa  = 4/3
!!!RDF**ratio: sol = 3/2
!!!RDF**ratio: la  = 5/3
!!!RDF**ratio: ti  = 15/8
</script>



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
*MM60	*Icemba	*Icemba	*Icemba
*	*ref:D3	*ref:D3	*ref:D3
1	m00	.	.
1	m02	.	.
1	m04	.	.
1	m05	.	.
1	m07	.	.
1	m09	.	.
1	m11	.	.
2	m00*2	.	.
1	0	.	.
1	m00	m04	m07
1	m02	m05	m09
1	m04	m07	m11
1	m05	m09	m00*2
!! out of tune:
2	m06	m10	m01*2
*-	*-	*-	*-
!!!RDF**ratio: m00 = 0c
!!!RDF**ratio: m01 = 117.1c
!!!RDF**ratio: m02 = 193.2c
!!!RDF**ratio: m03 = 310.3c
!!!RDF**ratio: m04 = 386.3c
!!!RDF**ratio: m05 = 503.4c
!!!RDF**ratio: m06 = 579.5c
!!!RDF**ratio: m07 = 696.6c
!!!RDF**ratio: m08 = 813.7c
!!!RDF**ratio: m09 = 889.7c
!!!RDF**ratio: m10 = 1006.8c
!!!RDF**ratio: m11 = 1082.9c
</script>

Here is the same music showing the meantone calculations:

{% include ratioscore.html id="qcmean-ratio" %}
<script type="application/x-ratioscore" id="qcmean-ratio">
!!!OTL: 1/4-comma meantone
**dtime	**ratio	**ratio	**ratio
*MM60	*Icemba	*Icemba	*Icemba
*	*ref:D3	*ref:D3	*ref:D3
1	m00	.	.
1	m02	.	.
1	m04	.	.
1	m05	.	.
1	m07	.	.
1	m09	.	.
1	m11	.	.
2	m00*2	.	.
1	0	.	.
1	m00	m04	m07
1	m02	m05	m09
1	m04	m07	m11
1	m05	m09	m00*2
!! out of tune:
2	m06	m10	m01*2
*-	*-	*-	*-
!!!RDF**ratio: x   = 5^(1/4)
!!!RDF**ratio: m00 = 1
!!!RDF**ratio: m01 = 8*5^(1/2)*x/5^2
!!!RDF**ratio: m02 = 5^(1/2)/2
!!!RDF**ratio: m03 = 4*x/5
!!!RDF**ratio: m04 = 5/4
!!!RDF**ratio: m05 = (2*5^(1/2)*x)/5
!!!RDF**ratio: m06 = 5*5^(1/2)/8
!!!RDF**ratio: m07 = x
!!!RDF**ratio: m08 = 8/5
!!!RDF**ratio: m09 = 5^(1/2)*x/2
!!!RDF**ratio: m10 = 4*5^(1/2)/5
!!!RDF**ratio: m11 = 5*x/4
</script>



{% include ratioscore.html id="mean-equal-compare" %}
<script type="application/x-ratioscore" id="mean-equal-compare">
!!!OTL: Comparing meantone and equal temperament chords
**dtime	**ratio	**ratio	**ratio
*MM50	*Icemba	*Icemba	*Icemba
*	*ref:D3	*ref:D3	*ref:D3
!! Meantone triads:
1	m00	m04	m07
1	m02	m05	m09
1	m04	m07	m11
1	m05	m09	m00*2
2	m06	m10	m01*2
1	0	0	0
!! Equal-tempered triads:
1	e00	e04	e07
1	e02	e05	e09
1	e04	e07	e11
1	e05	e09	e00*2
2	e06	e10	e01*2
1	0	0	0
!! Alternating between meantone and EQ triads:
1	m00	m04	m07
1	e00	e04	e07
1	m02	m05	m09
1	e02	e05	e09
1	m04	m07	m11
1	e04	e07	e11
1	m05	m09	m00*2
1	e05	e09	e00*2
1	m06	m10	m01*2
1	e06	e10	e01*2
*-	*-	*-	*-
!! 1/4-comma meantone temperament:
!!!RDF**ratio: x   = 5^(1/4)
!!!RDF**ratio: m00 = 1
!!!RDF**ratio: m01 = 8*5^(1/2)*x/5^2
!!!RDF**ratio: m02 = 5^(1/2)/2
!!!RDF**ratio: m03 = 4*x/5
!!!RDF**ratio: m04 = 5/4
!!!RDF**ratio: m05 = (2*5^(1/2)*x)/5
!!!RDF**ratio: m06 = 5*5^(1/2)/8
!!!RDF**ratio: m07 = x
!!!RDF**ratio: m08 = 8/5
!!!RDF**ratio: m09 = 5^(1/2)*x/2
!!!RDF**ratio: m10 = 4*5^(1/2)/5
!!!RDF**ratio: m11 = 5*x/4
!! Equal temperament:
!!!RDF**ratio: e00 = 2^(0/12)
!!!RDF**ratio: e01 = 2^(1/12)
!!!RDF**ratio: e02 = 2^(2/12)
!!!RDF**ratio: e03 = 2^(3/12)
!!!RDF**ratio: e04 = 2^(4/12)
!!!RDF**ratio: e05 = 2^(5/12)
!!!RDF**ratio: e06 = 2^(6/12)
!!!RDF**ratio: e07 = 2^(7/12)
!!!RDF**ratio: e08 = 2^(8/12)
!!!RDF**ratio: e09 = 2^(9/12)
!!!RDF**ratio: e10 = 2^(10/12)
!!!RDF**ratio: e11 = 2^(11/12)
</script>




