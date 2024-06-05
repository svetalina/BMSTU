from sympy import symbols, diff

EPS = 1e-6

def search_index(table, x, n):
    index = 0

    for i in table:
        if (i[0] > x):
            break
        index += 1

    if index >= len(table) - n:
        return len(table) - n - 1

    l_border = index
    r_border = index

    while (n > 0):
        if (r_border - index == index - l_border):
            if (l_border > 0):
                l_border -= 1
            else:
                r_border += 1
        else:
            if (r_border < len(table) - 1):
                r_border += 1
            else:
                l_border -= 1
        n -= 1

    return l_border

def divided_difference(x0, y0, x1, y1):
    if (abs(x0 - x1) > EPS):
        return (y0 - y1) / (x0 - x1)

def newton_polynomial(table, n, xf):
    index = search_index(table, xf, n)
    np = str(table[index][1])

    for i in range(n):
        for j in range(n - i):
            table[index + j][1] = divided_difference(
                table[index + j][0],         table[index + j][1],
                table[index + j + i + 1][0], table[index + j + 1][1])

        mult = "(" + str(table[index][1]) + ")"
        for j in range(i + 1):
            mult += " * (x - " + str(table[index + j][0]) + ")"

        np += " + " + mult

    x = symbols('x', real=True)
        
    return eval(np, {}, {"x":xf}), diff(diff(eval(np))).subs({x: xf})