import java.util.Scanner;
import java.util.*; 

public class organisation extends node{
	//Sub class of class node
	float x;
	float y;
	List<Integer> list_i = new ArrayList<>();
	
	public organisation(Scanner myObj) {
		super(myObj);
		this.type = "organisation";
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
