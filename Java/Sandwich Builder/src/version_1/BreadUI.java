package version_1;

import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.table.TableColumn;

public class BreadUI extends UITrial implements ActionListener{
	
	private JButton selectItem;
	private JButton addNewItem;
	private JComboBox cb;
	
	public void addToReciept() {
		
	}
	
	public void recieptCreator() {
		JLabel recieptTitle = new JLabel("This is your current order:");
		recieptTitle.setBounds(550, 20, 200, 50);
		getF().add(recieptTitle);
		
		String data[][] = {{"9 Grain Wheat bread", "£1.00", "Yes"},
				           {"Flat Bread", "£1.00", "Yes"}};
		String column[] = {"Ingredient", "Price", "Vegetarian"};
		
		JTable jt = new JTable(data, column);
		jt.setBounds(550, 50, 300, 300);
		TableColumn column1 = null;
	    for (int i = 0; i < 3; i++) {
	    	column1 = jt.getColumnModel().getColumn(i);
	    	if (i == 0) {
	    		column1.setPreferredWidth(200);
	    	}
	    	else {
	    		column1.setPreferredWidth(50);
	    	}
	    }
		getF().add(jt);
		getF().revalidate();
		getF().repaint();		
	}
	
	public void breadSelectionUI() {
		JLabel label1 = new JLabel("Please select your desired bread");
		label1.setBounds(50, 20, 500, 30);
		
		String bread[] = {"9 Grain Wheat bread", "Flat Bread", "Hearty Italian", "Honey Oat", "Italian Herbs and Cheese", "White Bread"};
		cb = new JComboBox(bread);
		cb.setBounds(50, 50, 200, 30);
		
		selectItem = new JButton("Select");
		selectItem.setBounds(260, 50, 80, 30);
		selectItem.addActionListener(this);
		
		addNewItem = new JButton("+");
		addNewItem.setBounds(400, 50, 30, 30);
		addNewItem.setMargin(new Insets(1, 1, 1, 1));
		addNewItem.addActionListener(this);
		
		getF().add(label1);
		getF().add(selectItem);
		getF().add(addNewItem);
		getF().add(cb);
		getF().revalidate();
		getF().repaint();
	}
	
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == selectItem) {
			System.out.println(cb.getItemAt(cb.getSelectedIndex()));
		}
		else if (e.getSource() == addNewItem) {
			System.out.println("(Create New Field)");
		}
		
	}
}
