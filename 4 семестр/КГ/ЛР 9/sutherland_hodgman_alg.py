def get_vector(dot1, dot2):
    return [dot2[0] - dot1[0], dot2[1] - dot1[1]]

def vector_mul(vec1, vec2):
    return (vec1[0] * vec2[1] - vec1[1] * vec2[0])

def scalar_mul(vec1, vec2):
    return (vec1[0] * vec2[0] + vec1[1] * vec2[1])

def check_polygon(cutter): 
    if len(cutter) < 4:
        return False

    if vector_mul(get_vector(cutter[1], cutter[2]), 
                  get_vector(cutter[0], cutter[1])) > 0:
        sign = 1 # по часовой стрелке
    else:
        sign = -1 # против часовой стрелки

    for i in range(3, len(cutter)):
        if sign * vector_mul(get_vector(cutter[i - 1], cutter[i]),
                             get_vector(cutter[i - 2], cutter[i - 1])) < 0:
            return False

    if sign < 0:
        cutter.reverse()

    return True

def get_normal(dot1, dot2, dot3):
    vector = get_vector(dot1, dot2)

    if vector[1]:
        normal = [1, - vector[0] / vector[1]]
    else:
        normal = [0, 1]

    if scalar_mul(get_vector(dot2, dot3), normal) < 0:
        normal[0] = - normal[0]
        normal[1] = - normal[1]

    return normal

def  is_visible(dot, f_dot, s_dot):
    vec1 = get_vector(f_dot, s_dot)
    vec2 = get_vector(f_dot, dot)

    if vector_mul(vec1, vec2) <= 0:
        return True
    else:
        return False

def get_lines_parametric_intersec(line1, line2, normal):
    d = get_vector(line1[0], line1[1])
    w = get_vector(line2[0], line1[0])

    d_scalar = scalar_mul(d, normal)
    w_scalar = scalar_mul(w, normal)

    t = -w_scalar / d_scalar

    return [line1[0][0] + d[0] * t, line1[0][1] + d[1] * t]

def sutherland_hodgman_algorythm(cutter_line, position, figure):
    cur_result = []

    dot1 = cutter_line[0]
    dot2 = cutter_line[1]

    normal = get_normal(dot1, dot2, position)
    prev_vision = is_visible(figure[-2], dot1, dot2)

    for i in range(-1, len(figure)):
        cur_vision = is_visible(figure[i], dot1, dot2)

        if prev_vision:
            if cur_vision:
                cur_result.append(figure[i])
            else:
                figure_line = [figure[i - 1], figure[i]]
                cur_result.append(get_lines_parametric_intersec(figure_line, cutter_line, normal))
        else:
            if cur_vision:
                figure_line = [figure[i - 1], figure[i]]
                cur_result.append(get_lines_parametric_intersec(figure_line, cutter_line, normal))
                cur_result.append(figure[i])

        prev_vision = cur_vision

    return cur_result
