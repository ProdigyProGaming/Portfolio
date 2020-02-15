package version_2;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedHashMap;


public class Topping {
	private LinkedHashMap<String, double[]> toppingTypes = new LinkedHashMap<String, double[]>();
	private List<String> toppingKeys = new ArrayList<>();
	
	public Topping() {
		//double[] - Price, Vegetarian, NutFree
		toppingTypes.put("Barbecue Sauce", new double[] 			{0.50, 1.0, 1.0});
		toppingTypes.put("Tomato Sauce", new double[] 				{0.50, 1.0, 1.0});
		toppingTypes.put("HP Sauce", new double[] 					{0.50, 1.0, 1.0});
		toppingTypes.put("Grated Cheddar Cheese", new double[] 		{0.80, 1.0, 1.0});
		toppingTypes.put("Grated Monterey Jack Cheese", new double[]{0.85, 1.0, 1.0});
		toppingTypes.put("Grated American Cheese", new double[] 	{0.85, 1.0, 1.0});
		
		toppingKeys.addAll(toppingTypes.keySet());
	}
	
	public List<String> getToppingList() {
		return toppingKeys;
	}
	
	public String getToppingName(int index) {
		return toppingKeys.get(index);
	}
	
	public double getValue(int requiredValue, int selectedFilling) {
		return (toppingTypes.get(toppingKeys.get(selectedFilling))[requiredValue]);
	}
}
