
from tkinter import *
import Input as i
from PfeFrame import *

root = Tk()
root.geometry('1700x800')

root_frame = Frame(root)
root_frame.pack(fill=BOTH, expand=1)

base_canvas = Canvas(root_frame)
base_canvas.pack(side=LEFT, fill=BOTH, expand=1)

base_scrollbar = Scrollbar(root_frame, orient=VERTICAL, command=base_canvas.yview)
base_scrollbar.pack(side=RIGHT, fill=Y)

base_canvas.configure(yscrollcommand=base_scrollbar.set)
base_canvas.bind('<Configure>', lambda e: base_canvas.configure(scrollregion=base_canvas.bbox(ALL)))

base_frame = Frame(base_canvas)
base_canvas.create_window((0,0), window=base_frame, anchor=NW)

experiment = PfeFrame(base_frame)

varList = {
    "lambda": StringVar(),
    "lambda2": StringVar(),
    "mu": StringVar(),
    "mu2": StringVar(),
    "k": StringVar(), 
    "N": StringVar(), 
    "start": StringVar(), 
    "end": StringVar(),
    "N_exp": StringVar(), 
    "lambda_min": StringVar(), 
    "lambda_max": StringVar(),
    "lambda2_min": StringVar(), 
    "lambda2_max": StringVar(),
    "mu_min": StringVar(),
    "mu_max": StringVar(),
    "mu2_min": StringVar(),
    "mu2_max": StringVar(),
}

def work_one(Event): 
    lam = float(varList["lambda"].get())
    lam2 = float(varList["lambda2"].get())
    mu = float(varList["mu"].get())
    mu2 = float(varList["mu2"].get())
    experiment.count_one(lam=lam, mu=mu, lam2=lam2, mu2=mu2)

def work_pfe(Event):
    try:
        lambda_min = float(varList["lambda_min"].get())
        lambda_max = float(varList["lambda_max"].get())
        mu_min = float(varList["mu_min"].get())
        mu_max = float(varList["mu_max"].get())
        lambda2_min = float(varList["lambda2_min"].get())
        lambda2_max = float(varList["lambda2_max"].get())
        mu2_min = float(varList["mu2_min"].get())
        mu2_max = float(varList["mu2_max"].get())
        count = float(varList["N"].get())
        experiment.run(
            lambda_min=lambda_min,
            lambda_max=lambda_max,
            mu_max=mu_max,
            mu_min=mu_min, 
            lambda2_min=lambda2_min,
            lambda2_max=lambda2_max,
            mu2_max=mu2_max,
            mu2_min=mu2_min, 
            count=count, 
        )        
        add_button.config(state='normal')

    
    except ValueError:
        tk.messagebox.showinfo(title="error", message="Ошибка ввода параметров!")

def pfe_inputs(root):
    t = tk.Label(root, text="ОЦКП")
    t.grid(column=1)
    frame_inputs = Frame(root)
    items_1 = [
        i.Item(text="Минимум:", var=varList["lambda_min"], value=10), 
        i.Item(text="Максимум:", var=varList["lambda_max"], value=30), 
    ]
    items_2 = [
        i.Item(text="Минимум:", var=varList["lambda2_min"], value=10), 
        i.Item(text="Максимум:", var=varList["lambda2_max"], value=30), 
    ]
    items_3 = [
        i.Item(text="Минимум:", var=varList["mu_min"], value=80),
        i.Item(text="Максимум:", var=varList["mu_max"], value=120),
    ]
    items_4 = [
        i.Item(text="Минимум:", var=varList["mu2_min"], value=80),
        i.Item(text="Максимум:", var=varList["mu2_max"], value=120),
    ]
    i_list_1 = i.InputList(master=frame_inputs, items=items_1, title="Интенсивность поступления заявок 1")
    i_list_2 = i.InputList(master=frame_inputs, items=items_2, title="Интенсивность поступления заявок 2")
    i_list_3 = i.InputList(master=frame_inputs, items=items_3, title="Интенсивность обработки заявок 1")
    i_list_4 = i.InputList(master=frame_inputs, items=items_4, title="Интенсивность обработки заявок 2")

    i_list_1.pack(side=LEFT, padx=10)
    i_list_2.pack(side=LEFT,  padx=10)
    i_list_3.pack(side=LEFT,  padx=10)
    i_list_4.pack(side=LEFT,  padx=10)

    frame_inputs.grid(column=1)

    items_4 = [
        i.Item(text="Число заявок:", var=varList["N"], value=5000), 
    ]

    i_list_5 = i.InputList(master=root, items=items_4)
    i_list_5.grid(column=1,  padx=10)

    btn = Button(root, text="Запуск")
    btn.bind("<Button-1>", work_pfe)
      
    btn.grid(column=1, padx=10, pady=10) 

def draw_new_point(root):
    items = [
        i.Item(text="Интенсивность поступления заявок 1:", var=varList["lambda"], value=20),
        i.Item(text="Интенсивность поступления заявок 2:", var=varList["lambda2"], value=20),
        i.Item(text="Интенсивность обслуживания заявок 1:", var=varList["mu"], value=100),
        i.Item(text="Интенсивность обслуживания заявок 2:", var=varList["mu2"], value=100),
    ]
    i_list = i.InputList(master=root, items=items, title="Добавление точки факторного пространства")
    i_list.grid(column=1)

    btn = Button(root, text="Добавить", state=DISABLED)
    btn.bind("<Button-1>", work_one)       
    btn.grid(column=1, padx=10, pady=10)
    btn.config(state="disabled")
    return btn


def expirement_list(root): 
    items = [
        i.Item(text="От:", var=varList["start"], value=0.01), 
        i.Item(text="До:", var=varList["end"], value=1.1), 
        i.Item(text="Число заявок:", var=varList["N_exp"], value=1000)
    ]

    i_list = i.InputList(master=root, items=items)
    i_list.grid(column=1)

    btn2 = Button(root, text="Запуск")
    btn2.bind("<Button-1>", work_view)       
    btn2.grid(column=1, padx=10, pady=10) 

if __name__ == '__main__':
    # f_proc = Frame(root)
    # f_view = Frame(root, highlightbackground="lightgrey", highlightthickness=1)

    # # one_model_list(f_proc)
    # expirement_list(f_view)

    # # f_proc.grid(row=0, column=2,  padx=10, pady=10)
    # # f_view.grid(row=0, column=3,  padx=10, pady=10)

    f_pfe = Frame(base_frame, highlightbackground="lightgrey", highlightthickness=1)
    f_one = Frame(base_frame, highlightbackground="lightgrey", highlightthickness=1)
    pfe_inputs(f_pfe)
    add_button = draw_new_point(f_one)
    f_pfe.grid(row=0, column=0)
    f_one.grid(row=0, column=1)

    experiment.grid(row=1, column=0, columnspan=2,   padx=10, pady=10)

    root.mainloop()
    

    