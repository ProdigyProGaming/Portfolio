//Author: Arron Rawstron
//Date: 11/12/18
//Program Purpose: Build sandwich and total the cost
//Class Purpose: Store map and list of selected object and have get/set methods for it

package version_6;
//Import Array List, Hash Map and List from java.util to allow these to be used
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;

public class Ingredients {
	//Declare map, list and variable with scope of ingredients class
	private LinkedHashMap<String, double[]> Types = new LinkedHashMap<String, double[]>();
	private List<String> Keys = new ArrayList<>();
	private int amount = 0;
	
	//Getter and setter for fields
	public LinkedHashMap<String, double[]> getTypes() {
		return Types;
	}
	
	public void setTypes(LinkedHashMap<String, double[]> types) {
		Types = types;
	}
	
	public double getValue(int requiredValue, int selectedBread) {
		//Gets the value from the array in the hash map value
		//from the hash map that corresponds to the selected item from the list
		return (getTypes().get(getKeys().get(selectedBread))[requiredValue]);
	}
	
	public List<String> getKeys() {
		return Keys;
	}
	
	public void setKeys(List<String> keys) {
		Keys = keys;
	}
	
	public String getName(int index) {
		return getKeys().get(index);
	}
	
	public int getAmount() {
		return amount;
	}

	public void setAmount(int amount) {
		this.amount = amount;
	}
}
