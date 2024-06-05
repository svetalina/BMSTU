import tkinter as tk

color1 = "#8CCBFF"
color2 = "#002A4D"
color3 = "#FFFFFF"

class Item:
    def __init__(self, text, var, value=0):
        self.text = text
        self.var = var
        self.value = value

class InputList(tk.Frame):
    def __init__(self, master, items = [], title=None):
        super().__init__(master)
        self.configure(bg=color1)
        i = 0
        if title:
            t = tk.Label(self, text=title, bg=color1)
            t.grid(row=i, column=0, columnspan=2, padx=10, pady=10)
            i += 1
        for item in items: 
            label = tk.Label(self, text=item.text, background=color1)
            label.grid(row=i, column=0, sticky="e")
            entry = tk.Entry(self, width=10, textvariable=item.var, background="white")
            entry.grid(row=i, column=1)
            entry = tk.Entry(self, width=10, textvariable=item.var, justify="center")
            entry.insert(0, str(item.value))
            i+=1
        
