package version_3;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedHashMap;

public class Bread{
	private LinkedHashMap<String, double[]> breadTypes = new LinkedHashMap<String, double[]>();
	private List<String> breadKeys = new ArrayList<>();
	
	public Bread() {
		//double[] - Price, Vegetarian, NutFree
		breadTypes.put("9 Grain Wheat bread", new double[] 		{1.00, 1.0, 1.0});
		breadTypes.put("Flat bread", new double[] 				{1.20, 1.0, 1.0});
		breadTypes.put("Hearty Italian bread", new double[] 	{1.20, 1.0, 1.0});
		breadTypes.put("Honey Oat", new double[] 				{1.30, 1.0, 1.0});
		breadTypes.put("Italian Herbs and Cheese", new double[] {1.55, 1.0, 1.0});
		breadTypes.put("White bread", new double[] 				{1.00, 1.0, 1.0});
		
		breadKeys.addAll(breadTypes.keySet());
	}
	
	public List<String> getBreadList() {
		return breadKeys;
	}
	
	public String getBreadName(int index) {
		return breadKeys.get(index);
	}
	
	public double getValue(int requiredValue, int selectedBread) {
		return (breadTypes.get(breadKeys.get(selectedBread))[requiredValue]);
	}
}
