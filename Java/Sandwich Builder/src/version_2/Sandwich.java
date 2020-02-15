package version_2;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;

public class Sandwich {
	private LinkedHashMap<String, Double> fullSandwich = new LinkedHashMap<String, Double>();
	private List<String> sandwichKeys = new ArrayList<>();
	private boolean vegetarian = true;
	private boolean nutFree = true;
	
	public void addIngredient(int ingredType, int selection) {
		Getter objGetter = new Getter();
		
		fullSandwich.put(objGetter.getName(ingredType, selection-1), objGetter.getValue(ingredType, 0, selection-1));
		sandwichKeys.add(objGetter.getName(ingredType, selection-1));
		
		if (objGetter.getValue(ingredType, 1, selection-1) == 0) {
			vegetarian = false;
		}
		if (objGetter.getValue(ingredType, 2, selection-1) == 0) {
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
		for (int i = 0; i < 50; i++) {
			System.out.print("-");
		}
		System.out.println("");
		System.out.format("Your total cost without tax comes to:    £%.2f %n", sum);
		System.out.format("Your total cost with tax comes to:       £%.2f %n", sum * 1.2);
		System.out.println("Your sandwich is " + ((vegetarian) ? "" : "not ") + "vegetarian.");
		System.out.println("Your sandwich is " + ((nutFree) ? "" : "not ") + "nut free.");
	}
}
