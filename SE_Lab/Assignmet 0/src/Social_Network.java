import java.util.*;
import java.util.Scanner;

public class Social_Network {

	public static void main(String[] args) {
		//Main function
		Scanner myObj = new Scanner(System.in);	//Create a scanner object
		List<node> arrl = new ArrayList<>();
		print_menu();
	    while(true) {
	    	System.out.print("Please enter a number corresponding to the function you wish to perform(Press 0 to print the menu):");
	    	int input = myObj.nextInt();
	    	switch (input) {	//Switch cases as per menu
	    	case -1:
	    		myObj.close();
	    		System.exit(1);
	    		break;
	    	case 0:
	    		print_menu();
	    		break;
	        case 1:
	        	arrl.add(CreateNode(myObj));
	        	break;
	        case 2:
	        	DeleteNode(myObj, arrl);
	            break;
	        case 3:
	        	insert_links(myObj, arrl);
	            break;
	        case 4:
	        	search_display(myObj, arrl);
	            break;
	        case 5:
	        	print_links(myObj, arrl, 0);
	            break;
	        case 6:
	        	post_content(myObj, arrl);
	            break;
	        case 7:
	        	System.out.println("Enter the user id");
	    		int id = myObj.nextInt();
	    		myObj.nextLine();
	    		int index = find_index(id, arrl);
	    		if(index == -1) System.out.println("No such user exists");
	    		else System.out.println(arrl.get(index).posts);
	            break;
	        case 8:
	        	print_links(myObj, arrl, 1);
	        	break;
	        default:
	            System.out.print("Invalid input");
	        }
	    }
	}

	public static int find_index(int id, List<node> arrl) {
		/*Function to return the value of the index given node id
		 * Arguements:
		 *id(int):id of the node whose index is to be found
		 *arrl(list<node>):List of all the stored nodes
		 *Return:
		 *index(int):index of the node in arrl, -1 if node not present*/
		for (int i = 0; i < arrl.size(); i++)
            if(arrl.get(i).id == id) return i;
        return -1;
	}
	
	public static void print_menu() {
		//Function to print menu
		System.out.print("-1->To Exit the menu\n"
				+ "0->To print the menu \n"
	    		+ "1->Create nodes \n"
	    		+ "2->Delete nodes \n"
	    		+ "3->Insert links \n"
	    		+ "4->Search for nodes using the name or type or birthday\n"
	    		+ "5->Print all linked nodes to a given input node\n"
	    		+ "6->Create and post content by a user\n"
	    		+ "7->Search for content posted by any node\n"
	    		+ "8->Display all content posted by nodes linked to a given node\n");
	}
	
	public static node CreateNode(Scanner myObj) {
		/*Function to return a new node
		 * Arguements:
		 *myObj(object of class Scanner):Scanner object to take user input
		 *Return:
		 *node(node):a new node of a type else a null node*/
		System.out.println("Enter the type(i->individual,b->business,o->organisation,g->group):");
		String type = myObj.next();
		if(type.equals("i") || type.equals("individual")) return new individual(myObj);
		if(type.equals("b") || type.equals("business")) return new business(myObj);
		if(type.equals("o") || type.equals("organisation")) return new organisation(myObj);
		if(type.equals("g") || type.equals("group")) return new group(myObj);
		return null;
	}
	
	public static void DeleteNode(Scanner myObj, List<node> arrl) {
		/*Function to delete a node
		 * Arguements:
		 *myObj(object of class Scanner):Scanner object to take node id
		 *arrl(list<node>):List of all the stored nodes*/
		System.out.println("Enter the id of node to be deleted:");
		int id = myObj.nextInt();
		int index = find_index(id, arrl);
		if(index == -1)	System.out.println("Id does not exist");
		else	arrl.remove(index);
	}
	
	public static void search_display(Scanner myObj, List<node> arrl) {
		/*Function to search and display a node using name,type or birthday
		 * Arguements:
		 *myObj(object of class Scanner):Scanner object to take node id
		 *arrl(list<node>):List of all the stored nodes*/
		System.out.println("How do you want to search:\n"
				+ "1->using name\n"
				+ "2->using type\n"
				+ "3->using birthday\n");
		int option = myObj.nextInt();
		if (option == 1) {
			System.out.println("Please enter the name:");
			String name = myObj.next();
			for (int i = 0; i < arrl.size(); i++)
	            if(name.equals(arrl.get(i).name)) arrl.get(i).print_obj();
		}
		if (option == 2) {
			System.out.println("Please enter the type(individual,group,business,organisation):");
			String type = myObj.next();
			for (int i = 0; i < arrl.size(); i++) 
	            if(type.equals(arrl.get(i).type)) arrl.get(i).print_obj();
		}
		if (option == 3) {
			System.out.println("Please enter the birthday:");
			String birthday = myObj.next();
			String type = "individual";
			for (int i = 0; i < arrl.size(); i++)
	            if(type.equals(arrl.get(i).type)) if(birthday.equals(((individual)arrl.get(i)).birthday)) arrl.get(i).print_obj();
		}
	}
	
	public static void post_content(Scanner myObj, List<node> arrl) {
		/*Function to post content of a node
		 * Arguements:
		 *myObj(object of class Scanner):Scanner object to take node id
		 *arrl(list<node>):List of all the stored nodes*/
		System.out.println("Enter the user id");
		int id = myObj.nextInt();
		myObj.nextLine();
		System.out.println("Enter the contents of the post");
		String content = myObj.nextLine();
		
		int index = find_index(id, arrl);
        if(index != -1)	arrl.get(index).posts.add(content);
        else	System.out.println("No user with ID:"+id);
	}

	public static void insert_links(Scanner myObj, List<node> arrl) {
		/*Function to insert links between nodes
		 * Arguements:
		 *myObj(object of class Scanner):Scanner object to take node id
		 *arrl(list<node>):List of all the stored nodes*/
		System.out.print("Enter the type of link\n"
				+ "1->Group-Individual\n"
				+ "2->Organisation-Individual\n"
				+ "3->Business-Individual(as an owner)\n"
				+ "4->Business-Individual(as a customer)\n"
				+ "5->Business-Group\n");
		int option = myObj.nextInt();
		if(option == 1) {
			System.out.print("Enter Group id:");
			int grp_id = myObj.nextInt();
			System.out.print("Enter Individual id:");
			int ind_id = myObj.nextInt();
			int grp_index = find_index(grp_id, arrl);
			int ind_index = find_index(ind_id, arrl);
			
			((group)arrl.get(grp_index)).list_i.add(((individual)arrl.get(ind_index)).id);
			((individual)arrl.get(ind_index)).list_n.add(((group)arrl.get(grp_index)).id);
		}
		if(option == 2) {
			System.out.print("Enter Organistation id:");
			int org_id = myObj.nextInt();
			System.out.print("Enter Individual id:");
			int ind_id = myObj.nextInt();
			int org_index = find_index(org_id, arrl);
			int ind_index = find_index(ind_id, arrl);
			
			((organisation)arrl.get(org_index)).list_i.add(((individual)arrl.get(ind_index)).id);
			((individual)arrl.get(ind_index)).list_n.add(((organisation)arrl.get(org_index)).id);
		}
		if(option == 3) {
			System.out.print("Enter Business id:");
			int bus_id = myObj.nextInt();
			System.out.print("Enter Individual id:");
			int ind_id = myObj.nextInt();
			int bus_index = find_index(bus_id, arrl);
			int ind_index = find_index(ind_id, arrl);
			
			((business)arrl.get(bus_index)).list_owner.add(((individual)arrl.get(ind_index)).id);
			((individual)arrl.get(ind_index)).list_n.add(((business)arrl.get(bus_index)).id);
		}
		if(option == 4) {
			System.out.print("Enter Business id:");
			int bus_id = myObj.nextInt();
			System.out.print("Enter Individual id:");
			int ind_id = myObj.nextInt();
			int bus_index = find_index(bus_id, arrl);
			int ind_index = find_index(ind_id, arrl);
			
			((business)arrl.get(bus_index)).list_customer.add(((individual)arrl.get(ind_index)).id);
			((individual)arrl.get(ind_index)).list_n.add(((business)arrl.get(bus_index)).id);
		}
		if(option == 5) {
			System.out.print("Enter Business id:");
			int bus_id = myObj.nextInt();
			System.out.print("Enter Group id:");
			int grp_id = myObj.nextInt();
			int bus_index = find_index(bus_id, arrl);
			int grp_index = find_index(grp_id, arrl);
			
			((business)arrl.get(bus_index)).list_g.add(((group)arrl.get(grp_index)).id);
			((group)arrl.get(grp_index)).list_b.add(((business)arrl.get(bus_index)).id);
		}
	}

	public static void print_links(Scanner myObj, List<node> arrl, int verbose) {
		/*Function to print all nodes linked to a given node
		 * Arguements:
		 *myObj(object of class Scanner):Scanner object to take node id
		 *arrl(list<node>):List of all the stored nodes*
		 *verbose(int):1 if want to print posts also otherwise 0*/
		System.out.println("Enter the user id");
		int id = myObj.nextInt();
		node master = arrl.get(find_index(id, arrl));
		String type = master.type;
		
		if (type.equals("individual")) {
			for (int i = 0; i < ((individual)master).list_n.size(); i++) {
				int x = find_index(((individual)master).list_n.get(i), arrl);
				if(x == -1)	continue;
				node temp = arrl.get(x);
				System.out.println("ID:" +temp.id);
				System.out.println("Name:" +temp.name);
				System.out.println("Type:" +temp.type);
				if(verbose == 1)	System.out.println(temp.posts);
			}
		}
		if (type.equals("business")) {
			System.out.println("Owners:");
			for (int i = 0; i < ((business)master).list_owner.size(); i++) {
				int x = find_index(((business)master).list_owner.get(i), arrl);
				if(x == -1)	continue;
				node temp = arrl.get(x);
				System.out.println("ID:" +temp.id);
				System.out.println("Name:" +temp.name);
				if(verbose == 1)	System.out.println(temp.posts);
			}
			System.out.println("Customers:");
			for (int i = 0; i < ((business)master).list_customer.size(); i++) {
				int x = find_index(((business)master).list_customer.get(i), arrl);
				if(x == -1)	continue;
				node temp = arrl.get(x);
				System.out.println("ID:" +temp.id);
				System.out.println("Name:" +temp.name);
				if(verbose == 1)	System.out.println(temp.posts);
			}
			System.out.println("Groups:");
			for (int i = 0; i < ((business)master).list_g.size(); i++) {
				int x = find_index(((business)master).list_g.get(i), arrl);
				if(x == -1)	continue;
				node temp = arrl.get(x);
				System.out.println("ID:" +temp.id);
				System.out.println("Name:" +temp.name);
				if(verbose == 1)	System.out.println(temp.posts);
			}
		}
		if (type.equals("group")) {
			System.out.println("Individuals:");
			for (int i = 0; i < ((group)master).list_i.size(); i++) {
				int x = find_index(((group)master).list_i.get(i), arrl);
				if(x == -1)	continue;
				node temp = arrl.get(x);
				System.out.println("ID:" +temp.id);
				System.out.println("Name:" +temp.name);
				if(verbose == 1)	System.out.println(temp.posts);
			}
			System.out.println("Businesses:");
			for (int i = 0; i < ((group)master).list_b.size(); i++) {
				int x = find_index(((group)master).list_b.get(i), arrl);
				if(x == -1)	continue;
				node temp = arrl.get(x);
				System.out.println("ID:" +temp.id);
				System.out.println("Name:" +temp.name);
				if(verbose == 1)	System.out.println(temp.posts);
			}
		}
		if (type.equals("organisation")) {
			System.out.println("Individuals:");
			for (int i = 0; i < ((organisation)master).list_i.size(); i++) {
				int x = find_index(((organisation)master).list_i.get(i), arrl);
				if(x == -1)	continue;
				node temp = arrl.get(x);
				System.out.println("ID:" +temp.id);
				System.out.println("Name:" +temp.name);
				if(verbose == 1)	System.out.println(temp.posts);
			}
		}
	}
}
