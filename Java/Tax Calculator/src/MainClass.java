//Author: Arron Rawstron
//Date: 23/10/18
//Program Purpose: Calculate and Display Tax
//Class Purpose: Give user main menu options

//Import libraries
import java.util.Scanner;

public class MainClass {
	public static Scanner in = new Scanner(System.in);
	
	public static void displayMaxSalary() {
		//Call method to calculate the salary where the tax is equal to the income
		int incomeEqualsTax = Test.maxSalary();
		
		//Output the smallest where the net pay is 0
		System.out.println("The smallest income where the net pay is £0 is £" + incomeEqualsTax);
	}
	
	public static void main (String[] args) {
		TaxCalculator.childTax();
		
		int[] income = Test.taxTables();

		//Create object to enable construct in TaxChart class
		TaxChart objTest = new TaxChart(income);
		
		//Call draw and drawTable methods to draw the graph and table
		objTest.draw();
		objTest.printTable();
		
		//Call method to display the salary where the tax is equal to the income
		displayMaxSalary();
		
		System.out.println("Press enter to exit");
		
		//Take input to delay exit of program
		in.nextLine();
		in.nextLine();
		
		in.close();
		
		//Close program
		System.exit(0);
	}
}
