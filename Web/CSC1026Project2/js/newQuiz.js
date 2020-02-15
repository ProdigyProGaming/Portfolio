//set variables for counter, card element and max number of cards (so it can be used with different numbers of questions)
var i;
var element = document.getElementById("questionContainer");
var max = element.children.length;
//For each of the questions (except the first one), set the display to none (if the javascript fails to run, all will be displayed instead of none)
for (i = 2; i <= max; i++) {
	document.getElementById(i).style.display = "none";
}

//Create variables for answer buttons
var a1 = document.getElementById("a1");
var a2 = document.getElementById("a2");
var a3 = document.getElementById("a3");
var a4 = document.getElementById("a4");
//Create variable for current and answer current (increments by 4 due to 4 answers per question)
var current = 1;
var quizA = 0;

//Call refresh function
refresh();

function refresh() {
	//Set the answer buttons to the array elements
    a1.innerHTML = array2[quizA];
    a2.innerHTML = array2[quizA+1];
    a3.innerHTML = array2[quizA+2];
    a4.innerHTML = array2[quizA+3];
}

function rightClick() {
	//If the current is not max (not at last question)
    if (current != max) {
		//Set the current question to display none (hide the question to show the other one, only displaying one at a time)
        document.getElementById(current).style.display = "none";
		//Increment current (go right by one question)
        current++;
		//Increment quizA (go right by four answers)
        quizA += 4;
		//Unhide the current card (after incrementing or decrementing)
        document.getElementById(current).style.display = "block";
		//Get the percentage by getting the current -1 dividing by the total and multiplying by 100 (then rounding)
        var percentage = Math.round(((current-1)/max)*100);
		//Set the percentage value in the progress bar to the percentage variable
        document.getElementById("percentage").innerHTML = percentage + "%";
		//Set the width of the progress bar to the percentage
        document.getElementById("innerProgressBar").style.width = percentage + "%";
    }
	//If the current is max (at the last question)
    else if (current == max) {
		//Set variable percentage to 100
        var percentage = 100;
		//Tell the user they got them all right
		alert("You got them all right!");
		//Set the percentage value in the progress bar to the percentage variable
        document.getElementById("percentage").innerHTML = percentage + "%";
		//Set the width of the progress bar to the percentage
        document.getElementById("innerProgressBar").style.width = percentage + "%";
		//Set the colour of the inner progress bar to green
        document.getElementById("innerProgressBar").style.backgroundColor = "#8ded87";
		//Set the display of the buttons to other pages to block (unhide the buttons)
		document.getElementById("newButtonContainer").style.display = "block";
    }
	//Call refresh function
    refresh();
}
//Add event listener to answer buttons
a1.addEventListener("click", function() {
	//If the answer is equal to the button pressed
    if (array[current-1] == "a1") {
		//Give user message
        alert("Correct!");
		//Call right click function to progress to next question
        rightClick();
    }
	//If they did not get the question right
    else {
		//Give user message
        alert("False!");
    }
});
a2.addEventListener("click", function() {
    if (array[current-1] == "a2") {
        alert("Correct!");
        rightClick();
    }
    else {
        alert("False!");
    }
});
a3.addEventListener("click", function() {
    if (array[current-1] == "a3") {
        alert("Correct!");
        rightClick();
    }
    else {
        alert("False!");
    }
});
a4.addEventListener("click", function() {
    if (array[current-1] == "a4") {
        alert("Correct!");
        rightClick();
    }
    else {
        alert("False!");
    }
});
