//Author: Arron Rawstron
//Date: 23/10/18
//Program Purpose: Calculate and Display Tax
//Class Purpose: Create Chart and Table

public class TaxChart {
	//Declare variables and arrays with the scope of TaxChart class
	private static int[] income;
	private static double[] tax;
	private static int arrayLength;
	
	//Constructor that takes in income array, assigns it to the global array
	//and passes the user to the createTaxArray method
	public TaxChart(int[] customIncome) {
		income = customIncome;
		arrayLength = customIncome.length;
		createTaxArray();
	}
	
	//Method to create global tax array using the global income array
	public void createTaxArray() {
		//Declare temporary tax array with scope createTaxArray method
		double[] tempTax = new double[arrayLength];
		
		//For each value in income array, pass that value to the TaxCalculator class
		//and store it in the global tax array
		for (int counter = 0; counter < arrayLength; counter++) {
			tempTax[counter] = TaxCalculator.taxCalc(TaxChart.income[counter]);
		}
		
		tax = tempTax;
	}
	
	public void draw() {
		//Declare variables with scope draw method
		final double MULTIPLIER = 0.45;
		final int MAX_ARRAY_VALUE = 600;
		
		final int AXIS_BAR_LENGTH_OR_HEIGHT = 1;
		final int AXIS_BAR_HORIZONTAL_MOVE = -55;
		final int X_LENGTH_Y_HEIGHT = 280;
		final int X_AXIS_BAR_VERTICAL_MOVE = 245;
		final int Y_AXIS_BAR_VERTICAL_MOVE = -35;
		
		final int BAR_WIDTH = 1;
		final int OBJ_MOVE_HORIZONTAL = -50;
		final int OBJ_MOVE_VERTICAL = -25;
				
		//Create canvas for displaying the graph
		Canvas graph = Canvas.getCanvas();
		graph.setVisible(true);
		
		//Create bar and adjust settings for x axis
		Bar xAxisBar = new Bar();
		xAxisBar.changeColour(Colour.BLACK);
		xAxisBar.changeSize(X_LENGTH_Y_HEIGHT, AXIS_BAR_LENGTH_OR_HEIGHT);
		xAxisBar.moveVertical(X_AXIS_BAR_VERTICAL_MOVE);
		xAxisBar.moveHorizontal(AXIS_BAR_HORIZONTAL_MOVE);
		xAxisBar.makeVisible();
		
		//Create bar and adjust settings for y axis
		Bar yAxisBar = new Bar();
		yAxisBar.changeColour(Colour.BLACK);
		yAxisBar.changeSize(AXIS_BAR_LENGTH_OR_HEIGHT, X_LENGTH_Y_HEIGHT);
		yAxisBar.moveVertical(Y_AXIS_BAR_VERTICAL_MOVE);
		yAxisBar.moveHorizontal(AXIS_BAR_HORIZONTAL_MOVE);
		yAxisBar.makeVisible();
		
		//For each item in the income array
		for (int counter = 0; counter < arrayLength; counter++) {
			//Create new bar for the net income and adjust the settings for it
			Bar incomeBar = new Bar();
			incomeBar.changeColour(Colour.YELLOW);
			incomeBar.changeSize(BAR_WIDTH, (int)(income[counter] * MULTIPLIER));
			incomeBar.moveVertical((int) Math.round(OBJ_MOVE_VERTICAL + (MAX_ARRAY_VALUE - income[counter]) * MULTIPLIER));
			incomeBar.moveHorizontal((int) Math.round(OBJ_MOVE_HORIZONTAL + income[counter] * MULTIPLIER ));
			incomeBar.makeVisible();
			
			//Create new bar for the tax and adjust the settings for it
			Bar taxBar = new Bar();
			taxBar.changeColour(Colour.RED);
			taxBar.moveVertical((int) Math.round(OBJ_MOVE_VERTICAL + (MAX_ARRAY_VALUE - income[counter]) * MULTIPLIER));
			taxBar.moveHorizontal((int) Math.round(OBJ_MOVE_HORIZONTAL + income[counter] * MULTIPLIER));
			taxBar.makeVisible();
			
			//Set tax bar to 1 if tax is smaller than 1 but greater than 0
			if (((int)(tax[counter] * MULTIPLIER) == 0) && (tax[counter] * MULTIPLIER != 0)) {
				taxBar.changeSize(BAR_WIDTH, 1);
			}
			else {
				taxBar.changeSize(BAR_WIDTH, (int)(tax[counter] * MULTIPLIER));
			}
		}
	}
	
	public void printTable() {
		//Declare string with format settings
		String formatSetting = ("|%-10s|%-10s|%-10s|\n");
		
		//Output headers in the format
		
		System.out.format(formatSetting, "Income", "Net Income", "Tax");
		System.out.println("----------------------------------------");
		
		//For each item in income array, output the income, net income and tax with the format applied
		for (int counter = 0; counter < arrayLength; counter ++) {
			System.out.format(formatSetting, income[counter], income[counter] - tax[counter], tax[counter]);
		}
	}
}
