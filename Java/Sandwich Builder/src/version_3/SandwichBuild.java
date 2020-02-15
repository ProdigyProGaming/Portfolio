package version_3;

import java.util.Scanner;

public class SandwichBuild {
	private Sandwich objSandwich = new Sandwich();
	
	public void selecter(int ingredType) {
		Getter objGetter = new Getter();
		Scanner in = new Scanner(System.in);
		int counter = 1;
		
		System.out.println("Please type the ingredient number you wish to select");
		
		for (String s:objGetter.getList(ingredType)) {
			System.out.format("%s - %-30s - £%.2f %n", counter, s, objGetter.getValue(ingredType, 0, counter-1));
			counter++;
		}
		System.out.print("Ingredient Number: ");
		int userSelection = in.nextInt();
		objSandwich.addIngredient(ingredType, userSelection);
	}
	
	public void display() {
		objSandwich.printer();
	}
}
