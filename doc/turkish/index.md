---
title: "Turkish music"
permalink: /turkish/index.html
layout: page
vim: ts=8:ft=html
---

{% include_relative listeners.html %}
{% include_relative mu2.html %}
{% include_relative scripts-local.html %}
{% include_relative styles-local.html %}

Music from the <a target="_blank" href="https://github.com/MTG/SymbTr">Turkish Makam Music Symbolic Data Collection, <a target="_blank" href="https://www.researchgate.net/publication/267365456_A_TURKISH_MAKAM_MUSIC_SYMBOLIC_DATABASE_FOR_MUSIC_INFORMATION_RETRIEVAL_SymbTr">M. Kemal Karaosmanoğlu</a>, ed.

<div style="display:inline-block;" id="songlist"></div>
<nobr><label for="rdf">Pitch&nbsp;units</label><select onchange="playSong(event);" id="rdf">
	<option value="ratio">ratios</option>
	<option value="cents">cents</option>
</select></nobr>
<div style="display:inline-block;" id="pdf"></div>
<nobr><label for="instrument">Instrument:</label>{% include_relative instrument.html %}&nbsp;&nbsp;&nbsp;</nobr>



{% include ratioscore.html id="main" %}
<script type="application/x-ratioscore" id="main">
</script>

<h2> See also </h2>

<ul>
<li> <a href="/makam">Turkish makams</a> </li>
</ul>
