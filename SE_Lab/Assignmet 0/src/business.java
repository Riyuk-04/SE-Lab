import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class business extends node{
	//Sub class of class node
	float x;
	float y;
	List<Integer> list_owner = new ArrayList<>();
	List<Integer> list_customer = new ArrayList<>();
	List<Integer> list_g = new ArrayList<>();
	
	public business(Scanner myObj) {
		super(myObj);
		this.type = "business";
		System.out.print("Enter the x coordinate:");
		this.x = myObj.nextFloat();
		System.out.print("Enter the y coordinate:");
		this.y = myObj.nextFloat();
	}
	
	void print_obj() {
		super.print_obj();
		System.out.println("Type:"+type);
		System.out.printf("Coordinates:(%f,%f)\n",x,y);
	}
}
