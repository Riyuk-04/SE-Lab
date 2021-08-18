import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class individual extends node{
	//Sub class of class node
	String birthday;
	List<Integer> list_n = new ArrayList<>();
	
	public individual(Scanner myObj) {
		super(myObj);
		this.type = "individual";
		System.out.print("Enter the birthday(dd/mm/yyyy):");
		this.birthday = myObj.next();
	}
	
	void print_obj() {
		super.print_obj();
		System.out.println("Type:"+type);
		System.out.println("Birthday:"+birthday);
	}
}
