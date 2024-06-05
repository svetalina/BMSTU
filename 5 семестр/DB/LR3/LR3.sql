-- 1.1 Скалярная функция: ставит в соответсвии рейтингу буквенную рекоммендацию
drop function if exists recommendation(rating float);

create function recommendation(rating float)
returns varchar(128) as $$
declare rtrn_var varchar(128);
begin
    case rating
    	when '10' then rtrn_var := 'Лучший';
		when '0' then rtrn_var := 'Худший';
		else rtrn_var := 'Средний';
	end case;
	return rtrn_var;
end;
$$ language PLPGSQL;

select shop_id, name_sh, address, recommendation(rating)
from shop;



-- 1.2 Подставляемая табличная функция: возвращает произведения жанра "Приключения" и написанные в максимальный год в БД
drop function if exists genre_ficiton();

create function genre_ficiton()
returns table
(
    name_fc VARCHAR(256),
    genre VARCHAR(128),
    year_wr INT  
)
as $$
begin
    return QUERY
    select f.name_fc, f.genre, f.year_wr
    from fiction as f
    where f.genre = 'Приключения' and f.year_wr = 
    (
        select max(f.year_wr) 
        from fiction as f
    );
end;
$$ language PLPGSQL;

select *
from genre_ficiton();



-- 1.3 Многооператорная табличная функция: возвращает произведения и автора жанра "Юмор" и написанные позже какого-то года
drop function if exists genre_year_ficiton(year_wr_f INT);

create function genre_year_ficiton(year_wr_f INT)
returns table
(
	author VARCHAR(256), 
    name_fc VARCHAR(256),
    genre VARCHAR(128),
    year_wr INT  
)
as $$
begin
    drop table if exists tmp_table;

    create temp table if not exists tmp_table
    (
    	author VARCHAR(256), 
        name_fc VARCHAR(256),
    	genre VARCHAR(128),
    	year_wr INT
    );

    insert into tmp_table
    select ffaa.surname, ffaa.name_fc, ffaa.genre, ffaa.year_wr
    from ((fiction AS f JOIN _fiction_author AS fa ON f.fiction_id = fa.fiction_id) AS ffa 
          JOIN author AS ath ON ffa.author_id = ath.author_id) AS ffaa
    where ffaa.genre = 'Юмор' and ffaa.year_wr > year_wr_f;

    return QUERY
    select *
    from tmp_table;
end;
$$ language PLPGSQL;

select *
from genre_year_ficiton(1970)



-- 1.4 Рекурсивная функция или функция с рекурсивным ОТВ
drop table if exists friends_author;

create table if not exists friends_author
(
    author_id INT not null primary key,
    surname VARCHAR(128),
    friend_id  INT
);

insert into friends_author(author_id, surname, friend_id) VALUES
(1, 'Толстой', 3),
(2, 'Лермонтов', null),
(3, 'Пушкин', 4),
(4, 'Гоголь', 2);

select *
from friends_author;

--------------------

drop function if exists friends(start_id INT);

create function friends(start_id INT)
returns table
(
    author_id INT,
    surname VARCHAR,
    friend_id INT
)
as $$
begin
    return QUERY
	with recursive recursive_friends(author_id, surname, friend_id) as
	(
	    -- Определение закрепленного элемента.
	    select fa.author_id, fa.surname, fa.friend_id
	    from friends_author as fa
	    where fa.author_id = start_id
	    union all
	    -- Определение рекурсивного элемента
	    select fa.author_id, fa.surname, fa.friend_id
	    from friends_author as fa
	    join recursive_friends as rec on fa.author_id = rec.friend_id
	)
	select *
	from recursive_friends;
end;
$$ language PLPGSQL;

select *
from friends(1);



-- 2.1 Хранимая процедура без параметров или с параметрами: увеличить рейтинг заданному по id магазину на заданное число
drop procedure if exists change_rating(id INT, rating_increase INT);

create procedure change_rating(id INT, rating_increase INT)
as $$
begin
    update shop
    SET rating = rating + rating_increase
    where shop_id = id;
end;
$$ language PLPGSQL;

call change_rating(2, 1);

select *
from shop



-- 2.2 Рекурсивная хранимая процедуру или хранимая процедура с рекурсивным ОТВ: вывести номера телефонов издательств
-- по геометрической прогрессии 2 от 1 до 50
drop procedure if exists recursive_procedure(cur_id INT, end_id INT);

create procedure recursive_procedure(cur_id INT, end_id INT)
as $$
declare
    cur_phone VARCHAR;
begin
    select ph.phone
    from publishing_house as ph
    where ph.ph_id = cur_id
	into cur_phone;

    if cur_id < end_id then
        raise notice 'ph_id = %, phone = %', 
            cur_id, cur_phone;

        cur_id = cur_id * 2;
        call recursive_procedure(cur_id, 50);
    else
        raise notice 'END';
    end if;
end;
$$ language PLPGSQL;

call recursive_procedure(1, 50);



--2.3 Хранимая процедура с курсором: получить произведения, год написания которых между заданными годами
drop procedure if exists fiction_year_wr(beg_year INT, end_year INT);

create procedure fiction_year_wr(beg_year INT, end_year INT)
as $$
declare 
    cur_fiction RECORD;
    fiction_cursor cursor for
        select *
        from fiction as fc
        where fc.year_wr >= beg_year and fc.year_wr <= end_year;
begin
    open fiction_cursor;
    loop
        fetch fiction_cursor into cur_fiction;
        
        raise notice 'id = %, name = %, genre = %, year_wr = %', 
            cur_fiction.fiction_id, cur_fiction.name_fc, cur_fiction.genre, cur_fiction.year_wr;

        exit when not found;
    end loop;
    close fiction_cursor;
end;
$$ language PLPGSQL;

call fiction_year_wr(2021, 2022);



-- 2.4 Хранимая процедура доступа к метаданным: вывести названия атрибутов таблицы и их возможность быть "NULL"
drop procedure if exists get_metadata(my_table_name VARCHAR);

create procedure get_metadata(my_table_name VARCHAR)
as $$
declare
    cur_column RECORD;
    my_cursor cursor for
        select *
        from information_schema.columns
        where my_table_name = table_name;
begin
    open my_cursor;
    loop
        fetch my_cursor into cur_column;

        raise notice 'column_name = %, data_type = %, is_nullable = %', 
            cur_column.column_name, cur_column.data_type, cur_column.is_nullable;

        exit when not found;
    end loop;
    close my_cursor;
end;
$$ language PLPGSQL;

call get_metadata('shop');



-- 3.1 Триггер AFTER: выводит сообщение при дабавлении информации в таблицу произведений
drop function if exists insert_info() cascade;

create function insert_info()
returns trigger
as $$
begin
    raise notice 'Произведение добавлено';
    return new;
end;
$$ language PLPGSQL;

create trigger insert_info_trigger after insert on fiction
for row execute procedure insert_info();

insert into fiction
values (5001, 'Парфюмер', 'Триллер', 1967)

delete from fiction 
where fiction_id = 5001;

select *
from fiction



-- 3.2 Триггер INSTEAD OF: добавить произведение оно написано не позднее среднего года написания произведений в таблице
drop function if exists insert_info_with_limit() cascade;

create function insert_info_with_limit()
returns trigger
as $$
begin
    if new.year_wr < (select avg(year_wr) from fiction) then
        raise notice 'Слишком старое произведение, сейчас такое уже не читают';
        return null;
    else
        insert into fiction
        values(new.fiction_id, new.name_fc, new.genre, new.year_wr);

        raise notice 'Произведение добавлено';
        return new;
    end if;
end;
$$ language PLPGSQL;

drop view if exists ficiton_view;
create view ficiton_view
as
    select *
    from fiction;

create trigger insert_with_lim_trigger instead of INSERT on ficiton_view
for row execute procedure insert_info_with_limit();

insert into ficiton_view
values(5001, 'Слово о полку Игореве', 'Фольклор', 1701);

insert into ficiton_view
values(5002, 'Небожители', 'Фантастика', 2019);

delete from fiction 
where fiction_id = 5001;

delete from fiction 
where fiction_id = 5002;

select *
from fiction
