---
title: "Meantone temperaments"
permalink: /meantone/index.html
layout: page
vim: ts=8:ft=html
---

<h2 data-sidebar="1/4-comma"> 1/4-comma meantone </h2>

The perfect fifth is reduced by 1/4 of a syntonic comma so that the major third
is pure (5/4) as well as its complement the minor 6th (8/5).  Here is an example
of 1/4-comma meantone by defining the notes using cents:

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

Here is the same music showing the meantone calculations, which are
stacks of perfect fifths that are reduced by 1/4 of a syntonic comma to
make pure major thirds (5/4):

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
!!!RDF**ratio: m01 = x^-5 * 2^ 3
!!!RDF**ratio: m08 = x^-4 * 2^ 3
!!!RDF**ratio: m03 = x^-3 * 2^ 2
!!!RDF**ratio: m10 = x^-2 * 2^ 2
!!!RDF**ratio: m05 = x^-1 * 2^ 1
!!!RDF**ratio: m00 = x^ 0 * 2^ 0
!!!RDF**ratio: m07 = x^ 1 * 2^ 0
!!!RDF**ratio: m02 = x^ 2 * 2^-1
!!!RDF**ratio: m09 = x^ 3 * 2^-1
!!!RDF**ratio: m04 = x^ 4 * 2^-2
!!!RDF**ratio: m11 = x^ 5 * 2^-2
!!!RDF**ratio: m06 = x^ 6 * 2^-3
</script>


Not reducing the fifth calculations:

{% include ratioscore.html id="qcmean-expanded" %}
<script type="application/x-ratioscore" id="qcmean-expanded">
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

!!!RDF**ratio: x   = (3/2)*(80/81)^(1/4)
!!!RDF**ratio: m01 = x^-5 * 2^ 3
!!!RDF**ratio: m08 = x^-4 * 2^ 3
!!!RDF**ratio: m03 = x^-3 * 2^ 2
!!!RDF**ratio: m10 = x^-2 * 2^ 2
!!!RDF**ratio: m05 = x^-1 * 2^ 1
!!!RDF**ratio: m00 = x^ 0 * 2^ 0
!!!RDF**ratio: m07 = x^ 1 * 2^ 0
!!!RDF**ratio: m02 = x^ 2 * 2^-1
!!!RDF**ratio: m09 = x^ 3 * 2^-1
!!!RDF**ratio: m04 = x^ 4 * 2^-2
!!!RDF**ratio: m11 = x^ 5 * 2^-2
!!!RDF**ratio: m06 = x^ 6 * 2^-3

</script>


<h2 data-sidebar="1/3-comma"> 1/3-comma meantone </h2>

The perfect fifth is reduced by 1/3 of a syntonic comma so that the minor third
is pure (6/5) as well as its complement the major 6th (5/3).

{% include ratioscore.html id="third-comma-ratio" %}
<script type="application/x-ratioscore" id="third-comma-ratio">
!!!OTL: 1/3-comma meantone
**dtime	**ratio	**ratio	**ratio
*MM60	*Icemba	*Icemba	*Icemba
*	*ref:D3	*ref:D3	*ref:D3
1	m00	.	.
1	m02	.	.
1	m03	.	.
1	m05	.	.
1	m07	.	.
1	m08	.	.
1	m11	.	.
2	m00*2	.	.
1	0	.	.
1	m00	m03	m07
1	m02	m05	m09
1	m04	m07	m11
1	m05	m08	m00*2
!! out of tune:
2	m06	m09	m01*2
*-	*-	*-	*-
!!!RDF**ratio: x   = (3/2)*(80/81)^(1/3)
!!!RDF**ratio: m01 = x^-5 * 2^ 3
!!!RDF**ratio: m08 = x^-4 * 2^ 3
!!!RDF**ratio: m03 = x^-3 * 2^ 2
!!!RDF**ratio: m10 = x^-2 * 2^ 2
!!!RDF**ratio: m05 = x^-1 * 2^ 1
!!!RDF**ratio: m00 = x^ 0 * 2^ 0
!!!RDF**ratio: m07 = x^ 1 * 2^ 0
!!!RDF**ratio: m02 = x^ 2 * 2^-1
!!!RDF**ratio: m09 = x^ 3 * 2^-1
!!!RDF**ratio: m04 = x^ 4 * 2^-2
!!!RDF**ratio: m11 = x^ 5 * 2^-2
!!!RDF**ratio: m06 = x^ 6 * 2^-3
</script>


Comparing 1/4-comma and 1/3-comma:

{% include ratioscore.html id="comparing-comma" %}
<script type="application/x-ratioscore" id="comparing-comma">
!!!OTL: 1/4-comma and 1/3-comma meantone comparison
**dtime	**ratio	**ratio
*MM60	*Iclars	*Iclars
*	*ref:D3	*ref:D3
!! First 1/4-comma meantone major scale:
1	m400	.
1	m402	.
1	m404	.
1	m405	.
1	m407	.
1	m409	.
1	m411	.
2	m400*2	.
1	0	.
!! Then 1/3-comma meantone major scale:
1	.	m300
1	.	m302
1	.	m304
1	.	m305
1	.	m307
1	.	m309
1	.	m311
2	.	m300*2
1	0	.
!! Then playing both meantone scales at the same time:
*MM30	*	*
1	m400	m300
1	m402	m302
1	m404	m304
1	m405	m305
1	m407	m307
1	m409	m309
1	m411	m311
2	m400*2	m300*2
*-	*-	*-
!! 1/4-comma meantone:
!!!RDF**ratio: x   = (3/2)*(80/81)^(1/4)
!!!RDF**ratio: m401 = x^-5 * 2^ 3
!!!RDF**ratio: m408 = x^-4 * 2^ 3
!!!RDF**ratio: m403 = x^-3 * 2^ 2
!!!RDF**ratio: m410 = x^-2 * 2^ 2
!!!RDF**ratio: m405 = x^-1 * 2^ 1
!!!RDF**ratio: m400 = x^ 0 * 2^ 0
!!!RDF**ratio: m407 = x^ 1 * 2^ 0
!!!RDF**ratio: m402 = x^ 2 * 2^-1
!!!RDF**ratio: m409 = x^ 3 * 2^-1
!!!RDF**ratio: m404 = x^ 4 * 2^-2
!!!RDF**ratio: m411 = x^ 5 * 2^-2
!!!RDF**ratio: m406 = x^ 6 * 2^-3
!! 1/3-comma meantone:
!!!RDF**ratio: y   = (3/2)*(80/81)^(1/3)
!!!RDF**ratio: m301 = y^-5 * 2^ 3
!!!RDF**ratio: m308 = y^-4 * 2^ 3
!!!RDF**ratio: m303 = y^-3 * 2^ 2
!!!RDF**ratio: m310 = y^-2 * 2^ 2
!!!RDF**ratio: m305 = y^-1 * 2^ 1
!!!RDF**ratio: m300 = y^ 0 * 2^ 0
!!!RDF**ratio: m307 = y^ 1 * 2^ 0
!!!RDF**ratio: m302 = y^ 2 * 2^-1
!!!RDF**ratio: m309 = y^ 3 * 2^-1
!!!RDF**ratio: m304 = y^ 4 * 2^-2
!!!RDF**ratio: m311 = y^ 5 * 2^-2
!!!RDF**ratio: m306 = y^ 6 * 2^-3
</script>


