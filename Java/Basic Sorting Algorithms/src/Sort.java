
/*****************************************************/
/*** Sort class currently contains some initial    ***/
/*** methods for implementing sorting algorithms   ***/
/***                                               ***/
/***     Initial Author: Jason Steggles 20/09/19   ***/
/***     Extended by: Arron Rawstron 16/10/19      ***/
/*****************************************************/

import java.io.*;
import java.text.*;
import java.util.*;

public class Sort {

/** Size of array **/
private int size;

/** Number of used elements in array **/
private int usedSize;

/** Array of integers **/
private int[] A;

/** Global variables for counting sort comparisons **/
public int compIS; /** Global comparison count for Insertion Sort **/
public int compQS; /** Global comparison count for Quicksort **/
public int compNS; /** Global comparison count for newsort **/

/*****************/
/** Constructor **/
/*****************/
Sort(int max)
{
    /** Initialiase global sort count variables **/
    compIS = 0;
    compQS = 0;
    compNS = 0;
    
    /** Initialise size variables **/
    usedSize = 0;
    size = max;
    
    /** Create Array of Integers **/
    A = new int[size];
}

/*********************************************/
/*** Read a file of integers into an array ***/
/*********************************************/
public void readIn(String file)
{
   try
   {
       /** Initialise loop variable **/
       usedSize = 0;
       
       /** Set up file for reading **/
       FileReader reader = new FileReader(file);
       Scanner in = new Scanner(reader);
       
       /** Loop round reading in data while array not full **/
       while(in.hasNextInt() && (usedSize < size))
       {
           A[usedSize] = in.nextInt();
           usedSize++;
       }
       
    }
    catch (IOException e)
    {
       System.out.println("Error processing file " + file);
    }
   
}

/**********************/
/*** Insertion Sort ***/
/**********************/
public void insertion() {
	/** For each of the elements excluding the first one **/
	for (int i = 1; i < usedSize; i++) {
		/** Set key to the second element in the array and j to the index **/
		int key = A[i];
		int j = i;
		/** Increment the counter for the first check **/
		compIS++;
		/** While j isnt the correct index, keep making space while ensuring j doesn't go beyond 0 **/
		while ((j > 0) && (key < A[j-1])) {
			A[j] = A[j-1];
			j = j-1;
			/** Increment the counter for the next checks **/
			compIS++;
		}
		/** Set the correct index to the key **/
		A[j] = key;
	}
}

/******************/
/*** Quick Sort ***/
/******************/
public void quicksort(int L, int R) {
	/** Check if one value is left **/
	if (R > L) {
		/** Split the into two using resulting in a pivot point**/
		int p = partition(L, R);
		/** Apply quick sort to the first half **/
		quicksort(L, p-1);
		/** Apply quick sort the the second half **/
		quicksort(p+1, R);
	}
}

/*****************/
/*** Partition ***/
/*****************/
public int partition(int left, int right) {
	/** Select the pivot point and create scanning pointers **/
	int v = A[right];
	int pointerL = left;
	int pointerR = right;
	
	/** While the pointers have not crossed **/
	while (pointerL < pointerR) {
		/** Increment the counter for the first check **/
		compQS++;
		/** While the value at the left pointer is less than the pivot (on correct side or pivot) **/
		while (A[pointerL] < v) {
			/** Increment pointer the find out of place value **/
			pointerL = pointerL + 1;
			/** Increment the counter for the next checks **/
			compQS++;
		}
		
		/** Increment the counter for the first check **/
		compQS++;
		/** While the value at the right pointer is greater than the pivot and it is not gone past the lowest value in array section **/
		while ((A[pointerR] >= v) && (pointerR > left)) {
			/** Decrement pointer the find out of place value **/
			pointerR = pointerR - 1;
			/** Increment the counter for the next checks **/
			compQS++;
		}
		
		/** If the pointers have not crossed **/
		if (pointerL < pointerR) {
			/** Swap the two selected values **/
			swap(pointerL, pointerR);
		}
		
	}
	/** Swap the pivot point with the last selected value to put pivot in correct place **/
	swap(pointerL, right);
	
	/** Return left pointer (pivot position) to return pivot position **/
	return pointerL;
}

/************/
/*** Swap ***/
/************/
public void swap(int left, int right) {
	/** Swap two given values using temp variable **/
	int temp = A[left];
	A[left] = A[right];
	A[right] = temp;
}

/****************/
/*** New Sort ***/
/****************/
public void newsort() {
	/** Set starting position **/
	int pos = 0;
	/** For every element in the array **/
	while (pos < usedSize) {
		/** Find the minimum value from pos to end of array (excludes sorted elements) **/
		int min = findMinFrom(pos);
		/** From pos to end of array, look for the min value **/
		for (int i = pos; i < usedSize; i++) {
			/** Increment the counter for the first check **/
			compNS++;
			/** If the selected element is the minimum value, swap it with pos to put it into place and increment pos **/
			if (A[i] == min) {
				swap (i, pos);
				pos = pos + 1;
			}
		}
	}
}

/*********************/
/*** Find Min From ***/ 
/*********************/
public int findMinFrom(int pos) {
	/** Set starting minimum as first element **/
	int min = A[pos];
	/** For every element from pos + 1 to end of array **/
	for (int i = pos + 1; i < usedSize; i++) {
		/** Increment the counter for the first check **/
		compNS++;
		/** If the selected element is less than the current min, replace min wiht that value **/
		if (A[i] < min) {
			min = A[i];
		}
	}
	/** Return minimum value **/
	return min;
}

/**********************/
/*** Display array  ***/
/**********************/
public void display(int line, String header)
{
    /*** Integer Formatter - three digits ***/
    NumberFormat FI = NumberFormat.getInstance();
    FI.setMinimumIntegerDigits(3);

    /** Print header string **/
    System.out.print("\n"+header);

    /** Display array data **/
    for (int i=0;i<usedSize;i++)
    {
        /** Check if new line is needed **/
        if (i%line == 0) 
        { 
            System.out.println(); 
        }
        
        /** Display an array element **/
        System.out.print(FI.format(A[i])+" ");
    }
}

}  /** End of Sort Class **/
