--АВТОР
CREATE TABLE IF NOT EXISTS author
(
    author_id serial PRIMARY KEY,
    first_name VARCHAR(128) NOT NULL,
    middle_name VARCHAR(128) NOT NULL,
    surname VARCHAR(128) NOT NULL,
    main_genre VARCHAR(128) NOT NULL
);

--ИЗДАТЕЛЬСТВО
CREATE TABLE IF NOT EXISTS publishing_house
(
    ph_id serial PRIMARY KEY,
    name_ph VARCHAR(128) NOT NULL,
    address VARCHAR(128) NOT NULL,
    website VARCHAR(128) NOT NULL,                  	--UNIQUE
    phone VARCHAR(11) NOT NULL         					--UNIQUE
);

--МАГАЗИН
CREATE TABLE IF NOT EXISTS shop
(
    shop_id serial PRIMARY KEY,
    name_sh VARCHAR(128) NOT NULL,
    address VARCHAR(128) NOT NULL,
    website VARCHAR(128) NOT NULL,
    rating FLOAT									   --CHECK(rating >= 0 and rating <= 10)
);

--ПРОИЗВЕДЕНИЕ
CREATE TABLE IF NOT EXISTS fiction
(
    fiction_id serial PRIMARY KEY,
    name_fc VARCHAR(256) NOT NULL,
    genre VARCHAR(128) NOT NULL,
    year_wr INT                                       --CHECK(year_wr >= 1 and year_wr <= 2022)
);

CREATE TABLE IF NOT EXISTS _fiction_author
(
    fiction_id INT, author_id INT,
    PRIMARY key (fiction_id, author_id),
    FOREIGN KEY (fiction_id) REFERENCES fiction(fiction_id) on delete cascade,
    FOREIGN KEY (author_id) REFERENCES author(author_id) on delete cascade
);

--КНИГА
CREATE TABLE IF NOT EXISTS book
(
    book_id serial PRIMARY KEY,
    ph_id INT,
    FOREIGN KEY (ph_id) REFERENCES publishing_house(ph_id) on delete cascade
);

CREATE TABLE IF NOT EXISTS _book_fiction
(
    book_id INT, 
    fiction_id INT,
    PRIMARY KEY (book_id, fiction_id),
    FOREIGN KEY (book_id) REFERENCES book(book_id) on delete cascade,
    FOREIGN KEY (fiction_id) REFERENCES fiction(fiction_id) on delete cascade
);


CREATE TABLE IF NOT EXISTS _book_shop
(
    book_id INT, 
    shop_id INT, 
    PRIMARY key (book_id, shop_id),
    FOREIGN KEY (book_id) REFERENCES book(book_id) on delete cascade,
    FOREIGN KEY (shop_id) REFERENCES shop(shop_id) on delete cascade
); 

drop table author cascade; 
drop table publishing_house cascade;
drop table shop cascade;
drop table fiction cascade;
drop table book cascade;
drop table _fiction_author;
drop table _book_fiction;
drop table _book_shop;

-- Anthony

DROP table if exists car CASCADE;
DROP table if exists cars_drivers CASCADE;
DROP table if exists driver CASCADE;
DROP table if exists vehicle_passport CASCADE;

create table cars_drivers(
  state_number CHAR(10),
  passport_number CHAR(15)
);

create table driver(
  passport_number CHAR(15),
  surname CHAR(20),
  name CHAR(20),
  patronymic CHAR(20),
  driving_experience INT
);

create table vehicle_passport(
  vehicle_passport_id CHAR(15),
  state_number CHAR(10),
  engine_number CHAR(15),
  model CHAR(30),
  colour CHAR(20),
  weight INT
);

create table car(
  state_number CHAR(10),
  engine_number CHAR(15),
  vehicle_passport CHAR(15),
  vehicle_registration_certificate CHAR(15),
  year_of_release INT,
  passport_number_of_owner CHAR(15)
);

ALTER TABLE car ADD CONSTRAINT state_number_PK PRIMARY KEY (state_number);
ALTER TABLE vehicle_passport ADD CONSTRAINT vehicle_passport_id_PK PRIMARY KEY (vehicle_passport_id);
ALTER TABLE vehicle_passport ADD CONSTRAINT engine_number_FK FOREIGN KEY (state_number) REFERENCES  car (state_number) ON DELETE CASCADE;
ALTER TABLE driver ADD CONSTRAINT passport_number_driver_PK PRIMARY KEY (passport_number);
ALTER TABLE cars_drivers ADD CONSTRAINT cars_drivers_PK PRIMARY KEY (state_number, passport_number);

COPY driver
FROM '/home/tables_Anthony/driver.csv'
DELIMITER ','
CSV HEADER;

COPY car
FROM '/home/tables_Anthony/car.csv'
DELIMITER ','
CSV HEADER;

COPY cars_drivers
FROM '/home/tables_Anthony/cars_drivers.csv'
DELIMITER ','
CSV HEADER;

COPY vehicle_passport
FROM '/home/tables_Anthony/pts.csv'
DELIMITER ','
CSV HEADER;

SELECT avg(d.driving_experience), vp.model
FROM driver d 
JOIN cars_drivers cd ON d.passport_number = cd.passport_number
JOIN car c ON cd.state_number = c.state_number
JOIN vehicle_passport vp ON vp.state_number = c.state_number
GROUP BY vp.model;


-- Nastya

CREATE TABLE IF NOT EXISTS star
(
    id serial,
    name_star VARCHAR(128) NOT NULL,
    alpha VARCHAR(128) NOT NULL,
    constelation VARCHAR(128) NOT NULL,
    rise FLOAT, --                   CHECK (rise > 0);
    size_star FLOAT NOT NULL, --     CHECK(size_star > 0), 
    
     extra_id INT
);

COPY star
FROM '/home/Nastya/Star.csv'
DELIMITER ','
CSV HEADER;