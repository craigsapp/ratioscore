---
title: "Ratioscore: Polyrhythm generator"
permalink: /doc/polyrhythm/index.html
layout: default
vim: ts=3:ft=html
---

{% include_relative styles-local.html %}
{% include_relative scripts-local.html %}
{% include_relative listeners.html %}


<table>
	<tr>
		<td>
			<span class="heading">Part 1:</span>
		</td>
		<td>
			<label for="cycle-1">Cycle size: </label><input id="cycle-1" value="2" size="3">
		</td>
		<td>
			<label for="timbre-1">Timbre:</label><select id="timbre-1">{% include_relative instrument.html %}</select>
		</td>
		<td>
			<label for="pitch-1">Pitch: </label><input id="pitch-1" value="1" size="3">
		</td>
		<td>
			<label for="ref-1">Reference: </label><select id="ref-1">{% include_relative reference-pitch.html %}</select>
		</td>
	</tr>
	<tr>
		<td>
			<span class="heading">Part 2:</span>
		</td>
		<td>
			<label for="cycle-2">Cycle size: </label><input id="cycle-2" value="3" size="3">
		</td>
		<td>
			<label for="timbre-2">Timbre:</label><select id="timbre-2">{% include_relative instrument.html %}</select>
		</td>
		<td>
			<label for="pitch-2">Pitch: </label><input id="pitch-2" value="1" size="3">
		</td>
		<td>
			<label for="ref-2">Reference: </label><select id="ref-2">{% include_relative reference-pitch.html %}</select>
		</td>
	</tr>
	<tr>
		<td>
			<span class="heading">Part 3:</span>
		</td>
		<td>
			<label for="cycle-3">Cycle size: </label><input id="cycle-3" value="0" size="3">
		</td>
		<td>
			<label for="timbre-3">Timbre:</label><select id="timbre-3">{% include_relative instrument.html %}</select>
		</td>
		<td>
			<label for="pitch-3">Pitch: </label><input id="pitch-3" value="1" size="3">
		</td>
		<td>
			<label for="ref-3">Reference: </label><select id="ref-3">{% include_relative reference-pitch.html %}</select>
		</td>
	</tr>
	<tr>
		<td>
			<span class="heading">Part 4:</span>
		</td>
		<td>
			<label for="cycle-4">Cycle size: </label><input id="cycle-4" value="0" size="3">
		</td>
		<td>
			<label for="timbre-4">Timbre:</label><select id="timbre-4">{% include_relative instrument.html %}</select>
		</td>
		<td>
			<label for="pitch-4">Pitch: </label><input id="pitch-4" value="1" size="3">
		</td>
		<td>
			<label for="ref-4">Reference: </label><select id="ref-4">{% include_relative reference-pitch.html %}</select>
		</td>
	</tr>
	<tr>
		<td>
			<span class="heading">Part 5:</span>
		</td>
		<td>
			<label for="cycle-5">Cycle size: </label><input id="cycle-5" value="0" size="3">
		</td>
		<td>
			<label for="timbre-5">Timbre:</label><select id="timbre-5">{% include_relative instrument.html %}</select>
		</td>
		<td>
			<label for="pitch-5">Pitch: </label><input id="pitch-5" value="1" size="3">
		</td>
		<td>
			<label for="ref-5">Reference: </label><select id="ref-5">{% include_relative reference-pitch.html %}</select>
		</td>
	</tr>
</table>

<nobr><label for="tempo">Tempo: </label><input id="tempo" size="3" value="60"></nobr> <nobr><label for="repeats">Cycle repetitions: </label><input id="repeats" size="3" value="10"></nobr>


{% include ratioscore.html id="polyrhythm" height="600px" erase="false" %}
<script type="application/x-ratioscore" id="polyrhythm">
</script>


