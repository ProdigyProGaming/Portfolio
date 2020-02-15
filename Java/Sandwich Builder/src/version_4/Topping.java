package version_4;

public class Topping extends Ingredients{
	public Topping() {
		//double[] - Price, Vegetarian, NutFree
		getTypes().put("Teriyaki Glaze", new double[] 			{0.60, 1.0, 1.0});
		getTypes().put("Tomato Sauce", new double[] 				{0.50, 1.0, 1.0});
		getTypes().put("Marinara Sauce", new double[]				{0.85, 1.0, 1.0});
		getTypes().put("Parmesan Cheese", new double[] 			{0.80, 1.0, 1.0});
		getTypes().put("Grated Cheddar Cheese", new double[] 		{0.80, 1.0, 1.0});
		getTypes().put("Grated American Cheese", new double[] 	{0.85, 1.0, 1.0});
		
		getKeys().addAll(getTypes().keySet());
	}
}
