---
title: "Ratioscore: file structure"
permalink: /doc/structure/index.html
layout: default
vim: ts=8:ft=html
---


<h2> Metadata </h2>

Metadata information can be added to Ratioscores to document
information about the score.  Metadata lines are called "reference records"
and start with three exclamations, then a reference key followed by a colon
and then the reference value.   Here is an example, where the title of the
score is "My Score":

{% include ratioscore.html id="title-example" %}
<script type="application/x-ratioscore" id="title-example">
!!!OTL: My Score
**dtime	**ratio
*	*Iclars
*	*ref:C3
1.5	8
1	7
2	8
*-	*-
</script>


The line:

```
!!!OTL: My Score
```

gives the title, with "OTL" meaning "Opus, TitLe".  Standard reference
records can be found on the <a target="_blank"
href="https://www.humdrum.org/reference-records/index.html">Humdrum
website</a>.  Standard reference record keys are typically three
upper-case letters, so perferrably use lowercase letters for
non-standard records.

Reference records can occur on any line in the score, but typically
important information about the score is given at the start of the
file and less important ones at the end.


<h2> Comments </h2>

Reference records are a special type of comment.  Two types of
free-form comments can also be added to the score. <i>Global
comments</i> are a single line and start with two exclamation marks
at the begnning of the line. <i>Local comments</i> are comments
that apply to specific spines (columns) of data.  Here is an example of
various global and local comments sprinkled around a score:

{% include ratioscore.html id="comment-example" %}
<script type="application/x-ratioscore" id="comment-example">
!!!OTL: My Score
!! comment
**dtime	**ratio
*	*Iclars
*	*ref:C3
!! comment
1.5	8
!	!comment
1	7
!comment	!comment
2	8
!! comment
*-	*-
!! comment
</script>

Notice that local comments require a `!` placeholder on local comment
line where a spine does not include a comment.


<h2> Barlines </h2>

Barlines and time signatures can be added to scores:


{% include ratioscore.html id="barline-example" %}
<script type="application/x-ratioscore" id="barline-example">
**recip	**ratio
*M6/8	*I#68
*	*ref:C2
=1	=1
8	8
8	9
8	10
4	11
8	9
=2	=2
8.	8
16	7
8	9
4.	8
=	=
*-	*-
</script>



