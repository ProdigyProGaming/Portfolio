package version_3;

import java.util.List;

public class Getter {
	Bread objBread = new Bread();
	Filling objFilling = new Filling();
	Topping objTopping = new Topping();
	
	public List<String> getList(int var) {
		if (var == 1) {
			return objBread.getBreadList();
		}
		else if (var == 2) {
			return objFilling.getFillingList();
		}
		else if (var == 3) {
			return objTopping.getToppingList();
		}
		else {
			return null;
		}
		
	}
	
	public String getName(int var, int index) {
		if (var == 1) {
			return objBread.getBreadName(index);
		}
		else if (var == 2) {
			return objFilling.getFillingName(index);
		}
		else if (var == 3) {
			return objTopping.getToppingName(index);
		}
		else {
			return null;
		}
		
	}
	
	public double getValue(int var, int requiredValue, int selected) {
		if (var == 1) {
			return objBread.getValue(requiredValue, selected);
		}
		else if (var == 2) {
			return objFilling.getValue(requiredValue, selected);
		}
		else if (var == 3) {
			return objTopping.getValue(requiredValue, selected);
		}
		else {
			return 0;
		}
	}
}
