from read_print import read_matrix
from full_combinations import full_combinations_alg
from ant_algorythm import ant_alg


def parametrization():

    alpha_arr = [num / 10 for num in range(1, 10)]
    k_eva_arr = [num / 10 for num in range(1, 9)]
    days_arr = [50, 100, 200]

    size = 10

    size, matrix = read_matrix()
    if size == 0:
        return

    optimal = full_combinations_alg(matrix, size)

    file = open("parametrization.txt", "w")

    count = 0
    count_all = len(alpha_arr) * len(k_eva_arr)

    print()

    for alpha in alpha_arr:
        beta = 1 - alpha

        for k_eva in k_eva_arr:
            count += 1

            for days in days_arr:
                res = ant_alg(matrix, size, alpha, beta, k_eva, days)


                sep = "&"
                end = "\\\\"

                str = "%4.1f %s %4.1f %s %4.1f %s %4d %s %5d %s %5d %s\n" \
                    % (alpha, sep, beta, sep, k_eva, sep, days, sep, optimal[0], sep, res[0] - optimal[0], end)


                file.write(str)
            file.write("\\hline\n")
            
    file.close()