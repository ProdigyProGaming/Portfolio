//set variables for counter, card element and max number of cards (so it can be used with different numbers of cards)
var i;
var element = document.getElementById("card");
var max = element.children.length;

//For each of the cards, set the display to none (if the javascript fails to run, all will be displayed instead of none)
for (i = 1; i <= max; i++) {
	document.getElementById(i).style.display = "none";
}

//Create variables for left and right buttons
var left = document.getElementById("left");
var right = document.getElementById("right");

//Create variables for path name and get the last part of the pathname to get the file name
var url = window.location.pathname;
var filename = url.substring(url.lastIndexOf('/')+1);
var current;
var currentType;
//If the file name is the HTML card document
if (filename == "learnHTML.html") {
	//Set the current type to htmlCurrent (storing the location of whcih card the user is up to)
	//Seperate to ensure the css cards has a different marker
	currentType = "htmlCurrent";
}
else {
	//Set the current type to cssCurrent
	currentType = "cssCurrent";
}

//Function to check if IE or Edge is being used (IE and Edge doesnt support local storage using file: protocol)
//Code edited from https://jsfiddle.net/alvaroAV/svvz7tkn/
function isIE() {
	//Create var for userAgent
	userAg = navigator.userAgent;
	//Create var to store return of index of strings
	var is_ie = userAg.indexOf("MSIE ") > -1 || userAg.indexOf("Trident/") > -1 || userAg.indexOf("Edge") > -1;
	//return result
	return is_ie;
}
//If the browser is IE or Edge, dont use local storage, just set current to 1 each time
if (isIE()) {
	current = 1;
}
//If the browser is not IE or Edge, use local storage
else {
	//If there is no value stored in the marker
	if (localStorage.getItem(currentType) === null) {
		//Set current to start of the cards
		current = 1;
	}
	//If there is already a value of where the user is
	else {
		//Set the current to that value
		current = localStorage.getItem(currentType);
	}
}


//Call the update function
update();

//Add an event listener for a click to the left button
left.addEventListener("click", function(){
	//If the current is not 1 (not at first card)
    if (current != 1) {
		//Set the current card to display none (hide the card to show the other one, only displaying one at a time)
        document.getElementById(current).style.display = "none";
		//Decrement current (go left by one card)
        current--;
		//Call the update function
        update();
    }
	//Store the current in local storage
	localStorage.setItem(currentType, current);
});

//Add an event listener for a click to the right button
right.addEventListener("click", function(){
	//If the current is not max (not at last card)
    if (current != max) {
		//Set the current card to display none (hide the card to show the other one, only displaying one at a time)
        document.getElementById(current).style.display = "none";
		//Increment current (go right by one card)
        current++;
		//Call the update function
		update();
    }
	//Store the current in local storage
	localStorage.setItem(currentType, current);
});

function update() {
	//If the current is max (at the last card)
	if (current == max) {
		//Set variable percentage to 100
		var percentage = 100;
		//Set the colour of the inner progress bar to green
		document.getElementById("innerProgressBar").style.backgroundColor = "#8ded87";
		//Set the display of the buttons to other pages to block (unhide the buttons)
		document.getElementById("newButtonContainer").style.display = "block";
	}
	//If the current is not at the last card
	else {
		//Get the percentage by getting the current -1 dividing by the total and multiplying by 100 (then rounding)
		var percentage = Math.round(((current-1)/max)*100);
		//Set the colour of the inner progress bar to grey
		document.getElementById("innerProgressBar").style.backgroundColor = "Gray";
	}
	//Unhide the current card (after incrementing or decrementing)
	document.getElementById(current).style.display = "block";
	//Set the percentage value in the progress bar to the percentage variable
	document.getElementById("percentage").innerHTML = percentage + "%";
	//Set the width of the progress bar to the percentage
	document.getElementById("innerProgressBar").style.width = percentage + "%";
}
