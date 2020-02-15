//Code edited from https://reactgo.com/build-your-own-html-editor/
//Create constant of div with id first
const first = document.querySelector("#first");
//Create constant of iframe type
const iframe = document.querySelector("iframe");

//Function to check if IE or Edge is being used (IE and Edge doesnt support local storage using file: protocol)
//Code found at https://jsfiddle.net/alvaroAV/svvz7tkn/
function isIE() {
	//Create var for userAgent
	userAg = navigator.userAgent;
	//Create var to store return of index of strings
	var is_ie = userAg.indexOf("MSIE ") > -1 || userAg.indexOf("Trident/") > -1 || userAg.indexOf("Edge") > -1;
	//return result
	return is_ie;
}

//If the browser is not IE or Edge (they do not support local storage fully)
if (!(isIE())) {
    //If the local storage for htmlCode is not null
    if (!(localStorage.getItem("htmlCode") === null)) {
        //Set the text for the editor to whatever is stored
        first.innerHTML = localStorage.getItem("htmlCode");
        //Set the content to the variable html
        var html = first.textContent;
        //Set the source of the iframe to the text in html format
        iframe.src = "data:text/html;charset=utf-8," + encodeURI(html);
    }
}


//When there is a keyup in the first box
first.addEventListener('keyup',()=>{
    //Set the content to the variable html
    var html = first.textContent;
    //Set the source of the iframe to the text in html format
    iframe.src = "data:text/html;charset=utf-8," + encodeURI(html);
    //Store the content of the first div to htmlCode
    localStorage.setItem("htmlCode", first.innerHTML);
});

//When the user tries to paste
first.addEventListener("paste", function(e) {
    //Prevent the normal action from happening
    e.preventDefault();
    //Store the data in the clipboard to the variable text
    var text = e.clipboardData.getData("text/plain");
    //Execute the command to insert the text
    document.execCommand("insertText", false, text);
});
