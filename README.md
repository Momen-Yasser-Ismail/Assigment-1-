# CS213: Object-Oriented Programming (OOP) - Assignment 1 (Part 2)
**Faculty of Computers and Artificial Intelligence (FCAI), Cairo University**  
**Supervisor:** Dr. Mohammad El-Ramly  
**Date:** 12 October 2026

---

## 1. Project Overview & Scope
**Repository Link:** [Assigment-1-](https://github.com/Momen-Yasser-Ismail/Assigment-1-)

This application allows users to load, process, apply multiple filters, and save images. It supports both a command-line interface (Console Menu) and a modern Graphical User Interface (GUI).

---

## 2. Team Details & Work Breakdown
**Course:** CS213 Object-Oriented Programming

* **Adham Abdelrahman** — ID: `20250078` | Section: S(35,36) | **Filters:** Grayscale, Flip, Merge and Sepia
* **Ali Yasser** — ID: `20250407` | Section: No Group | **Filters:** Black and white, Rotate, Detect Image Edges and Televisions
* **Yehia Nabil** — ID: `20250742` | Section: S(25,26) | **Filters:** Invert, lighten_darken, Crop and Purple Effect
* **Mo'men Yasser** — ID: `20251441` | Section: S(13,14) | **Filters:** Frame, Resize, Blur and Infrared

---

## 3. Setup and Environment
**Tools & Compilers Used:**
* **Language:** C++ (Standard C++17 or C++20)
* **Compiler:** GCC / MinGW g++ v11.0 or higher / MSVC
* **GUI Framework:** Qt Framework (Qt 5.15 / Qt 6.x)

---

## 4. How to Compile and Run the Code

### A. Console Version (Command-Line Interface)
1. **Clone or Download the Repository:**
   ```bash
   git clone https://github.com/Momen-Yasser-Ismail/Assigment-1-.git
   ```

2. **Compile and run `Console.cpp`:**
   * **Command Line (g++):**
     ```bash
     g++ -o Console Console.cpp -std=c++17
     ./Console
     ```
     *(Use `Console.exe` on Windows)*
   * *Alternatively*, open the project folder in VS Code or your preferred C++ IDE and run `Console.cpp` directly.

3. **Follow the interactive menu in the console:**
   * **Option 1:** Load Image
   * **Option 2:** Apply Filters (1 to 18 filters available)
   * **Option 3:** Save Image
   * **Option 4:** Exit

---

### B. GUI Version (Graphical User Interface)
1. Launch **Qt Creator**.
2. Select **File** -> **Open File or Project...**
3. Navigate into the **`GUI`** folder and select the **`CMakeLists.txt`** file.
4. Configure the build kit (e.g., *Desktop Qt 6.x MinGW 64-bit*).
5. Build the project by pressing `Ctrl + B` (or clicking the hammer icon).
6. Run the project by pressing `Ctrl + R` (or clicking the green Play button).
7. Use the GUI window controls to load an image, select a filter, preview live effects, and save your output.

---

> **Note:** Executable (`.exe`) files and external library binaries (Qt binaries) are excluded from this repository as per assignment guidelines.
