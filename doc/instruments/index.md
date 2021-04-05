---
title: "Ratioscore: instruments"
permalink: /doc/instruments/index.html
layout: default
vim: ts=3:ft=html
---

{% include_relative style-local.html %}

Instruments for each ratio column can be specified either as <a
target="_blank"
href="https://en.wikipedia.org/wiki/General_MIDI#Program_change_events">General
MIDI instrument numbers</a> (starting from 0 for grand piano), or
as <a target="_blank"
href="https://www.humdrum.org/instrument-codes/index.html">Humdrum
instrument codes</a>.


<h2> General MIDI instrument numbers </h2>

Here is a list of General MIDI instruments that can be used in Ratioscores:


<ul>

	<li>
		<div class="heading">Keyboards</div>
		<table class="octet">
			<tr><td>0</td><td>Acoustic grand piano</td></tr>
			<tr><td>1</td><td>Bright acoustic piano</td></tr>
			<tr><td>2</td><td>Electric grand piano</td></tr>
			<tr><td>3</td><td>Honky-tonk piano</td></tr>
			<tr><td>4</td><td>Electric piano 1</td></tr>
			<tr><td>5</td><td>Electric piano 2</td></tr>
			<tr><td>6</td><td>Harpsichord</td></tr>
			<tr><td>7</td><td>Clavi</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Pitched perc.</div>
		<table class="octet">
			<tr><td>8</td><td>Celesta</td></tr>
			<tr><td>9</td><td>Glockenspiel</td></tr>
			<tr><td>10</td><td>Music box</td></tr>
			<tr><td>11</td><td>Vibraphone</td></tr>
			<tr><td>12</td><td>Marimba</td></tr>
			<tr><td>13</td><td>Xylophone</td></tr>
			<tr><td>14</td><td>Tubular bells</td></tr>
			<tr><td>15</td><td>Dulcimer</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Organs</div>
		<table class="octet">
			<tr><td>16</td><td>Drawbar organ</td></tr>
			<tr><td>17</td><td>Percussive organ</td></tr>
			<tr><td>18</td><td>Rock organ</td></tr>
			<tr><td>19</td><td>Pipe organ</td></tr>
			<tr><td>20</td><td>Reed organ</td></tr>
			<tr><td>21</td><td>Accordion</td></tr>
			<tr><td>22</td><td>Harmonica</td></tr>
			<tr><td>23</td><td>Tango Accordion</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Guitars</div>
		<table class="octet">
			<tr><td>24</td><td>Nylon acoustic guitar</td></tr>
			<tr><td>25</td><td>Steel acoustic guitar</td></tr>
			<tr><td>26</td><td>Jazz electric guitar</td></tr>
			<tr><td>27</td><td>Clean electric guitar</td></tr>
			<tr><td>28</td><td>Muted eletric guitar</td></tr>
			<tr><td>29</td><td>Overdriven guitar</td></tr>
			<tr><td>30</td><td>Distortion guitar</td></tr>
			<tr><td>31</td><td>Guitar harmonics</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Bass</div>
		<table class="octet">
			<tr><td>32</td><td>Acoustic bass</td></tr>
			<tr><td>33</td><td>Fingered electric bass</td></tr>
			<tr><td>34</td><td>Picked electric bass</td></tr>
			<tr><td>35</td><td>Fretless bass</td></tr>
			<tr><td>36</td><td>Slap bass 1</td></tr>
			<tr><td>37</td><td>Slap bass 2</td></tr>
			<tr><td>38</td><td>Synth bass 1</td></tr>
			<tr><td>39</td><td>Synth bass 2</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Strings</div>
		<table class="octet">
			<tr><td>40</td><td>Violin</td></tr>
			<tr><td>41</td><td>Viola</td></tr>
			<tr><td>42</td><td>Cello</td></tr>
			<tr><td>43</td><td>Contrabass</td></tr>
			<tr><td>44</td><td>Tremolo strings</td></tr>
			<tr><td>45</td><td>Pizzicato strings</td></tr>
			<tr><td>46</td><td>Orchestral harp</td></tr>
			<tr><td>47</td><td>Timpani</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Ensemble</div>
		<table class="octet">
			<tr><td>48</td><td>String ensemble 1</td></tr>
			<tr><td>49</td><td>String ensemble 2</td></tr>
			<tr><td>50</td><td>Synth strings 1</td></tr>
			<tr><td>51</td><td>Synth strings 2</td></tr>
			<tr><td>52</td><td>Choir aahs</td></tr>
			<tr><td>53</td><td>Choir oohs</td></tr>
			<tr><td>54</td><td>Synth voice</td></tr>
			<tr><td>55</td><td>Orchestra hit</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Brass</div>
		<table class="octet">
			<tr><td>56</td><td>Trumpet</td></tr>
			<tr><td>57</td><td>Trombone</td></tr>
			<tr><td>58</td><td>Tuba</td></tr>
			<tr><td>59</td><td>Muted trumpet</td></tr>
			<tr><td>60</td><td>French horn</td></tr>
			<tr><td>61</td><td>Brass section</td></tr>
			<tr><td>62</td><td>Synth brass 1</td></tr>
			<tr><td>63</td><td>Synth brass 2</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Reeds</div>
		<table class="octet">
			<tr><td>64</td><td>Soprano sax</td></tr>
			<tr><td>65</td><td>Alto sax</td></tr>
			<tr><td>66</td><td>Tenor sax</td></tr>
			<tr><td>67</td><td>Baritone sax</td></tr>
			<tr><td>68</td><td>Oboe</td></tr>
			<tr><td>69</td><td>English horn</td></tr>
			<tr><td>70</td><td>Bassoon</td></tr>
			<tr><td>71</td><td>Clarinet</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Pipes</div>
		<table class="octet">
			<tr><td>72</td><td>Piccolo</td></tr>
			<tr><td>73</td><td>Flute</td></tr>
			<tr><td>74</td><td>Recorder</td></tr>
			<tr><td>75</td><td>Pan flute</td></tr>
			<tr><td>76</td><td>Blown bottle</td></tr>
			<tr><td>77</td><td>Shakuhachi</td></tr>
			<tr><td>78</td><td>Whistle</td></tr>
			<tr><td>79</td><td>Ocarina</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Leads</div>
		<table class="octet">
			<tr><td>80</td><td>Square lead</td></tr>
			<tr><td>81</td><td>Sawtooth lead</td></tr>
			<tr><td>82</td><td>Calliope lead</td></tr>
			<tr><td>83</td><td>Chiff lead</td></tr>
			<tr><td>84</td><td>Charang lead</td></tr>
			<tr><td>85</td><td>Voice lead</td></tr>
			<tr><td>86</td><td>Fifths lead</td></tr>
			<tr><td>87</td><td>Base + lead</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Pads</div>
		<table class="octet">
			<tr><td>88</td><td>New age pad</td></tr>
			<tr><td>89</td><td>Warm pad</td></tr>
			<tr><td>90</td><td>Polysynth pad</td></tr>
			<tr><td>91</td><td>Choir pad</td></tr>
			<tr><td>92</td><td>Bowed pad</td></tr>
			<tr><td>93</td><td>Metallic pad</td></tr>
			<tr><td>94</td><td>Halo pad</td></tr>
			<tr><td>95</td><td>Sweep pad</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Effects</div>
		<table class="octet">
			<tr><td>96</td><td>Rain</td></tr>
			<tr><td>97</td><td>Soundtrack</td></tr>
			<tr><td>98</td><td>Cystal</td></tr>
			<tr><td>99</td><td>Atmosphere</td></tr>
			<tr><td>100</td><td>Brightness</td></tr>
			<tr><td>101</td><td>Goblins</td></tr>
			<tr><td>102</td><td>Echoes</td></tr>
			<tr><td>103</td><td>Sci-fi</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Ethnic</div>
		<table class="octet">
			<tr><td>104</td><td>Sitar</td></tr>
			<tr><td>105</td><td>Banjo</td></tr>
			<tr><td>106</td><td>Shamisen</td></tr>
			<tr><td>107</td><td>Koto</td></tr>
			<tr><td>108</td><td>Kalimba</td></tr>
			<tr><td>109</td><td>Bagpipe</td></tr>
			<tr><td>110</td><td>Fiddle</td></tr>
			<tr><td>111</td><td>Shanai</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Percussive</div>
		<table class="octet">
			<tr><td>112</td><td>Tinkle bell</td></tr>
			<tr><td>113</td><td>Agogo</td></tr>
			<tr><td>114</td><td>Steel drums</td></tr>
			<tr><td>115</td><td>Woodblock</td></tr>
			<tr><td>116</td><td>Taiko drum</td></tr>
			<tr><td>117</td><td>Melodic tom</td></tr>
			<tr><td>118</td><td>Synth drum</td></tr>
			<tr><td>119</td><td>Reverse cymbal</td></tr>
		</table>
	</li>

	<li>
		<div class="heading">Sound effects</div>
		<table class="octet">
			<tr><td>120</td><td>Guitar fret noise</td></tr>
			<tr><td>121</td><td>Breath noise</td></tr>
			<tr><td>122</td><td>Seashore</td></tr>
			<tr><td>123</td><td>Bird tweet</td></tr>
			<tr><td>124</td><td>Telephone ring</td></tr>
			<tr><td>125</td><td>Helicopter</td></tr>
			<tr><td>126</td><td>Applause</td></tr>
			<tr><td>127</td><td>Gunshot</td></tr>
		</table>
	</li>

</ul>

The instrument number 14 in the following example is prefixed with the 
text `*I#`.  Try changing the instrument number to another one in the
above list of General MIDI instruments.

{% include ratioscore.html id="gm-instrument" %}
<script type="application/x-ratioscore" id="gm-instrument">
**time	**ratio	**ratio
*	*I#14	*I#14
*	*ref:G3	*ref:G2
0	1	.
0.5	.	3/2
1	8/3	.
2	11/4	11/5
4	1	14/3
*-	*-	*-
</script>


<h2 style="margin-top:90px; margin-bottom:50px;"> Instrument codes </h2>



{% include ratioscore.html id="humdrum-instrument" %}
<script type="application/x-ratioscore" id="humdrum-instrument">
**time	**ratio	**ratio
*	*Ivioln	*Iclars
*	*ref:G3	*ref:G2
0	1	.
0.5	.	3/2
1	8/3	.
2	11/4	11/5
4	1	14/3
*-	*-	*-
</script>




