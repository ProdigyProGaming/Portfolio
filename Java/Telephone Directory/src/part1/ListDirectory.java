package part1;

import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

public class ListDirectory implements Directory{
	
	//Entry linked list as field so it can be accessed by any methods within the class
	private List<Entry> list = new LinkedList<Entry>();
	//List iterator as field so the same iterator can be used by the methods and to keep track of current location
	private ListIterator<Entry> listIter;
	//Length stores the number of elements currently being held
	private int length = 0;
	
	//Insert class inserts the passed Entry into the array
	public boolean insertEntry(Entry e) {
		//Search for the number from the 0th element to the length-1th element and store the return in result2 variable of type Entry
		Entry result2 = search(e.getTelExtension(), 0, length - 1);
		//Search for the surname from the 0th element to the length-1th element and store the return in result variable of type Entry
		Entry result = search(e.getSurname(), 0, length);
		//If the search method returned the found surname, another of the same name can not be added so return false
		if (result != null && result.compareTo(e) == 0) {
			return false;
		}
		//If the search method returned the found surname, another of the same name can not be added so return false
		if (length != 0 && (result2 != null && result2.getTelExtension().equals(e.getTelExtension()))) {
			return false;
		}
		//Add the Element to the list at the place of the iterator
		listIter.add(e);
		//Increment the field length
		length++;
		//Return true from the method
		return true;
	}

	//Delete class deletes the passed Entry from the array
	public boolean deleteEntry(Entry e) {
		//If passed entry is null, return false (can't remove null from list)
		if (e == null) {
			return false;
		}
		//Remove Entry from list and store boolean result in done variable
		boolean done = list.remove(e);
		//Decrement length variable
		length--;
		//Return value of done
		return done;
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
		//Set listIter to an iterator on the list
		listIter = list.listIterator();
		//While there is another item in the list
		while (listIter.hasNext()) {
			//Create result variable for storing comparison result
			int result;
			//Create variable current to store current Entry
			Entry current = listIter.next();
			//If the value is a name
			if (isName) {
				//Compare current surname and the passed value and store comparison result in result
				result = current.getSurname().compareToIgnoreCase(value);
				//If the result is greater than 0, gone past where it should stop
				if (result > 0) {
					//Return previous list item
					return listIter.previous();
				}
			}
			//If the value is a number
			else {
				//Compare current number and the passed value and store comparison result in result
				result = current.getTelExtension().compareTo(value);
			}
			//If the result from the comparison is 0 (value is equal to current)
			if (result == 0) {
				//Return previous list item
				return listIter.previous();
			}
		}
		//If value was not found, return null
		return null;
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
		//Create list iterator on list
		listIter = list.listIterator();
		//While there is more items in the list
		while (listIter.hasNext()) {
			//Set current to next item in list
			Entry current = listIter.next();
			//Print the current element to the console
			System.out.print(current.toString());
		}
		//Return true
		return true;
	}
	
	//Return array method to return the array for displaying in the GUI window
	public Entry[] returnArray() {
		//Create new array of size length
		Entry[] returnedArray = new Entry[length];
		int i = 0;
		//For every entry in list
		for (Entry e: list) {
			//Add entry to array
			returnedArray[i] = e;
			//Increment i
			i++;
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
