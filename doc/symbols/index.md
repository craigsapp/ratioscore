---
title: "Ratioscore: symbol substitution"
permalink: /doc/symbols/index.html
layout: default
vim: ts=8:ft=html
---

Here are examples of using symbols to give names to ratios.
Substitutions will be applied before interpreting the note, and
substitutions will be applied in the order they occur in the file.

{% include ratioscore.html id="rdf-example" %}
<script type="application/x-ratioscore" id="rdf-example">
!!!OTL: Just major scale
**recip	**ratio
*MM144	*I#75
*	*ref:C4
16	.
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



{% include ratioscore.html id="slendro-example" %}
<script type="application/x-ratioscore" id="slendro-example">
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



