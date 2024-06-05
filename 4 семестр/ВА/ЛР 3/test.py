from math import fabs

from spline import spline

EPS = 1e-6


def test_main():
    table = [[0, 0],
             [1, 0.496],
             [2, 0.986],
             [3, 1.102],
             [4, 0.972],
             [5, 0.754],
             [6, 0.539],
             [7, 0.364],
             [8, 0.236],
             [9, 0.148],
             [10, 0.091]]

    test_table = [[5.7, 1, 0.600243],
                  [5.7, 2, 0.600243],
                  [5.7, 3, 0.600243],
                  [4.3, 1, 0.910846],
                  [4.3, 2, 0.910846],
                  [4.3, 3, 0.910846],
                  [3.0, 1, 1.102000],
                  [3.0, 2, 1.102000],
                  [3.0, 3, 1.102000],
                  [1.0, 1, 0.496000],
                  [1.0, 2, 0.496000],
                  [1.0, 3, 0.496000]]

    for i in range(len(test_table)):
        spl = spline(table, test_table[i][0], test_table[i][1])

        if fabs(spl - test_table[i][2]) < EPS:
            print("Тест №%d пройден" % (i + 1))
        else:
            print("Тест №%d не пройден" % (i + 1))


if __name__ == "__main__":
    test_main()
