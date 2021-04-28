---
title: "Score generator"
permalink: /generator/index.html
layout: page
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
</nobr><nobr>Time increment: <input id="timeval" value="1"></nobr><nobr>Tempo: <input id="tempo" value="120"></nobr><nobr>Ratio spines: <select id="spines">
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

<span class="link" onclick="copyUrl(); alert('Link copied to clipboard');">copy page link with settings</span>
{% include ratioscore.html id="generated" %}
<script type="application/x-ratioscore" id="generated">
</script>



<h2 class="ignore"> Spreadsheet editing </h2>

It may be convenient to edit a Ratioscore in a spreadsheet program
such as <a target="_blank" href="https://sheets.google.com">Google
Sheets</a>.  To do so, copy the text from a Ratioscore box and then
paste into a spreadsheet.  A score can be copied from an edit box by
either clicking on the copy button underneath a Ratioscore editor, or
by the standard method for the computer's OS (such as clicking in the edit
box and then typing control|command-a to select all of the text, then 
control|command-c to copy the text, and then control|command-v after clicking 
in a cell on the spreadsheet.

Here is an example view after pasting a Ratioscore into Google Sheets:

<a target="_blank" href="/doc/generator/spreadsheet.jpg"><img src="/doc/generator/spreadsheet.jpg" style="display:block; margin-left:auto; margin-right:auto; width:50%;"></a>

The Ratioscore can then be edited in the spreadsheet and then copied
back into a Ratioscore box on this website to create a MIDI or MP3 file
for the score.

Note that barlines (cells starting with `=`) are difficult to work with
in a spreadsheet.  you can add a single quote before the `=` sign to make
it display properly in a spreadsheet.





