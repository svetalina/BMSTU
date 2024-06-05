--АВТОР
COPY author(author_id, first_name, middle_name, surname, main_genre)
FROM '/home/tables/author.csv'
DELIMITER ';'
CSV HEADER;

--ИЗДАТЕЛЬСТВО
COPY publishing_house(ph_id, name_ph, address, website, phone)
FROM '/home/tables/publishing house.csv'
DELIMITER ';'
CSV HEADER;

--МАГАЗИН
COPY shop(shop_id, name_sh, address, website, rating)
FROM '/home/tables/shop.csv'
DELIMITER ';'
CSV HEADER;

--ПРОИЗВЕДЕНИЕ
COPY fiction(fiction_id, name_fc, genre, year_wr)
FROM '/home/tables/fiction.csv'
DELIMITER ';'
CSV HEADER;

COPY _fiction_author(fiction_id, author_id)
FROM '/home/tables/_fiction_author.csv'
DELIMITER ';'
CSV HEADER;

--КНИГА
COPY book(book_id, ph_id)
FROM '/home/tables/book.csv'
DELIMITER ';'
CSV HEADER;

COPY _book_fiction(book_id, fiction_id)
FROM '/home/tables/_book_fiction.csv'
DELIMITER ';'
CSV HEADER;

COPY _book_shop(book_id, shop_id)
FROM '/home/tables/_book_shop.csv'
DELIMITER ';'
CSV HEADER;


select * from author;
select * from publishing_house;
select * from shop;
select * from fiction;
select * from book;
select * from _fiction_author;
select * from _book_fiction;
select * from _book_shop;


--ЗАЩИТА

--1
insert into fiction values (5001, 'Ха-ха', 'Юмор', 2023);
insert into _fiction_author values (5001, 3);

--2
delete from book where book_id in(select book_id 
from book where exists (select * from _book_fiction 
where book.book_id = _book_fiction.book_id and exists(select * from fiction 
where fiction.fiction_id = _book_fiction.fiction_id and genre = 'Приключения')));

select bf.book_id, f.genre 
from _book_fiction as bf full join fiction as f on bf.fiction_id = f.fiction_id

