---
title: "Ratioscore: interval grid"
permalink: /doc/interval-grid/index.html
layout: default
vim: ts=8:ft=html
---

{% include_relative styles-local.html %}
{% include_relative listeners.html %}
{% include_relative scripts-local.html %}

<nobr><label for="rows">Rows:&nbsp;</label><input id="rows" value="10" size="3"></nobr>
<nobr><label for="columns">Columns:&nbsp;</label><input id="columns" value="10" size="3"></nobr>
<nobr><label for="reference">Reference&nbsp;pitch:&nbsp;</label>{% include_relative reference-pitch.html %}</nobr>
<nobr><label for="reference">Instrument</label>{% include_relative instrument.html %}</nobr>
<nobr><label for="reduce">Reduce&nbsp;fractions</label><input id="reduce" type="checkbox"></nobr>

<div id="grid"></div>
