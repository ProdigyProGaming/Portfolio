package part1;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Arrays;
import java.util.Scanner;

public class ArrayDirectory implements Directory{
	
	private static StopWatch sw = new StopWatch();
	
	//Entry array as field so it can be accessed by any methods within the class
	private Entry[] array;
	//Length stores the number of elements currently being held (not same as length of array due to array size being doubled when needed)
	private int length = 0;
	//Select stores the current selected array index to be used. Set to -1 so not to interfere with another array element
	private int select = -1;
	
	//Check size method is called when inserting an element into the directory and checks if the array is big enough to add the element
	public void checkSize() {
		//If the array is empty or if the number of elements is close to the array length
		if (array != null && length + 1 == array.length) {
			//Set array to be a copy of the current array with double the length
			Entry[] array = Arrays.copyOf(this.array, this.array.length*2);
			this.array = array;
		}
	}
	
	//Insert class inserts the passed Entry into the array
	public boolean insertEntry(Entry e) {
		//Call check size to see if the array is big enough to add the Entry
		checkSize();
		
		//If the array is null (no items have been added)
		if (array == null) {
			//Initialise the array with a size of 20
			array = new Entry[20];
			//Set the first element to the passed Entry
			array[0] = e;
			//Increment the field length
			length ++;
			//Return true from the method
			return true;
		}
		//If there is at least one element in the array, or it has been initialised
		else {
			//Search for the surname from the 0th element to the length-1th element and store the return in result variable of type Entry
			Entry result = search(e.getSurname(), 0, length - 1);
			//Search for the number from the 0th element to the length-1th element and store the return in result2 variable of type Entry
			Entry result2 = search(e.getTelExtension(), 0, length - 1);
			//If the search method returned the found surname, another of the same name can not be added so return false
			if (result != null && result.compareTo(e) == 0) {
				return false;
			}
			//If the search method returned the found surname, another of the same name can not be added so return false
			if (length != 0 && (result2 != null && result2.getTelExtension().equals(e.getTelExtension()))) {
				return false;
			}
		}
		//For each item in the array from the last Entry to the selected one
		for (int i = length; i > select; i-- ) {
			//Set the ith element to the one before it (shift them all to the right by 1)
			array[i] = array[i-1];
		}
		//Add the passed element to the array at the select index
		array[select] = e;
		//Increment the field length
		length ++;
		//Return true from the method
		return true;
	}
	
	//Delete class deletes the passed Entry from the array
	public boolean deleteEntry(Entry e) {
		//If the length of the array is 0, an element can not be deleted so return false
		if (length == 0) {
			return false;
		}
		//Search for the surname from the 0th element to the length-1th element and store the return in result variable of type Entry
		Entry result = search(e.getSurname(), 0, length);
		//If search result is not equal to given entry, return false
		if (!(result.getSurname().equals(e.getSurname()))) {
			return false;
		}
		//Otherwise, for every element from the selected entry to the end, move them all one to the left
		for (int i = select; i < length; i++) {
			array[i] = array[i + 1];
		}
		//Set the last element (same as one before) to null
		array[length - 1] = null;
		//Decrement length by one
		length --;
		//Return true from method
		return true;
	}
	
	//Search class searches for an element in the array using the passed value
	public Entry search(String value, int left, int right) {
		//Set variable isName to false to check if the value is a name or number
		boolean isName = false;
		//Try to convert the value to an integer
		try {
			//If you can convert the value to a number, set isName to false
			Integer.parseInt(value);
			isName = false;
		}
		//If the value cannot be converted to a number it must be a name
		catch (NumberFormatException exception) {
			isName = true;
		}
		//If the value is a name
		if (isName) {
			//If the left marker has not gone past the right marker
			if (left <= right) {
				//Set mid to middle (ish) or remaining part
				int mid = (left + right) / 2;
				//Set result to comparison of the mid surname and the value
				int result = array[mid].getSurname().compareTo(value);
				//If result is 0 (the mid surname is the same as the value)
				if (result == 0) {
					//Set select field to mid
					select = mid;
					//Return Entry in mid position
					return array[mid];
				}
				//If result is greater than 0 (mid is greater than value)
				else if (result > 0) {
					//Return a search in the lower half of array
					return search(value, left, mid - 1);
				}
				//If result is less than 0 (mid is lower than value)
				else {
					//Return a search in the upper half of array
					return search(value, mid + 1, right);
				}
			}
			//Set select field to left value (place of crossover for insertion)
			select = left;
			//Return null
			return null;
		}
		//If the value is a number
		else {
			//For each Entry in array
			for (int i = 0; i < length; i++) {
				//Set result to the comparison of ith element's number and the value
				int result = array[i].getTelExtension().compareTo(value);
				//If result is 0 (ith element's number is the same as value
				if (result == 0) {
					//Set select field to i
					select = i;
					//Return the ith element
					return array[i];
				}
			}
			//If number is not found, return first element of array to prevent null return
			return null;
		}
	}
	
	//Get Number method to return number of passed Entry
	public String getNum(Entry e) {
		//Return number of passed Entry
		return e.getTelExtension();
	}
	
	//Edit entry method to change number of passed entry
	public boolean editEntry(Entry e, String newNum) {
		//Search for the number from the 0th element to the length-1th element and store the return in result variable of type Entry
		Entry result = search(e.getTelExtension(), 0, length - 1);
		//If the search method did not return the found number, it cannot be edited so return false
		if (result == null || (!(result.getTelExtension().equals(e.getTelExtension())))) {
			return false;
		}
		//Set number of passed entry to passed number
		e.setTelExtension(newNum);
		//Return true
		return true;
	}
	
	//Display directory method to print the directory to the console
	public boolean displayDir() {
		int i = 0;
		//While i is less than length (there are more entries in the array)
		while (i < length) {
			//Print the ith element to the console
			System.out.print(array[i].toString());
			//Increment i
			i ++;
		}
		//Return true
		return true;
	}
	
	//Return array method to return the array for displaying in the GUI window
	public Entry[] returnArray() {
		//Create new array of size length to remove any null entries in array
		Entry[] returnedArray = new Entry[length];
		int i = 0;
		//For every element in the array
		for (Entry e:array) {
			//if the entry is not null
			if (e != null) {
				//Add the entry to the array
				returnedArray[i] = e;
				//Increment i
				i++;
			}
		}
		//Return new array
		return returnedArray;
	}
	
	//Get length method to return the length of array
	public int getLength() {
		//Return length field
		return length;
	}
}