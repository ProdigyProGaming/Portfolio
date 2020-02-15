//Author: Arron Rawstron
//Date: 11/12/18
//Program Purpose: Build sandwich and total the cost
//Class Purpose: Give user options for the type of sandwich

package version_6;
//Import Exception and Scanner from java.util to allow these to be used
import java.util.InputMismatchException;
import java.util.Scanner;

public class SandwichChoice {
	//Method to be called for integer input to check for integer being input from user
	public int tryCheck() {
		//Declare scanner and variables with scope of tryCheck method
		Scanner in = new Scanner(System.in);
		int input = -1;
		boolean check = true;
		//While loop to loop until check variable is false (the input was valid)
		while (check) {
			//Try block
			try {
				//Take integer input
				input = in.nextInt();
				//If this runs without throwing an exception, break the loop by making check false
				check = false;
			}
			//Catch if input is not an integer
			catch (InputMismatchException e) {
				//Print message and take next line to "refresh" scanner
				System.out.print("That is not a valid input. Please try again: ");
				in.nextLine();
			}
		}
		//Return valid input to caller
		return input;
	}
	//Method to be called to start the program from the beginning
	public void start() {
		//Create object to be used in start method
		SandwichBuild objSB = new SandwichBuild();
		Sandwich objS = new Sandwich();
		SandwichMenu objSM = new SandwichMenu();
		Bread objB = new Bread();
		Filling objF = new Filling();
		Topping objT = new Topping();
		
		//Declare variables with scope of start method
		int sandwichOption = 0;
		int fillingAmount = -1;
		int toppingAmount = -1;
		
		//While loop to continue if the users input was not 1 or 2
		while (sandwichOption != 1 && sandwichOption != 2) {
			//Print the users options
			System.out.println("Would you like to build your own sandwich or select a premade one? \n" + 
							   "1 - Build your own \n" + 
					 		   "2 - Select premade one");
			//Take input through the tryCheck method
			sandwichOption = tryCheck();
			//If the user selected the first option (custom sandwich)
			if (sandwichOption == 1) {
				//Print the users options
				System.out.println("You are now able to build your sandwich. \n" + 
								   "You are allowed: \n" + 
								   "1 type of bread, \n" +
								   "up to 5 fillings \n" +
								   "and up to 3 toppings.\n" +
								   "v - Vegetarian\nn - Nutfree \n\n" +
								   "First is bread: ");
				//Call selector method and pass the object of ingredient type and the sandwich object
				objSB.selecter(objB, objS);
				//Call validator method and pass the minimum, maximum and the message for this specific input
				fillingAmount = objSB.validator(0, 5, "How many fillings would you like: ");
				//Loop the number of time the user specified (0-5) 
				for (int i = 0; i < fillingAmount; i++) {
					//Call selector method and pass the object of ingredient type and the sandwich object
					objSB.selecter(objF, objS);
				}
				//Call validator method and pass the minimum, maximum and the message for this specific input
				toppingAmount = objSB.validator(0, 3, "How many toppings would you like: ");
				//Loop the number of time the user specified (0-5) 
				for (int i = 0; i < toppingAmount; i++) {
					//Call selector method and pass the object of ingredient type and the sandwich object
					objSB.selecter(objT, objS);
				}
				//Call printer method to display entire report
				objS.printer();
			}
			//If the user selected the second option (pre-made sandwich)
			else if (sandwichOption == 2) {
				//Call menu method to handle the pre made sandwich input
				objSM.menu();
			}
			//If the users input was not 1 or 2
			else {
				//Display message to user
				System.out.println("That input was not valid. Please try again.");
			}
		}
	}
	//Main method to start program
	public static void main(String[] args) {
		//Create object of beginning class
		SandwichChoice objMain = new SandwichChoice();
		//Call start method to begin the program
		objMain.start();
	}
}
