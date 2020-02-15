/**
 *  @Purpose: The Generator class generates a list of shapes of random width and height.
 * Do NOT modify the names and signatures of the generator method
 * 
 * @author  RYK
 * @since   30/10/2019
 * extended by @author 
 * Modified by Arron Rawstron, 180360194
 */
import java.util.ArrayList;
import java.util.List;

public class Generator {

	public static final int MAX_SIZE_HEIGHT = 250;
	public static final int MAX_SIZE_WIDTH = 300;

	/**
	 * This method will generate a list of shapes of random width and height
	 * (integers). The random width is between 1 and MAX_SIZE_WIDTH inclusive.
	 * The random height is between 1 and MAX_SIZE_HEIGHT inclusive.
	 * 
	 * @param numberOfShapes: the number of shapes to generate
	 * @return a list of shapes of random sizes
	 */

	public List<Shape> generateShapeList(int numberOfShapes) {
		//Create empty list of shapes
		List<Shape> shapes = new ArrayList<Shape>();
		
		/*
		 * THIS METHOD CURRENTLY RETURNS AN EMPTY LIST SO YOU WILL NEED TO ADD
		 * IN YOUR OWN CODE TO GENERATE A LIST OF SHAPES randomly
		 */
		
		//While numberOfShapes hasn't been created
		for (int i = 0; i < numberOfShapes; i++) {
			//Create 2 variables for width and height
			int randomHeight, randomWidth;
			
			//Generate a random integer from 1 to max width
			randomWidth = (int) (Math.random() * ((MAX_SIZE_WIDTH - 1) + 1)) + 1;
			//Generate a random integer from 1 to max height
			randomHeight = (int) (Math.random() * ((MAX_SIZE_HEIGHT - 1) + 1)) + 1;
			
			//Create shape to add using random width and height
			Shape shape = new Shape(randomWidth, randomHeight);
			//Add shape to shape list
			shapes.add(shape);
		}
		//Return list of shapes
		return shapes;
	}

}