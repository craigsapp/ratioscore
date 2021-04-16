---
title: "Ratioscore: Equal-temperament calculator"
permalink: /doc/scales/equal-temperament/index.html
layout: default
vim: ts=8:ft=html
---

{% include_relative listeners.html %}
{% include_relative styles-local.html %}
{% include_relative scripts-local.html %}

Octave: <input id="octave" value="2"> 
Divisions: <input id="divisions" value="12">
Tempo: <input id="tempo" value="120">
Reference: <input id="reference" value="C4">
Instrument: <input id="instrument" value="clars">
<span class="link" onclick="copyUrl(); alert('Link copied to clipboard');">copy link</span>

{% include ratioscore.html id="etscore" tabsize="15" %}
<script type="application/x-ratioscore" id="etscore">
</script>

