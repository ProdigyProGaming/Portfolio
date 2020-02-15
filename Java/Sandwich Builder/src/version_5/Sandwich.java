package version_5;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;

public class Sandwich {
	private LinkedHashMap<String, Double> fullSandwich = new LinkedHashMap<String, Double>();
	private List<String> sandwichKeys = new ArrayList<>();
	private boolean vegetarian = true;
	private boolean nutFree = true;
	
	public void addIngredient(Ingredients obj, int selection) {
		String ingredName = (obj.getName(selection-1));
		double ingredPrice = (obj.getValue(0, selection-1));
		fullSandwich.put(ingredName, ingredPrice);
		sandwichKeys.add(ingredName);
		
		if (obj.getValue(1, selection-1) == 0) {
			vegetarian = false;
		}
		if (obj.getValue(2, selection-1) == 0) {
			nutFree = false;
		}		
	}
	
	public void printer() {
		double sum = 0;
		for (int i = 0; i < 50; i++) {
			System.out.print("-");
		}
		
		System.out.println("\nThis is your sandwich: ");
		for (int counter = 0; counter < sandwichKeys.size(); counter++) {
			System.out.format("%-30s - £%.2f %n", sandwichKeys.get(counter), fullSandwich.get(sandwichKeys.get(counter)));
			
			sum += fullSandwich.get(sandwichKeys.get(counter));
		}
		System.out.println("Your sandwich is " + ((vegetarian) ? "" : "not ") + "vegetarian.");
		System.out.println("Your sandwich is " + ((nutFree) ? "" : "not ") + "nut free.");
		for (int i = 0; i < 50; i++) {
			System.out.print("-");
		}
		System.out.println("");
		System.out.format("Your total cost without tax comes to:    £%.2f %n", sum);
		System.out.format("Your total cost with tax comes to:       £%.2f %n", sum * 1.2);
		
	}
}
