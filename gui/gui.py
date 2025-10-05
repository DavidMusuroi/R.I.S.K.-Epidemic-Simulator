import sys
from PyQt6.QtGui import QPixmap
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QComboBox, QPushButton, QLabel
from PyQt6.QtCore import Qt

class RISKSimGUI(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("R.I.S.K. Simulator")

        # Controls
        self.country_dropdown = QComboBox()
        self.country_dropdown.addItems(["EMPTY", "Romania", "USA", "Austria"])
        self.country_dropdown.currentTextChanged.connect(self.load_country)

        self.next_day_btn = QPushButton("Next Day")
        #self.next_month_btn = QPushButton("Next Month")
        #self.next_year_btn = QPushButton("Next Year")

        # Map view
        self.map_label = QLabel()
        pixmap = QPixmap("assets/maps/romania.png")  # placeholder image
        self.map_label.setPixmap(pixmap)
        self.map_label.setAlignment(Qt.AlignmentFlag.AlignCenter)

        # Info and Stats panel
        self.info_label = QLabel("Select a region to start playing")
        self.info_label.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.region_stats = QLabel("No region selected yet.")
        self.region_stats.setAlignment(Qt.AlignmentFlag.AlignLeft)

        # Layout
        top_layout = QHBoxLayout()
        top_layout.addWidget(self.country_dropdown)
        top_layout.addWidget(self.next_day_btn)
        #top_layout.addWidget(self.next_month_btn)
        #top_layout.addWidget(self.next_year_btn)

        main_layout = QVBoxLayout()
        main_layout.addLayout(top_layout)
        main_layout.addWidget(self.map_label)
        main_layout.addWidget(self.info_label)
        main_layout.addWidget(self.region_stats)
        self.setLayout(main_layout)
        self.resize(500, 400)

    def load_country(self, country):
        if country == "Romania":
            pixmap = QPixmap("assets/Romania_map.png")
            self.map_label.setPixmap(pixmap)
            # Later: load region data from C++ backend
        else:
            self.map_label.setPixmap(QPixmap())

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = RISKSimGUI()
    window.show()
    sys.exit(app.exec())