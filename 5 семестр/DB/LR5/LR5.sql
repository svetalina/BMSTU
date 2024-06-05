-- 1. Извлечение данных в json

SELECT row_to_json(a) FROM author AS a;
SELECT row_to_json(f) FROM fiction AS f;
SELECT row_to_json(s) FROM shop AS s;
SELECT row_to_json(b) FROM book AS b;
SELECT row_to_json(ph) FROM publishing_house AS ph;
SELECT row_to_json(fa) FROM _fiction_author AS fa;
SELECT row_to_json(bf) FROM _book_fiction AS bf;
SELECT row_to_json(bs) FROM _book_shop AS bs;



-- 2. Загрузка и сохранение данных из json в таблицу

DROP TABLE IF EXISTS author_copy;
CREATE TABLE IF NOT EXISTS author_copy(
    author_id serial PRIMARY KEY,
    first_name VARCHAR(128) NOT NULL,
    middle_name VARCHAR(128) NOT NULL,
    surname VARCHAR(128) NOT NULL,
    main_genre VARCHAR(128) NOT NULL
);

COPY
(
    SELECT row_to_json(a) FROM author AS a
)
TO '/home/author.json';


-------
DROP TABLE IF EXISTS author_copy_import;
CREATE TABLE IF NOT EXISTS author_copy_import( doc json );

COPY author_copy_import FROM '/home/author.json';
SELECT * FROM author_copy_import;

INSERT INTO author_copy(author_id, first_name, middle_name, surname, main_genre)
SELECT (doc->>'author_id')::integer, doc->>'first_name', doc->>'middle_name', doc->>'surname', doc->>'main_genre'
FROM author_copy_import;

SELECT * FROM author_copy;



-- 3. Атрибут с типом json

DROP TABLE IF EXISTS author_new;
CREATE TABLE IF NOT EXISTS author_new
(
    id serial PRIMARY KEY,
    surname VARCHAR(128),
    info json
);

INSERT INTO author_new(surname, info) VALUES
	('Сазонов', '{"first_name":"Николай","middle_name":"Филиппович","main_genre":"Юмор"}'::json),
	('Бойко',   '{"first_name":"Семен","middle_name":"Вольфович","main_genre":"Триллер"}'::json),
	('Авдеева', '{"first_name":"Лидия","middle_name":"Робертовна","main_genre":"Детектив"}'::json);

SELECT * FROM author_new;




--4.1 Извлечение XML/JSON фрагмента из XML/JSON документа

DROP TABLE IF EXISTS geted_info_signature;
CREATE TABLE IF NOT EXISTS geted_info_signature
(
	surname VARCHAR(128),
	main_genre VARCHAR(128)
);

SELECT *
FROM author_copy_import, json_populate_record(NULL::geted_info_signature, doc);



-- 4.2 Извлечение значения конкретных атрибутов XML/JSON документа

select info->'main_genre' AS main_genre from author_new;



-- 4.3 Выполнение проверки существования узла или атрибута

DROP FUNCTION IF EXISTS check_on_exists_field;
CREATE OR REPLACE FUNCTION check_on_exists_field(field_name VARCHAR)
RETURNS int
AS $$
	query = '''
		SELECT doc->>'%s' as ch_field FROM author_copy_import
			'''%field_name

	res = plpy.execute(query)

	if res[0]['ch_field'] is not None:
		return 1
	return 0
$$ LANGUAGE plpython3u;

SELECT * FROM check_on_exists_field('main_genre');



-- 4.4 Изменение XML/JSON документ

DROP TABLE IF EXISTS author_newb;
CREATE TABLE IF NOT EXISTS author_newb
(
    id serial PRIMARY KEY,
    surname VARCHAR(128),
    info jsonb
);

INSERT INTO author_newb(surname, info) VALUES
	('Сазонов', '{"first_name":"Николай","middle_name":"Филиппович","main_genre":"Юмор"}'::jsonb),
	('Бойко',   '{"first_name":"Семен","middle_name":"Вольфович","main_genre":"Триллер"}'::jsonb),
	('Авдеева', '{"first_name":"Лидия","middle_name":"Робертовна","main_genre":"Детектив"}'::jsonb);

select * from author_newb;

UPDATE author_newb
SET info = jsonb_set(info, '{main_genre}', '"Драма"')
WHERE id = 3;



-- 4.5 Разделение XML/JSON документ на несколько строк по узлам

DROP TABLE IF EXISTS author_new;
CREATE TABLE IF NOT EXISTS author_new
(
    id serial PRIMARY KEY,
    info json
);

INSERT INTO author_new(info) VALUES
(
'[{"first_name":"Николай","middle_name":"Филиппович","surname":"Сазонов","main_genre":"Юмор"},
{"first_name":"Семен","middle_name":"Вольфович","surname":"Бойко","main_genre":"Триллер"},
{"first_name":"Лидия","middle_name":"Робертовна","surname":"Авдеева","main_genre":"Детектив"},
{"first_name":"Арина","middle_name":"Владиславовна","surname":"Каримова","main_genre":"Научный"},
{"first_name":"Савва","middle_name":"Валентинович","surname":"Лукин","main_genre":"Роман"}]'
);

SELECT json_array_elements(info) FROM author_new;


--ЗАЩИТА

SELECT row_to_json(slct) FROM (SELECT _book_shop.shop_id, array_agg(ARRAY[_book_shop.book_id]) 
FROM _book_shop
GROUP BY _book_shop.shop_id) AS sel

