from peewee import *
import datetime

CON = PostgresqlDatabase(
    host='localhost',
    user='alina',
    password='2606',
    database='postgres'
)

class BaseModel(Model):
    class Meta:
        database = CON

class Emp(BaseModel):
    id = IntegerField(column_name='id')
    name = CharField(column_name='name')
    birthday = DateField(column_name='birthday')
    dep = TextField(column_name='dep')

    class Meta:
        table_name = 'emp'


class InOut(BaseModel):
    io_id = IntegerField(column_name='id')
    emp_id = ForeignKeyField(Emp, backref='emp_id')
    date = DateField(column_name='date')
    wday = TextField(column_name='wday')
    time = TimeField(column_name='time')
    type12 = IntegerField(column_name='type12')

    class Meta:
        table_name = 'in_out'


def ql1():
    min_birthday = (Emp.select(fn.min(Emp.birthday)).where(Emp.dep ==
            'Бухгалтерия'))

    query = Emp.select(Emp.id, Emp.name, Emp.birthday).where(Emp.dep ==
                'Бухгалтерия' and Emp.birthday == min_birthday)

    for elem in query.dicts().execute():
        print(elem)
    print()

def ql2():
    query = InOut.select(InOut.emp_id, InOut.date,
                fn.count(InOut.emp_id)).where(InOut.type12 == 2).group_by(InOut.emp_id,
                InOut.date).having(fn.count(InOut.emp_id) > 3)

    for elem in query.dicts().execute():
        print(elem)
    print()

def ql3():
    query = Emp.select(Emp.id, Emp.name).join(InOut).where(InOut.date ==
                datetime.datetime.now() and InOut.type12 == 1 and InOut.time ==
                InOut.select(fn.max(InOut.time)).where(InOut.type12 == 1 and
                InOut.date == datetime.datetime.now()))

    for elem in query.dicts().execute():
        print(elem)
    print()
