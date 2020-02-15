
/*************************************************/
/***  Simple test class for Sort class         ***/
/***                                           ***/
/***  Author: Arron Rawstron    20/09/2019     ***/
/*************************************************/


public class TestSort
{
	public static void main(String[] args) 
    {
        /*************/
        /*** Setup ***/
        /*************/
        
        /** Some simple tests using class Sort **/
        
        /** Create array of all test files **/
        String[] testFiles = new String [6];
        testFiles[0] = "test1.txt";
        testFiles[1] = "test2.txt";
        testFiles[2] = "test3.txt";
        testFiles[3] = "test4.txt";
        testFiles[4] = "test5.txt";
        testFiles[5] = "test6.txt";
        
        /** Run all 3 sorts for each of the test files **/
        for (String s:testFiles) {
        	/** Set size of array for object creation depending on the current file **/
        	int size;
        	/** If the file is 1, 2 or 3 (50 in length), set size to 50 **/
        	if (s.equals("test1.txt") || s.equals("test2.txt") || s.equals("test3.txt")) {
        		size = 50;
        	}
        	/** If the file is 4, 5 or 6 (1000 in length), set size to 1000 **/
        	else {
        		size = 1000;
        	}
        	/** Display which file is being tested **/
        	System.out.println(s);
        	
        	/**********************/
        	/*** Insertion Sort ***/
        	/**********************/
        	
        	/** Create object if size "size" and read in the file to the object **/
        	Sort sortTest1 = new Sort(size);
        	sortTest1.readIn(s);
        	
        	/** If it is the first file, display before and after the array has been sorted **/
        	if (s.equals("test1.txt")) {
        		sortTest1.display(15,"Values in " + s);
        		sortTest1.insertion();
        		sortTest1.display(15,"\nSorted Values in " + s);
        		System.out.println();
        	}
        	/** Else, just sort the array **/
        	else {
        		sortTest1.insertion();
        	}
        	/** Display the number of comparisons it took **/
        	System.out.println("Insertion sort comparison counter: " + sortTest1.compIS);
        	
        	/******************/
        	/*** Quick Sort ***/
        	/******************/
        	
        	/** Create object if size "size" and read in the file to the object **/
        	Sort sortTest2 = new Sort(size);
        	sortTest2.readIn(s);
        	
        	/** If it is the first file, display before and after the array has been sorted **/
        	if (s.equals("test1.txt")) {
        		sortTest2.display(15,"Values in " + s);
        		sortTest2.quicksort(0, size - 1);
        		sortTest2.display(15,"\nSorted Values in " + s);
        		System.out.println();
        	}
        	/** Else, just sort the array **/
        	else {
        		sortTest2.quicksort(0, size - 1);
        	}
        	/** Display the number of comparisons it took **/
        	System.out.println("Quick Sort comparison counter: " + sortTest2.compQS);
        	
        	/****************/
        	/*** New Sort ***/
        	/****************/
        	
        	/** Create object if size "size" and read in the file to the object **/
        	Sort sortTest3 = new Sort(size);
        	sortTest3.readIn(s);
        	
        	/** If it is the first file, display before and after the array has been sorted **/
        	if (s.equals("test1.txt")) {
        		sortTest3.display(15,"Values in " + s);
        		sortTest3.newsort();
        		sortTest3.display(15,"\nSorted Values in " + s);
        		System.out.println();
        	}
        	/** Else, just sort the array **/
        	else {
        		sortTest3.newsort();
        	}
        	/** Display the number of comparisons it took **/
        	System.out.println("New Sort comparison counter: " + sortTest3.compNS + "\n");
        }        
    }
    
} /** End of TestSort class **/
