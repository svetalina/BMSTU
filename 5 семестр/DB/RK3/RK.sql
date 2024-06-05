--- Создать таблицы и соответствующие связи

DROP TABLE emp CASCADE;
DROP TABLE in_out CASCADE;

CREATE TABLE IF NOT EXISTS emp (
    id SERIAL PRIMARY KEY,
    name VARCHAR,
    birthday DATE,
    dep VARCHAR
);

CREATE TABLE IF NOT EXISTS in_out (
    io_id SERIAL PRIMARY KEY,
    emp_id INT,
    date DATE,
    wday VARCHAR,
    time TIME,
    type12 INT,
    FOREIGN KEY (emp_id) REFERENCES emp(id) ON DELETE CASCADE
);

INSERT INTO emp (name, birthday, dep) VALUES
('Иванов Иван Иванович', '1990-09-25', 'ИТ'),
('Петров Петр Петрович', '1987-11-12', 'Бухгалтерия'),
('Гаврилова Юлия Михайловна', '1995-06-21', 'ИТ'),
('Сидоров Сидор Сидорович', '2001-09-25', 'Бухгалтерия');

INSERT INTO in_out (emp_id, date, wday, time, type12) VALUES
(1, '2022-12-17', 'Суббота', '9:05:00', 1),
(1, '2022-12-17', 'Суббота', '9:20:00', 2),
(1, '2022-12-17', 'Суббота', '9:20:00', 2),
(1, '2022-12-16', 'Пятница', '9:20:00', 2),
(1, '2022-12-14', 'Среда', '9:20:00', 2),
(1, '2022-12-13', 'Вторник', '9:25:00', 1),
(2, '2022-12-14', 'Среда', '9:36:00', 1),
(2, '2022-12-16', 'Пятница', '18:36:00', 2),
(2, '2022-12-15', 'Четверг',   '9:05:00', 1),
(2, '2022-12-15', 'Четверг',   '17:10:00', 2),
(3, '2022-12-17', 'Суббота', '10:00:00', 1),
(1, '2022-12-16', 'Пятница', '9:20:00', 2),
(1, '2022-12-16', 'Пятница', '9:20:00', 2),
(1, '2022-12-16', 'Пятница', '9:20:00', 2),
(1, '2022-12-16', 'Пятница', '9:20:00', 2);

SELECT * FROM emp;
SELECT * FROM in_out;

--- Написать скалярную функцию, возвращающую минимальный возраст 
--- сотрудника, опаздавшего более, чем на 10 минут

DROP FUNCTION min_age_late;

CREATE OR REPLACE FUNCTION min_age_late()
RETURNS int
LANGUAGE plpgsql
AS $$
BEGIN
   RETURN (SELECT min(date_part('year', now()) - date_part('year', birthday))
           FROM emp JOIN in_out ON emp.id = in_out.emp_id
           WHERE type12 = 1
           GROUP BY emp_id
           HAVING min(time) - '09:00:00' > INTERVAL '10 minutes');
END
$$

SELECT *
FROM min_age_late()
      