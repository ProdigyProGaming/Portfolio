package version_4;

import java.util.Scanner;

public class SandwichBuild {
	private Sandwich objSandwich = new Sandwich();
	
	public void selecter(int ingredType) {
		Getter objG = new Getter();
		
		Scanner in = new Scanner(System.in);
		int counter = 1;
		
		System.out.println("Please type the ingredient number you wish to select");
		
		for (String s:(((Ingredients) objG.getObj(ingredType)).getList())) {
			System.out.format("%s - %-30s - £%.2f %n", counter, s, ((Ingredients) objG.getObj(ingredType)).getValue(0, counter-1));
			counter++;
		}
		System.out.print("Ingredient Number: ");
		int userSelection = in.nextInt();
		System.out.println("Done");
		objSandwich.addIngredient(ingredType, userSelection);
		
	}
	
	public void display() {
		objSandwich.printer();
	}
}
