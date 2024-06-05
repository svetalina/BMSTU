from algorithms import *
from color import *

def fill_table(x_arr, y_arr, methods):
    table = [[0 for i in range(7)] for j in range(6)]
    step = x_arr[1] - x_arr[0]

    for i in range(len(x_arr)):
        table[i][0] = x_arr[i]
        table[i][1] = y_arr[i]

        for j in range(2, len(methods) + 2):
            if methods[j - 2] == alignment_vars_difference:
                table[i][j] = alignment_vars_difference(y_arr, x_arr, step, i)
            else:
                table[i][j] = methods[j - 2](y_arr, step, i)

    return table

def print_table(table):
    print("\n%s%s" %(set_color, base_color), "-" * 63, sep = '')
    print("|%s%s   X   %s%s|%s%s    Y   %s%s|%s%s    1   %s%s|%s%s    2   %s%s|"
          "%s%s    3   %s%s|%s%s    4   %s%s|%s%s    5   %s%s|"
          %(set_color, green, set_color, base_color, set_color, green, set_color, base_color,
            set_color, green, set_color, base_color, set_color, green, set_color, base_color,
            set_color, green, set_color, base_color, set_color, green, set_color, base_color,
            set_color, green, set_color, base_color))
    print("-" * 63)

    for i in range(len(table)):
        for j in range(len(table[i])):
            if table[i][j] != " ---":
                table[i][j] = str(round(table[i][j], 3))

    for i in range(len(table)):
        print("|", end='')
        print("%s%s   %-4s%s%s|%s%s  %-6s%s%s|%s%s  %-6s%s%s|%s%s  %-6s%s%s|"
               "%s%s  %-6s%s%s|%s%s  %-6s%s%s|%s%s %-7s%s%s|" 
            %(set_color, blue,   table[i][0], set_color, base_color,
              set_color, blue,   table[i][1], set_color, base_color,
              set_color, red, table[i][2], set_color, base_color,
              set_color, red, table[i][3], set_color, base_color,
              set_color, red, table[i][4], set_color, base_color,
              set_color, red, table[i][5], set_color, base_color,
              set_color, red, table[i][6], set_color, base_color,))

    print("-" * 63, "\n")
    