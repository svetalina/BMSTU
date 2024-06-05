from shop import shop
import json
import psycopg2

from colors import * 

def connection():
	con = None
	# Подключаемся к БД.
	try:
		con = psycopg2.connect(
			host='localhost',
			user='alina',
			password='2606',
			database='postgres'
		)
	except:
		print("Ошибка при подключении к БД")
		return con

	print("База данных успешно открыта")
	return con
	
def output_json(array):
	print(BLACK, end='')
	for elem in array:
		string = json.dumps(elem.get(), ensure_ascii=False).encode('utf8')
		print(string.decode())
	print()

def read_table_json(cur, count = 15):
	# Возвращает массив кортежей словарей.
	cur.execute("select * from shops_json")

	rows = cur.fetchmany(count)

	array = list()
	array_rc = list()
	for elem in rows: 
		tmp = elem[0]
		array.append([str(tmp['shop_id']), str(tmp['name_sh']), str(tmp['address']), str(tmp['website']), str(tmp['rating'])])
		array_rc.append(shop(tmp['shop_id'], tmp['name_sh'], tmp['address'], tmp['website'], tmp['rating']))

	print(BLACK, end='')
	print(f"{'id':<3} {'name':<20} {'address':<60} {'website':<30} {'rating':<5}")
	for i in range(len(array)):
			print("%-3s %-20s %-60s %-30s %-5s" % (array[i][0], array[i][1], array[i][2], array[i][3], array[i][4]))

	return array_rc


def update_shop(shops, in_id):
	# Увеличивает рейтинг магазина
	for elem in shops:
		if elem.id == in_id:
			elem.rating += 1
	output_json(shops)

def add_user(users, user):
	users.append(user)
	output_json(users)

def task_2():
	con = connection()
	# Объект cursor используется для фактического
	# выполнения наших команд.
	cur = con.cursor()

	# 1. Чтение из XML/JSON документа.
	print(BLUE, f'{"1. Чтение из XML/JSON документа:":^130}')
	shops_array = read_table_json(cur)
	# 2. Обновление XML/JSON документа.
	print(BLUE, f'\n{"2. Обновление XML/JSON документа:":^130}')
	update_shop(shops_array, 2)
	# 3. Запись (Добавление) в XML/JSON документ.
	print(BLUE, f'{"3. Запись (Добавление) в XML/JSON документ:":^130}')
	add_user(shops_array, shop(16, 'Books here', 'Везде', 'http://bookshere.com/1', 10))

	# Закрываем соединение с БД.
	cur.close()
	con.close()