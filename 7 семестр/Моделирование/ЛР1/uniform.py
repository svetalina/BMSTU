import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import uniform
import tkinter as tk
from tkinter import ttk

def plot_uniform_distribution(a, b, start, end, step):
    x = np.arange(start, end + step, step)
    cdf = uniform.cdf(x, a, b - a)
    pdf = uniform.pdf(x, a, b - a)

    plt.figure(figsize=(12, 6))

    plt.subplot(1, 2, 1)
    plt.plot(x, cdf)
    plt.title('Функция равномерного распределения')
    plt.xlabel('x')
    plt.ylabel('F(x)')
    plt.grid(True)

    plt.subplot(1, 2, 2)
    plt.plot(x, pdf)
    plt.title('Плотность равномерного распределения')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.grid(True)

    plt.tight_layout()
    plt.show()

def on_submit():
    a_value = float(a_entry.get())
    b_value = float(b_entry.get())
    display_start_value = float(display_start_entry.get())
    display_end_value = float(display_end_entry.get())
    step_value = float(step_entry.get())

    plot_uniform_distribution(a_value, b_value, display_start_value, display_end_value, step_value)


root = tk.Tk()
root.title("Параметры построения")


a_label = ttk.Label(root, text="Значение параметра a:")
a_label.grid(row=0, column=0, padx=10, pady=5, sticky="w")
a_entry = ttk.Entry(root)
a_entry.grid(row=0, column=1, padx=10, pady=5)

b_label = ttk.Label(root, text="Значение параметра b:")
b_label.grid(row=1, column=0, padx=10, pady=5, sticky="w")
b_entry = ttk.Entry(root)
b_entry.grid(row=1, column=1, padx=10, pady=5)

display_start_label = ttk.Label(root, text="Начало интервала:")
display_start_label.grid(row=2, column=0, padx=10, pady=5, sticky="w")
display_start_entry = ttk.Entry(root)
display_start_entry.grid(row=2, column=1, padx=10, pady=5)

display_end_label = ttk.Label(root, text="Конец интервала:")
display_end_label.grid(row=3, column=0, padx=10, pady=5, sticky="w")
display_end_entry = ttk.Entry(root)
display_end_entry.grid(row=3, column=1, padx=10, pady=5)

step_label = ttk.Label(root, text="Шаг:")
step_label.grid(row=4, column=0, padx=10, pady=5, sticky="w")
step_entry = ttk.Entry(root)
step_entry.grid(row=4, column=1, padx=10, pady=5)

submit_button = ttk.Button(root, text="Построить", command=on_submit)
submit_button.grid(row=5, column=0, columnspan=2, pady=10)

root.mainloop()