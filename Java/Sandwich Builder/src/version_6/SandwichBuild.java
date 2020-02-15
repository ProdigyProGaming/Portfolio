//Author: Arron Rawstron
//Date: 11/12/18
//Program Purpose: Build sandwich and total the cost
//Class Purpose: Selects the ingredient, adds it to the sandwich and contains a looper to validate user input

package version_6;

public class SandwichBuild {
	//Selector method that takes the desired object and the sandwich object to ensure the sandwich is consistent
	public void selecter(Ingredients obj, Sandwich objS) {
		//Declare variables with scope of the selector method
		int counter = 1;
		int userSelection = -1;
		String question = "Please type the ingredient number you wish to select: ";
		//Loops through all the elements in the keys list to output each option for the user
		for (String s: obj.getKeys()) {
			//Displays the options with price, and properties (vegetarian, nutfree)
			System.out.format("%s - %-30s - £%.2f - %-1s - %-1s %n", counter, s, obj.getValue(0, counter-1), obj.getValue(1, counter-1) == 1? "V":"", obj.getValue(2, counter-1) == 1? "N":"");
			counter++;
		}
		//Call validator method and pass the minimum, maximum and the message for this specific input
		userSelection = validator(1, (obj.getAmount())-1, question);
		
		objS.addIngredient(obj, userSelection);
		
	}
	
	public int validator(int min, int max, String text) {
		SandwichChoice objStart = new SandwichChoice();
		int userSelection = -1;
		
		while (userSelection < min || userSelection > max) {
			System.out.print(text);
			userSelection = objStart.tryCheck();
			if (userSelection < min || userSelection > max) {
				System.out.println("That input was not valid. Please try again.");
			}
		}
		return userSelection;
	}
	
	public static void main(String[] args) {
		Sandwich objS = new Sandwich();
		Bread objB = new Bread();
		Filling objF = new Filling();
		Topping objT = new Topping();
		
		objS.addIngredient(objB, 1);
		objS.addIngredient(objF, 3);
		objS.addIngredient(objT, 3);
		objS.addIngredient(objT, 4);
		objS.printer();
	}
}
