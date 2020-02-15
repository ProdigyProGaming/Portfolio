package version_1;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Topping {
	private Map<String, Double> toppingTypes = new HashMap<>();
	private List<String> toppingKeys = new ArrayList<>();
	
	public Topping() {
		toppingTypes.put("Grated American Cheese", 1.00);
		toppingTypes.put("Grated Monterey Jack Cheese", 1.00);
		toppingTypes.put("Grated Cheddar Cheese", 1.00);
		
		toppingKeys.addAll(toppingTypes.keySet());
	}
	
	public List<String> getAllFillings() {
		return toppingKeys;
	}
	
	public double getPrice(String key) {
		return toppingTypes.get(key);
	}
}
