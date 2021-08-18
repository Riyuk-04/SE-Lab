from tkinter import *
import numpy as np
from matplotlib.figure import Figure 
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk) 

class RightFrame(Frame):
    def __init__(self, master = None):
        Frame.__init__(self, master, bg = "green")
        self.master = master
        self.grid(row = 1, column = 1, sticky = "nsew")
        label = Label(self, text = "Calculations", bg = "green", fg = "yellow")
        label.grid(row = 0, column = 0)     
        self.textbox = Text(self, width = 70, height = 20)
        self.textbox.grid(row = 1, column = 0)

    def insert(self, ins_string):
        self.textbox.insert(END,ins_string)

class GraphFrame(Frame):
    def __init__(self, master = None):
        Frame.__init__(self, master, bg = "green")
        self.master = master
        self.grid(row = 3, column = 0, columnspan = 2, sticky = "nsew")
        
class LeftFrame(Frame):
    def __init__(self, master = None, rframe = None, gframe = None):
        Frame.__init__(self, master,bg = "cyan")
        self.master = master
        self.rframe = rframe
        self.gframe = gframe
        self.grid(row = 1, column = 0, sticky = "nsew")
        master.grid_columnconfigure(0, weight = 1)

        self.label_exp = Label(self, text = "Expression (variable x): ", bg = "cyan").grid(row = 0, column = 0, padx = 10, pady =  20)
        self.entry_exp = Entry(self, bg = "yellow")
        self.entry_exp.grid(row = 0, column = 1, sticky = W)

        self.label_lower_bound = Label(self, text = "Lower Bound:", bg = "cyan").grid(row = 1, column = 0, padx = 10, pady = 20)
        self.entry_lower_bound = Entry(self, bg = "yellow")
        self.entry_lower_bound.grid(row = 1, column = 1, sticky = W)

        self.label_upper_bound = Label(self, text = "Upper Bound:", bg = "cyan").grid(row = 2, column = 0, padx = 10, pady = 20)
        self.entry_upper_bound = Entry(self, bg = "yellow")
        self.entry_upper_bound.grid(row = 2, column = 1, sticky = W)

        self.evaluate_button = Button(self, text = "Evaluate", command = self.evaluate, width = 10, height = 2, padx = 2, pady = 20).grid(row = 3, column = 0)
        self.plot_button = Button(self, text = "Plot", command = self.plot, width = 10, height = 2, padx = 2, pady = 20).grid(row = 3, column = 1, sticky = W)
        self.exit_button = Button(self, text = "Exit", command = exit, width = 10, height=2, padx = 2, pady = 20).grid(row = 3, column = 2)

    def evaluate(self):
        expression = self.entry_exp.get()
        lower_bound = self.entry_lower_bound.get()
        upper_bound = self.entry_upper_bound.get()
        lower_bound = float(lower_bound)
        upper_bound = float(upper_bound)
        self.rframe.textbox.delete(1.0,END)
        for x in np.linspace(lower_bound, upper_bound, 20):
            y = eval(expression)
            print(expression + ' ( ' + str(x) + ' ) ' + ' = ' + str(y))
            self.rframe.insert(expression + ' ( ' + str(x) + ' ) ' + ' = ' + str(y) + '\n')

    def plot(self):
        expression = self.entry_exp.get()
        lower_bound = self.entry_lower_bound.get()
        upper_bound = self.entry_upper_bound.get()
        lower_bound = float(lower_bound)
        upper_bound = float(upper_bound)
        x_axis = []
        y_axis = []
        for x in np.linspace(lower_bound, upper_bound, 200):
            x_axis.append(x)
            y_axis.append(eval(expression))

        fig = Figure(figsize = (5, 5), dpi = 100)
        plt = fig.add_subplot(111)
        plt.plot(x_axis,y_axis)
        canvas = FigureCanvasTkAgg(fig, master = self.gframe)   
        canvas.draw() 
        canvas.get_tk_widget().pack() 
        toolbar = NavigationToolbar2Tk(canvas, self.gframe) 
        toolbar.update() 
        canvas.get_tk_widget().pack()
            
class Window(Frame):
    def __init__(self, master = None):
        Frame.__init__(self, master)
        self.master = master
        self.grid(row = 0, column = 0, sticky = "nsew")

        self.rightframe = RightFrame(master)
        self.graphframe = GraphFrame(master)
        self.leftframe = LeftFrame(master, self.rightframe, self.graphframe)
        master.wm_title("Graph Plotter")

        master.geometry("1000x700")
        Header = Label(master, text = "Graph Plotter")
        Header.grid(row = 0, columnspan = 2)
        Output = Label(master, text = "Graph")
        Output.grid(row = 2, columnspan = 2)
        
if __name__ == "__main__":
    root = Tk() 
    app = Window(root)
    root.grid_rowconfigure(3, weight = 1)
    root.mainloop()