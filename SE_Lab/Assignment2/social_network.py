from tkinter import *
from PIL import Image,ImageTk
from tkinter import filedialog

users = {"None"}
groups = {"None"}
user_all = {"None"}
groups_all = {"None"}
current_user = "Please Select An User"
all_messages = []

def initialize():
    global users, user_all, groups, current_user, all_messages
    file = open('social_network.txt', 'r')
    flag = 0
    for line in file:
        for word in line.split():
            if word == "#users":
                flag = 1
                continue
            if word == "#groups":
                flag = 2
            if ((word[-1] == ":" or word[-1] == ",") and flag == 1):
                user_all.add(word[:-1])
            if (word[-1] != ":" and word[-1] != "," and flag == 1):
                user_all.add(word)
            if(word[-1] == ":" and flag == 2):
                groups_all.add(word[:-1])

    if len(user_all) > 1:
        user_all.remove("None")
    if len(groups_all) > 1:
        groups_all.remove("None")
    file.close()

    caption = ""
    sender = ""
    reciever = ""
    image = ""
    file = open('messages.txt', 'r')
    for line in file:
        if len(line) > 1:
            if line.split()[0] == "Sender:":
                sender = line.split()[1]
            elif line.split()[0] == "Reciever:":
                reciever = line.split()[1]
            elif line.split()[0] == "Caption:":
                caption = line[9:]
            elif line.split()[0] == "Image:":
                image = line[7:-1]
                all_messages.append(Message(sender, reciever, caption, image))
            else:
                caption += line + "\n"

    file.close()

def user_add(line):
    global users, user_all, groups, current_user
    for word in line.split():
        if word != (current_user + ":"):
            if word[-1] == ",":
                users.add(word[:-1])
            else:
                users.add(word)

def find_friends():
    global users, user_all, groups, current_user
    users.clear()
    users.add("None")
    groups.clear()
    groups.add("None")

    file = open('social_network.txt', 'r')
    flag = 0
    for line in file:
        for word in line.split():
            if word == "#users":
                flag = 1
                continue
            if word == "#groups":
                flag = 2
                continue
            if (word == (current_user + ":") and flag == 1):
                user_add(line)
            if ((word == (current_user) or word == (current_user + ",")) and flag == 2):
                groups.add(line.split()[0][:-1])
    if len(groups) > 1:
        groups.remove("None")
    if len(users) > 1:
        users.remove("None")
    file.close()

class Message(object):
    def __init__(self, sender, reciever, caption, image_path):
        self.sender = sender
        self.reciever = reciever
        self.caption = caption
        self.image_path = image_path

    def store_message(self):
        file = open('messages.txt', 'a')
        file.write("Sender: " + self.sender + "\n") 
        file.write("Reciever: " + self.reciever + "\n") 
        file.write("Caption: " + self.caption + "\n") 
        file.write("Image: " + self.image_path + "\n")
        file.close()

    def print_message(self):
        print("Sender:" + self.sender + "\n") 
        print("Reciever:" + self.reciever + "\n") 
        print("Caption:" + self.caption + "\n") 
        print("Image:" + self.image_path + "\n")

class User_ID_label(Frame):
    def __init__(self, master = None):
        Frame.__init__(self, master, bg = "white")
        self.grid(row = 0, column = 0, sticky = "nsew")
        self.grid_rowconfigure(0, weight = 1)
        self.grid_columnconfigure(0, weight = 1)
        self.user_id_label = Label(self, text = "User ID:", bg = "white")
        self.user_id_label.grid(row = 0, column = 0, sticky = E)

class User_ID(Frame):
    def __init__(self, master = None):
        Frame.__init__(self, master, bg = "white")
        self.master = master
        User_ID_label(master)
        self.grid(row = 0, column = 1, columnspan = 3, sticky = "nsew")
        self.grid_columnconfigure(1, weight = 1)
        self.user_id = Label(self, bg = "white")
        self.user_id.grid(row = 0, column = 0, sticky = W)

        self.user_id_var = StringVar(self)
        self.user_id_var.set(current_user)
        self.drop_down = OptionMenu(self, self.user_id_var, *user_all)
        self.drop_down.grid(row = 0, column = 1)

        self.change_user_button = Button(self, text = "Change User", command = change_user, width = 10, height = 1, padx = 2, pady = 10)
        self.change_user_button.grid(row = 0, column = 2)
        
class Contacts(Frame):
    def __init__(self, master = None):
        Frame.__init__(self, master, bg = "pink")
        self.master = master
        self.grid(row = 1, column = 0, sticky = "nsew")
        self.grid_rowconfigure(1, weight = 1)

        self.contacts_label = Label(self, text = "CONTACTS:", bg = "pink", padx = 10, pady = 10)
        self.contacts_label.grid(row = 0, column = 0)

        self.textbox = Text(self, width = 15, bg = "yellow")
        self.textbox.grid(row = 1, column = 0, sticky = "ns")

    def insert(self):
        self.textbox.delete(1.0,END)
        for contact_id in users:
            self.textbox.insert(END,contact_id + "\n")

class Groups(Frame):
    def __init__(self, master = None):
        Frame.__init__(self, master, bg = "SteelBlue1")
        self.master = master
        self.grid(row = 2, column = 0, sticky = "nsew")
        self.grid_rowconfigure(1, weight = 1)

        self.group_label = Label(self, text = "GROUPS:", bg = "SteelBlue1", padx = 10, pady = 10)
        self.group_label.grid(row = 0, column = 0)
        
        self.textbox = Text(self, width = 15, bg = "yellow")
        self.textbox.grid(row = 1, column = 0, sticky = "ns")

    def insert(self):
        self.textbox.delete(1.0,END)
        for group_id in groups:
            self.textbox.insert(END,group_id + "\n")

class Post_content(Frame):
    def __init__(self, master = None):
        Frame.__init__(self, master, bg = "cyan")
        self.master = master
        self.grid(row = 2, column = 1, rowspan = 5, columnspan = 2, sticky = "nsew")
        self.grid_columnconfigure(0, weight = 1)
        self.grid_columnconfigure(1, weight = 1)
        self.grid_rowconfigure(4, weight = 1)

        self.post_label = Label(self, text = "POST CONTENT", bg = "cyan", padx = 10, pady = 10)
        self.post_label.grid(row = 0, column = 0, columnspan = 2)

        self.selection_label = Label(self, text = "Please select location for the post", bg = "cyan", padx = 100, pady = 10)
        self.selection_label.grid(row = 1, column = 0, sticky = E)
        self.user_id_var = StringVar(self)
        self.user_id_var.set("None")
        self.drop_down = OptionMenu(self, self.user_id_var, *users.union(groups))
        self.drop_down.grid(row = 1, column = 1, sticky = W)
        
        self.text_entry_label = Label(self, text = "Enter text", bg = "cyan", padx = 10, pady = 10)
        self.text_entry_label.grid(row = 2, column = 0)
        self.image_entry_label = Label(self, text = "Insert image", bg = "cyan", padx = 10, pady = 10)
        self.image_entry_label.grid(row = 2, column = 1)
        self.entry_image_text = Text(self, bg = "yellow", width = 70, height = 1)
        self.entry_image_text.grid(row = 4, column = 1)

        self.entry_text = Text(self, bg = "yellow", width = 70, height = 10)
        self.entry_text.grid(row = 3, column = 0)
        self.entry_image = Button(self, text = "Select Image", command = self.select_image, width = 30, height = 2, padx = 2, pady = 2)
        self.entry_image.grid(row = 3, column = 1)

        self.post_button = Button(self, text = "POST!", command = self.post, width = 30, height = 2, padx = 2, pady = 10)
        self.post_button.grid(row = 4, column = 0)

        self.image_path = "None"

    def update_menu(self):
        menu = self.drop_down["menu"]
        menu.delete(0, "end")
        for string in users.union(groups):
            menu.add_command(label=string, 
                             command=lambda value=string: self.user_id_var.set(value))

    def select_image(self):
        image_path = filedialog.askopenfilename(filetypes = (("Png image", "*.png*"), ("Jpeg image", "*.jpeg*")))
        if len(image_path) > 0:
            self.image_path = image_path
            self.entry_image_text.insert(END, self.image_path)

    def post(self):
        global all_messages
        self.caption = self.entry_text.get("1.0", END)
        self.entry_text.delete(1.0,END)
        message = Message(current_user, self.user_id_var.get(), self.caption, self.image_path)
        message.store_message()
        all_messages.append(message)
        change_user()

class Inbox(Frame):
    def __init__(self, master = None):
        Frame.__init__(self, master, bg = "green yellow")
        self.master = master
        self.grid(row = 1, column = 1, sticky = "nsew")
        self.grid_rowconfigure(1, weight = 1)
        self.grid_columnconfigure(0, weight = 1)

        self.inbox_label = Label(self, text = "INBOX", bg = "green yellow", font = ("Calibiri", 20)).grid(row = 0, column = 0)
        self.textbox = Text(self, bg = "white")
        self.textbox.grid(row = 1 , column = 0, sticky = "nsew")

    def insert(self, caption):
        self.textbox.insert(END, caption + "\n")

    def update_inbox(self):
        self.images = []
        index = 0
        self.textbox.delete(1.0,END)
        for message in all_messages:
            if ((message.reciever == current_user) or (message.reciever in groups)):
                self.insert(message.sender + " -> " + message.reciever + " : " + message.caption)
                if message.image_path != "None":
                    self.images.append(PhotoImage(file = message.image_path))
                    self.images[index] = self.images[index].subsample(2, 2)
                    self.textbox.image_create(END, image = self.images[index])
                    self.textbox.insert(END, "\n\n")
                    index += 1

class Window(Frame):
    def __init__(self, master = None):
        Frame.__init__(self, master)
        self.master = master
        self.grid(row = 0, column = 0, rowspan = 3,columnspan = 2, sticky = "nsew")
        master.wm_title("Facebok")

        master.grid_columnconfigure(1, weight = 1)
        master.grid_rowconfigure(1, weight = 100)
        master.grid_rowconfigure(2, weight = 1)

        self.top_bar = User_ID(master)
        self.contacts = Contacts(master)
        self.groups = Groups(master)
        self.post_content = Post_content(master)
        self.inbox = Inbox(master)

        master.geometry("{0}x{1}+0+0".format(master.winfo_screenwidth(), master.winfo_screenheight()))

def change_user():
    global users, user_all, groups, current_user
    app.top_bar.user_id.config(text = app.top_bar.user_id_var.get())
    current_user = app.top_bar.user_id_var.get()
    find_friends()

    app.contacts.insert()
    app.groups.insert()
    app.post_content.update_menu()
    app.inbox.update_inbox()

initialize()
root = Tk()
app = Window(root)
root.mainloop()