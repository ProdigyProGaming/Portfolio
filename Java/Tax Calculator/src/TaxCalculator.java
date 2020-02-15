//Author: Arron Rawstron
//Date: 23/10/18
//Program Purpose: Calculate and Display Tax
//Class Purpose: Calculate tax for given input

public class TaxCalculator {
	public static int taxCalc(int childIncome) {
		//Declare final arrays with scope of taxCalc method
		final int[] LOWER_LIMIT = {400, 300, 200, 150, 100};
		final double[] TAX_RATE = {1.5, 0.2, 0.15, 0.1, 0.05};
		
		//Declare variables with scope of taxCalc method
		double childTaxPayment = 0;
		double tempDeduction = 0;
		
		//For each of the values in the lower limit array
		for (int counter = 0; counter < LOWER_LIMIT.length; counter++) {
			//If the current income value is larger than the active lower limit
			//calculate tax using tax rate and reduce income
			if (childIncome > LOWER_LIMIT[counter]) {
				tempDeduction = childIncome - LOWER_LIMIT[counter];
				childTaxPayment += (tempDeduction * TAX_RATE[counter]);
				childIncome -= tempDeduction;
			}
		}
		//Round the double value to a whole number
		childTaxPayment = Math.round(childTaxPayment);
		
		//Return child tax
		return (int)childTaxPayment;
	}
	
	public static void childTax() {
		//Take input for child's income
		System.out.print("Please enter the child's income: ");
		int childIncome = MainClass.in.nextInt();
		
		//Store child tax in variable and output tax required for custom income
		int childTaxPayment = taxCalc(childIncome);
		
		//Check if tax is greater than income
		if (childTaxPayment > childIncome) {
			childTaxPayment = childIncome;
		}
		
		System.out.println("The tax required for £" + childIncome + " is £" + childTaxPayment);
	}
}
