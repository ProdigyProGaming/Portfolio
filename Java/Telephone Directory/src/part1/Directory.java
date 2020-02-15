package part1;

public interface Directory {
	//Return boolean from insertEntry to say whether entry has been added successfully 
	boolean insertEntry(Entry e);
	//Return boolean from deleteEntry to say whether entry has been deleted successfully 
	boolean deleteEntry(Entry e);
	//Return Entry to return either the found Entry or not.
	Entry search(String value, int left, int right);
	//Return String to return the telephone number. Must be a string to display 0 at start if required
	String getNum(Entry s);
	//Return boolean from editEntry to say whether entry has been changed successfully 
	boolean editEntry(Entry e, String newNum);
	//Return boolean from displayDir to return whether it has been displayed
	boolean displayDir();
	//Return Entry array from returnArray to convert the list or array to an array to be used for the GUI
	Entry[] returnArray();
	//Return int to return length of array or list
	int getLength();
}
