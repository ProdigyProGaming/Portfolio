package part1;

public class Entry {
	
	//Fields containing surname, initials and telephone extension
	String surname;
	String initials;
	String telExtension;
	
	//Set surname method to set the surname of the object to the passed parameter
	public void setSurname(String surname) {
		this.surname = surname;
	}
	//Set initials method to set the initials of the object to the passed parameter
	public void setInitials(String initials) {
		this.initials = initials;
	}
	//Set telephone extension method to set the extension of the object to the passed parameter
	public void setTelExtension(String telExtension) {
		this.telExtension = telExtension;
	}
	
	//Get surname method to return the object's surname
	public String getSurname() {
		return surname;
	}
	//Get initials method to return the object's initials
	public String getInitials() {
		return initials;
	}
	//Get telephone extension method to return the object's extension
	public String getTelExtension() {
		return telExtension;
	}
	
	//To string method to return the objects details as a string
	public String toString() {
		//Set string s to the 3 fields in a formatted manner
		String s = String.format("Surname: %-20s|Initials: %-4s|Number: %-6s| \n", surname, initials, telExtension);
		return s;
	}
	
	//Compare to method to enable comparison between Entrys
	public int compareTo(Entry e) {
		//If the surname of "this" is equal to the surname of "e", return 0
		if (this.getSurname().compareToIgnoreCase(e.getSurname()) == 0) {
			return 0;
		}
		//If the surname of "this" is less than the surname of "e", return -1
		else if (this.getSurname().compareToIgnoreCase(e.getSurname()) < 0) {
			return -1;
		}
		//If the surname of "this" is greater than the surname of "e", return 1
		else {
			return 1;
		}
	}
}
