package version_2;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedHashMap;


public class Filling {
	private LinkedHashMap<String, double[]> fillingTypes = new LinkedHashMap<String, double[]>();
	private List<String> fillingKeys = new ArrayList<>();
	
	public Filling() {
		//double[] - Price, Vegetarian, NutFree
		fillingTypes.put("Black Forest Ham", new double[] 			{1.50, 0.0, 1.0});
		fillingTypes.put("Poached Egg", new double[] 				{1.30, 1.0, 1.0});
		fillingTypes.put("Tuna", new double[] 						{1.20, 1.0, 1.0});
		fillingTypes.put("Rotisserie-Style Chicken", new double[] 	{1.80, 0.0, 1.0});
		fillingTypes.put("Veggie Patty", new double[] 				{1.95, 1.0, 1.0});
		fillingTypes.put("Teriyaki Chicken", new double[] 			{1.70, 0.0, 1.0});
		
		fillingKeys.addAll(fillingTypes.keySet());
	}
	
	public List<String> getFillingList() {
		return fillingKeys;
	}
	
	public String getFillingName(int index) {
		return fillingKeys.get(index);
	}
	
	public double getValue(int requiredValue, int selectedFilling) {
		return (fillingTypes.get(fillingKeys.get(selectedFilling))[requiredValue]);
	}
}
