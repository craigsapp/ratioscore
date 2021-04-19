---
title: "Ratioscore: Equal-temperament calculator"
permalink: /doc/scales/equal-temperament/index.html
layout: default
vim: ts=8:ft=html
---

{% include_relative listeners.html %}
{% include_relative styles-local.html %}
{% include_relative scripts-local.html %}

<nobr>
Octave: <input id="octave" value="2"> 
</nobr>
<nobr>
Divisions: <input id="divisions" value="12">
</nobr>
<nobr>
Tempo: <input id="tempo" value="120">
</nobr>
<nobr>
Reference: <input id="reference" value="C4">
</nobr>
<nobr>
{% include_relative instrument.html %}
</nobr>
<!--
<span class="link" onclick="copyUrl(); alert('Link copied to clipboard');">copy link</span>
-->

{% include ratioscore.html id="etscore" tabsize="15" %}
<script type="application/x-ratioscore" id="etscore">
</script>


Notes:

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
like `**Xratio`.
</li>

<li markdown="1">
The `URL` entry contains a link to this page with parameters
used create the current equal-tempered scale.
</li>

</ul>

