---
title: "Ratioscore: TENOR 2021 examples"
permalink: /doc/tenor2021/index.html
layout: default
vim: ts=8:ft=html
---

<style>

img {

	width:700px;
	background: white;
	padding: 50px;
}

</style>

<h2> Figure 1 </h2>

<img src="figure1.png">

{% include ratioscore.html id="figure1" %}
<script type="application/x-ratioscore" id="figure1">
!!!OTL: Figure 1
**time	**ratio
*	*Ivioln
*	*ref:G3
0	1
1	3
2	11/4
2.25	5/2
2.5	0
3	7
3.5	4/3
4	0
*-	*-
</script>

<h2> Figure 2 </h2>

<img src="figure2.png">

{% include ratioscore.html id="figure2" %}
<script type="application/x-ratioscore" id="figure2">
!!!OTL: Figure 2
**time	**ratio	**ratio
*	*Ivioln	*Iclars
*	*ref:G3	*ref:G3
0	1	(3/2)^0
0.5	3/2	(3/2)^1
1	9/4	(3/2)^2
1.5	27/8	(3/2)^3
2	81/16	(3/2)^4
2.5	243/32	(3/2)^5
3	729/64	(3/2)^6
3.5	2187/128	(3/2)^7
4	0	0
*-	*-	*-
</script>

Listening to only the violin part:

{% include ratioscore.html id="figure2a" %}
<script type="application/x-ratioscore" id="figure2a">
!!!filter: extract -s 1,2
!!!OTL: Figure 2a, violin part only
**time	**ratio	**ratio
*	*Ivioln	*Iclars
*	*ref:G3	*ref:G3
0	1	(3/2)^0
0.5	3/2	(3/2)^1
1	9/4	(3/2)^2
1.5	27/8	(3/2)^3
2	81/16	(3/2)^4
2.5	243/32	(3/2)^5
3	729/64	(3/2)^6
3.5	2187/128	(3/2)^7
4	0	0
*-	*-	*-
</script>

Listening to only the clarinet part:

{% include ratioscore.html id="figure2b" %}
<script type="application/x-ratioscore" id="figure2b">
!!!filter: extract -s 1,3
!!!OTL: Figure 2b, clarinet part only
**time	**ratio	**ratio
*	*Ivioln	*Iclars
*	*ref:G3	*ref:G3
0	1	(3/2)^0
0.5	3/2	(3/2)^1
1	9/4	(3/2)^2
1.5	27/8	(3/2)^3
2	81/16	(3/2)^4
2.5	243/32	(3/2)^5
3	729/64	(3/2)^6
3.5	2187/128	(3/2)^7
4	0	0
*-	*-	*-
</script>


<h2> Figure 3 </h2>

<img src="figure3.png">

{% include ratioscore.html id="figure3" %}
<script type="application/x-ratioscore" id="figure3">
!!!OTL: Figure 3
**time	**ratio	**ratio	**ratio	**ratio
*MM60	*Ivioln	*Ivioln	*Iviola	*Icello
*M4/4	*ref:G3+2c	*ref:D4+4c	*ref:C3	*ref:C2
0	1	.	.	6/5
0.5	.	1	6/5	.
=1	=1	=1	=1	=1
1	3	6/5	1	4/3
1.5	6/5	3	.	1
2	5	4/3	3	3/2
2.5	4/3	.	3/2	3
3	7	3/2	5	9/8
3.5	.	7	9/8	5
4	9	.	7	7/5
4.5	9/8	9	.	7
=2	=2	=2	=2	=2
5	11	7/5	9	9/7
5.5	7/5	11	9/7	.
6	13	9/7	.	13/11
6.5	9/7	13	13/11	11
7	15	13/11	13	.
7.5	13/11	15	.	13
=3	=3	=3	=3	=3
9	.	.	.	.
*-	*-	*-	*-	*-
</script>


<h2> Figure 4 </h2>

(Sounds the same as figure 3)

{% include ratioscore.html id="figure4" %}
<script type="application/x-ratioscore" id="figure4">
!!!OTL: Figure 4
**time	**ratio	**ratio	**ratio	**ratio
*MM120	*Ivioln	*Ivioln	*Iviola	*Icello
*M4/4	*ref:G3+2c	*ref:D4+4c	*ref:C3	*ref:C2
1	1	.	.	6/5
1	.	1	6/5	.
=1	=1	=1	=1	=1
1	3	6/5	1	4/3
1	6/5	3	.	1
1	5	4/3	3	3/2
1	4/3	.	3/2	3
1	7	3/2	5	9/8
1	.	7	9/8	5
1	9	.	7	7/5
1	9/8	9	.	7
=2	=2	=2	=2	=2
1	11	7/5	9	9/7
1	7/5	11	9/7	.
1	13	9/7	.	13/11
1	9/7	13	13/11	11
1	15	13/11	13	.
3	13/11	15	.	13
=3	=3	=3	=3	=3
*-	*-	*-	*-	*-
</script>



<h2> Figure 5 </h2>

{% include ratioscore.html id="figure5" %}
<script type="application/x-ratioscore" id="figure5">
!!!OTL: Figure 5
**recip	**ratio
*MM60	*Ivioln
*	*ref:G3
4	1
4	3
16	11/4
16	5/2
*MM44	*
8	0
8	7
8	4/3
</script>



<h2> Figure 6 </h2>

<img src="figure6.png">

{% include ratioscore.html id="figure6" %}
<script type="application/x-ratioscore" id="figure6">
!!!OTL: Figure 6
**time	**ratio	**ratio
*	*Ivioln	*Iclars
*	*ref:C4	*refC4
*	*	*grate:10
0	1H	0
2	_3/2	3/2
4	_1h	_3/2H
4.5	0	.
5	.	_1
6	.	.
6.5	3/2	_6/5
7	1H	.
8	_5/4h	5/4
9	.	_1h
10	0	1H
11	3H	_2h
12	_2h	.
13	0	0
*-	*-	*-
</script>


