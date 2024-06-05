from color import base_color, green, red, blue

## Объект лабораторной работы, словарь термов и признака

dict = {'очень мало': [1, 2], 'мало': [3, 4], 'не очень мало': [5], 'средне': [6, 7],
         'не очень много': [8, 9],  'много': [10, 11], 'очень много': [12, 13, 14, 15]}

object = ["лабораторная работа №6",
          "лабораторной работы №6",
          "лабораторной работой №6",
          "лабораторной работе №6",
          "лабораторную работу №6",
          "лабораторной работе №6",
          "шестая лабораторная работа",
          "шестой лабораторной работы",
          "шестой лабораторной работой",
          "шестой лабораторной работе",
          "шестую лабораторную работу",
          "шестой лабораторной работе"]

term =   ["очень мало",
          "мало",
          "не очень мало",
          "средне",
          "не очень много",
          "много",
          "очень много"]
##

MSG =   "Перед использованием ознакомьтесь с правилами программы:\n"\
        "1. Вводите вопрос с маленькой буквы\n"\
        "2. Не допускайте орфографических ошибок\n"\
        "2. Ставьте вопросительный знак по своему усмотрению\n"\
        "\nВведите свой вопрос: "\

def print_hours(arr):
    if len(arr) == 1:
        print("%sВаш ответ: %d %s" % (blue, arr[0], base_color))
    else:
        print("%sВаш ответ: %d - %d %s" % (blue, arr[0], arr[len(arr) - 1], base_color))

def print_term(str):
    print("%sВаш ответ: %s %s" % (blue, str, base_color))

def main():
    answer = input(MSG)

    if any(elem in answer for elem in object):
        print("\n%sВаш вопрос содержит рассматриваемый объект, я постараюсь дать ответ%s\n" % (green, base_color))

        for elem in term:
            if elem in answer and not any(ch.isdigit() for ch in answer):
                print_hours(dict.get(elem))
                return

        for elem in answer:
            if all(ch.isdigit() for ch in elem):
                for k, v in dict.items():
                    if int(elem) in v:
                        print_term(k)
                        return

        print("%sКажется, я еще не умею отвечать на такие вопросы%s" % (red, base_color))

    else:
        print("\n%sВаш вопрос не содержит рассматриваемый объект, к сожалению, я не смогу дать ответ%s\n" % (red, base_color))

if __name__ == "__main__":
    main()
