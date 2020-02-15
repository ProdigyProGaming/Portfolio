/**
 * @Purpose: The shape class represents a single shape. DO NOT MODIFY THE
 *           SIGNITURE OF EXISTING METHODS, You may add additional methods if
 *           you wish
 * 
 * @author RYK
 * @since 30/10/2019 
 * extended by @author
 * Modified by Arron Rawstron, 180360194
 **/

public class Shape implements Comparable<Shape> {

	private int sWidth;   // width of the shape
	private int sHeight;  // height of the shape

	/**
	 * A Shape constructor to set the width and height of a shape. 
	 * @param width of a shape
	 * @param height of a shape
	 **/
	public Shape(int width, int height) {

		// Shape width and height should not be greater than the sheet width and height
		if (width > Sheet.SHEET_WIDTH || height > Sheet.SHEET_HEIGHT) {
			throw new IllegalArgumentException("Shape width or height is not valid");
		}

		this.sWidth = width;
		this.sHeight = height;
	}

	/**
	 * @return height of a shape
	 **/
	public int getHeight() {
		return sHeight;
	}

	/**
	 * @return width of a shape
	 */
	public int getWidth() {
		return sWidth;
	}
	
	/**
	 * @return area of a shape
	 */
	public int getArea() {
		return this.getWidth() * this.getHeight();
	}

	public int compareTo(Shape o, int compareType, int order) {
		// You may want to implement this method
		//Create variables to compare
		int val = 0, oVal = 0;
		//If compare type is 1 (compare widths)
		if (compareType == 1) {
			//Set variables to widths
			val = this.getWidth();
			oVal = o.getWidth();
		}
		//If compare type is 2 (compare heights)
		else if (compareType == 2) {
			//Set variables to heights
			val = this.getHeight();
			oVal = o.getHeight();
		}
		//If compare type is 3 (compare areas)
		else if (compareType == 3) {
			//Set variables to areas
			val = this.getWidth() * this.getHeight();
			oVal = o.getWidth() * o.getHeight();
		}
		
		//If order is 1 (low to high)
		if (order == 1) {
			//If the variables are equal return 0
			if (val == oVal) {
				return 0;
			}
			//If this shape is less than given shape
			else if (val < oVal) {
				//Return -1
				return -1;
			}
			//If this shape is greater than given shape
			else {
				//Return 1
				return 1;
			}
		}
		//If order is 1 (high to low)
		else if (order == 2) {
			//If the variables are equal return 0
			if (val == oVal) {
				//Return 0
				return 0;
			}
			//If given shape is less than this shape
			else if (val > oVal) {
				//Return -1
				return -1;
			}
			//If given shape is greater than this shape
			else {
				//Return 1
				return 1;
			}
		}
		//Otherwise return 0 (shouldn't happen)
		return 0;
	}

	@Override
	public int compareTo(Shape o) {
		// TODO Auto-generated method stub
		return 0;
	}
}
