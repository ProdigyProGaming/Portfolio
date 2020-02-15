package version_1;

import java.util.Scanner;

public class SandwichBuilder {
	public void breadSelection() {
		Scanner in = new Scanner(System.in);
		Bread objBreadTypes = new Bread();
		Sandwich objSandwich = new Sandwich();
				
		int breadSelection = 0;
		boolean firstIteration = true;
		
		while ((breadSelection < 1) || (breadSelection > objBreadTypes.getAllBread().size())) {
			if (!firstIteration) {
				System.out.println("That was not a valid input");
			}
			System.out.println("What bread: ");
			int counter = 1;
			for (String s: objBreadTypes.getAllBread()) {
				System.out.format("%-5s %-30s £%.2f \n",counter,  s, objBreadTypes.getPrice(s));
				counter++;
			}
			breadSelection = in.nextInt();
			firstIteration = false;
		}
		
		objSandwich.setFullSandwich();
	}
	
	public static void main(String[] args) {
		SandwichBuilder objBuilder = new SandwichBuilder();
		objBuilder.breadSelection();
	}
}
