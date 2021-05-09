---
title: "Temperament calculator"
permalink: /temperament/index.html
layout: default
vim: ts=3:ft=html
---

{% include_relative listeners.html %}
{% include_relative styles-local.html %}
{% include_relative scripts-local.html %}

[under development]

<nobr><label for="temperament">Temperament:</label>{% include_relative temperament.html %}</nobr>
<br/>

<p markdown="1">
Boxes between pitch classes in the list below should be filled
with adjustments to the perfect fifth to either fit the circle-of-fifths
better to twelve tones (such as by flattening all fifths by 1/12
of a Pythagorean comma to create equal temperament) or to adjust major
thirds closer to a 5/4 ratio.  A value `-1/4s` means to flatten the
fifth between the two adjacent notes by 1/4 of a syntonic comma
(81/80 ratio).  The value `-1/4p` is 1/4 of a Pythagorean comma
(`3^12/2^19` ratio).
</p>


<nobr><label for="fifths">Fifths:</label><input id="fifths" size="3" value="12">&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="flatest">Flatest:</label>{% include_relative flatest.html %}&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="center">Center:</label>{% include_relative center.html %}&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="decimal">Decimal&nbsp;places:</label>{% include_relative decimal.html %}&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="instrument">Instrument:</label>{% include_relative instrument.html %}&nbsp;&nbsp;&nbsp;</nobr>

<div id="display"></div>

<div id="grid"></div>


<h2> Ratioscore </h2>

{% include ratioscore.html id="tscore" tabsize="15" links="false" erase="false" %}
<script type="application/x-ratioscore" id="tscore">
</script>


