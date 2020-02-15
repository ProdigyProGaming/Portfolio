import java.util.ArrayList;
import java.util.List;
/**
 * @Purpose: The SortedTest class is used to compare the implemented algorithms
 *           in term of the number of sheets used WHEN the list of
 *           shapes is SORTED
 *
 *           You can add additional methods if you need to in this class
 * 
 * @author RYK
 * @since 30/10/2019
 * extended by @author
 * Modified by Arron Rawstron, 180360194
 */

public class SortedTest {
	
	static int unsorted = 0;
	static int widthLH = 0;
	static int widthHL = 0;
	static int heightLH = 0;
	static int heightHL = 0;
	static int areaLH = 0;
	static int areaHL = 0;
	
	public static int partition(List<Shape> shapes, int left, int right, int compareType, int order) {
		Shape v = shapes.get(right);
		int pointerL = left;
		int pointerR = right;
		
		while (pointerL < pointerR) {
			while (shapes.get(pointerL).compareTo(v, compareType, order) < 0) {
				pointerL++;
			}
			while (shapes.get(pointerR).compareTo(v, compareType, order) >= 0 && pointerR > left) {
				pointerR--;
			}
			if (pointerL < pointerR) {
				Shape temp = shapes.get(pointerL);
				shapes.set(pointerL, shapes.get(pointerR));
				shapes.set(pointerR, temp);
			}
		}
		Shape temp = shapes.get(pointerL);
		shapes.set(pointerL, shapes.get(right));
		shapes.set(right, temp);
		
		return pointerL;
	}
	
	public static void quicksort(List<Shape> shapes, int L, int R, int compareType, int order) {
		if (R > L) {
			int p = partition(shapes, L, R, compareType, order);
			quicksort(shapes, L, p-1, compareType, order);
			quicksort(shapes, p+1, R, compareType, order);
		}
	}
	
	public static void main(String[] args) {
		System.out.println("*********************************************");
		System.out.println("**************** Sorted Test ****************");
		System.out.println("*********************************************");
		System.out.println();

		/*
		 * Generate a random shape list and then check the number of sheets used
		 * when
		 ** this shape list is passed un-sorted
		 ** the list is sorted based on different criteria as set in the speciication document.
		 * 
		 * run several tests for different sizes of the "list of shapes" 
		 */

		/*
		 * HINT: you might want to implements the comparTo method in the Shape
		 * class or implement the Comparator Interface to do the sorting
		 */
		
		//Total number of tests
		int noOfTests = 5;
		//Number of shapes for first run
		int noOfShapes = 10000;
		//How many to increment each test
		int increment = 10000;
		
		//If next fit is being run or not (if not, then first fit)
		boolean nextFit = true;
		
		
		//Display header
		System.out.println("+-------------------------------------------------------------------------+");
		System.out.println("|                                 Next Fit                                |");
		System.out.println("+--------------+----------+---------------+---------------+---------------+");
		System.out.println("| No of Shapes | Unsorted |     Width     |     Height    |      Area     |");
		System.out.println("|              |          |  L-H  |  H-L  |  L-H  |  H-L  |  L-H  |  H-L  |");
		System.out.println("+--------------+----------+-------+-------+-------+-------+---------------+");
		
		//Counter to track number of tests run
		int counter = 0;
		//For each of the tests
		for (int i = 0; i < noOfTests; i++) {
			
			//Call sortingTypes to sort in specific ways and set values
			sortingTypes(noOfShapes, nextFit);
			//Display values in tabulated format
			System.out.printf("| %12d | %8d | %5d | %5d | %5d | %5d | %5d | %5d |\n", noOfShapes, unsorted, widthLH, widthHL, heightLH, heightHL, areaLH, areaHL);
			//Increment noOfShapes by increment
			noOfShapes += increment;
			//Increment counter
			counter++;
			//If counter is noOfTests (noOfTests tests have been run means next fit is finished)
			if (counter == noOfTests) {
				//Set nextFit to false, no longer running next fit
				nextFit = false;
				//Set i to -1 (for look will ++ to 0)
				i = -1;
				//Reset number of shapes
				noOfShapes = 10000;
				//Display header for first fit
				System.out.println("+--------------+----------+-------+-------+-------+-------+---------------+\n");
				System.out.println("+-------------------------------------------------------------------------+");
				System.out.println("|                                First Fit                                |");
				System.out.println("+--------------+----------+---------------+---------------+---------------+");
				System.out.println("| No of Shapes | Unsorted |     Width     |     Height    |      Area     |");
				System.out.println("|              |          |  L-H  |  H-L  |  L-H  |  H-L  |  L-H  |  H-L  |");
				System.out.println("+--------------+----------+-------+-------+-------+-------+---------------+");
			}
		}
		//Display footer
		System.out.println("+--------------+----------+-------+-------+-------+-------+---------------+");
		
		
		
	}
	public static void sortingTypes(int noOfShapes, boolean nextFit) {
		//Create algorithm object
		Algorithms a1 = new Algorithms();
		//Create generator and generate 10000 shapes and store in a list
		Generator g1 = new Generator();
		//Set variables for comparison types and order types
		/*
		 * comp 1 = sort by width
		 * comp 2 = sort by height
		 * comp 3 = sort by area
		 * 
		 * order 1 = low to hight
		 * order 2 = high to low
		 */
		int numberOfCompTypes = 3;
		int numberOfOrderTypes = 2;
		
		//Number of times to repeat the run
		int noOfRep = 5;
		
		//Create sheets1 and set to null
		List<Sheet> sheets1 = null;
		
		//For each of the comparison types
		for (int i = 0; i <= numberOfCompTypes; i++) {
			//For each of the order types
			for (int j = 1; j <= numberOfOrderTypes; j++) {
				//For each of the repetitions
				for (int k = 0; k < noOfRep; k++) {
					//Generate a list of shapes using noOfShapes
					List<Shape> shapes = g1.generateShapeList(noOfShapes);
					//Call quicksort method with shapes, left and right value and current comp type and order if i is not 0 (0 is unsorted)
					if (i != 0) {
						quicksort(shapes, 0, shapes.size() - 1, i, j);
					}
					//Call nextFit or firstFit and store result in sheets1 after sorting
					sheets1 = (nextFit) ? a1.nextFit(shapes) : a1.firstFit(shapes);
					//Switch i
					switch(i) {
					case 0: 
						//If j is 1 (low to high) increment unsorted by size (only one order)
						if (j == 1) {unsorted += sheets1.size();}
						break;
					//If i is 1 (sort by width)
					case 1: 
						//If j is 1 (low to high) increment widthLH by size
						if (j == 1) {widthLH += sheets1.size();}
						//If j is not 1 (high to low) increment widthHL by size
						else {widthHL += sheets1.size();}
						break;
					//If i is 2 (sort by height)
					case 2: 
						//If j is 1 (low to high) increment heightLH by size
						if (j == 1) {heightLH += sheets1.size();}
						//If j is not 1 (high to low) increment heightHL by size
						else {heightHL += sheets1.size();}
						break;
					//If i is 3 (sort by area)
					case 3: 
						//If j is 1 (low to high) increment areaLH by size
						if (j == 1) {areaLH += sheets1.size();}
						//If j is not 1 (high to low) increment areaHL by size
						else {areaHL += sheets1.size();}
						break;
					}
				}
			}
		}
		unsorted = unsorted / noOfRep;
		widthLH = widthLH / noOfRep;
		widthHL = widthHL / noOfRep;
		heightLH = heightLH / noOfRep;
		heightHL = heightHL / noOfRep;
		areaLH = areaLH / noOfRep;
		areaHL = areaHL / noOfRep;
	}
}
