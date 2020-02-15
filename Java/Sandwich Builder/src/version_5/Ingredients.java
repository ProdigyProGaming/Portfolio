package version_5;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;

public class Ingredients {
	private LinkedHashMap<String, double[]> Types = new LinkedHashMap<String, double[]>();
	private List<String> Keys = new ArrayList<>();
	
	public List<String> getList() {
		return getKeys();
	}
	
	public String getName(int index) {
		return getKeys().get(index);
	}
	
	public double getValue(int requiredValue, int selectedBread) {
		return (getTypes().get(getKeys().get(selectedBread))[requiredValue]);
	}

	public LinkedHashMap<String, double[]> getTypes() {
		return Types;
	}

	public void setTypes(LinkedHashMap<String, double[]> types) {
		Types = types;
	}

	public List<String> getKeys() {
		return Keys;
	}

	public void setKeys(List<String> keys) {
		Keys = keys;
	}
}
