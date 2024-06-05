import sys
import numpy as np
from scipy.integrate import odeint
from PyQt5.QtWidgets import \
    QApplication, QWidget, QHBoxLayout, QVBoxLayout, QSpinBox, QLabel, QTableWidget, QTableWidgetItem, QPushButton, QMessageBox
from PyQt5.QtCore import Qt

from style import Styles

def getP(transition_matrix):
    eigenvalues, eigenvectors = np.linalg.eig(transition_matrix.T)
    stationary_index = np.argmin(np.abs(eigenvalues - 1))
    stationary_vector = np.real(eigenvectors[:, stationary_index])
    stationary_vector /= np.sum(stationary_vector)
    return stationary_vector

class App(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Лабораторная работа №2')
        self.setFixedSize(1050, 630)
        self.setStyleSheet(Styles)

        self.initUI()

    def initUI(self):
        self.time = 0
        self.matrix_size = 0
        self.matrix = []

        self.matrix_label = QLabel("Матрица состояний:")

        self.matrix_spinbox = QSpinBox()
        self.matrix_spinbox.setRange(0, 10)
        self.matrix_spinbox.valueChanged.connect(self.update_tables)

        self.time_label = QLabel("Время работы системы:")

        self.time_spinbox = QSpinBox()
        self.time_spinbox.setRange(0, 100)

        self.matrix_table = QTableWidget(self.matrix_size, self.matrix_size)
        self.matrix_table.setFixedHeight(330)

        self.button = QPushButton("Рассчитать")
        self.button.clicked.connect(self.calculate)

        self.result_label = QLabel("Результат:")

        self.result_table = QTableWidget(self.matrix_size, self.matrix_size)
        self.result_table.setRowCount(2)
        self.result_table.setVerticalHeaderItem(0,
                                                QTableWidgetItem('P  '))
        self.result_table.setVerticalHeaderItem(1,
                                                QTableWidgetItem('t  '))

        self.result_table.setFixedHeight(200)

        vbox = QVBoxLayout()
        hbox = QHBoxLayout()
        hbox.addWidget(self.matrix_label)
        hbox.addWidget(self.matrix_spinbox)
        hbox.addWidget(self.button)
        ##hbox.addWidget(self.time_label)
        ##hbox.addWidget(self.time_spinbox)
        vbox.addLayout(hbox)
        vbox.addWidget(self.matrix_table)
        vbox.addWidget(self.matrix_table)
        vbox.addWidget(self.result_label)
        vbox.addWidget(self.result_table)

        self.setLayout(vbox)

    def update_tables(self):
        self.matrix_size = self.matrix_spinbox.value()
        self.matrix_table.setRowCount(self.matrix_size)
        self.matrix_table.setColumnCount(self.matrix_size)

        self.result_table.setColumnCount(self.matrix_size)

        self.populate_table()

    def populate_table(self):
        for row in range(self.matrix_size):
            for col in range(self.matrix_size):
                item = QTableWidgetItem()
                item.setTextAlignment(Qt.AlignCenter)
                self.matrix_table.setItem(row, col, item)

        for row in range(2):
            for col in range(self.matrix_size):
                item = QTableWidgetItem()
                item.setTextAlignment(Qt.AlignCenter)
                self.matrix_table.setItem(row, col, item)

    def read_matrix(self):
        matrix = []
        for row in range(self.matrix_size):
            matrix_row = []
            for col in range(self.matrix_size):
                item = self.matrix_table.item(row, col)
                if item is not None:
                    value = item.text()
                    try:
                        value = float(value)
                        matrix_row.append(value)
                    except ValueError:
                        error_message = f"В ячейке ({row + 1}, {col + 1}) не число"
                        QMessageBox.critical(self, "Ошибка", error_message, QMessageBox.Ok)
                    if value < 0:
                        error_message = f"В ячейке ({row + 1}, {col + 1}) отрицательное число"
                        QMessageBox.critical(self, "Ошибка", error_message, QMessageBox.Ok)
            matrix.append(matrix_row)
        return matrix

    def calculate(self):
       self.matrix = self.read_matrix()

       p = self.getP()
       for col in range(self.matrix_size):
           self.result_table.setItem(0, col, QTableWidgetItem(str(round(p[col], 2))))

       time = max(self.getT(p))

       for col in range(self.matrix_size):
           self.result_table.setItem(1, col, QTableWidgetItem(str(round(p[col] * time, 2))))

    def getP(self):
        factors = self.get_factors()
        factors[-1] = [1] * self.matrix_size

        free_numbers = [0] * self.matrix_size
        free_numbers[-1] = 1

        return np.linalg.solve(factors, free_numbers)

    def getT(self, limit_probabilities):
        time = np.arange(0, 20, 0.01)

        start_probabilities = [0] * self.matrix_size
        start_probabilities[0] = 1

        factors = self.get_factors()

        integrated_probabilities = np.transpose(odeint(self.get_derivatives,
                                                       start_probabilities,
                                                       time, args=(factors,)))

        stabilization_time = []

        for state in range(self.matrix_size):
            probabilities = integrated_probabilities[state]

            for i, probability in enumerate(probabilities):
                if abs(limit_probabilities[state] - probability) < 1e-4:
                    stabilization_time.append(time[i])
                    break

                if i == len(probabilities) - 1:
                    stabilization_time.append(0)

        return stabilization_time

    def get_factors(self):
        factors = []

        for state in range(self.matrix_size):
            factors.append([0] * self.matrix_size)

            for i in range(self.matrix_size):
                if i != state:
                    factors[state][i] = self.matrix[i][state]
                    factors[state][state] += self.matrix[state][i]
            factors[state][state] *= -1

        return factors

    def get_derivatives(self, probabilities, time, factors):
        derivatives = [0] * self.matrix_size

        for state in range(self.matrix_size):
            for i, probability in enumerate(probabilities):
                derivatives[state] += factors[state][i] * probability

        return derivatives


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    ex.show()
    sys.exit(app.exec_())
