package version_6;

public class SandwichMenu {
	public void menu() {
		SandwichBuild objSB = new SandwichBuild();
		Sandwich objS = new Sandwich();
		Bread objB = new Bread();
		Filling objF = new Filling();
		Topping objT = new Topping();
		int preMadeSandwich = 0;
		
		String[] preMade = new String[] {"Meatball Marinara", "Chicken Teriyaki", "Black Forest Ham"};
		
		for (int counter = 1; counter <= preMade.length; counter++) {
			System.out.format("%s - %-30s %n", counter, preMade[counter-1]);
		}
		
		preMadeSandwich = objSB.validator(1, 3, "Please pick a sandwich: ");
		
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

		objS.printer();
	}
	public static void main(String[] args) {
		SandwichMenu objSM = new SandwichMenu();
		objSM.menu();
	}
}
