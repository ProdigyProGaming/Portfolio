package version_5;

import java.util.Scanner;

public class MainClass {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		SandwichBuild objSB = new SandwichBuild();
		Sandwich objS = new Sandwich();
		Bread objB = new Bread();
		Filling objF = new Filling();
		Topping objT = new Topping();
		
		int sandwichOption = 0;
		int fillingAmount = -1;
		int toppingAmount = -1;
		int preMadeSandwich = 0;
		
		while (sandwichOption != 1 && sandwichOption != 2) {
			System.out.println("Would you like to build your own sandwich or select a premade one? \n" + 
							   "1 - Build your own \n" + 
					 		   "2 - Select premade one");
			sandwichOption = in.nextInt();
			if (sandwichOption == 1) {
				System.out.println("You are now able to build your sandwich. \n" + 
								   "You are allowed: \n" + 
								   "1 type of bread, \n" +
								   "up to 5 fillings \n" +
								   "and up to 3 toppings.");
				System.out.println("First is bread: ");
				objSB.selecter(objB);
				
				while (fillingAmount < 0 || fillingAmount > 5) {
					System.out.print("How many fillings would you like: ");
					fillingAmount = in.nextInt();
					if (fillingAmount < 0 || fillingAmount > 5) {
						System.out.println("That input was not valid. Please try again.");
					}
				}
				
				for (int i = 0; i < fillingAmount; i++) {
					objSB.selecter(objF);
				}
				
				while (toppingAmount < 0 || toppingAmount > 3) {
					System.out.print("How many toppings would you like: ");
					toppingAmount = in.nextInt();
					if (toppingAmount < 0 || toppingAmount > 3) {
						System.out.println("That input was not valid. Please try again.");
					}
				}
				
				for (int i = 0; i < toppingAmount; i++) {
					objSB.selecter(objT);
				}
				
				objSB.display();
			}
			else if (sandwichOption == 2) {
				
				String[] preMade = new String[] {"Meatball Marinara", "Chicken Teriyaki", "Black Forest Ham"};
				
				for (int counter = 0; counter < preMade.length; counter++) {
					System.out.format("%s - %-30s %n", counter, preMade[counter]);
					counter++;
				}
				
				System.out.println("Please pick a sandwich: \n" +
								   "Meatball Marinara \n" +
								   "Chicken Teriyaki \n" + 
								   "Black Forest Ham");
				
				while (preMadeSandwich < 1 || preMadeSandwich > 3) {
					preMadeSandwich = in.nextInt();
					if (preMadeSandwich == 1) {
						objS.addIngredient(objB, 1);
						objS.addIngredient(objF, 3);
						objS.addIngredient(objT, 3);
						objS.addIngredient(objT, 4);
					}
					else if (preMadeSandwich == 2) {
						objS.addIngredient(objB, 1);
						objS.addIngredient(objF, 2);
						objS.addIngredient(objF, 6);
						objS.addIngredient(objF, 7);
						objS.addIngredient(objF, 8);
						objS.addIngredient(objT, 1);
					}
					else if (preMadeSandwich == 3) {
						objS.addIngredient(objB, 6);
						objS.addIngredient(objF, 1);
						objS.addIngredient(objF, 2);
						objS.addIngredient(objF, 7);
						objS.addIngredient(objF, 8);
					}
					else {
						System.out.println("That input was not valid. Please try again.");
					}
				}
				objS.printer();
			}
			else {
				System.out.println("That input was not valid. Please try again.");
			}
		}
	}
}
