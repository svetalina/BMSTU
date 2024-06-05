from table import *
from algorithms import *

def main():
    x_arr = [1, 2, 3, 4, 5, 6]
    y_arr = [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]

    methods = [left_difference_derivative, center_difference_derivative, second_formula_runge,
               alignment_vars_difference, second_difference_derivative]

    table = fill_table(x_arr, y_arr, methods)
    print_table(table)

if __name__ == "__main__":
    main()
