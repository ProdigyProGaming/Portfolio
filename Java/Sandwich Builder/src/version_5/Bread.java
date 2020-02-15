package version_5;

public class Bread extends Ingredients{
	public Bread() {
		//double[] - Price, Vegetarian, NutFree
		getTypes().put("9 Grain Wheat bread", new double[] 		{1.00, 1.0, 1.0});
		getTypes().put("Flat bread", new double[] 				{1.20, 1.0, 1.0});
		getTypes().put("Hearty Italian bread", new double[] 	{1.20, 1.0, 1.0});
		getTypes().put("Honey Oat", new double[] 				{1.30, 1.0, 1.0});
		getTypes().put("Italian Herbs and Cheese", new double[] {1.55, 1.0, 1.0});
		getTypes().put("White bread", new double[] 				{1.00, 1.0, 1.0});
		
		getKeys().addAll(getTypes().keySet());
	}
}
