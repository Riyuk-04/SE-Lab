import java.util.Scanner;
import java.util.*;

public class node {
	//Super class of all types of nodes
	int id;
	String name;
	String type;
	String creation_date;
	Set<String> posts = new HashSet<String>(); 
	
	public node(Scanner myObj) {
		System.out.print("Enter the node id(unique):");
		this.id = myObj.nextInt();
		System.out.print("Enter the name:");
		this.name = myObj.next();
		System.out.print("Enter the creation date(dd/mm/yyyy):");
		this.creation_date = myObj.next();
	}
	
	void print_obj() {
		//Function to print variables of the class
		System.out.println("ID:"+id);
		System.out.println("Name:"+name);
		System.out.println("Creation date:"+creation_date);
		System.out.println("Posts:"+posts);
	}
	
}
