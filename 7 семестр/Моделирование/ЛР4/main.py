import sys
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QLineEdit, QPushButton
from style import Styles

from qsystem import QSystem


class MyWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Лабораторная работа №4')
        self.setFixedSize(700, 500)
        self.setStyleSheet(Styles)

        self.initUI()

    def initUI(self):
        vbox = QVBoxLayout(self)

        #Генератор
        title_1 = QLabel('<b>Генератор</b>')
        title_1.setAlignment(Qt.AlignCenter)

        vbox_1_1 = QVBoxLayout()
        vbox_1_2 = QVBoxLayout()
        hbox_1 = QHBoxLayout()

        title_1_a = QLabel('a')
        title_1_a.setAlignment(Qt.AlignCenter)
        self.a_form = QLineEdit()
        self.a_form.setAlignment(Qt.AlignCenter)

        title_1_b = QLabel('b')
        title_1_b.setAlignment(Qt.AlignCenter)
        self.b_form = QLineEdit()
        self.b_form.setAlignment(Qt.AlignCenter)

        vbox_1_1.addWidget(title_1_a)
        vbox_1_1.addWidget(self.a_form)
        hbox_1.addLayout(vbox_1_1)

        vbox_1_2.addWidget(title_1_b)
        vbox_1_2.addWidget(self.b_form)
        hbox_1.addLayout(vbox_1_2)

        vbox.addWidget(title_1)
        vbox.addLayout(hbox_1)

        # Обслуживающий аппарат
        title_2 = QLabel('<b>Обслуживающий аппарат</b>')
        title_2.setAlignment(Qt.AlignCenter)

        vbox_2_1 = QVBoxLayout()
        vbox_2_2 = QVBoxLayout()
        hbox_2 = QHBoxLayout()

        title_2_mu = QLabel('μ')
        title_2_mu.setAlignment(Qt.AlignCenter)
        self.mu_form = QLineEdit()
        self.mu_form.setAlignment(Qt.AlignCenter)

        title_2_sigma = QLabel('σ')
        title_2_sigma.setAlignment(Qt.AlignCenter)
        self.sigma_form = QLineEdit()
        self.sigma_form.setAlignment(Qt.AlignCenter)

        vbox_2_1.addWidget(title_2_mu)
        vbox_2_1.addWidget(self.mu_form)
        hbox_2.addLayout(vbox_2_1)

        vbox_2_2.addWidget(title_2_sigma)
        vbox_2_2.addWidget(self.sigma_form)
        hbox_2.addLayout(vbox_2_2)

        vbox.addWidget(title_2)
        vbox.addLayout(hbox_2)

        # Параметры заявок
        title_3 = QLabel('<b>Параметры заявок</b>')
        title_3.setAlignment(Qt.AlignCenter)

        hbox_3_1 = QHBoxLayout()
        hbox_3_2 = QHBoxLayout()
        hbox_3_3 = QHBoxLayout()

        title_3_n = QLabel('Количество')
        title_3_n.setAlignment(Qt.AlignCenter)
        self.n_form = QLineEdit()
        self.n_form.setAlignment(Qt.AlignCenter)
        self.n_form.setFixedWidth(500)

        title_3_p = QLabel('Вероятность возврата')
        title_3_p.setAlignment(Qt.AlignCenter)
        self.p_form = QLineEdit()
        self.p_form.setAlignment(Qt.AlignCenter)
        self.p_form.setFixedWidth(500)

        title_3_t = QLabel('Временной шаг')
        title_3_t.setAlignment(Qt.AlignCenter)
        self.t_form = QLineEdit()
        self.t_form.setAlignment(Qt.AlignCenter)
        self.t_form.setFixedWidth(500)

        hbox_3_1.addWidget(title_3_n)
        hbox_3_1.addWidget(self.n_form)

        hbox_3_2.addWidget(title_3_p)
        hbox_3_2.addWidget(self.p_form)

        hbox_3_3.addWidget(title_3_t)
        hbox_3_3.addWidget(self.t_form)

        vbox.addWidget(title_3)
        vbox.addLayout(hbox_3_1)
        vbox.addLayout(hbox_3_2)
        vbox.addLayout(hbox_3_3)

        # Результат
        title_4 = QLabel('<b>Результат</b>')
        title_4.setAlignment(Qt.AlignCenter)

        title_4_1 = QLabel('Максимальна длина очереди')
        title_4_1.setAlignment(Qt.AlignCenter)

        vbox_4_1 = QVBoxLayout()
        vbox_4_2 = QVBoxLayout()
        hbox_4 = QHBoxLayout()

        title_4_step = QLabel('Пошаговый принцип')
        title_4_step.setAlignment(Qt.AlignCenter)
        self.step_form = QLineEdit()
        self.step_form.setAlignment(Qt.AlignCenter)

        title_4_event = QLabel('Событийный принцип')
        title_4_event.setAlignment(Qt.AlignCenter)
        self.event_form = QLineEdit()
        self.event_form.setAlignment(Qt.AlignCenter)

        vbox_4_1.addWidget(title_4_step)
        vbox_4_1.addWidget(self.step_form)
        hbox_4.addLayout(vbox_4_1)

        vbox_4_2.addWidget(title_4_event)
        vbox_4_2.addWidget(self.event_form)
        hbox_4.addLayout(vbox_4_2)

        vbox.addWidget(title_4)
        vbox.addWidget(title_4_1)
        vbox.addLayout(hbox_4)

        button = QPushButton('Промоделировать')
        button.clicked.connect(self.modeling)

        vbox.addWidget(button)

        self.setLayout(vbox)

    def modeling(self):
        a = float(self.a_form.text())
        b = float(self.b_form.text())
        mu = float(self.mu_form.text())
        sigma = float(self.sigma_form.text())

        n = int(self.n_form.text())
        p = float(self.p_form.text())
        t = float(self.t_form.text())

        self.qsystem = QSystem(a, b, mu, sigma, n, p, t)

        step_res = self.qsystem.step_principle()
        event_res = self.qsystem.event_principle()

        self.step_form.setText(str(step_res))
        self.event_form.setText(str(event_res))


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())
