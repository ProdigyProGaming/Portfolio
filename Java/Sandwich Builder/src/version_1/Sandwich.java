package version_1;

import java.util.HashMap;
import java.util.Map;

public class Sandwich {
	
	private Map<String, Double> fullSandwich = new HashMap<>();
	private boolean vegetarian = true;
	private boolean nutFree = true;
	
	public void setFullSandwich() {
		//fullSandwich.put(arg0, arg1)
	}
	
	public void addIngredient(String name, double price) {
		fullSandwich.put(name, price);
	}
	
	public void printer() {
		for(String k:fullSandwich.keySet()) {
			System.out.format("%s%n", k);
		}
		for(double l:fullSandwich.values()) {
			System.out.format("£%.2f%n", l);
		}
	}
	
	public static void main(String[] args) {
		Sandwich objSW = new Sandwich();
		
		Bread objBread = new Bread();
		double breadPrice = objBread.getPrice("White Bread");
		objSW.addIngredient("White Bread", breadPrice);
		
		Filling objFilling = new Filling();
		double fillingPrice = objFilling.getPrice("Black Forest Ham");
		objSW.addIngredient("Black Forest Ham", fillingPrice);
		
		Topping objTopping = new Topping();
		double toppingPrice = objTopping.getPrice("Grated Cheddar Cheese");
		objSW.addIngredient("Grated Cheddar Cheese", toppingPrice);
		
		objSW.printer();
	}
}
