from Training import training
from Demonstration import demonstration
from Testing import testing
from utils import exists, read_image

import sys
from PyQt5.QtWidgets import \
    QApplication, QMainWindow, QLabel, QFrame, QRadioButton, QButtonGroup, QSpinBox, \
    QPushButton, QMessageBox, QLineEdit, QTableWidget, QTableWidgetItem
from PyQt5.QtCore import Qt


color1 = "#ADCEF3"
color2 = "#001C3B"
color3 = "#005EC6"

class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Многокадровый SRCNN")
        self.setStyleSheet(f"background-color: {color1}; font-size: 13pt;")
        self.setGeometry(100, 50, 460, 790)

        self.init_ui()

    def init_ui(self):
        train_frame = QFrame(self)
        train_frame.setGeometry(30, 30, 400, 200)
        train_frame.setStyleSheet(f"border: 1px solid {color2};")

        label = QLabel("Обучение", self)
        label.setGeometry(40, 40, 200, 30)
        label.setStyleSheet("font-weight: bold;")

        label = QLabel("Architecture:", self)
        label.setGeometry(40, 80, 200, 30)

        self.radioButton1_1 = QRadioButton("1", self)
        self.radioButton1_1.setGeometry(180, 82, 100, 30)
        self.radioButton1_1.setChecked(True)
        self.radioButton1_2 = QRadioButton("3", self)
        self.radioButton1_2.setGeometry(220, 82, 100, 30)
        self.radioButton1_3 = QRadioButton("5", self)
        self.radioButton1_3.setGeometry(260, 82, 100, 30)

        self.button_group1 = QButtonGroup()
        self.button_group1.addButton(self.radioButton1_1)
        self.button_group1.addButton(self.radioButton1_2)
        self.button_group1.addButton(self.radioButton1_3)

        label = QLabel("Steps:", self)
        label.setGeometry(40, 110, 200, 30)

        self.spinbox1 = QSpinBox(self)
        self.spinbox1.setStyleSheet(f"background-color: white; color: {color2};")
        self.spinbox1.setAlignment(Qt.AlignCenter)
        self.spinbox1.setMinimum(1)
        self.spinbox1.setMaximum(500000)
        self.spinbox1.setValue(100000)
        self.spinbox1.setGeometry(180, 115, 100, 23)

        label = QLabel("Batch_size:", self)
        label.setGeometry(40, 140, 200, 30)

        self.spinbox2 = QSpinBox(self)
        self.spinbox2.setStyleSheet(f"background-color: white; color: {color2};")
        self.spinbox2.setAlignment(Qt.AlignCenter)
        self.spinbox2.setMinimum(1)
        self.spinbox2.setMaximum(512)
        self.spinbox2.setValue(128)
        self.spinbox2.setGeometry(180, 145, 100, 23)

        label = QLabel("Save_every:", self)
        label.setGeometry(40, 170, 200, 30)

        self.spinbox3 = QSpinBox(self)
        self.spinbox3.setStyleSheet(f"background-color: white; color: {color2};")
        self.spinbox3.setAlignment(Qt.AlignCenter)
        self.spinbox3.setMinimum(1)
        self.spinbox3.setMaximum(10000)
        self.spinbox3.setValue(1000)
        self.spinbox3.setGeometry(180, 175, 100, 23)

        button1 = QPushButton("Запуск", self)
        button1.setStyleSheet(f"background-color: {color3}; color: white;")
        button1.setGeometry(305, 190, 100, 30)
        button1.clicked.connect(self.train_button)



        demo_frame = QFrame(self)
        demo_frame.setGeometry(30, 240, 400, 200)
        demo_frame.setStyleSheet(f"border: 1px solid {color2};")

        label = QLabel("Демонстрация", self)
        label.setGeometry(40, 250, 200, 30)
        label.setStyleSheet("font-weight: bold;")

        label = QLabel("Architecture:", self)
        label.setGeometry(40, 290, 200, 30)

        self.radioButton2_1 = QRadioButton("1", self)
        self.radioButton2_1.setGeometry(180, 292, 100, 30)
        self.radioButton2_1.setChecked(True)
        self.radioButton2_2 = QRadioButton("3", self)
        self.radioButton2_2.setGeometry(220, 292, 100, 30)
        self.radioButton2_3 = QRadioButton("5", self)
        self.radioButton2_3.setGeometry(260, 292, 100, 30)

        self.button_group2 = QButtonGroup()
        self.button_group2.addButton(self.radioButton2_1)
        self.button_group2.addButton(self.radioButton2_2)
        self.button_group2.addButton(self.radioButton2_3)

        label = QLabel("Image_path1:", self)
        label.setGeometry(40, 320, 200, 30)

        self.line1 = QLineEdit(self)
        self.line1.setStyleSheet(f"background-color: white; color: {color2}; font-size: 12pt;")
        self.line1.setText("img/animal1.png")
        self.line1.setGeometry(180, 322, 160, 25)

        label = QLabel("Image_path2:", self)
        label.setGeometry(40, 350, 200, 30)

        self.line2 = QLineEdit(self)
        self.line2.setStyleSheet(f"background-color: white; color: {color2}; font-size: 12pt;")
        self.line2.setText("img/animal2.png")
        self.line2.setGeometry(180, 352, 160, 25)

        label = QLabel("Scale:", self)
        label.setGeometry(40, 380, 200, 30)

        self.radioButton3_1 = QRadioButton("2", self)
        self.radioButton3_1.setGeometry(180, 382, 100, 30)
        self.radioButton3_1.setChecked(True)
        self.radioButton3_2 = QRadioButton("3", self)
        self.radioButton3_2.setGeometry(220, 382, 100, 30)
        self.radioButton3_3 = QRadioButton("4", self)
        self.radioButton3_3.setGeometry(260, 382, 100, 30)

        self.button_group3 = QButtonGroup()
        self.button_group3.addButton(self.radioButton3_1)
        self.button_group3.addButton(self.radioButton3_2)
        self.button_group3.addButton(self.radioButton3_3)

        button2 = QPushButton("Запуск", self)
        button2.setStyleSheet(f"background-color: {color3}; color: white;")
        button2.setGeometry(305, 400, 100, 30)
        button2.clicked.connect(self.demo_button)



        test_frame = QFrame(self)
        test_frame.setGeometry(30, 450, 400, 310)
        test_frame.setStyleSheet(f"border: 1px solid {color2};")

        label = QLabel("Тестирование", self)
        label.setGeometry(40, 460, 200, 30)
        label.setStyleSheet("font-weight: bold;")

        label = QLabel("Architecture:", self)
        label.setGeometry(40, 500, 200, 30)

        self.radioButton4_1 = QRadioButton("1", self)
        self.radioButton4_1.setGeometry(180, 502, 100, 30)
        self.radioButton4_1.setChecked(True)
        self.radioButton4_2 = QRadioButton("3", self)
        self.radioButton4_2.setGeometry(220, 502, 100, 30)
        self.radioButton4_3 = QRadioButton("5", self)
        self.radioButton4_3.setGeometry(260, 502, 100, 30)

        self.button_group4 = QButtonGroup()
        self.button_group4.addButton(self.radioButton4_1)
        self.button_group4.addButton(self.radioButton4_2)
        self.button_group4.addButton(self.radioButton4_3)

        label = QLabel("Scale:", self)
        label.setGeometry(40, 530, 200, 30)

        self.radioButton5_1 = QRadioButton("2", self)
        self.radioButton5_1.setGeometry(180, 532, 100, 30)
        self.radioButton5_1.setChecked(True)
        self.radioButton5_2 = QRadioButton("3", self)
        self.radioButton5_2.setGeometry(220, 532, 100, 30)
        self.radioButton5_3 = QRadioButton("4", self)
        self.radioButton5_3.setGeometry(260, 532, 100, 30)

        self.button_group5 = QButtonGroup()
        self.button_group5.addButton(self.radioButton5_1)
        self.button_group5.addButton(self.radioButton5_2)
        self.button_group5.addButton(self.radioButton5_3)

        button3 = QPushButton("Запуск", self)
        button3.setStyleSheet(f"background-color: {color3}; color: white;")
        button3.setGeometry(305, 720, 100, 30)
        button3.clicked.connect(self.test_button)

        self.table = QTableWidget(self)
        self.table.setStyleSheet("font-size: 10pt;")
        self.table.setGeometry(0, 0, 0, 0)


    def train_button(self):
        if self.radioButton1_1.isChecked():
            architecture = self.radioButton1_1.text()
        elif self.radioButton1_2.isChecked():
            architecture = self.radioButton1_2.text()
        elif self.radioButton1_3.isChecked():
            architecture = self.radioButton1_3.text()
        architecture = int(architecture)

        steps = self.spinbox1.value()
        batch_size = self.spinbox2.value()
        save_every = self.spinbox3.value()
        training(architecture, steps, batch_size, save_every)

        QMessageBox.information(self, "Обучение", "Обучение завершено, модель сохранена по стандартному пути")

    def demo_button(self):
        if self.radioButton2_1.isChecked():
            architecture = self.radioButton2_1.text()
        elif self.radioButton2_2.isChecked():
            architecture = self.radioButton2_2.text()
        elif self.radioButton2_3.isChecked():
            architecture = self.radioButton2_3.text()
        architecture = int(architecture)

        image_path1 = self.line1.text()
        image_path2 = self.line2.text()

        if self.radioButton3_1.isChecked():
            scale = self.radioButton3_1.text()
        elif self.radioButton3_2.isChecked():
            scale = self.radioButton3_2.text()
        elif self.radioButton3_3.isChecked():
            scale = self.radioButton3_3.text()
        scale = int(scale)

        if not exists(image_path1):
            QMessageBox.warning(self, "Демонстрация", "Image_path1 не существует")
            return
        if not exists(image_path2):
            QMessageBox.warning(self, "Демонстрация", "Image_path2 не существует")
            return

        if not (image_path1.lower().endswith('.png') or
                image_path1.lower().endswith('.jpg') or
                image_path1.lower().endswith('.jpeg')):
            QMessageBox.warning(self, "Демонстрация", "Формат изображения 1 не поддерживается")
            return
        if not (image_path2.lower().endswith('.png') or
                image_path2.lower().endswith('.jpg') or
                image_path2.lower().endswith('.jpeg')):
            QMessageBox.warning(self, "Демонстрация", "Формат изображения 2 не поддерживается")
            return

        _, height1, width1 = read_image(image_path1).shape
        if height1 > 1024 or width1 > 1024:
            QMessageBox.warning(self, "Демонстрация", "Изображение 1 не может быть обработано")
            return

        _, height2, width2 = read_image(image_path2).shape
        if height2 > 1024 or width2 > 1024:
            QMessageBox.warning(self, "Демонстрация", "Изображение 2 не может быть обработано")
            return

        if height1 != height2 or width1 != width2:
            QMessageBox.warning(self, "Демонстрация", "Входные изображения имеют разное разрешение")
            return

        demonstration(architecture, image_path1, image_path2, scale)

    def test_button(self):
        if self.radioButton4_1.isChecked():
            architecture = self.radioButton4_1.text()
        elif self.radioButton4_2.isChecked():
            architecture = self.radioButton4_2.text()
        elif self.radioButton4_3.isChecked():
            architecture = self.radioButton4_3.text()
        architecture = int(architecture)

        if self.radioButton5_1.isChecked():
            scale = self.radioButton5_1.text()
        elif self.radioButton5_2.isChecked():
            scale = self.radioButton5_2.text()
        elif self.radioButton5_3.isChecked():
            scale = self.radioButton5_3.text()
        scale = int(scale)

        data = testing(architecture, scale)

        self.table.setGeometry(40, 570, 322, 146)

        self.table.setRowCount(len(data))
        self.table.setColumnCount(len(data[0]))

        for j in range(len(data[0])):
            self.table.setColumnWidth(j, 75)

        self.table.setHorizontalHeaderLabels(["Метод", "MSE", "PSNR", "SSIM"])

        for i in range(len(data)):
            for j in range(len(data[0])):
                self.table.setItem(i, j, QTableWidgetItem(str(data[i][j])))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())