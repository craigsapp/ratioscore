//
// Programmer:     Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date:  Mon Jun 27 04:31:26 PDT 2016
// Last Modified:  Tue Dec 22 20:58:43 PST 2020
// Filename:       drop.js
// Syntax:         JavaScript 1.8/ECMAScript 5
// vim:            ts=3: ft=javascript
//
// Description:   Event listeners for drag/drop of Ratioscore file onto page.
//

var DROPAREA = "";


//////////////////////////////
//
// setupDropArea --
//

function setupDropArea(target) {
   if (!target) {
     console.log("Error: need to set a target element for dropping data");
     DROPAREA = null;
     return;
   }
   var droparea = document.querySelector(target);
   if (!droparea) {
      console.log("Error: cannot find target: ", target);
      DROPAREA = null;
      returnl;
   }

   DROPAREA = droparea;

   window.addEventListener('dragenter', function(event) {
      showDropArea();
   });

   droparea.addEventListener('dragenter', allowDrag);
   droparea.addEventListener('dragover', allowDrag);
   droparea.addEventListener('dragleave', function(event) {
      hideDropArea();
   });
   droparea.addEventListener('drop', handleDrop);
}


//////////////////////////////
//
// showDropArea --
//

function showDropArea(droparea) {
   if (!droparea) {
     droparea = DROPAREA;
   }
   droparea.style.visibility = "visible";
}




//////////////////////////////
//
// hideDropArea --
//

function hideDropArea(droparea) {
   if (!droparea) {
     droparea = DROPAREA;
   }
   droparea.style.visibility = "hidden";
}



//////////////////////////////
//
// allowDrag --
//

function allowDrag(event) {
   if (true) {  // Test that the item being dragged is a valid one
      event.dataTransfer.dropEffect = 'copy';
      event.preventDefault();
   }
}





//////////////////////////////
//
// handleDrop --
//

function handleDrop(event) {
   event.preventDefault();
   document.body.classList.add("waiting");
   hideDropArea();
   var file;
   var files = event.dataTransfer.files;
   for (var i=0; i<files.length; i++) {
      file = files[i];
      // console.log("NAME", escape(file.name));
      // console.log("SIZE", file.size);
      // console.log("DATE", file.lastModifiedDate.toLocaleDateString());

      var reader = new FileReader();

      // reader.readAsDataURL(file); // loads MIME64 version of file
      // reader.readAsBinaryString(file);
      // file has to be read as Text with UTF-8 encoding
      // in order that files with UTF-8 characters are read
      // properly:
      reader.readAsText(file, 'UTF-8');

      var myevent = event;

      reader.onload = function (event) {
         var contents = reader.result;
         if (myevent.shiftKey) {
            replaceEditorContentWithHumdrumFile(contents);
         } else {
            var inputdata = document.querySelector("#inputdata");
            if (inputdata) {
               inputdata.innerText = contents;
            } else {
               console.log("Cannot find #inputdata to store", contents);
            }
         }

         document.body.classList.remove("waiting");
      };

      // Only reading the first file if more than one.
      // Maybe allow multiple files, but then the order
      // might be undefined.  Alternatively allow a method
      // of appending a data file to the end of the text (such
      // as if the control key is held down when drag-and-dropping.
      break;
   }
}


