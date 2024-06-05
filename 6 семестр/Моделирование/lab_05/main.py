#! /bin/python
import sys
from PyQt5 import QtWidgets

from src.ui.mainwindow import MainWindow

def main() -> int:
    qapp = QtWidgets.QApplication(sys.argv)
    window = MainWindow();
    window.show()

    return qapp.exec_()


if __name__ == "__main__":
    exit(main())

