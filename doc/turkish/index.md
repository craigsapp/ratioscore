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

<div style="display:inline-block;" id="songlist"></div>
<nobr><label for="rdf">Pitch&nbsp;units</label><select onchange="playSong(event);" id="rdf">
	<option value="ratio">ratios</option>
	<option value="cents">cents</option>
</select></nobr>
<div style="display:inline-block;" id="pdf"></div>

{% include ratioscore.html id="main" %}
<script type="application/x-ratioscore" id="main">
</script>


