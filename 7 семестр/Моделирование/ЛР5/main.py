import sys
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QLineEdit, QPushButton
from style import Styles

from models import EvenDistribution
from models import Generator
from models import Processor
from models import EventModel


class MyWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Лабораторная работа №4')
        self.setFixedSize(700, 500)
        self.setStyleSheet(Styles)

        self.initUI()

    def initUI(self):
        vbox = QVBoxLayout(self)

        ######################################
        title_client = QLabel('<b>Клиенты</b>')
        title_client.setAlignment(Qt.AlignCenter)

        vbox.addWidget(title_client)

        ##########################
        hbox_client = QHBoxLayout()

        title_client_n = QLabel('Количество клиентов: ')
        title_client_n.setAlignment(Qt.AlignCenter)
        title_client_n.setFixedWidth(180)
        self.client_n = QLineEdit()
        self.client_n.setAlignment(Qt.AlignCenter)
        self.client_n.setText("300")

        hbox_client.addWidget(title_client_n)
        hbox_client.addWidget(self.client_n)

        vbox.addLayout(hbox_client)

        ############################
        hbox_client_t = QHBoxLayout()

        title_client_t1 = QLabel('Прибытие клиентов: ')
        title_client_t1.setAlignment(Qt.AlignCenter)
        title_client_t1.setFixedWidth(180)
        self.client_t1 = QLineEdit()
        self.client_t1.setAlignment(Qt.AlignCenter)
        self.client_t1.setText("10")
        title_client_t2 = QLabel('±')
        title_client_t2.setAlignment(Qt.AlignCenter)
        self.client_t2 = QLineEdit()
        self.client_t2.setAlignment(Qt.AlignCenter)
        self.client_t2.setText("2")

        hbox_client_t.addWidget(title_client_t1)
        hbox_client_t.addWidget(self.client_t1)
        hbox_client_t.addWidget(title_client_t2)
        hbox_client_t.addWidget(self.client_t2)

        vbox.addLayout(hbox_client_t)

        ####################################
        title_op = QLabel('<b>Операторы</b>')
        title_op.setAlignment(Qt.AlignCenter)

        vbox.addWidget(title_op)

        #########################
        hbox_op1_t = QHBoxLayout()

        title_op1_t1 = QLabel('Первый оператор: ')
        title_op1_t1.setAlignment(Qt.AlignCenter)
        title_op1_t1.setFixedWidth(180)
        self.op1_t1 = QLineEdit()
        self.op1_t1.setAlignment(Qt.AlignCenter)
        self.op1_t1.setText("20")
        title_op1_t2 = QLabel('±')
        title_op1_t2.setAlignment(Qt.AlignCenter)
        self.op1_t2 = QLineEdit()
        self.op1_t2.setAlignment(Qt.AlignCenter)
        self.op1_t2.setText("5")

        hbox_op1_t.addWidget(title_op1_t1)
        hbox_op1_t.addWidget(self.op1_t1)
        hbox_op1_t.addWidget(title_op1_t2)
        hbox_op1_t.addWidget(self.op1_t2)

        vbox.addLayout(hbox_op1_t)

        #########################
        hbox_op2_t = QHBoxLayout()

        title_op2_t1 = QLabel('Второй оператор: ')
        title_op2_t1.setAlignment(Qt.AlignCenter)
        title_op2_t1.setFixedWidth(180)
        self.op2_t1 = QLineEdit()
        self.op2_t1.setAlignment(Qt.AlignCenter)
        self.op2_t1.setText("40")
        title_op2_t2 = QLabel('±')
        title_op2_t2.setAlignment(Qt.AlignCenter)
        self.op2_t2 = QLineEdit()
        self.op2_t2.setAlignment(Qt.AlignCenter)
        self.op2_t2.setText("10")

        hbox_op2_t.addWidget(title_op2_t1)
        hbox_op2_t.addWidget(self.op2_t1)
        hbox_op2_t.addWidget(title_op2_t2)
        hbox_op2_t.addWidget(self.op2_t2)

        vbox.addLayout(hbox_op2_t)

        #########################
        hbox_op3_t = QHBoxLayout()

        title_op3_t1 = QLabel('Третий оператор: ')
        title_op3_t1.setAlignment(Qt.AlignCenter)
        title_op3_t1.setFixedWidth(180)
        self.op3_t1 = QLineEdit()
        self.op3_t1.setAlignment(Qt.AlignCenter)
        self.op3_t1.setText("40")
        title_op3_t2 = QLabel('±')
        title_op3_t2.setAlignment(Qt.AlignCenter)
        self.op3_t2 = QLineEdit()
        self.op3_t2.setAlignment(Qt.AlignCenter)
        self.op3_t2.setText("20")

        hbox_op3_t.addWidget(title_op3_t1)
        hbox_op3_t.addWidget(self.op3_t1)
        hbox_op3_t.addWidget(title_op3_t2)
        hbox_op3_t.addWidget(self.op3_t2)

        vbox.addLayout(hbox_op3_t)

        ####################################
        title_comp = QLabel('<b>Компьютеры</b>')
        title_comp.setAlignment(Qt.AlignCenter)

        vbox.addWidget(title_comp)

        #########################
        hbox_comp1_t = QHBoxLayout()

        title_comp1_t = QLabel('Первый компьютер: ')
        title_comp1_t.setAlignment(Qt.AlignCenter)
        title_comp1_t.setFixedWidth(180)
        self.comp1_t = QLineEdit()
        self.comp1_t.setAlignment(Qt.AlignCenter)
        self.comp1_t.setText("15")

        hbox_comp1_t.addWidget(title_comp1_t)
        hbox_comp1_t.addWidget(self.comp1_t)

        vbox.addLayout(hbox_comp1_t)

        #########################
        hbox_comp2_t = QHBoxLayout()

        title_comp2_t = QLabel('Второй компьютер: ')
        title_comp2_t.setAlignment(Qt.AlignCenter)
        title_comp2_t.setFixedWidth(180)
        self.comp2_t = QLineEdit()
        self.comp2_t.setAlignment(Qt.AlignCenter)
        self.comp2_t.setText("30")

        hbox_comp2_t.addWidget(title_comp2_t)
        hbox_comp2_t.addWidget(self.comp2_t)

        vbox.addLayout(hbox_comp2_t)

        button = QPushButton('Промоделировать')
        button.clicked.connect(self.modeling)

        ####################################
        title_comp = QLabel('<b>Результат</b>')
        title_comp.setAlignment(Qt.AlignCenter)

        vbox.addWidget(title_comp)

        #########################
        hbox_res = QHBoxLayout()
        vbox_res1 = QVBoxLayout()

        title_res1 = QLabel('Обслуженные клиенты')
        title_res1.setAlignment(Qt.AlignCenter)
        title_res1.setFixedWidth(220)
        self.res1 = QLineEdit()
        self.res1.setAlignment(Qt.AlignCenter)

        vbox_res1.addWidget(title_res1)
        vbox_res1.addWidget(self.res1)

        vbox_res2 = QVBoxLayout()

        title_res2 = QLabel('Отказы')
        title_res2.setAlignment(Qt.AlignCenter)
        title_res2.setFixedWidth(220)
        self.res2 = QLineEdit()
        self.res2.setAlignment(Qt.AlignCenter)

        vbox_res2.addWidget(title_res2)
        vbox_res2.addWidget(self.res2)

        vbox_res3 = QVBoxLayout()

        title_res3 = QLabel('Вероятность отказа')
        title_res3.setAlignment(Qt.AlignCenter)
        title_res3.setFixedWidth(220)
        self.res3 = QLineEdit()
        self.res3.setAlignment(Qt.AlignCenter)

        vbox_res3.addWidget(title_res3)
        vbox_res3.addWidget(self.res3)

        hbox_res.addLayout(vbox_res1)
        hbox_res.addLayout(vbox_res2)
        hbox_res.addLayout(vbox_res3)

        vbox.addLayout(hbox_res)

        ######################################
        button = QPushButton('Промоделировать')
        button.clicked.connect(self.modeling)

        vbox.addWidget(button)

        self.setLayout(vbox)

    def modeling(self):
        client_n = int(self.client_n.text())
        client_t1 = int(self.client_t1.text())
        client_t2 = int(self.client_t2.text())

        op1_t1 = int(self.op1_t1.text())
        op1_t2 = int(self.op1_t2.text())

        op2_t1 = int(self.op2_t1.text())
        op2_t2 = int(self.op2_t2.text())

        op3_t1 = int(self.op3_t1.text())
        op3_t2 = int(self.op3_t2.text())

        comp1_t = int(self.comp1_t.text())
        comp2_t = int(self.comp2_t.text())

        generator = Generator(EvenDistribution(client_t1 - client_t2, client_t1 + client_t2), client_n)

        operators = [Processor(EvenDistribution(op1_t1 - op1_t2, op1_t1 + op1_t2), maxQueue=1),
                     Processor(EvenDistribution(op2_t1 - op2_t2, op2_t1 + op2_t2), maxQueue=1),
                     Processor(EvenDistribution(op3_t1 - op3_t2, op3_t1 + op3_t2), maxQueue=1)]

        computers = [Processor(EvenDistribution(comp1_t, comp1_t), maxQueue=1),
                     Processor(EvenDistribution(comp2_t, comp2_t), maxQueue=1)]

        model = EventModel(generator, operators, computers)
        result = model.run()

        self.res1.setText(str(result[0] - 1))
        self.res2.setText(str(result[1]))
        self.res3.setText(str(round(result[2], 2)))



if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())
