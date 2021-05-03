---
title: "Vallotti temperament"
permalink: /vallotti/index.html
layout: page
vim: ts=8:ft=html
---

{% include ratioscore.html id="vallotti" %}
<script type="application/x-ratioscore" id="vallotti">
**dtime	**ratio
*MM120	*Icemba
*	*ref:C4
1	v00
1	v01
1	v02
1	v03
1	v04
1	v05
1	v06
1	v07
1	v08
1	v09
1	v10
1	v11
2	v00*2
*-	*-
!!!RDF**ratio: v00 = 0c
!!!RDF**ratio: v01 = 94.135c
!!!RDF**ratio: v02 = 196.090c
!!!RDF**ratio: v03 = 298.045c
!!!RDF**ratio: v04 = 392.180c
!!!RDF**ratio: v05 = 501.955c
!!!RDF**ratio: v06 = 592.180c
!!!RDF**ratio: v07 = 698.045c
!!!RDF**ratio: v08 = 796.090c
!!!RDF**ratio: v09 = 894.135c
!!!RDF**ratio: v10 = 1000.000c
!!!RDF**ratio: v11 = 1090.225c
</script>

Below are the unreduced calculations for the temperament: Circle
of 5ths from F to B are just fifths reduced by 1/6 of a Pythagorean
comma (3^12/2^19), and others are just perfect fifths (3/2).


{% include ratioscore.html id="vallotti-unreduced" %}
<script type="application/x-ratioscore" id="vallotti-unreduced">
**dtime	**ratio
*MM120	*Icemba
*	*ref:C4
1	v00
1	v01
1	v02
1	v03
1	v04
1	v05
1	v06
1	v07
1	v08
1	v09
1	v10
1	v11
2	v00*2
*-	*-
!!!RDF**ratio: x1 = (3/2)*(2^19/3^12)^(1/6)
!!!RDF**ratio: x2 = 3/2
!!!RDF**ratio: v01 = x1^-1 * x2^-4 * 2^3
!!!RDF**ratio: v08 = x1^-1 * x2^-3 * 2^3
!!!RDF**ratio: v03 = x1^-1 * x2^-2 * 2^2
!!!RDF**ratio: v10 = x1^-1 * x2^-1 * 2^2
!!!RDF**ratio: v05 = x1^-1         * 2^1
!!!RDF**ratio: v00 = x1^ 0         * 2^0
!!!RDF**ratio: v07 = x1^ 1         * 2^0
!!!RDF**ratio: v02 = x1^ 2         * 2^-1
!!!RDF**ratio: v09 = x1^ 3         * 2^-1
!!!RDF**ratio: v04 = x1^ 4         * 2^-2
!!!RDF**ratio: v11 = x1^ 5         * 2^-2
!!!RDF**ratio: v06 = x1^ 5 * x2^1  * 2^-3

</script>



References:

<ul>
<li> <a target="_blank" href="https://en.xen.wiki/w/Well_temperament">Well temperament</a> on Xenharmonic Wiki </li>
<li> <a target="_blank" href="https://en.wikipedia.org/wiki/Vallotti_temperament">Vallotti temperament</a> on Wikipedia.</li>
</ul>



