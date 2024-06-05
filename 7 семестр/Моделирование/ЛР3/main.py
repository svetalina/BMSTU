import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QHBoxLayout, QVBoxLayout, QTableWidget, \
    QPushButton, QWidget, QLineEdit, QLabel, QTableWidgetItem, QSpinBox, QGroupBox

from style  import  Styles

class TableExample(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Лабораторная работа №3')
        self.setFixedSize(1050, 690)
        self.setStyleSheet(Styles)

        self.initUI()

    def initUI(self):
        main_layout = QVBoxLayout()

        string_1 = "Начало диапозона:"
        string_2 = "Конец диапозона:"
        string_3 = "Ожидаемое μ:"
        string_4 = "Получившеяся μ:"

        self.table1 = QTableWidget()
        self.table1.setColumnCount(1)
        self.table1.setHorizontalHeaderLabels(['Табличный метод'])
        self.table1.setColumnWidth(0, 340)
        self.table1.setMaximumWidth(340)
        self.table1.setMaximumHeight(500)

        self.fields1 = [QLineEdit() for _ in range(4)]
        for field in self.fields1:
            field.setFixedWidth(150)

        label_3 = QLabel(string_3)
        label_4 = QLabel(string_4)

        label_fields3_layout = QHBoxLayout()
        label_fields3_layout.addWidget(label_3)
        label_fields3_layout.addWidget(self.fields1[2])

        label_fields4_layout = QHBoxLayout()
        label_fields4_layout.addWidget(label_4)
        label_fields4_layout.addWidget(self.fields1[3])

        table1_layout = QVBoxLayout()
        table1_layout.addWidget(self.table1)
        table1_layout.addLayout(label_fields3_layout)
        table1_layout.addLayout(label_fields4_layout)


        self.table2 = QTableWidget()
        self.table2.setColumnCount(1)
        self.table2.setHorizontalHeaderLabels(['Алгоритмический метод'])
        self.table2.setColumnWidth(0, 340)
        self.table2.setMaximumWidth(340)
        self.table2.setMaximumHeight(500)

        self.fields2 = [QLineEdit() for _ in range(4)]
        for field in self.fields2:
            field.setFixedWidth(150)

        label_3 = QLabel(string_3)
        label_4 = QLabel(string_4)

        label_fields3_layout = QHBoxLayout()
        label_fields3_layout.addWidget(label_3)
        label_fields3_layout.addWidget(self.fields2[2])

        label_fields4_layout = QHBoxLayout()
        label_fields4_layout.addWidget(label_4)
        label_fields4_layout.addWidget(self.fields2[3])

        table2_layout = QVBoxLayout()
        table2_layout.addWidget(self.table2)
        table2_layout.addLayout(label_fields3_layout)
        table2_layout.addLayout(label_fields4_layout)


        self.table3 = QTableWidget()
        self.table3.setColumnCount(1)
        self.table3.setRowCount(10)
        self.table3.setHorizontalHeaderLabels(['Ручной метод'])
        self.table3.setColumnWidth(0, 340)
        self.table3.setMaximumWidth(340)
        self.table3.setMaximumHeight(450)

        self.fields3 = [QLineEdit() for _ in range(4)]
        for field in self.fields3:
            field.setFixedWidth(150)

        label_1 = QLabel(string_1)
        label_2 = QLabel(string_2)
        label_3 = QLabel(string_3)
        label_4 = QLabel(string_4)

        label_fields1_layout = QHBoxLayout()
        label_fields1_layout.addWidget(label_1)
        label_fields1_layout.addWidget(self.fields3[0])

        label_fields2_layout = QHBoxLayout()
        label_fields2_layout.addWidget(label_2)
        label_fields2_layout.addWidget(self.fields3[1])

        label_fields3_layout = QHBoxLayout()
        label_fields3_layout.addWidget(label_3)
        label_fields3_layout.addWidget(self.fields3[2])

        label_fields4_layout = QHBoxLayout()
        label_fields4_layout.addWidget(label_4)
        label_fields4_layout.addWidget(self.fields3[3])

        table3_layout = QVBoxLayout()
        table3_layout.addWidget(self.table3)
        table3_layout.addLayout(label_fields1_layout)
        table3_layout.addLayout(label_fields2_layout)
        table3_layout.addLayout(label_fields3_layout)
        table3_layout.addLayout(label_fields4_layout)

        horizontal_layout = QHBoxLayout()
        horizontal_layout.addLayout(table1_layout)
        horizontal_layout.addLayout(table2_layout)
        horizontal_layout.addLayout(table3_layout)

        options_groupbox = QGroupBox()
        options_groupbox.setMaximumWidth(685)
        options_layout = QVBoxLayout()

        self.step = 1
        self.min = 0
        self.max = 9

        self.step_label = QLabel("Количество чисел:")
        self.step_spinbox = QSpinBox()
        self.step_spinbox.setRange(1, 1000)
        self.step_spinbox.valueChanged.connect(self.update_step)

        step_layout = QHBoxLayout()
        step_layout.addWidget(self.step_label)
        step_layout.addWidget(self.step_spinbox)

        self.minmax_label = QLabel("Разрядность чисел:")
        self.minmax_spinbox = QSpinBox()
        self.minmax_spinbox.setRange(1, 3)
        self.minmax_spinbox.valueChanged.connect(self.update_minmax)

        minmax_layout = QHBoxLayout()
        minmax_layout.addWidget(self.minmax_label)
        minmax_layout.addWidget(self.minmax_spinbox)

        options_layout.addLayout(step_layout)
        options_layout.addLayout(minmax_layout)

        options_groupbox.setLayout(options_layout)

        self.button1 = QPushButton('Автоматическая генерация')
        self.button1.clicked.connect(self.calculate1)

        self.button2 = QPushButton('Ручная генерация')
        self.button2.clicked.connect(self.calculate2)

        main_layout.addWidget(options_groupbox)
        main_layout.addLayout(horizontal_layout)
        main_layout.addWidget(self.button1)
        main_layout.addWidget(self.button2)

        central_widget = QWidget()
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)

        self.current = 1
        self.a = 36261
        self.c = 66037
        self.m = 312500

    def update_step(self):
        self.step = self.step_spinbox.value()

    def update_minmax(self):
        if self.minmax_spinbox.value() == 1:
            self.min = 0
            self.max = 9

        if self.minmax_spinbox.value() == 2:
            self.min = 10
            self.max = 99

        if self.minmax_spinbox.value() == 3:
            self.min = 100
            self.max = 999


    def calculate1(self):
        self.table1.setRowCount(self.step)
        self.table2.setRowCount(self.step)

        numbersFile = self.readFile()

        if self.minmax_spinbox.value() == 1:
            numbers = [int(i) % 10 for i in numbersFile]

        if self.minmax_spinbox.value() == 2:
            numbers = [int(i) % 90 + 10 for i in numbersFile]

        if self.minmax_spinbox.value() == 3:
            numbers = [int(i) % 900 + 100 for i in numbersFile]

        sum = 0
        for i in range(self.step):
            num = numbers[i]
            sum = sum + num

            self.table1.setItem(i - 1, 1, QTableWidgetItem(str(round(num))))
        self.fields1[2].setText(str(round((self.max - self.min) / 2, 2)))
        self.fields1[3].setText(str(round(sum / self.step, 2)))

        sum = 0
        for i in range(self.step):
            num = self.algRandom(self.min, self.max)
            sum = sum + num

            self.table2.setItem(i - 1, 1, QTableWidgetItem(str(round(num))))
        self.fields2[2].setText(str(round((self.max - self.min) / 2, 2)))
        self.fields2[3].setText(str(round(sum / self.step, 2)))

    def algRandom(self, minNumb, maxNumb):
        self.current = (self.a * self.current + self.c) % self.m
        return int(minNumb + self.current % (maxNumb - minNumb))

    def readFile(self):
        numbers = set()

        with open("digits.txt") as file:
            rows = file.readlines()

        for row in rows:
            numbers.update(set(row.split()[1:]))
            if len(numbers) >= self.step + 1:
                break

        numbers = list(numbers)[:self.step]

        return numbers


    def calculate2(self):
        min_alg = 999
        max_alg = 0
        if (self.fields3[0].text() != '' and self.fields3[1].text() != ''):
            min_alg = int(self.fields3[0].text())
            max_alg = int(self.fields3[1].text())

        sum = 0
        for i in range(10):
            num = int(self.table3.item(i, 0).text())
            sum = sum + num
            if min_alg > num:
                min_alg = num
            if max_alg < num:
                max_alg = num

        self.fields3[0].setText(str(min_alg))
        self.fields3[1].setText(str(max_alg))
        self.fields3[2].setText(str(round((max_alg - min_alg) / 2, 2)))
        self.fields3[3].setText(str(round(sum / 10, 2)))

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = TableExample()
    ex.show()
    sys.exit(app.exec_())
