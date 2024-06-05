-- 1 выбрать произвдения, год написания которых более 2000
select * 
from fiction
where year_wr > 2000


-- 2 выбрать магазины с рейтингом более 4, но менее 7.5
select *
from shop
where rating between 4.0 and 7.5


-- 3 выбрать магазины, расположенные в Москве
select *
from shop 
where address like '%Москва%'


-- 4 выбрать книги, изданные в Воронеже
select *
from book b
where b.ph_id in (
	select ph_id 
	from  publishing_house
	where address like '%Воронеж%')


-- 5 выбрать книги, в которых содержится хоть одно произведение с жанром "Приключения"
select book_id 
from book 
where exists (
	select * 
	from _book_fiction 
	where book.book_id = _book_fiction.book_id and exists(
		select * 
		from fiction 
		where fiction.fiction_id = _book_fiction.fiction_id and genre = 'Приключения'))
			  		

--6 выбрать книги, в которых содержится хоть одно произведение, написанное в XX веке
select book_id
from _book_fiction bf  
where bf.fiction_id = any (
	select fiction_id 
	from fiction f
	where f.year_wr between 2000 and 2022);

select bf.book_id, f.year_wr      --Проверка
from (
	select book_id, fiction_id
	from _book_fiction bf  
	where bf.fiction_id in (
		select fiction_id 
		from fiction f
		where f.year_wr between 2000 and 2022))
as bf left join fiction as f 
on bf.fiction_id = f.fiction_id;  


-- 7 выбрать магазины с максимальным рейтингом
select *
from shop sh
where sh.rating = (
	select max(rating)
	from shop)

	
-- 8 выбрать авторов с именем Юлия
select *
from author
where first_name = 'Юлия'


-- 9 создать столбец, обозначающий буквенно магазины с максимально возможным и минимально возможным рейтингом
select name_sh, rating,
	case rating
		when '10' then 'Лучший'
		when '0' then 'Худший'
		else 'Нормальный'
	end
from shop 
							

-- 10 создать столбец, обозначающий буквенно рейтинг магазина 
select name_sh, rating,
	case 
		when rating > 5 then 'Хороший'
		when rating < 5 then 'Плохой'
		else 'Средний'
	end
from shop  


-- 11 создать временную таблицу с минимальным рейтингом для каждой сети магазинов
select name_sh, min(rating)
into temporary table shop_new
from shop
group by name_sh

select * from shop_new

drop table shop_new


-- 12 Получить все книги, в которых содержится хоть одно произведение с жанром "Приключения"
select book_id 
from _book_fiction as bf 
join (
	select fiction_id
	from fiction
	where genre = 'Приключения') as f
on bf.fiction_id = f.fiction_id


-- 13 выбрать все книги, у автора которых имя "Юлия"
select book_id --, first_name 
from _book_fiction as bf 
join (
	select fiction_id --, first_name 
	from _fiction_author as fa 
	join (
		select author_id --, first_name 
		from author
		where first_name = 'Юлия') as a
	on fa.author_id = a.author_id) as f
on bf.fiction_id = f.fiction_id



-- 14 выбрать сети мгазинов
select name_sh
from shop 
group by name_sh


-- 15 выбрать сети магазинов со средним рейтингом больше 5
select name_sh, avg(rating)
from shop 
group by name_sh
having avg(rating) > 5 


-- 16 вставить одну строку в таблицу автров
insert into author 
values (1001, 'Юлия', 'Михайловна', 'Гаврилова', 'Научный')


--17 
insert into author
select (
	select max(author_id) + 1
	from author),
first_name, middle_name, surname, concat(main_genre, ' и фантастика')
from author
where author_id = 1

--18 простая инструкция update
update shop
where shop_id = 1


-- 19 инструкция update с подзапросом
update shop 
set rating = (
	select avg(rating)
	from shop)
where shop_id = 2


-- 20 простая инструкция delete
delete from author 
where author_id = '1001' 


-- 21 удалить книги, изданные в Воронеже
delete from book 
where ph_id in (
	select ph_id
	from publishing_house 
	where address like '%Воронеж%')
	
	
-- 22 выбрать книги от ХХ века и сгруппировать по жанрам
with genres as 
	(select name_fc, genre  
	from fiction
	where year_wr > 1900
	order by genre)
select * from genres


-- 23 создать таблицу соавторов (считается соавтор моего соавтора не мой соавтор)
DROP TABLE IF EXISTS friends_author;

CREATE TABLE IF NOT EXISTS friends_author
(
    author_id INT NOT NULL PRIMARY KEY,
    surname VARCHAR(128),
    friend_id  INT
);

INSERT INTO friends_author(author_id, surname, friend_id) VALUES
(1, 'Толстой', 3),
(2, 'Лермонтов', NULL),
(3, 'Пушкин', 4),
(4, 'Гоголь', 2);

SELECT *
FROM friends_author;


WITH RECURSIVE recursive_friends(author_id, surname, friend_id) AS
(
    -- Определение закрепленного элемента.
    SELECT fa.author_id, fa.surname, fa.friend_id
    FROM friends_author AS fa
    WHERE fa.author_id = 1
    UNION ALL
    -- Определение рекурсивного элемента
    SELECT fa.author_id, fa.surname, fa.friend_id
    FROM friends_author AS fa
    JOIN recursive_friends AS rec ON fa.author_id = rec.friend_id
)
SELECT *
FROM recursive_friends;


--24 выбрать произведения со своими параметрами и дополнительным - средним годом написания книг такого жанра
select fiction_id, name_fc, genre, year_wr, avg(year_wr) over (partition by genre) as avg_year_wr
from fiction


--25 устранение запросов инструкцией row_number()
with table_with_duplicates as
(
    select *
    from fiction

    union all

    select *
    from fiction
),
tmp_table as
(   
    select *, row_number() over (partition by fiction_id) as number
    from table_with_duplicates
)
select *
from tmp_table
where number = 1


--ЗАЩИТА

--Проверить у кого из двух случайных авторов больше книг
select author_id, count(*) as count_id
from (
	select book_id, author_id
	from _book_fiction as bf 
	join (
		select fiction_id, author_id
		from _fiction_author) as fa
	on bf.fiction_id = fa.fiction_id) as ba
where author_id = 14 or author_id = 25
group by author_id
order by count_id desc
