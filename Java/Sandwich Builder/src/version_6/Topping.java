//Author: Arron Rawstron
//Date: 11/12/18
//Program Purpose: Build sandwich and total the cost
//Class Purpose: Add topping types and properties to hash map and list

package version_6;
//Topping class extends ingredients with methods in
public class Topping extends Ingredients{
	//Constructor to add all topping items to hash map and keys to list
	public Topping() {
		//double[] - Price, Vegetarian, NutFree
		getTypes().put("Teriyaki Glaze", new double[] 			{0.60, 1.0, 1.0});
		getTypes().put("Tomato Sauce", new double[] 				{0.50, 1.0, 1.0});
		getTypes().put("Marinara Sauce", new double[]				{0.85, 1.0, 1.0});
		getTypes().put("Parmesan Cheese", new double[] 			{0.80, 1.0, 1.0});
		getTypes().put("Grated Cheddar Cheese", new double[] 		{0.80, 1.0, 1.0});
		getTypes().put("Grated American Cheese", new double[] 	{0.85, 1.0, 1.0});
		
		getKeys().addAll(getTypes().keySet());
		
		setAmount(getKeys().size());
	}
}
