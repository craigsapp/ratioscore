---
permalink: /index.html
vim: ts=3
---

<div style="height:18px;"></div>

{% include ratioscore.html id="example" tabsize="12" minheight="500px" %}
<script type="application/x-ratioscore" id="example">
**dtime	**ratio
*	*Iclars
*	*ref:G3
1	1
0.75	3
0.5	11/4H
0.5	_11/4
1.25	_5/2h
1.25	0
1	7/2
0.5	4/3
*-	*-
</script>

{% include droparea/main.html %}


<script>


//////////////////////////////
//
// DOMContentloaded event listener -- Restore previous contents of editor
//    when returning.
//

document.addEventListener("DOMContentLoaded", function () {
	let previousContents = localStorage.ratioscore;
	if (previousContents) {
		let element = document.querySelector("#example");
		let element2 = document.querySelector("#inputdata-example");
		if (element) {
			element.textContent = previousContents;
		}
		if (element2) {
			element2.textContent = previousContents;
		}
	}

	// Store the editor contents periodically,
	// but only saving it if the previous contents
	// is different from the current contents.
	let lastcontents = "";
	setInterval(function () {
		let element = document.querySelector("#inputdata-example");
		if (element) {
			let contents = element.textContent;
			if (contents !== lastcontents) {
				localStorage.ratioscore = contents;
			}
			lastcontents = contents;
		}
	}, 1000);

});



</script>



