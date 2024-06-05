import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
import tkinter as tk
from tkinter import ttk

def plot_normal_distribution(m, d, start, end, step):
    x = np.arange(start, end + step, step)
    cdf = norm.cdf(x, m, d)
    pdf = norm.pdf(x, m, d)

    plt.figure(figsize=(12, 6))

    plt.subplot(1, 2, 1)
    plt.plot(x, cdf)
    plt.title('Функция нормального распределения')
    plt.xlabel('x')
    plt.ylabel('F(x)')
    plt.grid(True)

    plt.subplot(1, 2, 2)
    plt.plot(x, pdf)
    plt.title('Плотность нормального распределения')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.grid(True)

    plt.tight_layout()
    plt.show()

def on_submit():
    mean_value = float(mean_entry.get())
    std_dev_value = float(std_dev_entry.get())
    display_start_value = float(display_start_entry.get())
    display_end_value = float(display_end_entry.get())
    step_value = float(step_entry.get())

    plot_normal_distribution(mean_value, std_dev_value, display_start_value, display_end_value, step_value)

root = tk.Tk()
root.title("Параметры построения")

mean_label = ttk.Label(root, text="Значение параметра μ:")
mean_label.grid(row=0, column=0, padx=10, pady=5, sticky="w")
mean_entry = ttk.Entry(root)
mean_entry.grid(row=0, column=1, padx=10, pady=5)

std_dev_label = ttk.Label(root, text="Значение параметра σ:")
std_dev_label.grid(row=1, column=0, padx=10, pady=5, sticky="w")
std_dev_entry = ttk.Entry(root)
std_dev_entry.grid(row=1, column=1, padx=10, pady=5)

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
