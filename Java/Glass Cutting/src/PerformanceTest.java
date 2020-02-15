import java.util.ArrayList;
import java.util.List;

/**
 * @Purpose: The PerformanceTest class is used to compare the implemented
 *           algorithms in term of time and the number of sheets used
 *
 *           You can add additional methods if you need to in this class
 * 
 * @author RYK
 * @since 30/10/2019
 * extended by @author
 * Modified by Arron Rawstron, 180360194
 */

public class PerformanceTest {	
	//Create longs for averages and ints for number of sheets
	static double nextFitAverages = 0;
	static double firstFitAverages = 0;
	
	static int sheets1UsedAverage = 0;
	static int sheets2UsedAverage = 0;
	
	public static void main(String[] args) {

		System.out.println("***********************************************");
		System.out.println("*********** Performance analysis **************");
		System.out.println("**********************************************");

		System.out.println();
		/*
		 * You must complete the Generator class in order to generate a random
		 * test values. You must complete the Algorithms class in order to call
		 * the two algorithms.
		 * 
		 * You can use any additional method you created in this class
		 */

		

		/**
		 * Remember: You need to calculate the time and number of sheets used
		 * for each run of each algorithm.
		 * 
		 * You are expected to run several tests (e.g. noOfTests=5) of your
		 * programs for, 10000, 20000, 30000, 40000, 50000 shapes
		 * (noOfShapes=10000, increment=10000) so that one can see how the
		 * algorithms perform for large datasets.
		 * 
		 * You are expected to run the same test a number of times to ensure
		 * accurate result (noOfRep=4). In this case, you need to calculate the
		 * average time and sheets needed for each run
		 **/
		
		
		//Total number of tests
		int noOfTests = 5;
		//Number of shapes for first run
		int noOfShapes = 10000;
		//How many to increment each test
		int increment = 10000;
		
		//Display header
		System.out.println("+--------------+-----------------------------+-----------------------------+");
		System.out.println("|              |         Next Fit            |          First Fit          |");
		System.out.println("+--------------+-------------+---------------+-------------+---------------+");
		System.out.println("| No of Shapes | Sheets Used |   Time (ms)   | Sheets Used |   Time (ms)   |");
		System.out.println("+--------------+-------------+---------------+-------------+---------------+");
		
		
		//For each of the number of tests
		for (int i = 0; i < noOfTests; i++) {
			
			//Call performance method passing shape list to it
			performance(noOfShapes);
			//Display values in a tabulated format
			System.out.printf ("| %12d | %11d | %13f | %11d | %13f | \n", noOfShapes, sheets1UsedAverage, nextFitAverages/1000000, sheets2UsedAverage, firstFitAverages/1000000);
			//Increment noOfShapes by increment
			noOfShapes += increment;
		}
		//Display footer
		System.out.println("+--------------+-------------+---------------+-------------+---------------+");
	}
	
	public static void performance(int noOfShapes) {
		//Number of times to repeat the run
		int noOfRep = 6;
		
		//Create lists of sheets and set to null
		List<Sheet> sheets1 = null;
		List<Sheet> sheets2 = null;
		
		//Create algorithm object
		Algorithms a1 = new Algorithms();
		//Create a generator
		Generator g1 = new Generator();
		//Create longs for start time, end time and elapsed time
		long startTime = 0;
		long endTime = 0;
		long elapsedTime = 0;
		
		//For each of the repetitions
		for (int i = 0; i < noOfRep; i++) {
			//Generate a list of shapes using noOfShapes
			List<Shape> shapes = g1.generateShapeList(noOfShapes);
			sheets1 = a1.nextFit(shapes);
			//Set the start time to current nano time
			startTime = System.nanoTime();
			//Run the algorithm and store result in sheets1
			sheets1 = a1.nextFit(shapes);
			//Set the end time to current nano time
			endTime = System.nanoTime();
			//Set the elapsed time to end time - start time
			elapsedTime = endTime - startTime;
			//Set add elapsed time to average ignoring the first repetition (anomaly due to jvm)
			nextFitAverages += (i == 0) ? 0 : elapsedTime;
			//Add sheets used to average ignoring the first repetition (anomaly due to jvm)
			sheets1UsedAverage += (i == 0) ? 0 : sheets1.size();
			
			//Set the start time to current nano time
			startTime = System.nanoTime();
			//Run the algorithm and store result in sheets2
			sheets2 = a1.firstFit(shapes);
			//Set the end time to current nano time
			endTime = System.nanoTime();
			//Set the elapsed time to end time - start time
			elapsedTime = endTime - startTime;
			//Set add elapsed time to average ignoring the first repetition (anomaly due to jvm)
			firstFitAverages += (i == 0) ? 0 : elapsedTime;
			//Add sheets used to average ignoring the first repetition (anomaly due to jvm)
			sheets2UsedAverage += (i == 0) ? 0 : sheets2.size();

		}
		
		//Divide average value by number of repetitions - 1 (dont include first value)
		nextFitAverages = nextFitAverages / noOfRep - 1;
		firstFitAverages = firstFitAverages / noOfRep - 1;
		sheets1UsedAverage = sheets1UsedAverage / noOfRep - 1;
		sheets2UsedAverage = sheets2UsedAverage / noOfRep - 1;
	}
}
