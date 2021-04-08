---
title: "Ratioscore: glissandos"
permalink: /doc/glissandos/index.html
layout: default
vim: ts=8:ft=html
---

Glissandos are created by adding an `H` to the starting note of the
glissando, and an `h` on the ending note.  The maximum gliss interval
is one octave above/below the starting note of the glissando.  Glissandos
larger than that will not be rendered correctly.

{% include ratioscore.html id="glissando-example" %}
<script type="application/x-ratioscore" id="glissando-example">
**dtime	**ratio
*	*Iclars
*	*ref:C2
2	3/2H
1	4/3
2	3/2h
*-	*-
</script>


Adding an underscore to the note will prevent a glissando
note from reattacking.

{% include ratioscore.html id="sustain-example" %}
<script type="application/x-ratioscore" id="sustain-example">
**dtime	**ratio
*	*Iclars
*	*ref:C2
2	3/2H
1	4/3_
2	3/2_h
*-	*-
</script>


