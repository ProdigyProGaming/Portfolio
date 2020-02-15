/**
 * @Purpose: The CorrectnessTest class is used to validate the correctness of
 *           the implemented algorithms. You can add additional methods if you
 *           need
 * 
 * @author RYK
 * @since 30/10/2019 extended by @author
 * Modified by Arron Rawstron, 180360194
 */

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;


public class CorrectnessTest {
	
	//Create static algorithm object to be used in both smallTest and largeTest
	static Algorithms a1 = new Algorithms();
	
	public static void main(String[] args) {
		System.out.println("*********************************************");
		System.out.println("*********** Correctness testing *************");
		System.out.println("*********************************************");
		System.out.println();

		/*
		 * Here you will need to validate that your algorithms (nextFit() and
		 * firstFit()) behave as expected on small data sets. 
		 * Think about normal cases and border cases. 
		 * You can use any additional method you created in this class
		 */
		
		//Run small test
		smallTest();
		//Try to run large test
		try {
			largeTest();
			//Display where the results were displayed
			System.out.println("\nSmall test results printed to console. \n" + 
							   "Large test results printed to src/output.txt");
		}
		//If a file not found exception is caught (shouldn't happen)
		catch (FileNotFoundException e) {
			//Tell the user the file was not found
			System.out.println("FILE NOT FOUND");
			System.out.println("All results printed to console");
		}
	}
	
	public static void smallTest() {
		//Create empty list of shapes
		List<Shape> shapes = new ArrayList<Shape>();
		//Create arrays with width and height of test set of shapes
		int widths[] = {50, 250, 250, 51, 250, 50, 300, 50, 50, 150, 10,  10,  10,  10,  10,  10,  10,  10,  10,  10, 200, 300, 10};
		int heights[] = {50, 50, 50, 50, 10, 11, 29, 50, 100, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 201, 250, 50};
		
		//For each of the items in widths, create a new shape and add it to the list using the same index in widths and heights
		for (int i = 0; i < widths.length; i++) {
			Shape newShape = new Shape(widths[i], heights[i]);
			shapes.add(newShape);
		}
		//Run the algorithms and store results in two lists
		List<Sheet> sheets1 = a1.nextFit(shapes);		
		List<Sheet> sheets2 = a1.firstFit(shapes);
		//Call display method with both results as parameters
		display(sheets1, sheets2);
		
		//Display number of shapes packed and number of sheets used by the two algorithms
		System.out.println("Shapes packed - " + shapes.size());
		System.out.println("Next Fit Sheets Used  - " + sheets1.size());
		System.out.println("First Fit Sheets Used - " + sheets2.size());
	}
	
	public static void largeTest() throws FileNotFoundException {
		//Create a generator
		Generator g1 = new Generator();
		//Generate a list of 1000 shapes and store in list
		List<Shape> shapes = g1.generateShapeList(1000);
		//Set the variable stdout to the current System.out
		PrintStream stdout = System.out;
		
		//Try to set the print stream out to a new file and set the system.out to the file
		try {
			PrintStream out = new PrintStream(new FileOutputStream("src/output.txt"));
			System.setOut(out);
		}
		//If the file is not found (shouldn't happen)
		catch(FileNotFoundException e) {
			//Display message to console that the output will go to the console
			System.out.println("Can not send result to file. Printing results to console...");
			System.out.println("(May not display all due to console length restrictions)");
			System.out.println("PRESS ENTER TO CONTINUE...");
			//Try to get enter press
			try {
				System.in.read();
			}
			//Display exception (shouldn't happen)
			catch(Exception e2) {
				e2.printStackTrace();
			}
		}

		//Run the algorithms and store results in two lists
		List<Sheet> sheets1 = a1.nextFit(shapes);		
		List<Sheet> sheets2 = a1.firstFit(shapes);
		//Call display method with both results as parameters
		display(sheets1, sheets2);
		
		//Set system.out back to original
		System.setOut(stdout);
		//Display number of shapes packed and number of sheets used by the two algorithms
		System.out.println("Shapes packed - " + shapes.size());
		System.out.println("Next Fit Sheets Used  - " + sheets1.size());
		System.out.println("First Fit Sheets Used - " + sheets2.size());
	}
	
	public static void display(List<Sheet> sheets1, List<Sheet> sheets2) {
		//Display headers
		System.out.println("\n\n----------- NEXTFIT -----------");
		System.out.printf(" ------ Sheets Used: %3d ----- \n\n", sheets1.size());
		//For each of the sheets, call the sheets display method
		for (Sheet x : sheets1) {
			x.displaySheet();
		}
		//Display footer
		System.out.println("----------- ENDFIT ------------");
		
		//Display headers
		System.out.println("\n\n----------- FIRSTFIT ----------");
		System.out.printf(" ------ Sheets Used: %3d ----- \n\n", sheets2.size());
		//For each of the sheets, call the sheets display method
		for (Sheet x : sheets2) {
			x.displaySheet();
		}
		//Display footer
		System.out.println("----------- ENDFIT ------------");
	}
}
