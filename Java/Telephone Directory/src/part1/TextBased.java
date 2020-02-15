package part1;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.regex.Pattern;

public class TextBased {
	
	//Directory as field to be accessed by other methods but not initialised so it can done so with the correct type
	private static Directory direc;
	//Length as field to be accessed by other methods to get length
	private static int length;
	
	//Search validator method searches the directory for the given string and returns the Entry
	public static Entry searchValidator(String s) {
		//Store search result in Entry e
		Entry e = direc.search(s, 0, length);
		//Return Entry e
		return (e);
	}
	
	//Capitalise method to ensure strings do not have white spaces and are cased properly
	public static String capitalise(String s) {
		//If when the spaces have been taken away, there is an empty string left
		if (s.replaceAll("\\s+", "").equals("")) {
			//Return blank
			return ("");
		}
		//Otherwise, capitalise the first character and uncapitalise the rest of the string
		return (s.substring(0, 1).toUpperCase() + s.substring(1).toLowerCase());
	}
	
	//Check if number method to check if the string is a valid name or valid number
	public static int checkIfNumber(String s) {
		// 0 = Valid Number
		// 1 = Valid Name
		//-1 = Not Valid
		
		//Set check boolean to -1
		int check = -1;
		//Try to convert string to integer
		try {
			//If converting to integer works, must be a number
			Integer.parseInt(s);
			//Set check to 0
			check = 0;
		}
		//If Converting to integer does not work, must be a name
		catch(NumberFormatException e) {
			//Check the string for any numbers
			if (Pattern.compile("[0-9]").matcher(s).find()) {
				//If a number is found, it is not a valid name
				check = -1;
			}
			//If there are no numbers in the string
			else {
				//It is a valid name
				check = 1;
			}
		}
		//Return check
		return check;
	}
	
	//User input method to handle all input from the user
	public static String userInput(int min, int max) {
		//Create scanner object to take input from console
		Scanner in = new Scanner(System.in);
		//Create int input variable to store user input for menus
		int intInput = 0;
		//Create string input variable to store other inputs
		String stringInput = "";
		//If min is 0 and max is 0 (looking for name input), or min is 5 and max is 5 (looking for telephone number input)
		if ((min == 0 && max == 0) || (min == 5 && max == 5)) {
			//If a telephone number is required
			if (min == 5) {
				do {
					//Take next input from console
					stringInput = in.next();
					//If check if number returns anything except a 0 (it is not a number)
					if(checkIfNumber(stringInput) != 0) {
						//Display error message and prompt
						System.out.print("That is not a valid number. Please enter another one: ");
					}
					//If input is too long
					else if (stringInput.length() > max) {
						//Display error message and prompt
						System.out.print("The telephone extension is too long. Please enter another one: ");
					}
					//If input is too short
					else if (stringInput.length() < min) {
						//Add 0's to the start so it is 5 characters long
						return ("00000" + stringInput).substring(stringInput.length());
					}
				}
				//Loop until it is 5 characters long and the checkIfNumber method returns 0 (valid number)
				while ((stringInput.length() != 5) || (checkIfNumber(stringInput) != 0));
			}
			//If a name is required
			else {
				//Create valid name boolean to store if name is valid
				boolean validName = false;
				//While name is not valid
				while(!validName) {
					//Take next input from console
					stringInput = in.next();
					//Call capitalise method on string
					stringInput = capitalise(stringInput);	
					//If string is blank or check if number method returns anything other than 1 (not valid name)
					if ((stringInput.equals("")) || (checkIfNumber(stringInput) != 1)) {
						//Display error message and prompt
						System.out.print("That name is not valid. Please enter another one: ");
						//Set valid name to false (should already be)
						validName = false;
					}
					//If it is a valid name
					else {
						//Set valid name to true
						validName = true;
					}
				}
				
			}
			//Take rest of line to clear it
			in.nextLine();
			//Return the valid string
			return stringInput;
		}
		//If looking for menu input
		else {
			do {
				try {
					//Try to take next integer
					intInput = in.nextInt();
					//If input is out of specified range
					if (!(intInput >= min && intInput <= max)) {
						//Display error message and prompt
						System.out.print("The input must be from " + min + " to " + max + ". Please enter another one: ");
					}
				}
				//If anything other than int was entered
				catch(InputMismatchException e) {
					//Display error message and prompt
					System.out.print("That was not a valid input. Please enter another one: ");
					//Take rest of line to clear it
					in.nextLine();
					//Set input to 0 to prevent unintentional looping
					intInput = 0;
				}
			}
			//Loop while input is out of range
			while (!(intInput >= min && intInput <= max));
			//Return the int converted to a string (String return required for names)
			return Integer.toString(intInput);
		}
	}

	//Read in method to take file and place values into directory
	public void readIn(int type, String filePath) throws FileNotFoundException {
		//Print message
		System.out.println("Reading in dataset...");
		//Create inFile Scanner to read in file with specified path
		Scanner inFile = new Scanner(new FileReader(filePath));
		
		//Create Entry
		Entry entry;
		//Switch type for the different directory types
		switch(type) {
			//If type is 1 (array directory is requested)
			case 1: 
				//Set directory to be array directory
				direc = new ArrayDirectory();
				//Break out of switch
				break;
			//If type is 2 (list directory is requested)
			case 2:
				//Set directory to be list directory
				direc = new ListDirectory();
				//Break out of switch
				break;
			//If type is 3 (hash directory is requested)
			case 3:
				//Set directory to be hash directory
				direc = new HashDirectory();
				//Break out of switch
				break;
			//If type is anything else (should never be) 
			default: 
				//Set directory to be array directory
				direc = new ArrayDirectory();
				//Break out of switch
				break;
		}
		//Create percentage variable to store percentage completion
		int percentage = 0;
		//Create percent check var to store last percentage printed
		int percentCheck = 0;
		//Create Path object with file path parameter
		Path path = Paths.get(filePath);
		//Create divisor variable to hold length of file to divide for percentage
		int divisor;
		try {
			//Try to count number of lines in file
			divisor = (int) Files.lines(path).count();
		}
		//Catch IOexception (Should never happen)
		catch (IOException e) {
			//Display error message
			System.out.println("An error occured");
			//Display actual error
			e.printStackTrace();
			//Set divisor to 1000 (standard value)
			divisor = 1000;
		}
		//While there are more lines in the file
		while (inFile.hasNextLine()) {
			try {
				//Create new Entry
				entry = new Entry();
				//Try to set surname to next value in file (throws no such element if next line is blank)
				entry.setSurname(inFile.next());
				//Try to set initials to next value in file
				entry.setInitials(inFile.next());
				//Try to set number to next value in file
				entry.setTelExtension(inFile.next());
				//Insert Entry to directory
				direc.insertEntry(entry);
				//Calculate percentage using length and divisor
				percentage = (int)(((double)length/divisor)*100);
				//If percentage has increased compared to percent check (Prevents printing same percentage multiple times)
				if (!(percentage == percentCheck)) {
					//Set percent check to new percent
					percentCheck = percentage;
					//Print out current percent
					System.out.println("Loading... " + percentage + "%");
				}
				//Increment length
				length ++;
			}
			//Catch no such element if .next is empty (Shouldn't stop program)
			catch(NoSuchElementException e) {
				//Print warning message
				System.out.println("Warning! Please ensure your file has no blank lines.");
			}
		}
		//Print complete message
		System.out.println("Loading... 100% \n" + 
						   "Completed!");
	}
	
	//Insert method used for inserting into the directory
	public static boolean insert() {
		//Display prompt
		System.out.print("Please enter the first name: ");
		//Take input using userInput method for first name
		String forename = userInput(0, 0);
		//Display prompt
		System.out.print("Please enter the last name: ");
		//Take input using userInput method for last name
		String surname = userInput(0, 0);
		//Set initials to be the first character of first name and surname
		String initials = forename.charAt(0) + "." + surname.charAt(0);
		//Display prompt
		System.out.print("Please enter the telephone extension: ");
		//Take input using userInput method for number
		String telExtension = userInput(5, 5);
		
		//Create new entry
		Entry e = new Entry();
		
		//Create entry for search validator return for suranme and number
		Entry searchValSurnameResult = searchValidator(surname);
		Entry searchValTelResult = searchValidator(telExtension);
		
		//If searchVal return is null or not equal to the searched name and number (entered details are unique)
		if (searchValSurnameResult == null || (!(searchValSurnameResult.getSurname().equals(surname)))) {
			if (searchValTelResult == null || (!(searchValTelResult.getTelExtension().equals(telExtension)))) {
				//Set details of entry
				e.setSurname(surname);
				e.setInitials(initials);
				e.setTelExtension(telExtension);
			}
			//If searchVal return for number is not unique
			else {
				//Display message
				System.out.println("That extension already exists");
				//Return false (Did not insert entry)
				return false;
			}
		}
		//If searchVal return for name is not unique
		else {
			//Display message
			System.out.println("That surname already exists");
			//Return false (Did not insert entry)
			return false;
		}
		//Otherwise, insert entry
		direc.insertEntry(e);
		//Return true (inserted entry)
		return true;
	}
	
	//Delete method used for deleting entry from directory
	public static boolean delete() {
		//Display prompt and menu options
		System.out.print("Would you like to delete by surname or by telephone extension: \n" + 
						   "1 - Surname \n" + 
						   "2 - Telephone Extension \n");
		//Take input for menu using userInput and converting return (string) to int
		int response = Integer.parseInt(userInput(1, 2));
		//If 1 is entered (deleting by surname)
		if (response == 1) {
			//Display prompt
			System.out.print("Please enter the last name: ");
			//Take input using userInput method for last name
			String surname = userInput(0, 0);
			//Search for surname in directory
			Entry e = searchValidator(surname);
			//If the entry was found (not null returned and e surname is equal to surname)
			if (e != null && e.getSurname().equals(surname)) {
				//Delete entry from directory
				direc.deleteEntry(e);
				//Return true (deleted entry)
				return true;
			}
			else {
				//Otherwise, display message
				System.out.println("Did not find entry");
				//Return false (did not delete entry)
				return false;
			}
		}
		//If 2 is entered (deleting by number
		else {
			//Display prompt
			System.out.print("Please enter the telephone extension: ");
			//Take input using userInput method for number
			String number = userInput(5, 5);
			//Search for number in directory
			Entry e = searchValidator(number);
			//If the entry was found (not null returned and e number is equal to number)
			if (e != null && e.getTelExtension().equals(number)) {
				//Delete entry from directory
				direc.deleteEntry(e);
				//Return true (deleted entry)
				return true;
			}
			else {
				//Otherwise, display message
				System.out.println("Did not find entry");
				//Return false (did not delete entry)
				return false;
			}
		}
	}
	
	//Get number method for displaying the number for a given surname
	public static boolean getNumber() {
		//Display message
		System.out.print("Please enter the last name: ");
		//Take input using userInput method for last name
		String surname = userInput(0, 0);
		//Search for surname in directory
		Entry e = searchValidator(surname);
		//If the entry was found (not null returned and e surname is equal to surname)
		if (e != null && e.getSurname().equals(surname)) {
			//Display number for given surname
			System.out.println(direc.getNum(e));
			//Return true (printed number)
			return true;
		}
		else {
			//Otherwise, display message
			System.out.println("Did not find entry");
			//Return false (did not print number)
			return false;
		}
		
	}
	
	//Edit entry to change the number of an entry, given a surname
	public static boolean edit() {
		//Display prompt
		System.out.print("Please enter the last name: ");
		//Take input using userInput method for last name
		String surname = userInput(0, 0);
		//Display prompt
		System.out.print("Please enter the new telephone extension: ");
		//Take input using userInput method for number
		String number = userInput(5, 5);
		
		//Create entry for search validator return for surname and number
		Entry searchValSurnameResult = searchValidator(surname);
		Entry searchValTelResult = searchValidator(number);
		
		//If searchVal return is not null and equal to the searched name (found requested entry)
		if (searchValSurnameResult != null && searchValSurnameResult.getSurname().equals(surname)) {
			//If searchVal return is null or not equal to the searched number (entered details are unique)
			if (searchValTelResult == null || (!(searchValTelResult.getTelExtension().equals(number)))) {
				//Edit entry giving found entry and unique number
				direc.editEntry(searchValSurnameResult, number);
				//Return true (edited entry)
				return true;
			}
			else {
				//Otherwise, display message
				System.out.println("That extension already exists");
				//Return false (did not edit entry)
				return false;
			}
		}
		//If searchVal return for name is unique
		else {
			//Display message
			System.out.println("Did not find entry");
			//Return false (did not edit entry)
			return false;
		}
	}
	
	//Display method used to display whole directory to console
	public static boolean display() {
		//Display directory
		direc.displayDir();
		//Return true (directory displayed)
		return true;
	}
	
	//Start method to start the TextBased section
	public static void start() {
		//Create response variable to store user input for menus
		int response;
		//Create loop variable to check if looping is required
		int loop;
		do {
			//Display prompt with menu
			System.out.print("Please select the action you want to do: \n" + 
							   "1 - Insert Entry \n" + 
							   "2 - Delete Entry \n" + 
							   "3 - Get Telephone Extension \n" + 
							   "4 - Edit Entry \n" + 
							   "5 - Display Directory \n");
			//Take input for menu using userInput and converting return (string) to int
			response = Integer.parseInt(userInput(1, 5));
			//Create completed variable to store if task was completed
			boolean completed = false;
			//Switch user input for different menu options
			switch (response) {
				//If user input is 1 (inserting entry)
				case 1:
					//Set completed to be return of insert
					completed = insert();
					//Break out of switch
					break;
				//If user input is 2 (deleting entry)
				case 2:
					//Set completed to be return of delete
					completed = delete();
					//Break out of switch
					break;
				//If user input is 3 (displaying number)
				case 3:
					//Set completed to be return of getNumber
					completed = getNumber();
					//Break out of switch
					break;
				//If user input is 4 (editing entry)
				case 4:
					//Set completed to be return of edit
					completed = edit();
					//Break out of switch
					break;
				//If user input is 5 (displaying directory)
				case 5:
					//Set completed to be return of display
					completed = display();
					//Break out of switch
					break;	
			}
			//If task was not completed
			if (!completed) {
				//Display message
				System.out.println("The task was not completed due to an error");
			}
			//If task was completed
			else {
				//Display message
				System.out.println("Task was completed successfully");
			}
			//Display prompt
			System.out.print("Would you like to print the directory: \n" + 
							   "1 - Yes \n" + 
					       	   "2 - No \n");
			//Take input for menu using userInput and converting return (string) to int
			int print = Integer.parseInt(userInput(1, 2));
			//If input is 1 (user wants to display directory)
			if (print == 1) {
				//Call display method to display directory
				display();
			}
			//Display prompt
			System.out.print("Would you like to do another task: \n" + 
							   "1 - Yes \n" + 
							   "2 - No \n");
			//Take input for menu using userInput and converting return (string) to int
			loop = Integer.parseInt(userInput(1, 2));
		}
		//Loop while loop is 1
		while (loop == 1);
		//Once broken out of loop by users choice, display goodbye message
		System.out.println("Thank you! Goodbye!");
	}
}
