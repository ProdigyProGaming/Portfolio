package version_4;

public class Getter {
	public Object getObj(int var) {
		Object[] arr = new Object[3];
		arr[0] = new Bread();
		arr[1] = new Filling();
		arr[2] = new Topping();
		
		if (var == 1) {
			return arr[0];
		}
		else if (var == 2) {
			return arr[1];
		}
		else {
			return arr[2];
		}
	}
}
