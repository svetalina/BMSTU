-- Создать таблицы:
-- • Table1{id: integer, var1: string, valid_from_dttm: date, valid_to_dttm: date}
-- • Table2{id: integer, var2: string, valid_from_dttm: date, valid_to_dttm: date}
-- Версионность в таблицах непрерывная, разрывов нет.
-- Для каждого ID дата начала версионности и дата конца версионности в Table1 и Table2 совпадают. 

DROP TABLE IF EXISTS  t1, t2;

CREATE TABLE IF NOT EXISTS t1
(
	id INT,
	var1 VARCHAR,
	valid_from_dttm DATE,
	valid_to_dttm DATE
);

CREATE TABLE IF NOT EXISTS t2
(
	id INT,
	var2 VARCHAR,
	valid_from_dttm DATE,
	valid_to_dttm DATE
);

INSERT INTO t1 VALUES
(1, 'A', '2018-09-01', '2018-09-15'),
(1, 'B', '2018-09-16', '5999-12-31');

INSERT INTO t2 VALUES
(1, 'A', '2018-09-01', '2018-09-18'),
(1, 'B', '2018-09-19', '5999-12-31');


SELECT *
FROM (SELECT t1.id, t1.var1, t2.var2,
		GREATEST(t1.valid_from_dttm, t2.valid_from_dttm) AS valid_from_dttm,
		LEAST(t1.valid_to_dttm, t2.valid_to_dttm) AS valid_to_dttm
	  FROM t1 JOIN t2 ON t1.id = t2.id) AS dates
WHERE valid_from_dttm <= valid_to_dttm;
