import psycopg2
from color import red, green, blue, base_color

class BooksDB:

    def __init__(self):
        try:
            self.__connection = psycopg2.connect(
                host     = 'localhost', 
                user     = 'alina',
                password = '2606',
                database = 'postgres'
                )
            self.__cursor = self.__connection.cursor()
            print("%sPostgreSQL соединение установлено%s\n" % (green, base_color))

        except Exception as err:
            print("%sPostgreSQL соединение не установлено%s\n" % (red, base_color))
            return

    def __del__(self):
        if self.__connection:
            self.__cursor.close()
            self.__connection.close()
            print("%sPostgreSQL соединение закрыто%s\n" % (green, base_color))

    def __sql_executer(self, sql_query):
        try:
            self.__cursor.execute(sql_query)
        except Exception as err:
            print("%sPostgreSQL соединение было преравано%s\n" % (red, base_color))
            return
    
        return sql_query

    def scalar_query(self):

        print("%sПолучить средний рейтинг магазинов из Москвы:%s"
            %(blue, base_color))

        sql_query = \
            """
            --1
            select avg(rating)
            from shop
            where address like '%Москва%'
            """

        if self.__sql_executer(sql_query) is not None:
            row = self.__cursor.fetchone()

            return row

    def join_query(self):

        print("%sПолучить книги, у автора которых имя Юлия:%s\n"
            %(blue, base_color))

        sql_query = \
            """
            --2
            select book_id, name 
            from _book_fiction as bf 
            join (
                select fiction_id, name
                from _fiction_author as fa 
                join (
                    select author_id, CONCAT(surname, ' ', first_name, ' ', middle_name) as name 
                    from author
                    where first_name = 'Юлия') as a
                on fa.author_id = a.author_id) as f
            on bf.fiction_id = f.fiction_id
            """
        
        if self.__sql_executer(sql_query) is not None:
            row = self.__cursor.fetchone()
            table = list()

            while row is not None:
                table.append(row)
                row = self.__cursor.fetchone()

            return table

    def cte_row_number_query(self):

        print("%sУстранение дублей инструкцией row_number():%s\n"
            %(blue, base_color))

        sql_query = \
            """
            -- 3
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
            where number = 1 and fiction_id < 11
            """
        
        if self.__sql_executer(sql_query) is not None:

            row = self.__cursor.fetchone()
            table = list()

            while row is not None:
                table.append(row)
                row = self.__cursor.fetchone()

            return table
    
    def metadata_query(self):

        print("%sПолучить имя текущей базы данных и лимит подключений к ней:%s\n"
            %(blue, base_color))

        sql_query = \
            """
            -- 4
            select pg.datname, pg.datconnlimit
            from pg_database as pg
            where pg.datname = 'postgres';
            """
        
        if self.__sql_executer(sql_query) is not None:
            row = self.__cursor.fetchone()

            return [row]

    def scalar_function_call(self):

        print("%sПолучить в соответсвии рейтингу буквенную рекоммендацию:%s\n"
            %(blue, base_color))

        sql_query = \
            """
            -- 5
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
            from shop
            where shop_id < 11;
            """
        
        if self.__sql_executer(sql_query) is not None:

            row = self.__cursor.fetchone()
            table = list()

            while row is not None:
                table.append(row)
                row = self.__cursor.fetchone()

            return table

    def tabular_function_call(self):

        print("%sПолучить произведения и автора жанра Юмор и написанные позже заданного года:%s\n"
            %(blue, base_color))

        sql_query = \
            """
            -- 6
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
            """
        
        if self.__sql_executer(sql_query) is not None:

            row = self.__cursor.fetchone()
            table = list()

            while row is not None:
                table.append(row)
                row = self.__cursor.fetchone()

            return table
    
    def stored_procedure_call(self):

        print("%sУвеличить рейтинг заданному по id магазину на заданное число:%s\n"
            %(blue, base_color))

        sql_query = \
            """
            -- 7
            drop procedure if exists change_rating(id INT, rating_increase INT);

            create procedure change_rating(id INT, rating_increase INT)
            as $$
            begin
                update shop
                SET rating = rating + rating_increase
                where shop_id = id;
            end;
            $$ language PLPGSQL;
            
            call change_rating(3, 1);
            
            select *
            from shop
            where shop_id = 3
            """
        
        if self.__sql_executer(sql_query) is not None:

            row = self.__cursor.fetchone()
            table = list()

            while row is not None:
                table.append(row)
                row = self.__cursor.fetchone()

            return table

    def system_functionc_call(self):

        print("%sВызвать системную функцию для вывода имени текущей базы данных:%s\n"
            %(blue, base_color))

        sql_query = \
            """
            -- 8

            SELECT *
            FROM current_database();
            """
        
        if self.__sql_executer(sql_query) is not None:
            row = self.__cursor.fetchone()

            return row

    def create_new_table(self):

        print("%sСоздать таблицу соавторов:%s\n"
            %(blue, base_color))

        sql_query = \
            """
            -- 9
            drop table if exists friends_author;
            
            create table if not exists friends_author
            (
                author_id int primary key,
                surname varchar(128),
                friend_id  int
            );
            """
        
        if self.__sql_executer(sql_query) is not None:
            print("%sДействие выполнено успешно%s" %(blue, base_color))


    def insert_into_new_table(self):

        print("%sВыполнить вставку данных в созданную таблицу соавторов:%s\n"
            %(blue, base_color))

        sql_query = \
            """
            -- 10
            INSERT INTO friends_author(author_id, surname, friend_id) VALUES
            (1, 'Толстой', 3),
            (2, 'Лермонтов', NULL),
            (3, 'Пушкин', 4),
            (4, 'Гоголь', 2);
            
            SELECT *
            FROM friends_author;
            """
        
        if self.__sql_executer(sql_query) is not None:

            row = self.__cursor.fetchone()
            table = list()

            while row is not None:
                table.append(row)
                row = self.__cursor.fetchone()

            return table
