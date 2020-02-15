package version_2;

import java.util.Scanner;

public class SandwichBuild {
	private Sandwich objSandwich = new Sandwich();
	private Getter objGetter = new Getter();
	
	
	public void selecter(int ingredType) {
		Scanner in = new Scanner(System.in);
		int counter = 1;
		
		for (String s:objGetter.getList(ingredType)) {
			System.out.format("%s - %-30s - £%.2f %n", counter, s, objGetter.getValue(ingredType, 0, counter-1));
			counter++;
		}
		
		System.out.print("Please type the ingredient number you wish to select: ");
		int userSelection = in.nextInt();
		objSandwich.addIngredient(ingredType, userSelection);
	}
	
	public void display() {
		objSandwich.printer();
	}
	
	public static void main(String[] args) {
		SandwichBuild objSB = new SandwichBuild();
		objSB.selecter(1);
		objSB.selecter(2);
		objSB.selecter(2);
		objSB.selecter(3);
		objSB.selecter(3);

		objSB.display();
	}
}
