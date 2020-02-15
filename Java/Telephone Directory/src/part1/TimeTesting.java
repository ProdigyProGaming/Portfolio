package part1;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class TimeTesting {
	private static Directory direc;

	
	
	public static void inserting() throws FileNotFoundException {
		
		StopWatch sw = new StopWatch();
		Entry e;
		
		long[] timeArray = new long[88799];
		Scanner inFile = new Scanner(new FileReader("largeFile.txt"));
		int i = 0;
		long sum = 0;
		
		while (inFile.hasNextLine()) {
			e = new Entry();
			e.setSurname(inFile.next());
			e.setInitials(inFile.next());
			e.setTelExtension(inFile.next());
			sw.reset();
			sw.start();
			direc.insertEntry(e);
			sw.stop();
			sum += sw.getElapsedTime();
			timeArray[i] = sw.getElapsedTime();
			i++;
		}
		long average = sum/88799;
		System.out.println("Insert Average: " + average);
	}
	
	public static void search() throws FileNotFoundException {
		System.out.println("\nSearchAdding");
		inserting();
		
		StopWatch sw = new StopWatch();
		Entry e;
		
		long[] timeArray = new long[88799];
		Scanner inFile = new Scanner(new FileReader("largeFile.txt"));
		int i = 0;
		long sum = 0;
		
		while (inFile.hasNextLine()) {
			e = new Entry();
			e.setSurname(inFile.next());
			e.setInitials(inFile.next());
			e.setTelExtension(inFile.next());
			String s = e.getSurname();
			sw.reset();
			sw.start();
			direc.search(s, 0, 88799);
			sw.stop();
			sum += sw.getElapsedTime();
			timeArray[i] = sw.getElapsedTime();
			i++;
		}
		long average = sum/88799;
		System.out.println("Search Average: " + average);
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		
		System.out.print("ArrayDirInsert - ");
		direc = new ArrayDirectory();
		inserting();
		System.out.print("ListDirInsert - ");
		direc = new ListDirectory();
		inserting();
		System.out.print("HashDirInsert - ");
		direc = new HashDirectory();
		inserting();
		
		System.out.println("\nArrayDirSearch");
		direc = new ArrayDirectory();
		search();
		System.out.println("\nListDirSearch");
		direc = new ListDirectory();
		search();
		System.out.println("\nHashDirSearch");
		direc = new HashDirectory();
		search();
	}
}
