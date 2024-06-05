from py_linq import *

from shop import *
from colors import *

def request_1(shops):
	# Магазины с рейтингом больше 5, отсортированные по рейтингу
	return shops.where(lambda x: x['rating'] > 5).order_by(lambda x: x['rating'])\
		.select(lambda x: [x['name'], x['rating']])


def request_2(shops):
	# Количество магазинов с рейтингом больше 5
	return shops.count(lambda x: x['rating'] > 5)


def request_3(users):
	# Минимальный, максимальный, средний рейтинг
	return [users.min(lambda x: x['rating']), users.avg(lambda x: x['rating']), users.max(lambda x: x['rating'])]

def request_4(shops):
	# Группировка по рейтингу
	return shops.group_by(key_names=['rating'], key=lambda x: x['rating'])\
		.select(lambda g: [g.key.rating, g.count()])

def request_5(shops):
	# Соединение магазина и характеристики по рейтингу
	recommendation = Enumerable([{'rating':1.0, 'recommendation':'худший'},
						 {'rating':9.4, 'recommendation':'лучший'}])

	return shops.join(recommendation, lambda shp : shp['rating'], lambda rec: rec['rating'])

def task_1():
	# Создаем коллекцию.
	shops = Enumerable(create_shops('../data/shop.csv'))

	print(BLUE, '\n1.Магазины с рейтингом больше 5, отсортированные по рейтингу:\n')
	for elem in request_1(shops):
		print(BLACK, elem)

	print(BLUE, '\n2.Количество магазинов с рейтингом больше 5:', BLACK, f'{str(request_2(shops))}')

	print(BLUE, '\n3. Минимальный, средний, максимальный рейтинг:', BLACK, f'{str(request_3(shops))}')

	print(BLUE, '\n4.Группировка по рейтингу:\n')
	for elem in request_4(shops):
		print(BLACK, elem)

	print(BLUE, '\n5.Соединение магазина и характеристики по рейтингу:\n')
	for elem in request_5(shops):
		print(BLACK, elem)
