---
title: "Temperament calculator"
permalink: /temperament/index.html
layout: default
vim: ts=3:ft=html
---

{% include_relative listeners.html %}
{% include_relative styles-local.html %}
{% include_relative scripts-local.html %}

<nobr><label for="fifths">Fifths:</label><input id="fifths" size="3" value="12">&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="flatest">Flatest:</label>{% include_relative flatest.html %}&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="center">Center:</label>{% include_relative center.html %}&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="comma">Comma:</label>{% include_relative comma.html %}&nbsp;&nbsp;&nbsp;</nobr>

<nobr><label for="decimal">Decimal&nbsp;places:</label>{% include_relative decimal.html %}&nbsp;&nbsp;&nbsp;</nobr>


<div id="display"></div>




