package part1;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {

	//Try file method to check if the file path is valid
	public static boolean tryFile(String filePath) {
		try {
			//Try to create file reader for given path
			Scanner inFile = new Scanner(new FileReader(filePath));
			//If it succeeds, return true
			return true;
		}
		//If a file not found exception is thrown
		catch (FileNotFoundException e) {
			//Print error message
			System.out.println("File not found. Please try again.");
			//Return false
			return false;
		}
	}
	
	//Main method to start the entire program
	public static void main(String[] args) throws FileNotFoundException {
		//Create scanner for text input from console
		Scanner in = new Scanner(System.in);
		//Create string to store file path
		String filePath = "";
		//Create boolean to check if file is in specified file path
		boolean fileFound = false;
		//While a valid file has not been found
		while (!fileFound) {
			//Print menu options
			System.out.println("Please enter the type of file to use: ");
			System.out.println("1 - 1000 line file\n" + 
							   "2 - 88799 line file\n" +
							   "3 - Custom File");
			//Create int to store user's menu choice
			int fileSelection = 0;
			try {
				//Try to take an integer from the console
				fileSelection = in.nextInt();
				//Take rest of line if integer is taken in
				in.nextLine();
			}
			//If anything other than an integer is passed in
			catch (InputMismatchException e) {
				//Print error message
				System.out.println("That is not a valid option. Please try again.");
				//Take rest of line
				in.nextLine();
				//Return to while loop condition
				continue;
			}
			
			//Switch the users option to determine what to do next
			switch(fileSelection) {
				//If the user entered 1 (small file 1000 lines)
				case 1: 
					//Set file path to be in the projects dir with the name smallFile.txt
					filePath = "smallFile.txt";
					//Check if file is valid and store result (boolean) in fileFound (if valid, will stop while loop)
					fileFound = tryFile(filePath);
					//Break out of switch
					break;
				//If the user entered 2 (small file 88799 lines)
				case 2:
					//Set file path to be in the projects dir with the name largeFile.txt
					filePath = "largeFile.txt";
					//Check if file is valid and store result (boolean) in fileFound (if valid, will stop while loop)
					fileFound = tryFile(filePath);
					//Break out of switch
					break;
				//If the user entered 3 (custom file)		
				case 3:
					//Display prompt
					System.out.print("Please enter the FULL file path:");
					//Take in users input for the file path
					filePath = in.nextLine();
					//Check if file is valid and store result (boolean) in fileFound (if valid, will stop while loop)
					fileFound = tryFile(filePath);
					//Break out of switch
					break;
				//If the user entered a different number
				default:
					//Display error message
					System.out.println("That is not a valid option. Please try again.");
					//Break out of switch
					break;
			}
		}
		
		//Create int to store user's menu choice
		int dirType = 0;
		//While the user option isnt 1, 2 or 3
		while (dirType != 1 && dirType != 2 && dirType != 3) {
			//Print menu options
			System.out.println("Please enter the type of directory you want to use");
			System.out.println("1 - Array Dir\n" + 
						   	   "2 - List Dir\n" + 
							   "3 - Hash Dir");
			try {
				//Try to take an integer from the console
				dirType = in.nextInt();
			}
			//If anything other than an integer is passed in
			catch (InputMismatchException e) {
				//Set dirType to 0 (to prevent error and to loop again)
				dirType = 0;
			}
			//If the user option isnt 1, 2 or 3
			if (dirType != 1 && dirType != 2 && dirType != 3) {
				//Display error message
				System.out.println("That is not a valid option. Please try again.");
			}
			//Take rest of line
			in.nextLine();
		}
		
		//Create int to store user's menu choice
		int UISelection = 0;
		//While the user option isnt 1 and 2
		while (UISelection != 1 && UISelection != 2) {
			//Print menu options
			System.out.println("Please enter the type of interface you want to use");
			System.out.println("1 - Text Based\n" + 
							   "2 - GUI Based");
			try {
				//Try to take an integer from the console
				UISelection = in.nextInt();
			}
			//If anything other than an integer is passed in
			catch (InputMismatchException e) {
				//Set dirType to 0 (to prevent error and to loop again)
				UISelection = 0;
			}
			//If the user option isnt 1 and 2
			if (UISelection != 1 && UISelection != 2) {
				//Display error message
				System.out.println("That is not a valid option. Please try again.");
			}
			//Take rest of line
			in.nextLine();
		}
		//If UISelection is 1 (text based)
		if (UISelection == 1) {
			//Create object of TextBased
			TextBased txtDir = new TextBased();
			//Pass in dirType and file path to readin method
			txtDir.readIn(dirType, filePath);
			//Call start method for textDir
			txtDir.start();
		}
		//If UISelection is 2 (GUI based)
		else if (UISelection == 2) {
			//Print instructions
			System.out.println("To use the GUI: \n" + 
							   "Type the information required - \n" + 
							   "	Insert - Forename AND Surname AND Telephone Extension\n" + 
							   "	Delete - Surname OR Telephone Extension\n" + 
							   "	Get Number - Surname\n" + 
							   "	Edit - Surname AND Telephone Extension\n" +
							   "Then press the button to complete the action\n" + 
							   "The table will update automatically\n" + 
							   "Any errors will show below the buttons along with any output required (Get Num)\n");
			//Create object of GUIBased
			GUIBased guiDir = new GUIBased();
			//Pass in dirType and filePath to readin method
			guiDir.readIn(dirType, filePath);
			//Call start method for GUIDir
			guiDir.start();
		}
	}
}
