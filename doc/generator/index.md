---
title: "Ratioscore: Score generator"
permalink: /doc/generator/index.html
layout: default
vim: ts=3:ft=html
---

{% include_relative listeners.html %}
{% include_relative styles-local.html %}
{% include_relative scripts-local.html %}

This page can be used to create a Ratioscore template:

<nobr>
	Timeline:
	<select id="timeline">
		<option value="dtime"> delta time (seconds)         </option>
		<option value="time">  absolute time (seconds)      </option>
		<option value="dms">   delta time (milliseconds)    </option>
		<option value="ms">    absolute time (milliseconds) </option>
		<option value="recip"> musical rhythms              </option>
	</select>
</nobr><nobr>Time value/increment: <input id="timeval" value="1"></nobr><nobr>Tempo: <input id="tempo" value="120"></nobr><nobr>Ratio spines: <select id="spines">
	<option value="1">1</option>
	<option value="2">2</option>
	<option value="3">3</option>
	<option value="4">4</option>
	<option value="5">5</option>
	<option value="6">6</option>
	<option value="7">7</option>
	<option value="8">8</option>
	<option value="9">9</option>
	<option value="10">10</option>
	<option value="11">11</option>
	<option value="12">12</option>
	<option value="13">13</option>
	<option value="14">14</option>
	<option value="15">15</option>
	<option value="16">16</option>
	<option value="17">17</option>
	<option value="18">18</option>
	<option value="19">19</option>
	<option value="20">20</option>
</select></nobr><nobr>Data lines: <input id="lines" value="10"></nobr><nobr>Reference pitch: <input id="reference" value="C4"></nobr><nobr>Instrument: {% include_relative instrument-select.html %}</nobr>

<span class="link" onclick="copyUrl(); alert('Link copied to clipboard');">copy link</span>
{% include ratioscore.html id="generated" tabsize="15" %}
<script type="application/x-ratioscore" id="generated">
</script>

