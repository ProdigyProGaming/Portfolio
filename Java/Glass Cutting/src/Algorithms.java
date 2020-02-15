/**
 * @Purpose: The Algorithms class contains the two algorithms you have to implement  
 * Do NOT modify the names and signatures of the two algorithm methods
 * 
 * @author  RYK
 * @since   30/10/2019
 * extended by @author 
 * Modified by Arron Rawstron, 180360194
 **/

import java.util.ArrayList;
import java.util.List;

public class Algorithms {

	/**
	 * This method is used to implement the next fit algorithm
	 * 
	 * @param shapes:a list of shapes representing customer requests(shapes to be
	 *            cut/placed)
	 * @return a list of the sheets used to fulfil all customer requests (i.e.
	 *         place all the shapes). e.g. if you pass a "shapes" list that has
	 *         two shapes {(w=200,h=200),(w=50,h=100)}, then the returned list
	 *         of sheets should show us all the information needed (e.g. that
	 *         one sheet is used, this sheet has one shelf and this shelf has
	 *         two shapes in it). In the test program, you can use the returned
	 *         list to retrieve the total number of sheets used.
	 **/
	
	/*
	 * Checks whether the given shape can fit onto the given shelf of a given sheet
	 * (Allows ability to check if rotated shape will fit without more than 1 encompassing if statement
	 */
	public boolean checkCanAddShape(Shape shapeToCheck, Shelf shelfToCheck, Sheet sheetToCheck) {
		//If the shape is not null (could be null if shape can not be rotated)
		if (shapeToCheck != null) {
			//If the height of the shelf is greater than the height of the shape (shape is short enough to fit)
			if (shelfToCheck.getHeight() >= shapeToCheck.getHeight()) {				
				//If the remaining width on the shelf is greater than the shapes width (shape is thin enough to fit)
				if (sheetToCheck.getWidth() - shelfToCheck.getWidth() >= shapeToCheck.getWidth()) {
					//Return true, the shape can fit
					return true;
				}
			}
		}
		//Return false, the shape can not fit
		return false;
	}

	/*
	 * Adds given shape to new shelf and adds the shelf to new sheet and returns the sheet
	 * Occurs when the shape can not fit anywhere else
	 */
	public Sheet newSheet(Shape shapeToAdd) {
		Sheet newSheet = new Sheet();
		Shelf newShelf = new Shelf();
		newShelf.place(shapeToAdd);
		newSheet.addShelf(newShelf);
		return newSheet;
	}
	
	public List<Sheet> nextFit(List<Shape> shapes) {

		/*
		 * Start with an empty list of sheets (remember each sheet has a width
		 * of 300 and a height of 250 as specified in the Sheet class)
		 */
		List<Sheet> usedSheets = new ArrayList<Sheet>();

		/*
		 * Add in your own code so that the method will place all the shapes
		 * according to NextFit under ALL the assumptions mentioned in the
		 * specification
		 */

		/*
		 * Create counter variables
		 * Sheet count to track which sheet is the current one 
		 * (Starts at -1 to allow if statement to detect and increment to 0 when the first sheet is created)
		 * Shelf count to track which shelf is the current one
		 * Shapes count to track how many shapes are on each sheet
		 */
		int sheetCount = -1;
		int shelfCount = 0;
		int totalShapes = 0;
		
		//Create temporary sheet to get max width and height variables from sheet
		Sheet tempSheet = new Sheet();
		
		//For every shape in given list
		for (Shape currentShape : shapes) {
			
			//Set current sheet to sheet object or null (prevents error getting array index that does not exist)
			Sheet currentSheet = sheetCount != -1 ? usedSheets.get(sheetCount) : null;

			//Set rotated shape object to null to initialise object
			Shape currentShapeRotated = null;
			//Create 3 booleans for if the shape will fit
			boolean shapeOrigWillFit = false, shapeRotWillFit = false, shapeWillFit = false;
			
			//If the rotated shapes new dimensions are larger than the sheets (rotating width of 300 to height is larger than sheets max height of 250)
			if (currentShape.getHeight() <= tempSheet.getWidth() && currentShape.getWidth() <= tempSheet.getHeight()) {
				//Set variable to new shape with current shapes dimension swapped
				currentShapeRotated = new Shape(currentShape.getHeight(), currentShape.getWidth());
			}

			//Initialise variable
			int remainingHeight = 0;
			//If the first sheet exists
			if (sheetCount != -1) {
				//Check if shape and its rotated variant will fit
				shapeOrigWillFit = checkCanAddShape(currentShape, currentSheet.getShelves().get(shelfCount), currentSheet);
				shapeRotWillFit = checkCanAddShape(currentShapeRotated, currentSheet.getShelves().get(shelfCount), currentSheet);
				//OR the results giving one value
				shapeWillFit = shapeOrigWillFit || shapeRotWillFit;
				//Set remaining height to sheets height minus used height of sheet
				remainingHeight = currentSheet.getHeight() - currentSheet.allShelvesHeight();
			}
			
			/*
			 * If the used sheets list is not 0
			 * If the total shapes in the sheet is less than shape limit
			 * If the remaining height is greater than the shape height or shapes width
			 * If the shape will fit
			 */
			if (!(usedSheets.size() == 0 || totalShapes >= currentSheet.getShapeLimit() || ((remainingHeight < currentShape.getHeight() && remainingHeight < currentShape.getWidth()) && !shapeWillFit))) {
				//Set shelves list to list of shelves in sheet
				List<Shelf> shelves = currentSheet.getShelves();
				//If the original orientation fits
				if (shapeOrigWillFit) {
					//Place shape on shelf
					shelves.get(shelfCount).place(currentShape);
				}
				//If the rotated version fits
				else if (shapeRotWillFit) {
					//Place shape on shelf
					shelves.get(shelfCount).place(currentShapeRotated);
				}
				else {
					//Create new shelf and add either the original or rotated shape (Shape must fit due to previous if statement)
					Shelf shelfToAdd = new Shelf();
					shelfToAdd.place(remainingHeight < currentShape.getHeight() ? currentShapeRotated : currentShape);
					currentSheet.addShelf(shelfToAdd);
					//Increase shelf count as new shelf has been added
					shelfCount++;
				}
				//Increment total shapes as shape has been added
				totalShapes++;
			}
			/*
			 * If the sheet list is empty
			 * If the total shapes will breach the shape limit
			 * If there is no room for a new shelf and the shape doesn't fit on the current shelf
			 */
			else {
				//Create new sheet using separate method
				usedSheets.add(newSheet(currentShape));
				//Set shelf count to 0 as it is a new sheet
				shelfCount = 0;
				//Set total shapes to 1 as new shape has been added on new sheet
				totalShapes = 1;
				//Increment sheet count as new sheet has been created
				sheetCount++;
			}
		}
		//Return list of sheets used to store all given shapes using Next Fit algorithm
		return usedSheets;
	}
	
	/**
	 * This method is used to implement the first fit algorithm
	 * 
	 * @param shapes:a list of shapes representing customer requests (shapes to be
	 *            cut/placed)
	 * @return a list of the sheets used to fulfil all customer requests (i.e. place
	 *         all the shapes). e.g. if you pass a "shapes" list that has two
	 *         shapes {(w=200,h=200),(w=50,h=100)}, then the returned list of
	 *         sheets should show us all the information needed (e.g. that one
	 *         sheet is used, this sheet has one shelf and this shelf has two
	 *         shapes in it). In the test program, you can use the returned list
	 *         to retrieve the total number of sheets used
	 **/
	public List<Sheet> firstFit(List<Shape> shapes) {

		/*
		 * Start with an empty list of sheets (remember each sheet has a width
		 * of 300 and a height of 250 as specified in the Sheet class)
		 */
		List<Sheet> usedSheets = new ArrayList<Sheet>();

		/*
		 * Add in your own code so that the method will place all the shapes
		 * according to FirstFit under the assumptions mentioned in the spec
		 */
		
		//Create temporary sheet to get max width and height variables from sheet
		Sheet tempSheet = new Sheet();
		
		//For every shape in given list
		for (Shape currentShape : shapes) {
			/*
			 * Create counter variables which reset to 0 for every shape to check all sheets and shelves
			 * Sheet count to track which sheet is the current one 
			 * (Set to -1 if first sheet hasnt been created, otherwise 0 to start searching all sheets for a place for the shape)
			 * Shelf count to track which shelf is the current one
			 * Shapes count to track how many shapes are on each sheet
			 */
			int sheetCount = (usedSheets.size() == 0 ? -1 : 0);
			int shelfCount = 0;
			int totalShapes = 0;
			
			//Set shape added to false
			boolean shapeAdded = false;
			
			//Set rotated shape object to null to initialise object
			Shape currentShapeRotated = null;
			//Create 3 booleans for if the shape will fit
			boolean shapeOrigWillFit = false, shapeRotWillFit = false, shapeWillFit = false;
			
			//If the rotated shapes new dimensions are larger than the sheets (rotating width of 300 to height is larger than sheets max height of 250)
			if (currentShape.getHeight() <= tempSheet.getWidth() && currentShape.getWidth() <= tempSheet.getHeight()) {
				//Set variable to new shape with current shapes dimension swapped
				currentShapeRotated = new Shape(currentShape.getHeight(), currentShape.getWidth());
			}
			
			//While the shape has not been added
			while (!shapeAdded) {
				//Set current sheet to sheet object or null (prevents error getting array index that does not exist)
				Sheet currentSheet = sheetCount != -1 ? usedSheets.get(sheetCount) : null;
				
				//Create list of all shelves and initialise to null to prevent getting shelves of sheet that does not exist
				List<Shelf> shelves = null;
				//Initialise variable
				int remainingHeight = 0;
				//If the first sheet exists
				if (sheetCount != -1) {
					//Check if shape and its rotated variant will fit
					shapeOrigWillFit = checkCanAddShape(currentShape, currentSheet.getShelves().get(shelfCount), currentSheet);
					shapeRotWillFit = checkCanAddShape(currentShapeRotated, currentSheet.getShelves().get(shelfCount), currentSheet);
					//OR the results giving one value
					shapeWillFit = shapeOrigWillFit || shapeRotWillFit;
					//Set remaining height to sheets height minus used height of sheet
					remainingHeight = currentSheet.getHeight() - currentSheet.allShelvesHeight();
					
					//Get list of all shelves in sheet
					shelves = currentSheet.getShelves();
					//Set total shapes to 0 to reset value
					totalShapes = 0;
					//For every shelf in the sheet
					for (Shelf shelf : shelves) {
						//Count how many shapes are in the shelf giving number of shapes in sheet
						totalShapes += shelf.getShapes().size();
					}
				}
				
				/*
				 * If the used sheets list is not 0
				 * If the total shapes in the sheet is less than shape limit
				 * If the remaining height is greater than the shape height or shapes width
				 * If the shape will fit
				 */
				if (!(usedSheets.size() == 0 || totalShapes >= currentSheet.getShapeLimit() || ((remainingHeight < currentShape.getHeight() && remainingHeight < currentShape.getWidth()) && !shapeWillFit))) {
					//If the original orientation fits
					if (shapeOrigWillFit) {
						//Place shape on shelf
						shelves.get(shelfCount).place(currentShape);
						shapeAdded = true;
					}
					//If the rotated version fits
					else if (shapeRotWillFit) {
						//Place shape on shelf
						shelves.get(shelfCount).place(currentShapeRotated);
						shapeAdded = true;
					}
					else if (shelves.size() <= (shelfCount + 1)) {
						//Create new shelf and add either the original or rotated shape (Shape must fit due to previous if statement)
						Shelf shelfToAdd = new Shelf();
						shelfToAdd.place(remainingHeight < currentShape.getHeight() ? currentShapeRotated : currentShape);
						currentSheet.addShelf(shelfToAdd);
						shapeAdded = true;
					}
					else {
						shelfCount++;
					}				
				}
				/*
				 * If the sheet list is not empty
				 * If total shapes is less than shape limit
				 * If number of shelves is greater than shelf count plus 1 (there are more shelves to check)
				 */
				else if (usedSheets.size() != 0 && totalShapes < currentSheet.getShapeLimit() && shelves.size() > (shelfCount + 1)) {
					//Increment shelf count to check more shelves
					shelfCount++;					
				}
				/*
				 * If the sheet list is not empty
				 * If number of sheets is greater than sheet count plus 1 (there are more sheets to check)
				 */
				else if (usedSheets.size() != 0 && usedSheets.size() > sheetCount + 1) {
					//Increment sheet count and reset shelf count 0 to check all shelves of next sheet
					sheetCount++;
					shelfCount = 0;
				}
				/*
				 * If the sheet list is empty
				 * If the total shapes will breach the shape limit
				 * If none of the existing sheets can take the current shape
				 */
				else {
					//Create new sheet using separate method
					usedSheets.add(newSheet(currentShape));
					//Set shape added to true as shape has been added
					shapeAdded = true;
				}
			}
		}
		//Return list of sheets used to store all given shapes using First Fit algorithm
		return usedSheets;
	}
}
