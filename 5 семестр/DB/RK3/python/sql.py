import psycopg2

class RK03:
    def __init__(self):
        try:
            self.__connection = psycopg2.connect(
                host='localhost',
                user='alina',
                password='2606',
                database='postgres'
            )
            self.__cursor = self.__connection.cursor()
            print("PostgreSQL соединение установлено\n")

        except Exception as err:
            print("PostgreSQL соединение не установлено\n")
            return

    def __del__(self):
        if self.__connection:
            self.__cursor.close()
            self.__connection.close()
            print("PostgreSQL соединение закрыто\n")

    def __sql_executer(self, sql_query):
        try:
            self.__cursor.execute(sql_query)
        except Exception as err:
            print("PostgreSQL соединение было преравано\n")
            return

        return sql_query

    def q1(self):
        sql_query = \
            """
            SELECT id, name, birthday
            FROM emp
            WHERE dep = 'Бухгалтерия' AND
            birthday = (
                      SELECT MIN(birthday)
                      FROM emp
                      WHERE dep = 'Бухгалтерия'
                     )
            """
        if self.__sql_executer(sql_query) is not None:
            row = self.__cursor.fetchone()

            return row


    def q2(self):
        sql_query = \
            """
            SELECT emp_id, date, count(*) AS out
            FROM in_out
            WHERE type12 = 2
            GROUP BY emp_id, date
            HAVING count(*) > 3;
            """
        if self.__sql_executer(sql_query) is not None:
            row = self.__cursor.fetchone()

            return row

    def q3(self):
        sql_query = \
            """
            SELECT emp.id, name
            FROM emp JOIN in_out ON emp.id = in_out.emp_id
            WHERE date = current_date AND type12 = 1 AND
                time = (
                        SELECT max(time)
                        FROM in_out
                        WHERE type12 = 1 AND date = current_date
                    )
            """
        if self.__sql_executer(sql_query) is not None:
            row = self.__cursor.fetchone()

            return row
