package testing;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedHashMap;

public class Filling extends Ingredients{
	public Filling() {
		//double[] - Price, Vegetarian, NutFree
		getTypes().put("Black Forest Ham", new double[] 			{1.50, 0.0, 1.0});
		getTypes().put("Tomato", new double[] 					{0.75, 1.0, 1.0});
		getTypes().put("Meatballs", new double[] 					{1.20, 0.0, 1.0});
		getTypes().put("Rotisserie-Style Chicken", new double[] 	{1.80, 0.0, 1.0});
		getTypes().put("Veggie Patty", new double[] 				{1.95, 1.0, 1.0});
		getTypes().put("Chicken Strips", new double[] 			{1.70, 0.0, 1.0});
		getTypes().put("Cucumber", new double[]					{0.80, 1.0, 1.0});
		getTypes().put("Lettuce", new double[]					{0.80, 1.0, 1.0});
		
		getKeys().addAll(getTypes().keySet());
	}
}
