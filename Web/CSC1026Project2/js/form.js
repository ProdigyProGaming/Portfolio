//Add the onsubmit attribute to the form to return the value of the validate function
document.getElementById("form").setAttribute("onSubmit", "return validate();");

//The validate function
function validate() {
    //Set the regular expression variables for name, email and number
    var namePattern = /^[a-z]+$/i;
    var emailPattern = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/;
    var telNumPattern = /^[0-9]{11}$/;

    //Set the form values to variables
    var name = document.forms["form"]["username"].value;
    var email = document.forms["form"]["email"].value;
    var telNum = document.forms["form"]["tel"].value;
    var query = document.forms["form"]["query"].value;

    //If the name is not blank and follows the expression
    if (name !== "" && namePattern.test(name)) {
        //If the email is not blank and follows the expression
        if (email !== "" && emailPattern.test(email)) {
            //If the name follows the expression (telephone not required)
            if (telNumPattern.test(telNum)) {
                //If the query is not blank (doesnt need to follow expression)
                if (query !== "") {
                    //Tell the user it is working
                    alert("Submitting");
                    //Return true
                    return true;
                }
                //If the query is blank
                else {
                    //Give the user a prompt
                    alert("Query can not be blank");
                    //Return false
                    return false;
                }
            }
            //If the telephone does not follow the expression
            else {
                //Give the user a prompt
                alert("Telephone number is not valid");
                //Return false
                return false;
            }
        }
        //If the email does not follow the expression
        else {
            //Give the user a prompt
            alert("Email is not valid");
            //Return false
            return false;
        }
    }
    //If the name does not follow the expression
    else {
        //Give the user a prompt
        alert("Name is not valid");
        //Return false
        return false;
    }
}
