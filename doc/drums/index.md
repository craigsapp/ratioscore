---
title: "Ratioscore: drums"
permalink: /doc/drums/index.html
layout: default
vim: ts=8:ft=html
---

One or more `**drum` spines in a Ratioscore will be converted into
drum tracks.  Drum notes are General MIDI key numbers 
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

Unlike ratios, drum tracks can contain multiple notes at one time:

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
!!!filter: myank -m 0,1*24
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


Here are the names of the instruments in a drum track

{% include ratioscore.html id="drum-list" %}
<script type="application/x-ratioscore" id="drum-list">
!!!OTL: General MIDI Drum List
**dtime	**drum	**name
1	35	acoustic bass drum
1	36	electric bass drum
1	37	side stick
1	38	acoustic snare
1	39	hand clap
1	40	electric snare
1	41	low floor tom
1	42	closed hi-hat
1	43	high floor tom
1	44	pedal hi-hat
1	45	low tom
1	46	open hi-hat
1	47	low-mid tom
1	48	hi-mid tom
1	49	crash cymbal 1
1	50	high tom
1	51	ride cymbal 1
1	52	chinese cymbal
1	53	ride bell
1	54	tambourine
1	55	slpash cymbal
1	56	cowbell
1	57	crash cymbal 2
1	58	vibra slap
1	59	ride cymbal 2
1	60	high bongo
1	61	low bongo
1	62	mute high conga
1	63	open high conga
1	64	low conga
1	65	high timbale
1	66	low timbale
1	67	high agogo
1	68	low agogo
1	69	cabasa
1	70	maracas
1	71	short whistle
1	72	long whistle
1	73	short guiro
1	74	long guiro
1	75	claves
1	76	high woodblock
1	77	low woodblock
1	78	mute cuica
1	79	open cuica
1	80	mute triangle
1	81	open triangle
*-	*-	*-
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
!!!filter: myank -m 0,43,43,43,53,43,43,53,53,43,53,53,53,1
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

See the <a href="/doc/polyrhythm">Polyrhythm generator</a> page.

Drum and ratio tracks may occur in the same score and can
be interleaved in any order.

{% include ratioscore.html id="drum-ratio" %}
<script type="application/x-ratioscore" id="drum-ratio">
!!!filter: myank -m 0,1,2,3,2,1,3,2,2,1,3,1,1,2,3,2,3,2,2,2,1,1,1,1,3
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

