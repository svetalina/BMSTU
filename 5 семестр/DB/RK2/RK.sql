DROP DATABASE IF EXISTS RK2;
CREATE DATABASE RK2;

-----------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS florist
(
    id serial PRIMARY KEY,
    name VARCHAR,
    passport INT,
    phone BIGINT CHECK(phone >= 8900000000 AND phone <= 89999999999)
);

DROP TABLE IF EXISTS florist;

CREATE TABLE IF NOT EXISTS bouquet
(
    id serial PRIMARY KEY,
    flr_id INT,
    name VARCHAR,
    
    FOREIGN KEY (flr_id) REFERENCES florist(id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS bouquet;

CREATE TABLE IF NOT EXISTS buyer
(
    id serial PRIMARY KEY,
    name VARCHAR,
    birthday DATE,
    city VARCHAR,
    phone BIGINT CHECK(phone >= 8900000000 AND phone <= 89999999999)
);

DROP TABLE IF EXISTS buyer;

CREATE TABLE IF NOT EXISTS _flr_br
(
    flr_id INT, 
    br_id INT,
    PRIMARY KEY (flr_id, br_id),
    FOREIGN KEY (flr_id) REFERENCES florist(id) ON DELETE CASCADE,
    FOREIGN KEY (br_id) REFERENCES buyer(id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS _flr_br;


-----------------------------------------------------------------------

INSERT INTO florist VALUES (1, 'Васильева Юлия Викторовна', 141535, 89772528920);
INSERT INTO florist VALUES (2, 'Пирязева Антонина Юрьевна', 452367, 89772528921);
INSERT INTO florist VALUES (3, 'Науменко Ирина Алексеевна', 567835, 89772528922);
INSERT INTO florist VALUES (4, 'Бишенова Лидия Ивановна', 563957, 89772528923);
INSERT INTO florist VALUES (5, 'Петров Андрей Сергеевич', 671290, 89772528924);
INSERT INTO florist VALUES (6, 'Марченко Валентина Семеновна', 126734, 89772528925);
INSERT INTO florist VALUES (7, 'Винокуршина Алевтина Григорьевна', 362378, 89772528926);
INSERT INTO florist VALUES (8, 'Калашников Сергей Витальевич', 452390, 89772528927);
INSERT INTO florist VALUES (9, 'Завойских Евения Викторовна', 456782, 89772528928);
INSERT INTO florist VALUES (10, 'Лагутина Инна Петровна', 562391, 89772528929);

INSERT INTO bouquet VALUES (1, 1, 'Роза заката');
INSERT INTO bouquet VALUES (2, 2, 'Роза пустыни');
INSERT INTO bouquet VALUES (3, 3, 'Лилия в саду');
INSERT INTO bouquet VALUES (4, 4, 'Георгины снежные');
INSERT INTO bouquet VALUES (5, 5, 'Маки в крови');
INSERT INTO bouquet VALUES (6, 6, 'Подснежники из сказки');
INSERT INTO bouquet VALUES (7, 7, 'Полевые цветы');
INSERT INTO bouquet VALUES (8, 8, 'Одуванчики в венке');
INSERT INTO bouquet VALUES (9, 9, 'Цветение папоротника');
INSERT INTO bouquet VALUES (10, 10, 'Букет невесты');

INSERT INTO buyer VALUES (1, 'Лазарева Эльга Романовна', '2002-09-23', 'Москва', 89772528900);
INSERT INTO buyer VALUES (2, 'Шестакова Селена Авдеевна', '1989-08-23', 'Москва', 89772528911);
INSERT INTO buyer VALUES (3, 'Шестакова Габриэлла Вячеславовна', '1989-08-25', 'Воронеж', 89772528922);
INSERT INTO buyer VALUES (4, 'Селезнёва Роза Адольфовна', '1979-07-23', 'Белгород', 89772528933);
INSERT INTO buyer VALUES (5, 'Самойлова Любава Адольфовна', '1969-08-23', 'Екатеринбург', 89772528944);
INSERT INTO buyer VALUES (6, 'Исаева Розалия Богдановна', '1990-08-13', 'Воронеж', 89772528955);
INSERT INTO buyer VALUES (7, 'Голубева Георгина Тихоновна', '1991-08-13', 'Белгород', 89772528966);
INSERT INTO buyer VALUES (8, 'Харитонова Амелия Серапионовна', '1993-08-13', 'Курск', 89772528977);
INSERT INTO buyer VALUES (9, 'Соловьёва Илена Ильяовна', '1956-08-13', 'Брянск', 89772528988);
INSERT INTO buyer VALUES (10, 'Котова Ева Владимировна', '1990-12-13', 'Ижевск', 89772528999);

INSERT INTO _flr_br VALUES (1, 2);
INSERT INTO _flr_br VALUES (1, 6);
INSERT INTO _flr_br VALUES (2, 7);
INSERT INTO _flr_br VALUES (3, 8);
INSERT INTO _flr_br VALUES (3, 2);
INSERT INTO _flr_br VALUES (3, 1);
INSERT INTO _flr_br VALUES (4, 4);
INSERT INTO _flr_br VALUES (4, 5);
INSERT INTO _flr_br VALUES (5, 6);
INSERT INTO _flr_br VALUES (5, 9);
INSERT INTO _flr_br VALUES (6, 10);
INSERT INTO _flr_br VALUES (7, 3);
INSERT INTO _flr_br VALUES (8, 4);
INSERT INTO _flr_br VALUES (9, 8);
INSERT INTO _flr_br VALUES (9, 9);
INSERT INTO _flr_br VALUES (10, 10);

-----------------------------------------------------------------------

--1. select + поисковый case
--   Возвращает буквенную оценку возраста покупателя по дате рождения
SELECT id, name, birthday,
	CASE 
		WHEN birthday >= '1990-01-01' THEN 'Молодой'
		ELSE 'Взрослый'
	END 
	AS recommendation
FROM buyer; 

--2. update + set
--   Устанавливает дату рождения как максимальную в таблице для всех покупателей, 
--   рожденных позже определенной даты (в данном случаем 01.01.1990)
UPDATE buyer
SET birthday = (SELECT max(birthday)
                     FROM buyer)
WHERE birthday > '1990-01-01';


SELECT *
FROM buyer;

--3. group by + having
--   Возвращает дату рождения самого молодого покупателя по городам, 
--   но дата рождения должна быть больше определенной 
SELECT city, max(birthday)
from buyer 
group by city
having max(birthday) > '1990-01-01';

-----------------------------------------------------------------------

--Хранимая процедура о ограничениях CHECK, содержащих в своем тексте LIKE

CREATE TABLE IF NOT EXISTS test
(
    id serial PRIMARY KEY,
    email VARCHAR,
    CHECK (email LIKE '%_@_%._%')
);

CREATE OR REPLACE PROCEDURE info_like_check()
LANGUAGE plpgsql
AS $$ 
DECLARE
    check_r RECORD;
BEGIN
    RAISE NOTICE 'Список ограничений с like:';
    FOR check_r in
        SELECT constraint_name, check_clause
		FROM information_schema.check_constraints
		WHERE check_clause LIKE '%~~%'
    LOOP
        RAISE NOTICE '%', check_r;
    END LOOP;
END
$$

CALL info_like_check();
