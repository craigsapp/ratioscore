---
title: "Interval grid"
permalink: /grid/index.html
layout: page
vim: ts=8:ft=html
---

{% include_relative listeners.html %}
{% include_relative scripts-local.html %}
{% include_relative styles-local.html %}

<p>
	Click on a ratio or cents value to listen to the note/interval.
</p>

<nobr><label for="rows">Rows:&nbsp;</label><input id="rows" value="10" size="3"></nobr>
<nobr><label for="columns">Columns:&nbsp;</label><input id="columns" value="10" size="3"></nobr>
<nobr><label for="reference">Reference&nbsp;pitch:&nbsp;</label>{% include_relative reference-pitch.html %}</nobr>
<nobr><label for="instrument">Instrument:</label>{% include_relative instrument.html %}</nobr>
<nobr><label for="reduce">Reduce&nbsp;fractions:</label><input id="reduce" type="checkbox"></nobr>
<nobr><label for="playref">Play&nbsp;reference:</label><input id="playref" checked type="checkbox"></nobr>

<div id="grid"></div>


<h2 class="ignore"> Computer keyboard performance </h2>

As you press notes in the above grid or sorted list, the sounds
will be remembered in order.  You can then press keys on the computer
keyboard to recall them, starting with `1` for the first sound, `2`
for the second sound, etc.  The sequence will continue for all regular
keys on the US-layout keyboard.  Press the delete/backspace key to clear
the mapping so that another one can be loaded.  Up to 46 different notes
can be loaded (maybe allowing shift key in the future to allow for 92
different notes).

When pressing a key, the ratio/cents value will be displayed here below:

<div style="font-size: 3em; font-weight: bold;" id="notename"></div>

<div style="font-size: 0.5em;" id="notemapping"></div>

<textarea style="display:none; margin-top:100px; min-height:100px; min-width:300px; font-size: 0.75em !important; font: Courier; tab-size:12;" id="ratioscore"></textarea>


