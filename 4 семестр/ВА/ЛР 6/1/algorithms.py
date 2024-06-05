 def left_difference_derivative(y_arr, step, index):
    if index > 0 and index < len(y_arr):
        return (y_arr[index] - y_arr[index - 1]) / step
    else:
        return ' ---'

def center_difference_derivative(y_arr, step, index):
    if index > 0 and index < len(y_arr) - 1:
        return (y_arr[index + 1] - y_arr[index - 1]) / (2 * step)
    else:
        return ' ---'

def second_formula_runge(y_arr, step, index):
    if index < 2:
        return ' ---'
        
    f1 = left_difference_derivative(y_arr, step, index)
    f2 = (y_arr[index] - y_arr[index - 2]) / (2 * step)

    return 2 * f1 - f2

def alignment_vars_difference(y_arr, x_arr, step, index):
    if index > len(y_arr) - 2:
        return ' ---'

    d = (1 / y_arr[index + 1] - 1 / y_arr[index]) / \
        (1 / x_arr[index + 1] - 1 / x_arr[index])

    return d * y_arr[index] ** 2 / x_arr[index] ** 2

def second_difference_derivative(y_arr, step, index):
    if index > 0 and index < len(y_arr) - 1:
        return (y_arr[index - 1] - 2 * y_arr[index] + y_arr[index + 1]) / step ** 2
    else:
        return ' ---'
        