import java.util.*;
import java.util.List;
import java.util.Scanner;

public class group extends node{
	//Sub class of class node
	List<Integer> list_i = new ArrayList<>();
	List<Integer> list_b = new ArrayList<>();
	
	public group(Scanner myObj) {
		super(myObj);
		this.type = "group";
	}
	
	void print_obj() {
		super.print_obj();
		System.out.println("Type:"+type);
	}
}
