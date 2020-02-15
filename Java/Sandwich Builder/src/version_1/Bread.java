package version_1;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Bread {
	private Map<String, Double> breadTypes = new HashMap<>();
	private List<String> breadKeys = new ArrayList<>();
	
	public Bread() {
		breadTypes.put("9 Grain Wheat bread", 1.00);
		breadTypes.put("Flat Bread", 1.00);
		breadTypes.put("Hearty Italian", 1.00);
		breadTypes.put("Honey Oat", 1.00);
		breadTypes.put("Italian Herbs and Cheese", 1.00);
		breadTypes.put("White Bread", 1.00);
		
		breadKeys.addAll(breadTypes.keySet());
	}
	
	public List<String> getAllBread() {
		return breadKeys;
	}
	
	public double getPrice(String key) {
		return breadTypes.get(key);
	}
}
