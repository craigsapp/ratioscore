---
title: "Pythagorean tuning"
permalink: /pythagorean/index.html
layout: page
vim: ts=8:ft=html
---

<h2> 12-note Pythagorean tuning </h2>

{% include ratioscore.html id="pythagorean12" %}
<script type="application/x-ratioscore" id="pythagorean12">
!!!OTL: 12-note Pythagorean temperament

**dtime	**ratio	**ratio	**pitch	**cents
*MM60	*Ipiano	*Ipiano	*	*Ipiano
*	*ref:C4	*ref:C4	*	*ref:C4
1	P1	.	C	0c
1	m2	.	D♭	90.22c
1	M2	.	D	203.91c
1	m3	.	E♭	294.13c
1	M3	.	E	407.82c
1	P4	.	F	498.04c
1	A4	.	F♯	611.73c
1	P5	.	G	701.96c
1	m6	.	A♭	792.18c
1	M6	.	A	905.87c
1	m7	.	B♭	996.09c
1	M7	.	B	1109.78c
2	P1*2	.	C	1200c
1	0	.	.	.
!! Just Perfect fifths:
*MM40	*	*	*	*
1	P1	P5	C/G	.
1	m2	m6	D♭/A♭	.
1	M2	M6	D/A	.
1	m3	m7	E♭/B♭	.
1	M3	M7	E/B	.
1	P4	P1*2	F/C	.
1	P5	M2*2	G/D	.
1	m6	m3*2	A♭/E♭	.
1	M6	M3*2	A/E	.
1	m7	P4*2	B♭/F	.
2	M7	A4*2	B/F♯	.
!! Wolf fifth:
2	A4	m2*2	F♯/D♭	.
*-	*-	*-	*-	*-

!!!RDF**ratio: x  = 3/2
!!!RDF**ratio: m2 = x^-5 * 2^ 3
!!!RDF**ratio: m6 = x^-4 * 2^ 3
!!!RDF**ratio: m3 = x^-3 * 2^ 2
!!!RDF**ratio: m7 = x^-2 * 2^ 2
!!!RDF**ratio: P4 = x^-1 * 2^ 1
!!!RDF**ratio: P1 = x^ 0 * 2^ 0
!!!RDF**ratio: P5 = x^ 1 * 2^ 0
!!!RDF**ratio: M2 = x^ 2 * 2^-1
!!!RDF**ratio: M6 = x^ 3 * 2^-1
!!!RDF**ratio: M3 = x^ 4 * 2^-2
!!!RDF**ratio: M7 = x^ 5 * 2^-2
!!!RDF**ratio: A4 = x^ 6 * 2^-3
</script>


<h2> 25-note Pythagorean temperament </h2>

{% include ratioscore.html id="pythagorean25" %}
<script type="application/x-ratioscore" id="pythagorean25">
!!!OTL: 12-note Pythagorean temperament
**dtime	**ratio	**ratio	**ratio	**pitch
*MM80	*Ipiano	*Ipiano	*Ipiano	*
*	*ref:C4	*ref:C4	*ref:C4	*
1	d1	.	.	C♭
1	d2	.	.	D𝄫
1	P1	.	.	C
1	m2	.	.	D♭
1	A1	.	.	C♯
1	d3	.	.	E𝄫
1	M2	.	.	D
1	m3	.	.	E♭
1	A2	.	.	D♯
1	d4	.	.	F𝄫
1	M3	.	.	E
1	P4	.	.	F
1	A3	.	.	E♯
1	d5	.	.	G♭
1	A4	.	.	F♯
1	d6	.	.	A𝄫
1	P5	.	.	G
1	m6	.	.	A♭
1	A5	.	.	G♯
1	d7	.	.	B𝄫
1	M6	.	.	A
1	m7	.	.	B♭
1	A6	.	.	A♯
1	M7	.	.	B
1	A7	.	.	B♯
1	0	.	.	.
!! Well-spelled major triad:
4	M2	A4	M6	D/F♯/A
!! Poorly spelled major triad:
4	M2	d5	M6	D/G♭/A
*-	*-	*-	*-	*-
!!!RDF**ratio: A7 = 3^12 : 2^18
!!!RDF**ratio: A3 = 3^11 : 2^17
!!!RDF**ratio: A6 = 3^10 : 2^15
!!!RDF**ratio: A2 = 3^9  : 2^14
!!!RDF**ratio: A5 = 3^8  : 2^12
!!!RDF**ratio: A1 = 3^7  : 2^11
!!!RDF**ratio: A4 = 3^6  : 2^9
!!!RDF**ratio: M7 = 3^5  : 2^7
!!!RDF**ratio: M3 = 3^4  : 2^6
!!!RDF**ratio: M6 = 3^3  : 2^4
!!!RDF**ratio: M2 = 3^2  : 2^3
!!!RDF**ratio: P5 = 3^1  : 2^1
!!!RDF**ratio: P1 = 3^0  : 2^0
!!!RDF**ratio: P4 = 2^2  : 3^1
!!!RDF**ratio: m7 = 2^4  : 3^2
!!!RDF**ratio: m3 = 2^5  : 3^3
!!!RDF**ratio: m6 = 2^7  : 3^4
!!!RDF**ratio: m2 = 2^8  : 3^5
!!!RDF**ratio: d5 = 2^10 : 3^6
!!!RDF**ratio: d1 = 2^11 : 3^7
!!!RDF**ratio: d4 = 2^13 : 3^8
!!!RDF**ratio: d7 = 2^15 : 3^9
!!!RDF**ratio: d3 = 2^16 : 3^10
!!!RDF**ratio: d6 = 2^18 : 3^11
!!!RDF**ratio: d2 = 2^20 : 3^12
</script>




