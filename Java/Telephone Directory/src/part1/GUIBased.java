package part1;

import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.regex.Pattern;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

public class GUIBased {
	
	//Directory as field to be accessed by other methods but not initialised so it can done so with the correct type
	private static Directory direc;
	//Length as field to be accessed by other methods to get length
	private static int length;
	//Result as field so can be displayed even when repainted (used for output in GUI)
	private static String result;
	//Frame as field to be accessed by other methods
	private static JFrame frame = new JFrame();
	//content pane as field to be accessed by other methods
	private static JPanel contentPane = new JPanel();

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
			if (Pattern.compile("[0-9]").matcher( s ).find()) {
				//If a number is found, it is not a valid name
				check = 2;
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
	
	//Update table method to update the JTable
	public static void updateTable() {
		//Create array and store directory as array in it
		Entry[] array = direc.returnArray();
		
		//Create String array with headers for JTable
		String[] columnNames = {"Surname", "Initials", "Telephone Extension"};
		//Create Object array of size length by 3
		Object[][] data = new Object[direc.getLength()][3];
		int i = 0;
		//For every entry in array
		for (Entry e:array) {
			//Set surname, initials and number to the same row in the 3 columns
			data[i][0] = e.getSurname();
			data[i][1] = e.getInitials();
			data[i][2] = e.getTelExtension();
			//Increment i
			i++;
		}
		//Create a scroll pane for scrolling on the JTable
		JScrollPane scrollPane = new JScrollPane();
		//Set bounds of scroll pane
		scrollPane.setBounds(250, 11, 624, 539);
		//Add scroll pane to content pane
		contentPane.add(scrollPane);
		
		//Create JTable with data
		JTable table = new JTable(data, columnNames);
		//Add table to scroll pane
		scrollPane.setViewportView(table);
		
		//Disable editing of the table
		table.setDefaultEditor(Object.class, null);
	}
	
	//Start method to start the GUIBased section
	public void start() {
		//Set frame to visible
		frame.setVisible(true);
		//Set close operation to exit
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//Set bounds of frame
		frame.setBounds(100, 100, 900, 600);
		
		//Set content pane to a new JPanel
		contentPane = new JPanel();
		//Set border of content pane to new empty border
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		//Set content pane of frame to content pane
		frame.setContentPane(contentPane);
		//Set layout of content pane to null
		contentPane.setLayout(null);
		
		//Create new JLabel with title Forename
		JLabel forenameLabel = new JLabel("Forename");
		//Center label
		forenameLabel.setHorizontalAlignment(SwingConstants.CENTER);
		//Set font to new font, style serif, normal (not bold etc) and size 20
		forenameLabel.setFont(new Font("Serif", Font.PLAIN, 20));
		//Set bounds of label to values
		forenameLabel.setBounds(60, 35, 135, 25);
		//Add label to content pane
		contentPane.add(forenameLabel);
		
		//Create new JLabel with title Surname
		JLabel surnameLabel = new JLabel("Surname");
		//Center label
		surnameLabel.setHorizontalAlignment(SwingConstants.CENTER);
		//Set font to new font, style serif, normal (not bold etc) and size 20
		surnameLabel.setFont(new Font("Serif", Font.PLAIN, 20));
		//Set bounds of label to values
		surnameLabel.setBounds(60, 95, 135, 25);
		//Add label to content pane
		contentPane.add(surnameLabel);
		
		//Create new JLabel with title Tel Num
		JLabel telLabel = new JLabel("Tel Num");
		//Center label
		telLabel.setHorizontalAlignment(SwingConstants.CENTER);
		//Set font to new font, style serif, normal (not bold etc) and size 20
		telLabel.setFont(new Font("Serif", Font.PLAIN, 20));
		//Set bounds of label to values
		telLabel.setBounds(60, 155, 135, 25);
		//Add label to content pane
		contentPane.add(telLabel);
		
		//Create new text field
		JTextField forenameInput = new JTextField();
		//Set column size to 10
		forenameInput.setColumns(10);
		//Set bounds of text field to values
		forenameInput.setBounds(10, 60, 230, 25);
		//Add text field to content pane
		contentPane.add(forenameInput);				
		
		//Create new text field
		JTextField surnameInput = new JTextField();
		//Set column size to 10
		surnameInput.setColumns(10);
		//Set bounds of text field to values
		surnameInput.setBounds(10, 120, 230, 25);
		//Add text field to content pane
		contentPane.add(surnameInput);
		
		//Create new text field
		JTextField telInput = new JTextField();
		//Set column size to 10
		telInput.setColumns(10);
		//Set bounds of text field to values
		telInput.setBounds(10, 180, 230, 25);
		//Add text field to content pane
		contentPane.add(telInput);
		
		//Create new JLabel with no title
		JLabel output = new JLabel("");
		//Center label
		output.setHorizontalAlignment(SwingConstants.CENTER);
		//Set font to new font, style serif, normal (not bold etc) and size 15
		output.setFont(new Font("Serif", Font.PLAIN, 15));
		//Set bounds of label to values
		output.setBounds(10, 425, 230, 125);
		//Add label to content pane
		contentPane.add(output);
		
		//Create button with title Insert
		JButton insert = new JButton("Insert");
		//Add listener to button
		insert.addActionListener(new ActionListener() {
			//Action to perform when needed
			public void actionPerformed(ActionEvent arg0) {
				//Create variables for the text field values and capitalise the names
				String forename = capitalise(forenameInput.getText());
				String surname = capitalise(surnameInput.getText());
				String telNum = telInput.getText();
				
				//If none of the fields are blank (insert requires all fields)
				if (!((forename.equals("")) || (surname.equals("")) || (telNum.equals("")))) {
					//If number is less than 5 (size of number)
					if (telNum.length() < 5) {
						//Add 0's to the start so it is 5 characters long
						telNum = ("00000" + telNum).substring(telNum.length());
					}
					//If check if number method returns anything other than 1 for first name (not valid name)
					if (checkIfNumber(forename) != 1) {
						//Set output label to message
						output.setText("That first name is not valid");
					}
					//If check if number method returns anything other than 1 for surname (not valid name)
					else if (checkIfNumber(surname) != 1) {
						//Set output label to message
						output.setText("That surname is not valid");
					}
					//If check if number returns anything except a 0 (it is not a number)
					else if (checkIfNumber(telNum) != 0) {
						//Set output label to message
						output.setText("That number is not valid");
					}
					//If number is too long
					else if (telNum.length() > 5) {
						//Set output label to message
						output.setText("That number is not valid");
					}
					//If the inputs are valid
					else {
						//Create new entry
						Entry e = new Entry();
						//Set entry values to inputs
						e.setSurname(surname);
						e.setInitials(forename.charAt(0) + "." + surname.charAt(0));
						e.setTelExtension(telNum);
						//Insert entry to the directory and store return in r (completed or not)
						boolean r = direc.insertEntry(e);
						//If task was completed
						if (r) {
							//Set result (output label changed at end) to message
							result = "Task Completed";
						}
						//If task was not completed
						else {
							//Set result (output label changed at end) to message
							result = "Task Failed";
						}
						//Call start to refresh everything
						start();
					}
				}
				//If any of the text fields are missing values
				else {
					//Set output label to message
					output.setText("Requires more details");
				}
			}
		});
		//Set bounds of button to values
		insert.setBounds(80, 230, 90, 25);
		//Add button to content pane
		contentPane.add(insert);
		
		//Create button with title Delete
		JButton delete = new JButton("Delete");
		//Add listener to button
		delete.addActionListener(new ActionListener() {
			//Action to perform when needed
			public void actionPerformed(ActionEvent e) {
				//Create variables for the text field values and capitalise the names
				String surname = capitalise(surnameInput.getText());
				String telNum = telInput.getText();
				//If either of the required fields are filled (delete required surname or number)
				if (!((surname.equals("")) && (telNum.equals("")))) {
					//If the surname is not blank
					if (!(surname.equals(""))) {
						//If check if number method returns 1 for surname (valid name)
						if (checkIfNumber(surname) == 1) {
							//Search for surname in directory
							Entry searchValResult = searchValidator(surname);
							//If the entry was found (not null returned and e surname is equal to surname)
							if (searchValResult != null && searchValResult.getSurname().equals(surname)) {
								//Delete entry from directory
								direc.deleteEntry(searchValResult);
								//Set result (output label changed at end) to message
								result = "Task Completed";
								//Call start to refresh everything
								start();
							}
							//If the entry was not found
							else {
								//Set output label to message
								output.setText("That surname doesn't exist");
							}
						}
						//If check if number method returns anything other than 1 for surname (not valid name)
						else {
							//Set output label to message
							output.setText("That surname is not valid");
						}
					}
					//If the number is not blank
					else if (!(telNum.equals(""))) {
						//If check if number method returns 0 for number (valid number)
						if (checkIfNumber(telNum) == 0) {
							//If number is not too long
							if (!(telNum.length() > 5)) {
								//If number is too short
								if (telNum.length() < 5) {
									//Add 0's to the start so it is 5 characters long
									telNum = ("00000" + telNum).substring(telNum.length());
								}
								//Search for number in directory
								Entry searchValResult = searchValidator(telNum);
								//If the entry was found (not null returned and e surname is equal to surname)
								if (searchValResult != null && searchValResult.getTelExtension().equals(telNum)) {
									//Delete entry from directory
									direc.deleteEntry(searchValResult);
									//Set result (output label changed at end) to message
									result = "Task Completed";
									//Call start to refresh everything
									start();
								}
								//If the entry was not found
								else {
									//Set output label to message
									output.setText("That extension doesn't exist");
								}
							}
							//If number is too long
							else {
								//Set output label to message
								output.setText("That extension is too long.");
							}
						}
						//If check if number method returns anything other than 0 for number (not valid number)
						else {
							output.setText("That extension is not valid");
						}
					}
				}
				//If any of the required text fields are missing values
				else {
					//Set output label to message
					output.setText("Requires more details");
				}
			}
		});
		//Set bounds of button to values
		delete.setBounds(80, 270, 90, 25);
		//Add button to content pane
		contentPane.add(delete);
		
		//Create button with title Get Num
		JButton getExtension = new JButton("Get Num");
		//Add listener to button
		getExtension.addActionListener(new ActionListener() {
			//Action to perform when needed
			public void actionPerformed(ActionEvent e) {
				//Create variable for the text field value and capitalise the name
				String surname = capitalise(surnameInput.getText());
				//If surname is not blank
				if (!(surname.equals(""))) {
					//If check if number method returns 1 for surname (valid name)
					if (checkIfNumber(surname) == 1) {
						//Search for surname in directory
						Entry searchValResult = searchValidator(surname);
						//If the entry was found (not null returned and e surname is equal to surname)
						if (searchValResult != null && searchValResult.getSurname().equals(surname)) {
							//Set result (output label changed at end) to number
							result = direc.getNum(searchValResult);
							//Call start to refresh everything
							start();
						}
						//If the entry was not found
						else {
							//Set output label to message
							output.setText("That surname doesn't exist");
						}
					}
					//If check if number method returns anything other than 1 for surname (not valid name)
					else {
						//Set output label to message
						output.setText("That surname is not valid");
					}
				}
				//If any of the required text fields are missing values
				else {
					//Set output label to message
					output.setText("Requires more details");
				}
			}
		});
		//Set bounds of button to values
		getExtension.setBounds(80, 310, 90, 25);
		//Add button to content pane
		contentPane.add(getExtension);
		
		//Create button with title Edit
		JButton edit = new JButton("Edit");
		//Add listener to button
		edit.addActionListener(new ActionListener() {
			//Action to perform when needed
			public void actionPerformed(ActionEvent e) {
				//Create variables for the text field values and capitalise the name
				String surname = capitalise(surnameInput.getText());
				String telNum = telInput.getText();
				//If the required fields are filled (edit requires surname and number)
				if (!(surname.equals("") || telNum.equals(""))) {
					//If check if number method returns 1 for surname (valid name)
					if (checkIfNumber(surname) == 1) {
						//Search for surname in directory
						Entry searchValResult = searchValidator(surname);
						//If number is less than 5 (size of number)
						if (telNum.length() < 5) {
							//Add 0's to the start so it is 5 characters long
							telNum = ("00000" + telNum).substring(telNum.length());
						}
						//If check if number returns anything except a 0 (it is not a number)
						if (checkIfNumber(telNum) != 0) {
							//Set output label to message
							output.setText("That number is not valid");
						}
						//If number is too long
						else if (telNum.length() > 5) {
							//Set output label to message
							output.setText("That number is not valid");
						}
						//If the entry was found (not null returned and e surname is equal to surname)
						else if (searchValResult != null && searchValResult.getSurname().equals(surname)) {
							//Edit entry in the directory and store return in r (completed or not)
							boolean r = direc.editEntry(searchValResult, telNum);
							//If task was completed
							if (r) {
								//Set result (output label changed at end) to message
								result = "Task Completed";
							}
							//If task was not completed
							else {
								//Set result (output label changed at end) to message
								result = "Task Failed";
							}
							//Call start to refresh everything
							start();
						}
						//If the entry was not found
						else {
							//Set output label to message
							output.setText("That surname doesn't exist");
						}
					}
					//If check if number method returns anything other than 1 for surname (not valid name)
					else {
						//Set output label to message
						output.setText("That surname is not valid");
					}
				}
				//If any of the required text fields are missing values
				else {
					//Set output label to message
					output.setText("Requires more details");
				}
			}
		});
		//Set bounds of button to values
		edit.setBounds(80, 350, 90, 25);
		//Add button to content pane
		contentPane.add(edit);
		
		//If result has been set to something
		if (result != null) {
			//Set output label to message
			output.setText(result);
			//Set result back to null
			result = null;
		}
		//Update table to refresh the JTable incase of any changes
		updateTable();
		//Repaint frame with changed JTable
		frame.repaint();	
	}
}
