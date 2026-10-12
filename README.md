=========================================================
CS213 - Object-Oriented Programming | Assignment 1
Image Processing Toolbox with C++ & Qt GUI
=========================================================

1. Project Overview
-------------------
This project is an advanced C++ image processing application featuring multiple filters, history management (undo/redo/reset), and a custom Qt Creator UI.

2. Team Members & Contributions
--------------------------------
- Mo'men Yasser (ID: 20251441) - Frame, Resize, Blur, and Infrared filters
- Adham Abdelrahman (ID: 20250078) - Grayscale, Flip, Merge, and Sepia filters
- Ali Yasser (ID: 20250407) - Black & White, Rotate, Detect Image Edges, and Televisions
- Yehia Nabil (ID: 20250742) - Invert, Lighten/Darken, Crop, and Purple Effect

3. Tools & Versions Used
------------------------
- Language: C++ (C++17 / C++20 standard)
- IDE / Environment: Qt Creator (v13.0 or later) / Visual Studio / MinGW GCC
- GUI Framework: Qt 6.x (or Qt 5.15+)
- Operating System: Windows 10 / 11 (tested via MSI Thin 15 and Dell Precision systems)

4. Prerequisites & Setup Instructions
-------------------------------------
To run this project on your machine, follow these steps:

Step 1: Install Qt and C++ Compiler
- Download and install Qt Online Installer (Qt 6.x recommended).
- Ensure you install the MinGW or MSVC compiler component along with Qt Creator.

Step 2: Clone or Download the Repository
- Clone the repository to your local machine:
  git clone https://github.com/Momen-Yasser-Ismail/Assigment-1-.git

Step 3: Open the Project in Qt Creator
- Launch Qt Creator.
- Click on "File > Open File or Project".
- Navigate to the project folder and select the project configuration file (`CMakeLists.txt` or `.pro`).
- Configure the project using your installed Qt Kit (e.g., MinGW 64-bit).

Step 4: Build and Run
- Click the "Configure Project" button if prompted.
- Click the "Build" button (hammer icon) or press Ctrl+B to compile the source code.
- Click the "Run" button (green play icon) or press Ctrl+R to launch the application.
- Enter the image filename (supported formats: .jpg, .png, .bmp, .tga) when prompted in the console/UI interface to begin applying filters.
