/**
 * @Purpose: The Sheet class represents a sheet with a list of shelves.
 * DO NOT MODIFY THE EXISTING METHODS SIGNITURE, You may add additional methods if you wish
 * 
 * @author  RYK 
 * @since   30/10/2019
 * extended by @author 
 * Modified by Arron Rawstron, 180360194
 */
import java.util.ArrayList;
import java.util.List;

public class Sheet {

	public static final int SHEET_HEIGHT = 250; // sheet height

	public static final int SHEET_WIDTH = 300; // sheet width

	public static final int SHAPE_LIMIT = 20; // maximum number of shapes that can be placed in each sheet (rule F)

	private List<Shelf> shelves = new ArrayList<Shelf>(); // list of shelves

	/**
	 * empty constructor
	 */
	public Sheet() {
	}

	/**
	 * This method is used to add a shelf to a sheet
	 * @param a shelf
	 */
	public void addShelf(Shelf shelf) {
		shelves.add(shelf);
	}

	/**
	 * @return height of all shelves in a sheet
	 */
	public int allShelvesHeight() {

		int total = 0;

		for (Shelf shelf : this.shelves) {

			// has a shelf with at least 1 shape
			if (!shelf.getShapes().isEmpty()) {

				// add all shelf height to total
				total += shelf.getHeight();
			}
		}
		return total;
	}
	
	/**
	 * @return list of all shelves in a sheet
	 */
	public List<Shelf> getShelves() {
		return this.shelves;
	}

	/**
	 * @return height
	 */
	public int getHeight() {
		return SHEET_HEIGHT;
	}

	/**
	 * @return width
	 */
	public int getWidth() {
		return SHEET_WIDTH ;
	}
	
	/**
	 * @return shape limit
	 */
	public int getShapeLimit() {
		return SHAPE_LIMIT ;
	}
	
	public void displaySheet() {
		//Create variable to store shapes total
		int shapesTotal = 0;
		for (Shelf shelf : shelves) {
			shapesTotal += shelf.getShapes().size();
		}
		//Display headers
		System.out.println("  ---------- NEW SHEET ----------");
		System.out.printf ("   ----- Total Shapes: %3d ----- \n", shapesTotal);
		System.out.printf ("   -- All Shelves Height: %3d -- \n\n", allShelvesHeight());
		//For each of the shelves in the shelves list
		for (Shelf shelf : shelves) {
			//Display headers
			System.out.println("    -------- New Shelf --------  ");
			System.out.printf ("     --- Shelf Height: %3d ---   \n", shelf.getHeight());
			System.out.printf ("      --- Used Width: %3d ---    \n", shelf.getWidth());
			
			System.out.println("       - Shape__  w  x  h ");
			//Create list of shapes from the current shelf
			List<Shape> shapes = shelf.getShapes();
			//For each of the shapes in the current shelf
			for (int i = 0; i < shapes.size(); i++) {
				//Print the shape number, width and height
				System.out.printf("       - Shape%2d %3d x %3d \n", i+1, shapes.get(i).getWidth(), shapes.get(i).getHeight());
			}
			//Display footer
			System.out.println("    -------- End Shelf --------  \n");
		}
		//Display footer
		System.out.println("  ---------- END SHEET ----------\n");
	}
}
