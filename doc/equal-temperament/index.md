---
title: "Equal-temperament calculator"
permalink: /equal-temperament/index.html
layout: default
vim: ts=3:ft=html
---

{% include_relative listeners.html %}
{% include_relative styles-local.html %}
{% include_relative scripts-local.html %}

<div style="line-height:34px;">
	<nobr><label for="octave">Octave:</label><input id="octave" value="2">&nbsp;&nbsp;&nbsp;</nobr>
	<nobr><label for="divisions">Divisions:</label><input id="divisions" value="12">&nbsp;&nbsp;&nbsp;</nobr>
	<nobr><label for="tempo">Tempo:</label><input id="tempo" value="120">&nbsp;&nbsp;&nbsp;</nobr>
	<nobr><label for="reference">Reference:</label>{% include_relative reference-pitch.html %}&nbsp;&nbsp;&nbsp;</nobr>
	<nobr><label for="instrument">Instrument:</label>{% include_relative instrument.html %}&nbsp;&nbsp;&nbsp;</nobr>
</div>

<!--
<span class="link" onclick="copyUrl(); alert('Link copied to clipboard');">copy link</span>
-->

{% include ratioscore.html id="etscore" tabsize="15" links="false" %}
<script type="application/x-ratioscore" id="etscore">
</script>


<h3> Notes </h3>

<ul>

<li markdown="1">
"Octave" is the just interval that will be split into equally-spaced
intervals for each note in the scale. For example, `3` is an octave and a
perfect fifth, `3/2` is a perfect fifth.
</li>

<li markdown="1"> 
The `**cents` column is for reference.  You can listen to
the cents column directly by changing it to a `**ratio` column and
adding `c` at the end of each cent value.  You can suppress
playback of the `**ratio` column by renaming it to something
like `**mute`.
</li>

<li markdown="1">
The `URL` entry contains a link to this page with parameters
used create the current equal-tempered scale.
</li>

</ul>

