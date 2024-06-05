CREATE EXTENSION plpython3u



-- 1. Определяемая пользователем скалярная функция CLR: возвращает век написания произведения
DROP FUNCTION count_century_py(year_wr INT);

CREATE OR REPLACE FUNCTION count_century_py(year_wr INT)
RETURNS INT 
AS $$
    return year_wr // 100 + 1
$$ LANGUAGE PLPYTHON3U;

SELECT fiction_id, name_fc, genre, count_century_py(year_wr) AS century 
FROM fiction;



-- 2. Пользовательская агрегатная функция CLR: возвращает кол-во произведений определенного жанра определенного века
DROP FUNCTION find_number_genre_centure_py(genre VARCHAR, century INT);

CREATE OR REPLACE FUNCTION find_number_genre_centure_py(genre VARCHAR, century INT)
RETURNS INT 
AS $$
    query = '''
        SELECT genre, count_century_py(year_wr) AS century 
        FROM fiction 
            '''

    res = plpy.execute(query)
    
    if res is not None:
        quantity = 0;

        for fiction in res:
            if fiction["genre"] == genre and fiction["century"] == century:
            	quantity += 1
        return quantity

$$ LANGUAGE PLPYTHON3U;

SELECT find_number_genre_centure_py('Юмор', 20)



-- 3. Определяемая пользователем табличная функция CLR: возвращает магазины, с рейтингом выше среднего и расположенные в определенном городе
DROP FUNCTION best_shops_py(city VARCHAR);

CREATE OR REPLACE FUNCTION best_shops_py(city VARCHAR)
RETURNS TABLE
(
    shop_id INT,
    name_sh VARCHAR,
    address VARCHAR,
    website VARCHAR,
    rating FLOAT	
)
AS $$
    query = '''
        SELECT *
        FROM shop 
        WHERE rating > 
        (
            SELECT AVG(rating) 
            FROM shop 
        );
            '''

    res_query = plpy.execute(query)
    
    if res_query is not None:
        res = list()

        for shop in res_query:
            if city in shop["address"]:
                res.append(shop)

        return res

$$ LANGUAGE PLPYTHON3U;

SELECT *
FROM best_shops_py('Воронеж');



-- 4. Хранимая процедура CLR: добавляет нового автора в таблицу
DROP PROCEDURE add_author_py CASCADE;

CREATE OR REPLACE PROCEDURE add_author_py
(
    author_id INT,
    first_name VARCHAR,
    middle_name VARCHAR,
    surname VARCHAR,
    main_genre VARCHAR
) 
AS $$
    plan = plpy.prepare("INSERT INTO author VALUES($1, $2, $3, $4, $5)", 
        ["INT", "VARCHAR", "VARCHAR", "VARCHAR", "VARCHAR"])

    plpy.execute(plan, 
        [author_id, first_name, middle_name, surname, main_genre])

$$ LANGUAGE plpython3u;

CALL add_author_py(1001, 'Юлия',  'Михайловна', 'Гаврилова', 'SQL');

DROP FROM author
WHERE author_id = 1001;

SELECT *
FROM author

----------

DROP PROCEDURE add_shop_py CASCADE;

CREATE OR REPLACE PROCEDURE add_shop_py
(
    shop_id INT,
    name_sh VARCHAR,
    address VARCHAR,
    website VARCHAR,
    rating FLOAT
) 
AS $$
    plan = plpy.prepare("INSERT INTO shop VALUES($1, $2, $3, $4, $5)", 
        ["INT", "VARCHAR", "VARCHAR", "VARCHAR", "FLOAT"])

    plpy.execute(plan, 
        [shop_id, name_sh, address, website, rating])

$$ LANGUAGE plpython3u;

CALL add_shop_py(1001, 'Купи книгу',  'г. Чернянка, ул. Восточная, д. 14', 'https://qwerty.com', 9.6);

DELETE FROM shop WHERE id = 1001;

SELECT *
FROM shop

----------

DROP PROCEDURE del_shop_py CASCADE;

CREATE OR REPLACE PROCEDURE del_shop_py (shop_id INT) 
AS $$
	
	plan = plpy.prepare("DELETE FROM shop WHERE id = $1", ["INT"])
	
	plpy.execute(plan, [shop_id])

$$ LANGUAGE plpython3u;

CALL del_shop_py(1002);

SELECT *
FROM shop


-- 5. Триггер CLR: выводит сообщение при дабавлении информации в таблицу произведений
DROP FUNCTION insert_info_py() CASCADE;

CREATE OR REPLACE FUNCTION insert_info_py()
RETURNS TRIGGER
AS $$
    if TD["new"]["name_fc"] == "Книжный вор":
        plpy.notice(f"В таблицу была добавлена моя любимая книга, урааа (название = {TD['new']['name_fc']})")
    else:
        plpy.notice(f"Какая-то скучная книга была добавлена в таблицу (название = {TD['new']['name_fc']})")
$$ LANGUAGE PLPYTHON3U;

CREATE TRIGGER insert_info_trigger_py AFTER INSERT ON fiction
FOR ROW EXECUTE PROCEDURE insert_info_py();

INSERT INTO fiction
VALUES (5001, 'Книжный вор', 'Драма', 1981);

INSERT INTO fiction
VALUES (5002, 'Метро', 'Фантастика', 1982);

DROP FROM fiction
WHERE fiction_id = 5001;

DROP FROM fiction
WHERE fiction_id = 5002;



-- 6. Определяемый пользователем тип данных CLR: возвращает таблицу с именем произведения, годом написания больше определенного и автором(ФИО)
DROP FUNCTION find_fiction_author_by_year(year INT);

CREATE TYPE fiction_author_year AS
(
	name_fiction VARCHAR,
	year_writing INT,
    name_author VARCHAR
);
 
CREATE OR REPLACE FUNCTION find_fiction_author_by_year(year INT)
RETURNS SETOF fiction_author_year
AS $$
    query = '''
        SELECT
			f.name_fc AS name_fiction,
			f.year_wr AS year_writing,
            CONCAT(a.first_name, ' ', a.middle_name, ' ', a.surname)  AS name_author
        FROM 
            fiction AS f
            JOIN _fiction_author AS fa  ON f.fiction_id = fa.fiction_id
            JOIN author AS a ON fa.author_id = a.author_id
        WHERE
			f.year_wr > %d
            ''' %(year)

    res_query = plpy.execute(query)
    
    if res_query is not None:
        return res_query

$$ LANGUAGE PLPYTHON3U;

SELECT * 
FROM find_fiction_author_by_year(1900);



--ЗАЩИТА
DROP FUNCTION count_books_in_shop(id INT);

CREATE OR REPLACE FUNCTION count_books_in_shop(id INT)
RETURNS INT 
AS $$
    query = '''
        SELECT  book_id, shop_id
        FROM _book_shop
            '''

    res = plpy.execute(query)
    
    if res is not None:
        quantity = 0;

        for _book_shop in res:
            if _book_shop["shop_id"] == id:
            	quantity += 1
        return quantity

$$ LANGUAGE PLPYTHON3U;

SELECT count_books_in_shop(1);

SELECT shop_id, book_id 
FROM _book_shop;

