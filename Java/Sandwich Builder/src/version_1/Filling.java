package version_1;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Filling {
	private Map<String, Double> fillingTypes = new HashMap<>();
	private List<String> fillingKeys = new ArrayList<>();
	
	public Filling() {
		fillingTypes.put("Black Forest Ham", 1.00);
		fillingTypes.put("Oven Roasted Chicken", 1.00);
		fillingTypes.put("Roast Beef", 1.00);
		fillingTypes.put("Rotisserie-Style Chicken", 1.00);
		fillingTypes.put("Turkey Breast", 1.00);
		fillingTypes.put("Teriyaki Chicken", 1.00);
		
		fillingKeys.addAll(fillingTypes.keySet());
	}
	
	public List<String> getAllFillings() {
		return fillingKeys;
	}
	
	public double getPrice(String key) {
		return fillingTypes.get(key);
	}
}
