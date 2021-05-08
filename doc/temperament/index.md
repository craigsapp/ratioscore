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

<nobr><label for="fifths">Fifths:</label><input id="fifths" size="3" value="12">&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="flatest">Flatest:</label>{% include_relative flatest.html %}&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="center">Center:</label>{% include_relative center.html %}&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="decimal">Decimal&nbsp;places:</label>{% include_relative decimal.html %}&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="instrument">Instrument:</label>{% include_relative instrument.html %}&nbsp;&nbsp;&nbsp;</nobr>

<div id="display"></div>


{% include ratioscore.html id="tscore" tabsize="15" links="false" erase="false" %}
<script type="application/x-ratioscore" id="tscore">
</script>


