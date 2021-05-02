---
title: "Drums"
permalink: /drums/index.html
layout: page
vim: ts=8:ft=html
---

One or more `**drum` spines/columns/tracks in a Ratioscore will be
converted into drum tracks.  Drum notes are General MIDI key numbers
ranging from 35 to 81.

{% include ratioscore.html id="drum" %}
<script type="application/x-ratioscore" id="drum">
**dtime	**drum	**drum
*MM120	*	*
*	*	*
1	60	.
0.75	61	.
0.25	62	60
0.25	63	61
2	64	62
1.5	65	63
1	66	64
0.5	67	.
*-	*-	*-
</script>

Unlike ratio tracks, drum tracks can contain multiple notes at one time:

{% include ratioscore.html id="drum-combined" %}
<script type="application/x-ratioscore" id="drum-combined">
**dtime	**drum
*MM120	*
*	*
1	60
0.75	61
0.25	62 60
0.25	63 61
2	64 62
1.5	65 63
1	66 64
0.5	67
*-	*-
</script>

{% include ratioscore.html id="dununba" %}
<script type="application/x-ratioscore" id="dununba">
!!!OTL@@MKU: Dununba
!!!OTL@EN: The dance of the strong men
!!!filter: myank -m 0,1*40
**recip	**drum	**drum	**drum	**drum	**drum	**drum
=0	=0	=0	=0	=0	=0	=0
!	!bell	!djembe	!djembe	!djembe	!dundun	!clave
*	*vel:45	*vel:50	*vel:60	*vel:60	*vel:50	*vel:90
*MM164	*	*	*	*	*	*
*M12/8	*	*	*	*	*	*
=1	=1	=1	=1	=1	=1	=1
8	68V	50V	47V	.	62V	75V
8	.	.	47	.	.	.
8	68	50	.	50	63	75
8	68V	50V	.	.	63V	75V
8	.	47	.	47	.	.
8	68	47	.	50	63	.
8	.	50V	47V	.	.	75V
8	68	.	47	.	63	.
8	68	.	45	50	63	75
8	.	50V	.	.	.	75V
8	68	47	45	47	63	.
8	.	47	.	50	.	.
=	=	=	=	=	=	=
*-	*-	*-	*-	*-	*-	*-
!!!URL: http://africandanceblog.blogspot.com/2011/09/dununba-strong-man-dance.html
</script>


<h2 data-sidebar="Names"> Percussion names </h2>

Here are the names of the instruments in a drum track

{% include ratioscore.html id="drum-list" %}
<script type="application/x-ratioscore" id="drum-list">
!!!OTL: General MIDI Percussion timbre list
**drum	**name
*MM120	*
35	acoustic bass drum
36	electric bass drum
37	side stick
38	acoustic snare
39	hand clap
40	electric snare
41	low floor tom
42	closed hi-hat
43	high floor tom
44	pedal hi-hat
45	low tom
46	open hi-hat
47	low-mid tom
48	hi-mid tom
49	crash cymbal 1
50	high tom
51	ride cymbal 1
52	chinese cymbal
53	ride bell
54	tambourine
55	slpash cymbal
56	cowbell
57	crash cymbal 2
58	vibra slap
59	ride cymbal 2
60	high bongo
61	low bongo
62	mute high conga
63	open high conga
64	low conga
65	high timbale
66	low timbale
67	high agogo
68	low agogo
69	cabasa
70	maracas
71	short whistle
72	long whistle
73	short guiro
74	long guiro
75	claves
76	high woodblock
77	low woodblock
78	mute cuica
79	open cuica
80	mute triangle
81	open triangle
*-	*-
</script>


Below is an example of giving instrument names to the note numbers.
The letters `v` and `V` are deaccent and accent marks respectively.


{% include ratioscore.html id="ocelot-on-the-hunt" tabsize="12" %}
<script type="application/x-ratioscore" id="ocelot-on-the-hunt">
!!!OTL: Ocelot on the Hunt
!!!COM: Sapp, Craig Stuart
!!!ODT: 2021/04/21
!!!RDF**drum: triangle = 81
!!!RDF**drum: clap     = 39
!!!RDF**drum: bongo    = 61
!!!RDF**drum: bell     = 56
!!!RDF**drum: ocelot   = 76
**dtime	**drum	**drum	**drum	**drum
=0	=0	=0	=0	=0
*MM380	*vel:40	*vel:50	*vel:60	*vel:60
=1	=1	=1	=1	=1
1	triangleV	clap	bongo	ocelotV
1	.	.	.	bellv
1	.	.	bongo	ocelotV
1	.	.	.	bellv
=2	=2	=2	=2	=2
1	.	clap	bongo	ocelotV
1	.	.	.	bellv
1	triangleVVV	.	bongoV	ocelotV
1	triangle	.	.	bellv
=3	=3	=3	=3	=3
1	.	clap	bongo	.
1	.	.	.	.
1	triangle	.	.	ocelotv
1	.	.	.	bellV ocelotV
=4	=4	=4	=4	=4
1	.	clap	bongo	bellv
1	trianglev	.	.	.
1	.	.	.	.
1	.	.	.	bellV
=5	=5	=5	=5	=5
1	.	clap	.	bellv ocelotv
1	trianglev	.	bongoV	ocelotV
1	.	.	bongovv	ocelotV
1	.	clap	.	bellv ocelotv
=6	=6	=6	=6	=6
1	.	clap	.	bellV
1	.	.	bongo	.
1	triangleVV	.	bongoV	.
1	.	clap	.	bellv
=7	=7	=7	=7	=7
1	.	clap	.	ocelotV
1	.	.	bongovv	ocelotv
1	.	.	bongoVV	.
1	.	clap	.	bellv ocelotv
=8	=8	=8	=8	=8
1	triangleVV	clapVV	bongoVV	ocelotVV
*MM390	*	*	*	*
*-	*-	*-	*-	*-
!!!filter: myank -m 0,1-7,6-1,1*3,2*4,3*5,4*6,5*7,6*8,7*9,8*3,1,2,1,3,1,4,1,5,1,6,1,7,6,7,5,7,4,7,3,7,2,7,1*8,2*7,3*6,4*5,5*4,6*3,7*2,8*5
</script>



The attack velocity and volume system for ratio spines also applies to 
drums:


{% include ratioscore.html id="drum-vel" %}
<script type="application/x-ratioscore" id="drum-vel">
**recip	**drum
*M3/4	*vel:40
*MM144	*vstep:60
=1	=1
4	77V
4	77
4	77
=2	=2
4	77V
4	77
4	77
=3	=3
4	77V
4	77
4	77
=4	=4
4	77V
4	77
4	77
==	==
*-	*-
</script>

Polyrhythm example:

{% include ratioscore.html id="drum-34" %}
<script type="application/x-ratioscore" id="drum-34">
!!!filter: myank -m 0,43*3,53,43*2,53*2,43,53*3,1
**dtime	**drum	**drum
=0	=0	=0
*MM500	*	*
=43	=43	=43
!! 4 against 3
1	76	77
1	.	.
1	.	.
1	76	.
1	.	77
1	.	.
1	76	.
1	.	.
1	.	77
1	76	.
1	.	.
1	.	.
=53	=53	=53
!! 5 against 3
1	76	77
1	.	.
1	.	.
1	76	.
1	.	.
1	.	77
1	76	.
1	.	.
1	.	.
1	76	.
1	.	77
1	.	.
1	76	.
1	.	.
1	.	.
=1	=1	=1
1	76	77
=	=	=
*-	*-	*-
</script>

See the <a href="/polyrhythm">Polyrhythm generator</a> page.

<h2 data-sidebar="**drum + **ratio"> Mixing pitched and percussive instruments </h2>

Drum and ratio tracks may occur in the same score and can
be interleaved in any order.  Any number of drum tracks can
be present in the score, but ratio tracks are limited to 
15 due to the structure of MIDI.

{% include ratioscore.html id="drum-ratio" %}
<script type="application/x-ratioscore" id="drum-ratio">
!!!filter: myank -m 0,1,2,3,2,1,3,2*2,1,3,1*2,2,3,2,3,2*3,1*4,3
**dtime	**ratio	**drum	**ratio
=0	=0	=0	=0
*MM240	*I#14	*	*Iclars
*	*ref:C2	*	*ref:F#1
*	*vel:60	*vel:50	*vel:30
=1	=1	=1	=1
1	9	77 76	.
1	.	.	9
1	8	.	.
1	.	76	8
1	.	77	.
1	7	.	.
1	.	76	7
1	9	.	.
1	.	77	9
1	.	76	.
1	10	.	.
1	.	.	10
=2	=2	=2	=2
1	.	77	10
1	10	.	8
1	8	.	.
1	.	76	9
1	9	.	.
1	.	77	.
1	.	76	8
1	8	.	.
1	10	.	.
1	.	76	10
1	.	77	9
1	9	.	8
1	.	76	7
1	7	.	.
1	.	.	6
=3	=3	=3	=3
1	1/2	77	3
4	0	.	.
=	=	=	=
*-	*-	*-	*-
</script>

Unlike `**ratio` spines which are limited to 15, any number of `**drum` tracks can be
added to a Ratioscore.  However, since all percussion insturments are played on the same
MIDI channel, independent panning of parallel `**drum` tracks is not possible.

