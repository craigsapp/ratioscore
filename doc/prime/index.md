---
title: "Prime-limit intervals"
permalink: /prime/index.html
layout: default
vim: ts=12:ft=html
---

{% include_relative styles-local.html %}
{% include_relative scripts-local.html %}

This page lists intervals where the ratios contain prime factors 7 and
less for intervals an octave or less.


<nobr><label for="reference">Reference&nbsp;pitch:&nbsp;</label>{% include_relative reference-pitch.html %}</nobr>
<nobr><label for="instrument">Instrument:</label>{% include_relative instrument.html %}</nobr>

<h2 data-sidebar="2-limit"> 2 prime-limit intervals </h2>

{% include ratioscore.html id="f2" tabsize="12" %}
<script type="application/x-ratioscore" id="f2">
!! prime factors of 2 only
**dtime	**ratio	**ratio	**cents
*MM60	*Iclars	*Iclars	*
*	*ref:C4	*ref:C4	*
1	1	1	0c
1	1	2	1200.00c
*-	*-	*-	*-
</script>

<h2 data-sidebar="3-limit"> 3-prime limit intervals </h2>

{% include ratioscore.html id="f23" tabsize="12" %}
<script type="application/x-ratioscore" id="f23">

!! prime factors of 2 and 3 only
**dtime	**ratio	**ratio	**expanded	**cents	**name
*MM60	*Iclars	*Iclars	*	*	*
*	*ref:C4	*ref:C4	*	*	*
1	1	2^8  : 3^5	256/243	90.22c	m2
1	1	3^2  : 2^3	9/8	203.91c	M2
1	1	2^5  : 3^3	32/27	294.14c	m3
1	1	3^4  : 2^6	81/64	407.82c	M3
1	1	2^2  : 3	4/3	498.05c	P5
1	1	2^10 : 3^6	1024/729	588.27c	d5
1	1	3^6  : 2^9	729/512	611.73c	A4
1	1	3    : 2	3/2	701.96c	P5
1	1	2^7  : 3^4	128/81	792.18c	m6
1	1	3^3  : 2^4	27/16	905.87c	M6
1	1	2^4  : 3^2	16/9	996.09c	m7
1	1	3^5  : 2^7	243/128	1109.78c	M7
*-	*-	*-	*-	*-	*-

</script>

<h2 data-sidebar="5-limit"> 5-prime limit intervals </h2>

{% include ratioscore.html id="f25" tabsize="12" %}
<script type="application/x-ratioscore" id="f25">
!! prime factors of 2 and 5 only

**dtime	**ratio	**ratio	**expanded	**cents
*MM60	*Iclars	*Iclars	*	*
*	*ref:C4	*ref:C4	*	*
1	1	2^7 : 5^3	128/125	41.06c
1	1	5   : 2^2	5/4	386.31c
1	1	2^5 : 5^2	32/25	427.37c
1	1	5^2 : 2^4	25/16	772.63c
1	1	2^3 : 5	8/5	813.69c
*-	*-	*-	*-	*-

</script>


{% include ratioscore.html id="f35" tabsize="12" %}
<script type="application/x-ratioscore" id="f35">
!! prime factors of 3 and 5 only

**dtime	**ratio	**ratio	**expanded	**cents
*MM60	*Iclars	*Iclars	*	*
*	*ref:C4	*ref:C4	*	*
1	1	3^3 : 5^2	27/25	133.24c
1	1	5   : 3	5/3	884.36c
1	1	3^2 : 5	9/5	1017.60c
*-	*-	*-	*-	*-

</script>

{% include ratioscore.html id="f235" tabsize="16" %}
<script type="application/x-ratioscore" id="f235">
!! prime factors of 2, 3 and 5 only
**dtime	**ratio	**ratio	**expanded	**cents
*MM60	*Iclars	*Iclars	*	*
*	*ref:C4	*ref:C4	*	*
1	1	3^4     : 2^4*5	81/80	21.51c
1	1	5^2     : 2^3*3	25/24	70.67c
1	1	3^3*5   : 2^7	135/128	92.18c
1	1	2^4     : 3*5	16/15	111.73c
1	1	2^5*5^2 : 3^6	800/729	160.90c
1	1	2*5     : 3*3	10/9	182.40c
1	1	3*5^2   : 2^6	75/64	274.58c
1	1	2*3     : 5	8/5	315.64c
1	1	2^2*5^2 : 3^4	100/12	364.81c
1	1	3^3     : 2^2*5	9/20	519.55c
1	1	5^2     : 2*3^2	25/18	568.72c
1	1	3^2*5   : 2^5	45/32	590.22c
1	1	2^6     : 3^2*5	64/45	609.78c
1	1	2^2*3^2 : 5^2	36/25	631.28c
1	1	2^3*5   : 3^3	40/27	680.45c
1	1	3^4     : 2*5^2	81/50	835.19c
1	1	2^7     : 3*5^2	128/75	925.42c
1	1	2*5^2   : 3^3	50/27	1066.76c
1	1	3*5     : 2^3	15/8	1088.27c
1	1	2^4*3   : 5^2	48/25	1129.33c
1	1	2^5*5   : 3^4	160/81	1178.49c
*-	*-	*-	*-	*-

</script>


<h2 data-sidebar="7-limit"> 7-prime limit intervals </h2>

{% include ratioscore.html id="f27" tabsize="12" %}
<script type="application/x-ratioscore" id="f27">
!! prime factors of 2 and 7 only
**dtime	**ratio	**ratio	**cents
*MM60	*Iclars	*Iclars	*
*	*ref:C4	*ref:C4	*
1	1	2^3 : 7	231.17c
1	1	2^6 : 7^2	462.35c
1	1	7^2 : 2^5	737.65c
1	1	7   : 2^2	968.83c
*-	*-	*-	*-
</script>


{% include ratioscore.html id="f37" tabsize="12" %}
<script type="application/x-ratioscore" id="f37">
!! prime factors of 3 and 7 only
**dtime	**ratio	**ratio	**cents
*MM60	*Iclars	*Iclars	*
*	*ref:C4	*ref:C4	*
1	1	3^2 : 7	435.08c
1	1	3^4 : 7^2	870.17c
1	1	7^2 : 3^3	1031.79c
*-	*-	*-	*-
</script>


{% include ratioscore.html id="f57" tabsize="12" %}
<script type="application/x-ratioscore" id="f57">
!! prime factors of 5 and 7 only
**dtime	**ratio	**ratio	**cents
*MM60	*Iclars	*Iclars	*
*	*ref:C4	*ref:C4	*
1	1	7   : 5	582.51c
1	1	7^2 : 5^2	1165.02c
*-	*-	*-	*-
</script>


{% include ratioscore.html id="f237" tabsize="18" %}
<script type="application/x-ratioscore" id="f237">
!! prime factors of 2, 3 and 7 only
**dtime	**ratio	**ratio	**cents
*MM60	*Iclars	*Iclars	*
*	*ref:C4	*ref:C4	*
1	1	2^6     : 3^2*7	27.26c
1	1	7^2     : 2^4*3	35.70c
1	1	2^2*7   : 3^3	62.96c
1	1	2*3^3   : 7^2	168.21c
1	1	2^8     : 3^2*5^2	223.46c
1	1	7       : 2*3	266.87c
1	1	2*7^2   : 3^4	329.83c
1	1	3*7     : 2^4	470.78c
1	1	7^2     : 2^2*3^2	533.74c
1	1	2^4*7   : 3^4	561.01c
1	1	3^4     : 2^3*7	638.99c
1	1	2^3*3^2 : 7^2	666.26c
1	1	2^5     : 3*7	729.22c
1	1	2*7     : 3^2	764.92c
1	1	2^2*3   : 7	933.13c
1	1	3^3     : 2*7	1137.04c
1	1	2^5*3   : 7^2	1164.30c
1	1	3^2*7   : 2^5	1172.74c
*-	*-	*-	*-
</script>


{% include ratioscore.html id="f257" tabsize="16" %}
<script type="application/x-ratioscore" id="f257">
!! prime factors of 2, 5, and 7 only
**dtime	**ratio	**ratio	**cents
*MM60	*Iclars	*Iclars	*
*	*ref:C4	*ref:C4	*
1	1	2*5^2 : 7^2	34.98c
1	1	5*7   : 2^5	155.14c
1	1	2^2*7 : 5^2	196.20c
1	1	7^2   : 2^3*5	351.34c
1	1	2*5   : 7	617.49c
1	1	2^4*5 : 7^2	848.66c
1	1	5^2   : 2*7	1003.80c
1	1	2^6   : 5*7	1044.86c
*-	*-	*-	*-
</script>


{% include ratioscore.html id="f357" tabsize="16" %}
<script type="application/x-ratioscore" id="f357">
!! prime factors of 3, 5, and 7 only
**dtime	**ratio	**ratio	**cents
*MM60	*Iclars	*Iclars	*
*	*ref:C4	*ref:C4	*
1	1	7^2   : 3^2*5	147.43c
1	1	5^2   : 3*7	301.85c
1	1	5*7   : 3^3	449.28c
1	1	3*5^2 : 7^2	736.93c
*-	*-	*-	*-
</script>


{% include ratioscore.html id="f2357" tabsize="16" %}
<script type="application/x-ratioscore" id="f2357">
!! prime factors of 2, 3, 5 and 7 only
**dtime	**ratio	**ratio	**cents
*MM60	*Iclars	*Iclars	*
*	*ref:C4	*ref:C4	*
1	1	2^2*3^2 : 5*7	48.77c
1	1	3*7     : 2^2*5	84.47c
1	1	3*5     : 2*7	119.44c
1	1	3^4     : 2*5*7	252.68c
1	1	2^2*3*5 : 7^2	350.62c
1	1	2^3*7   : 3^2*5	378.60c
1	1	3^2*7   : 2*5^2	400.11c
1	1	2^4*5   : 3^2*7	413.58c
1	1	2*7^2   : 3*5^2	463.07c
1	1	3*5^2   : 2^3*7	505.76c
1	1	2^4*3   : 5*7	546.82c
1	1	5*7     : 2^3*3	653.19c
1	1	2^4*7   : 3*5^2	694.24c
1	1	2*3^3   : 5*7	750.73c
1	1	3^2*7   : 2^3*5	786.42c
1	1	2^2*5^2 : 3^2*7	799.89c
1	1	3^2*5   : 2^2*7	821.40c
1	1	7^2     : 2*3*5	849.38c
1	1	2*3*7   : 5^2	898.15c
1	1	2^2*5*7 : 3^4	947.32c
1	1	2*3^2*5 : 7^2	1052.57c
1	1	2^2*7   : 3*5	1080.56c
1	1	2^3*5   : 3*7	1115.53c
1	1	5*7     : 2*3^2	1151.23c
*-	*-	*-	*-
</script>


References:

<ul>
<li> <a name="_blank" href="https://en.wikipedia.org/wiki/Limit_(music)#Prime_limit">Prime limit</a> entry on Wikipedia.</li>
</ul>


