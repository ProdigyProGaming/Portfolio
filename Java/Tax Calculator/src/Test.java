//Author: Arron Rawstron
//Date: 23/10/18
//Program Purpose: Calculate and Display Tax
//Class Purpose: Create Test Array

public class Test {
	public static int[] taxTables() {
		//Declare test array with scope taxTables method		
		int[] income = new int[] {25, 50, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 425, 450, 500, 550};
		
		//Pass income array to the sorter method
		sorter(income);

		//Return sorted income array
		return income;		
	}
	
	public static int[] sorter(int[] income) {
		//For each of the element in the array, compare to every other element to find the next smallest
		for (int firstCounter = 0; firstCounter <  income.length - 1; firstCounter++) {
			int smallestNum = firstCounter;
			for (int secondCounter = firstCounter + 1; secondCounter < income.length; secondCounter++) {
				if (income[secondCounter] < income[smallestNum]) {
					smallestNum = secondCounter;
				}
			}
			//Swap the currently active element with the smaller one if there is one
			if (income[smallestNum] < income[firstCounter]) {
				int temp = income [firstCounter];
				income[firstCounter] = income[smallestNum];
				income[smallestNum] = temp;
			}
		}
		//Return the sorted array
		return income;
	}
	
	public static int maxSalary() {
		//Declare objects and variables with scope maxSalary method
		boolean looper = true;
		int starterNum = 1;
		int childTax = 0;
		
		//While variable looper is true, pass the current number to the taxCalc method
		//and round that value
		while (looper) {
			childTax = TaxCalculator.taxCalc(starterNum);
			childTax = Math.round(childTax);
			
			//If the tax is equal to the value, break out of the look
			if (childTax == starterNum) {
				looper = false;
			}
			//If the tax is not equal, loop again with the number plus one
			else {
				looper = true;
				starterNum++;
			}
		}
		//Return calculated value
		return childTax;
	}
}
