package version_1;

import javax.swing.*;

public class UITrial{
	
	private JFrame f;
	
	public JFrame getF() {
		return f;
	}

	public void setF(JFrame f) {
		this.f = f;
	}
	
	public void test() {
		f = new JFrame("Sandwich Builder");
		
		getF().setSize(1000, 1000);
		getF().setLayout(null);
		getF().setVisible(true);
	}
	
	
}
