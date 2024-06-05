from faker import *
import random
import codecs
import requests
from bs4 import BeautifulSoup as bs

iterations = 1000

genres = ["Детектив", "Фантастика", "Приключения", "Роман", "Научный", "Фольклор", "Юмор", "Поэзия", "Детский",
              "Религиозный", "Триллер", "Ужасы", "Комиксы"]

def generate_author_table_data():
    file = open('author.csv', 'w')

    # strk = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', ' ']
    # fil = open('female_sur.txt', 'w', encoding='utf-8')
    # with open('male_middlename.txt', encoding='utf-8') as f:
    #    nums = f.read()
    #    for i in range(len(strk)):
    #        nums = nums.replace(strk[i], '')
    #        nums = nums.replace("букв", '')
    #        nums = nums + '\n'
    #    fil.write(nums)

    with open('female_name.txt', encoding='utf-8') as f:
        female_name = [row.strip() for row in f]
    with open('male_name.txt', encoding='utf-8') as f:
        male_name = [row.strip() for row in f]
    with open('female_surname.txt', encoding='utf-8') as f:
        female_surname = [row.strip() for row in f]
    with open('male_surname.txt', encoding='utf-8') as f:
        male_surname = [row.strip() for row in f]
    with open('female_middlename.txt', encoding='utf-8') as f:
        female_middlename = [row.strip() for row in f]
    with open('male_middlename.txt', encoding='utf-8') as f:
        male_middlename = [row.strip() for row in f]

    for i in range(iterations):
        sex = random.randint(0, 1)
        if sex:
            first_name = female_name[random.randint(0, len(female_name) - 1)]
            middle_name = female_middlename[random.randint(0, len(female_middlename) - 1)]
            last_name = female_surname[random.randint(0, len(female_surname) - 1)]
        else:
            first_name = male_name[random.randint(0, len(male_name) - 1)]
            middle_name = male_middlename[random.randint(0, len(male_middlename) - 1)]
            last_name = male_surname[random.randint(0, len(male_surname) - 1)]

        genre = genres[random.randint(0, len(genres) - 1)]

        line = "{0};{1};{2};{3};{4}\n".format(i + 1, first_name, middle_name, last_name, genre)

        file.write(line)

    file.close()

def generate_publishing_table_data():
    faker = Faker('ru_RU')
    file = open('publishing house.csv', 'w')

    for i in range(iterations - 200):
        name = faker.company()
        address = faker.address()
        url = faker.url()

        phone = "89"
        for j in range(9):
            phone += str(random.randint(0, 9))

        line = "{0};{1};{2};{3};{4}\n".format(i + 1, name, address, url, phone)

        file.write(line)

    file.close()

def generate_shop_table_data():
    faker = Faker('ru_RU')
    file = codecs.open('shop.csv', 'w')

    with codecs.open('shops.txt', encoding='utf-8') as f:
        shops_local = [row.strip() for row in f]

    for i in range(iterations):
        name = shops_local[i%219]
        address = faker.address()
        url = faker.url()
        rating = random.uniform(0, 10)

        line = "{0};{1};{2};{3};{4:.1f}\n".format(i + 1, name, address, url, rating)
        print(line)
        file.write(line)

    file.close()

def generate_fcition_table_data():
    file = open('fiction.csv', 'w')

    URL_TEMPLATE = "https://www.afisha.ru/msk/shop/bookstores/"

    id = 0
    for i in range(2, 2749):
        r = requests.get(URL_TEMPLATE + str(i))
        soup = bs(r.text, "html.parser")
        names = soup.find_all('a', class_='product-card__img js-analytic-productlink')
        for name in names:
            id += 1
            name_local = name.img['title']
            genre = genres[random.randint(0, len(genres) - 1)]
            year = random.randint(1700, 2022)

            line = "{0};{1};{2};{3}\n".format(id, name_local, genre, year)
            file.write(line)
    file.close()

def array_is_empty(array):
    for i in range(len(array)):
        if array[i] != 0:
            return 1
    return 0


def generate_fa_table_data():
    file = open('ficiton_author.csv', 'w')

    array = []
    for i in range(1, 5001):
        array.append(i)

    while(array_is_empty(array)):

        id_f = random.randint(1, 5000)
        while array[id_f - 1] == 0:
            id_f = random.randint(1, 5000)
        if ((random.randint(0, 1000) % 3) < 2):
            array[id_f - 1] = 0

        id_a = random.randint(1, 1000)
        line = "{0};{1};\n".format(id_f, id_a)
        file.write(line)
    file.close()

def generate_book_table_data():
    file = open('book.csv', 'w')

    array_ph = []
    for i in range(1, 801):
        array_ph.append(i)

    id_b = 0
    while(array_is_empty(array_ph)):
        id_ph = random.randint(1, 800)
        while array_ph[id_ph - 1] == 0:
            id_ph = random.randint(1, 800)
        if ((random.randint(0, 1000) % 7) == 0):
            array_ph[id_ph - 1] = 0

        id_b += 1
        line = "{0};{1};\n".format(id_b, id_ph)
        file.write(line)
    file.close()
    print("dg")

def generate_bf_table_data():
    file = open('book_fiction.csv', 'w')

    array = []
    for i in range(1, 5746):
        array.append(i)

    while(array_is_empty(array)):

        id_b = random.randint(1, 5745)
        while array[id_b - 1] == 0:
            id_b = random.randint(1, 5745)
        if ((random.randint(0, 1000) % 3) < 2):
            array[id_b - 1] = 0

        id_f = random.randint(1, 5000)
        line = "{0};{1};\n".format(id_b, id_f)
        file.write(line)
    file.close()
    print("fdsg")


def generate_bs_table_data():
    file = open('book_shop.csv', 'w')

    array = []
    for i in range(1, 5746):
        array.append(i)

    while(array_is_empty(array)):

        id_b = random.randint(1, 5745)
        while array[id_b - 1] == 0:
            id_b = random.randint(1, 5745)
        if ((random.randint(0, 1000) % 3) < 2):
            array[id_b - 1] = 0

        id_s = random.randint(1, 1000)
        line = "{0};{1};\n".format(id_b, id_s)
        file.write(line)
    file.close()
    print("fdsg")



#generate_author_table_data()
#generate_publishing_table_data()
#generate_shop_table_data()
#generate_fcition_table_data()
#generate_book_table_data()

#generate_fa_table_data()
#generate_bf_table_data()
#generate_bs_table_data()

# fil = open('shops.txt', 'wt', encoding='utf-8')
# f = open('shop.txt', encoding='utf-8')
# nums = f.read()
# nums = nums.replace('\n\n', '\n')
# fil.write(nums)
# fil.close()
