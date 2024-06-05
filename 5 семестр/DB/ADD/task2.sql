DROP TABLE IF EXISTS emp;

CREATE TABLE IF NOT EXISTS emp
(
    id INT,
	fio VARCHAR,
	date DATE,
	status VARCHAR
);

INSERT INTO emp VALUES
(1, 'Иванов Иван Иванович', '2022-12-12', 'Работа offline'),
(1, 'Иванов Иван Иванович', '2022-12-13', 'Работа offline'),
(1, 'Иванов Иван Иванович', '2022-12-14', 'Больничный'),
(1, 'Иванов Иван Иванович', '2022-12-15', 'Больничный'),
(1, 'Иванов Иван Иванович', '2022-12-16', 'Удаленная работа'),
(2, 'Петров Петр Петрович', '2022-12-12', 'Работа offline'),
(2, 'Петров Петр Петрович', '2022-12-13', 'Работа offline'),
--(2, 'Петров Петр Петрович', '2022-12-14', 'Удаленная работа'),
--(2, 'Петров Петр Петрович', '2022-12-15', 'Удаленная работа'),
(2, 'Петров Петр Петрович', '2022-12-16', 'Работа offline');


----------------------------------
SELECT 
	id,
	fio, 
	min(date) AS date_from, 
	max(date) AS date_to, 
	status 
FROM emp
GROUP BY id, fio, status
ORDER BY fio, date_from;


----------------------------------
WITH grps AS (
    SELECT id, fio, date, status,
           date - (ROW_NUMBER() OVER
           (PARTITION BY fio, status ORDER BY date))::int AS grpdate
    FROM emp
)
SELECT id, fio, min(date) AS date_from, max(date) AS date_to, status
FROM grps
GROUP BY id, fio, status, grpdate
ORDER BY fio, date_from;

---- Подзапросы
SELECT id, fio, date, status, (ROW_NUMBER() OVER
	(PARTITION BY fio, status ORDER BY date))::int AS grpdate
FROM emp