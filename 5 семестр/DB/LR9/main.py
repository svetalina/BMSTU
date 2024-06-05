from time import time

import matplotlib.pyplot as plt
import psycopg2
import redis
import json
import threading
from random import randint

N_REPEATS = 5

def connection():
    try:
        con = psycopg2.connect(
            host='localhost',
            user='alina',
            password='2606',
            database='postgres'
        )
    except:
        print("Ошибка при подключении к Базе Данных")
        return

    print("База данных успешно открыта")
    return con


def get_shop_maxrating(cur):
    redis_client = redis.Redis(host="localhost", port=6379, db=0)

    cache_value = redis_client.get("shop_maxrating")
    if cache_value is not None:
        redis_client.close()
        return json.loads(cache_value)

    cur.execute("select * from shop where rating = 10")
    res = cur.fetchall()

    redis_client.set("shop_maxrating", json.dumps(res))
    redis_client.close()

    return res


def task_02(cur, rtn):
    threading.Timer(5.0, task_02, [cur, rtn]).start()

    cur.execute(f"select * from shop where rating = {rtn}")

    result = cur.fetchall()

    return result


def task_03(cur, rtn):
    threading.Timer(5.0, task_02, [cur, rtn]).start()

    redis_client = redis.Redis(host="localhost", port=6379, db=0)

    cache_value = redis_client.get(f"shop{rtn}_rating")
    if cache_value is not None:
        redis_client.close()
        return json.loads(cache_value)

    cur.execute(f"select * from shop where rating = {rtn}")

    result = cur.fetchall()
    data = json.dumps(result)
    redis_client.set(f"shop{rtn}_rating", data)
    redis_client.close()

    return result


def dont_do(cur):
    redis_client = redis.Redis()#host="localhost", port=6379, db=0)

    t1 = time()
    cur.execute("select * from shop where shop_id = 1")
    t2 = time()

    result = cur.fetchall()

    data = json.dumps(result)
    cache_value = redis_client.get("w1")
    if cache_value is not None:
        pass
    else:
        redis_client.set("w1", data)

    t11 = time()
    redis_client.get("w1")
    t22 = time()

    redis_client.close()

    return t2 - t1, t22 - t11


def delete(cur, con):
    redis_client = redis.Redis()

    wid = randint(1, 10)

    t1 = time()
    cur.execute(f"delete from shop where shop_id = {wid};")
    t2 = time()

    t11 = time()
    redis_client.delete(f"w{wid}")
    t22 = time()

    redis_client.close()

    con.commit()

    return t2 - t1, t22 - t11


def insert(cur, con):
    redis_client = redis.Redis()

    wid = randint(1000, 2000)

    t1 = time()
    cur.execute(f"insert into shop "
                f"values ({wid}, 'a', 'b', 'c', 1.0);")
    t2 = time()

    cur.execute(f"select * from shop where shop_id = {wid}")
    result = cur.fetchall()

    data = json.dumps(result)
    t11 = time()
    redis_client.set(f"w{wid}", data)
    t22 = time()

    redis_client.close()

    con.commit()

    return t2 - t1, t22 - t11


def update(cur, con):
    redis_client = redis.Redis()

    wid = randint(1, 10)

    t1 = time()
    cur.execute(f"UPDATE shop SET rating = 20 WHERE shop_id = {wid}")
    t2 = time()

    cur.execute(f"select * from shop where shop_id = {wid};")

    result = cur.fetchall()
    data = json.dumps(result)

    t11 = time()
    redis_client.set(f"w{wid}", data)
    t22 = time()

    redis_client.close()

    con.commit()

    return t2 - t1, t22 - t11


def task_04(cur, con):
    # simple
    t1 = 0
    t2 = 0
    for i in range(N_REPEATS):
        print(i)
        b1, b2 = dont_do(cur)
        t1 += b1
        t2 += b2
    print("simple 100 db redis", t1 / N_REPEATS, t2 / N_REPEATS)
    index = ["БД", "Redis"]
    values = [t1 / N_REPEATS, t2 / N_REPEATS]
    plt.bar(index, values)
    plt.title("Без изменения данных")
    plt.show()

    # delete
    t1 = 0
    t2 = 0
    for i in range(N_REPEATS):
        print(i)
        b1, b2 = delete(cur, con)
        t1 += b1
        t2 += b2
    print("delete 100 db redis", t1 / N_REPEATS, t2 / N_REPEATS)

    index = ["БД", "Redis"]
    values = [t1 / N_REPEATS, t2 / N_REPEATS]
    plt.bar(index, values)
    plt.title("При удалении строк каждые 10 секунд")
    plt.show()

    # insert
    t1 = 0
    t2 = 0
    for i in range(N_REPEATS):
        print(i)
        b1, b2 = insert(cur, con)
        t1 += b1
        t2 += b2
    print("ins_tour 100 db redis", t1 / N_REPEATS, t2 / N_REPEATS)

    index = ["БД", "Redis"]
    values = [t1 / N_REPEATS, t2 / N_REPEATS]
    plt.bar(index, values)
    plt.title("При добавлении строк каждые 10 секунд")
    plt.show()

    # updata
    t1 = 0
    t2 = 0
    for i in range(N_REPEATS):
        print(i)
        b1, b2 = update(cur, con)
        t1 += b1
        t2 += b2
    print("update 100 db redis", t1 / N_REPEATS, t2 / N_REPEATS)

    index = ["БД", "Redis"]
    values = [t1 / N_REPEATS, t2 / N_REPEATS]
    plt.bar(index, values)
    plt.title("При изменении строк каждые 10 секунд")
    plt.show()


def do_cache(cur):
    redis_client = redis.Redis(host="localhost", port=6379, db=0)

    for wid in range(10000):
        cache_value = redis_client.get(f"w{wid}")
        if cache_value is not None:
            pass
            #print(f"{wid} exists")
            # redis_client.close()
            # return json.loads(cache_value)

        cur.execute(f"select *\
                    from workers\
                    where worker_id = {wid};")

        result = cur.fetchall()
        redis_client.set(f"w{wid}", json.dumps(result))
        redis_client.close()




if __name__ == '__main__':

    con = connection()
    cur = con.cursor()

    # do_cache(cur)
    #task_04(cur, con)

    print("1. Магазины с рейтингом 10 (задание 2)\n"
          "2. Приложение выполняет запрос каждые 5 секунд на стороне БД (задание 3.1)\n"
          "3. Приложение выполняет запрос каждые 5 секунд через Redis в качестве кэша (задание 3.2)\n"
          "4. Гистограммы (задание 3.3)\n\n"
          )

    while True:
        c = int(input("Выбор: "))

        if c == 1:
            res = get_shop_maxrating(cur)

            for elem in res:
                print(elem)

        elif c == 2:
            rating = int(input("Рейтинг: "))

            res = task_02(cur, rating)

            for elem in res:
                print(elem)

        elif c == 3:
            dep_id = int(input("Рейтинг: "))

            res = task_03(cur, dep_id)

            for elem in res:
                print(elem)

        elif c == 4:
            task_04(cur, con)
        else:
            print("Ошибка\n")
            break

    cur.close()

    print("BY!")