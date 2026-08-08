# R.I.S.K. Simulator

**R.I.S.K. Simulator** is a hybrid C++/Python epidemic outbreak simulation application that models disease transmission across regions based on geographical properties, administrative borders, and custom environmental modifiers. The core simulation mechanics are compiled in high-performance C++ and bound to a Python PyQt6 graphical interface using Pybind11.

---

## Key Features

* **C++/Python Hybrid Core**: Native C++ simulation performance exposed directly to Python via Pybind11.
* **Interactive Desktop GUI**: Built using PyQt6, featuring map visualization, bounding-box selection, and live stats viewing.
* **Dynamic Epidemic Transmission**: Neighbor-based geographical spread across county and regional borders.
* **Environmental Modifiers**: Outbreak behavior scales based on region attributes (capitals, airports, ports, rivers, dams, mines, mountainous terrain).
* **Data-Driven Configuration**: Geographic maps, region data, and border connections are parsed dynamically from CSV and JSON inputs.

---

## System Requirements & Dependencies

### C++ Core Requirements
* **C++ Compiler**: Support for C++17/C++23 standard
* **CMake**: Version 3.10 or higher
* **`fmt` Library**: Formatting library for string generation
* **Pybind11**: C++/Python binding generator

### Python GUI Requirements
* **Python**: Python 3.x
* **PyQt6**: Desktop application framework

---

## Build & Execution

chmod + x cmake_script.sh
./cmake_script.sh