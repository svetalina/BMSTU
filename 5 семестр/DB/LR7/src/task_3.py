from peewee import *

from colors import *

# Подключаемся к нашей БД.
con = PostgresqlDatabase(
    host='localhost',
    user='alina',
    password='2606',
    database='postgres'
)


class BaseModel(Model):
    class Meta:
        database = con


class Shops(BaseModel):
    id = IntegerField(column_name='id')
    name_sh = CharField(column_name='name_sh')
    address = CharField(column_name='address')
    website = CharField(column_name='website')
    rating = FloatField(column_name='rating')

    class Meta:
        table_name = 'shop'


class BooksShops(BaseModel):
    book_id = IntegerField(column_name='book_id')
    shop_id = ForeignKeyField(Shops, backref='shop_id')

    class Meta:
        table_name = '_book_shop'


def query_1():
    print(BLUE, f'{"1. Однотабличный запрос на выборку:":^130}')

    query = Shops.select().where(Shops.rating > 5).limit(5).order_by(Shops.id)

    print(MAGENTA, f'\n{"Запрос:":^130}\n\n', BLACK, query)

    shops_selected = query.dicts().execute()

    print(MAGENTA, f'\n{"Результат:":^130}\n', BLACK)
    for elem in shops_selected:
        print(elem)


def query_2():
    global con

    print(BLUE, f'\n{"2. Многотабличный запрос на выборку:":^130}\n')

    print(MAGENTA, f'{"Магазины, продающие определенныю книгу:":^130}\n', BLACK)

    query = BooksShops.select(Shops.id, Shops.rating, BooksShops.book_id).join(Shops, on=(Shops.id == BooksShops.shop_id)).where(BooksShops.book_id == 1)

    query_res = query.dicts().execute()
    for elem in query_res:
        print(elem)


def print_last_five_shops():
    print(MAGENTA, f'\n{"Последние 5 магазинов:":^130}\n', BLACK)
    query = Shops.select().limit(5).order_by(Shops.id.desc())
    for elem in query.dicts().execute():
        print(elem)
    print()


def add_shop(new_id, new_name, new_address, new_website, new_rating):
    global con

    try:
        with con.atomic() as txn:
            Shops.create(id=new_id, name_sh=new_name, address=new_address, website=new_website, rating=new_rating)
            print(GREEN, "Магазин успешно добавлен!")
    except:
        print(RED, "Магазин уже существует!")
        txn.rollback()


def update_name(shop_id, new_name):
    shop = Shops(id=shop_id)
    shop.name_sh = new_name
    shop.save()
    print(GREEN, "Название успешно обновлено!")


def del_shop(shop_id):
    print(GREEN, "Магазин успешно удален!")
    shop = Shops.get(Shops.id == shop_id)
    shop.delete_instance()


def query_3():
    print(BLUE, f'\n{"3. Три запроса на добавление, изменение и удаление данных в базе данных:":^130}')

    print_last_five_shops()

    add_shop(1001, 'Книжный вор', 'г. Москва, ул. Ленина, д. 5', 'https://theif.com/1', 7.9)
    print_last_five_shops()

    update_name(1001, 'Книжный ворюга')
    print_last_five_shops()

    del_shop(1001)
    print_last_five_shops()


def query_4():
    global con
    cursor = con.cursor()

    print(BLUE, f'\n{"4. Получение доступа к данным, выполняя только хранимую процедуру:":^130}')

    print_last_five_shops()

    cursor.execute("CALL add_shop_py(%s, %s, %s, %s, %s);",
                   (1002, 'Купи книгу', 'г. Чернянка, ул. Восточная, д. 14', 'https://qwerty.com', 9.6))
    con.commit()

    print_last_five_shops()

    cursor.execute("CALL del_shop_py(%s);", (1002,))
    con.commit()

    cursor.close()


def task_3():
    global con

    query_1()
    query_2()
    query_3()
    query_4()

    con.close()
