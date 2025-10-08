import sys
import os
from PyQt6.QtGui import QPixmap
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QComboBox, QPushButton, QLabel, QMessageBox
from PyQt6.QtCore import Qt, QPoint, pyqtSignal
sys.path.append(os.path.join(os.path.dirname(__file__), "../build"))
import RISK_pycore
import json

class RISKSimGUI(QWidget):
    def __init__(self):
        super().__init__()
        self.sim = RISK_pycore.Simulation()
        self.sim.read_countries("../core/data/countries.csv")
        self.setWindowTitle("R.I.S.K. Simulator")

        # Choosing and Loading the Country
        self.current_country = None
        self.country_dropdown = QComboBox()
        self.country_dropdown.addItems(["EMPTY", "Romania", "USA", "Austria"])
        self.country_dropdown.currentTextChanged.connect(self.load_country_and_regions)

        # Initializing the Map
        self.map_label = ClickableMap()
        self.map_label.clicked.connect(self.load_starting_region)

        # Initializing the Coords
        self.region_coords = {}
        self.region_dropdown = None
        self.starting_region = False
        # Next Day Button
        self.next_day_btn = QPushButton("Next Day")
        #self.next_day_btn.clicked.connect(self.next_day)

        #self.next_month_btn = QPushButton("Next Month")
        #self.next_year_btn = QPushButton("Next Year")

        # Country, Starting Region and Stat Region Info Panel
        self.country_info_label = QLabel("Select a country to start playing")
        self.country_info_label.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.starting_region_info_label = QLabel("Select a region to start playing")
        self.starting_region_info_label.setAlignment(Qt.AlignmentFlag.AlignLeft)
        self.stat_region_info_label = QLabel("Select a region to see its stats")
        self.stat_region_info_label.setAlignment(Qt.AlignmentFlag.AlignLeft)
        # Layout
        top_layout = QHBoxLayout()
        top_layout.addWidget(self.country_dropdown)
        top_layout.addWidget(self.next_day_btn)
        #top_layout.addWidget(self.next_month_btn)
        #top_layout.addWidget(self.next_year_btn)
        main_layout = QVBoxLayout()
        main_layout.addLayout(top_layout)
        main_layout.addWidget(self.map_label)
        main_layout.addWidget(self.country_info_label)
        main_layout.addWidget(self.starting_region_info_label)
        main_layout.addWidget(self.stat_region_info_label)
        self.setLayout(main_layout)
        self.resize(700, 600)

    def load_country_and_regions(self, country):
        if country == "Romania":
            reply = QMessageBox.question(
            self,
            "Proceed?",
            "You chose Romania. Are you ready to proceed?",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
            )

            # Reset dropdown
            if reply == QMessageBox.StandardButton.No:
                self.country_dropdown.setCurrentText("EMPTY")
                return

            # Disable selection of country after confirming
            self.current_country = country
            self.sim.choose_country(country)
            self.country_dropdown.setEnabled(False)

            # Load the map
            pixmap = QPixmap("../gui/assets/Romania_map.png")
            self.map_label.setPixmap(pixmap)
            self.country_info_label.setText("Romania succesfully loaded! Simulation ready.")

            # Load the counties
            self.sim.read_Romania_counties("../core/data/RO_counties.csv", "../core/data/RO_borders.csv")

            # Load the json with the coords
            path_to_coords = f"../gui/assets/{self.current_country}_coords.json"
            with open(path_to_coords, "r") as f:
                self.region_coords = json.load(f)
        else:
            self.map_label.setPixmap(QPixmap())
            self.country_info_label.setText("No country selected yet")


    def load_starting_region(self, pos):
        x, y = pos.x(), pos.y()
        selected_region = None
        for name, (x1, y1, x2, y2) in self.region_coords.items():
            if x1 <= x <= x2 and y1 <= y <= y2:
                selected_region = name
                break

        if selected_region:
            if self.starting_region == False:
                reply = QMessageBox.question(
                self,
                "Confirm Region",
                f"Do you want to start in {selected_region}?",
                QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,
                )
            else:
                reply = QMessageBox.question(
                self,
                "Confirm Region",
                f"Do you want to see the stats of {selected_region}?",
                QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,
                )
        else:
            QMessageBox.information(self, "No region", "You clicked outside of known regions.")
            return

        if reply == QMessageBox.StandardButton.Yes and self.starting_region == False:
            self.sim.choose_county(selected_region)
            self.starting_region_info_label.setText(f"Starting region: {selected_region}")
            self.starting_region = True
        elif reply == QMessageBox.StandardButton.Yes and self.starting_region == True:
            self.stat_region_info_label.setText(f"You clicked on {selected_region}. Showing stats...")
            return


class ClickableMap(QLabel):
    clicked = pyqtSignal(QPoint)
    def mousePressEvent(self, event):
        if event.button():
            self.clicked.emit(event.pos())


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = RISKSimGUI()
    window.show()
    sys.exit(app.exec())