from color import base_color, red
from read_print import read_command
from full_combinations import parse_full_combinations
from ant_algorythm import parse_ant_algorythm
from parametrization import parametrization
from compare_time import compare_time


def main():
    command = -1

    while command != 0:
        command = read_command()

        if command == 1:
            parse_full_combinations()

        elif command == 2:
            parse_ant_algorythm()

        elif command == 3:
            parametrization()

        elif command == 4:
            compare_time()


if __name__ == "__main__":
    main()
