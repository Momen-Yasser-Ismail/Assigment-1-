================================================================================
  CS213: OBJECT-ORIENTED PROGRAMMING (OOP) - ASSIGNMENT 1 (PART 2)
  FACULTY OF COMPUTERS AND ARTIFICIAL INTELLIGENCE (FCAI), CAIRO UNIVERSITY
  SUPERVISOR: DR. MOHAMMAD EL-RAMLY
  DATE: 12 OCTOBER 2026
================================================================================

--------------------------------------------------------------------------------
1. PROJECT OVERVIEW & SCOPE
--------------------------------------------------------------------------------
Repository Link: https://github.com/Momen-Yasser-Ismail/Assigment-1-

This application allows users to load, process, apply multiple filters, and save
images. It supports both a command-line interface (Console Menu) and a modern 
Graphical User Interface (GUI).

--------------------------------------------------------------------------------
2. TEAM DETAILS & WORK BREAKDOWN
--------------------------------------------------------------------------------
Course: CS213 Object-Oriented Programming
Section: [Insert Section Number, e.g., S1, S2]

Team Members:
- Mo'men Yasser      (ID: 20251441) 	- Frame, Resize, Blur, and Infrared filters
- Adham Abdelrahman  (ID: 20250078) 	- Grayscale, Flip, Merge, and Sepia filters
- Ali Yasser 	     (ID: 20250407) 	- Black & White, Rotate, Detect Image Edges, and Televisions
- Yehia Nabil 	     (ID: 20250742) 	- Invert, Lighten/Darken, Crop, and Purple Effect

--------------------------------------------------------------------------------
3. SETUP AND ENVIRONMENT
--------------------------------------------------------------------------------
Tools & Compilers Used:
- Language: C++ (Standard C++17 or C++20)
- Compiler: GCC / MinGW g++ v11.0 or higher / MSVC
- GUI Framework: Qt Framework (Qt 5.15 / Qt 6.x)

--------------------------------------------------------------------------------
4. HOW TO COMPILE AND RUN THE CODE
--------------------------------------------------------------------------------

Option A CONSOLE VERSION (Command-Line Interface)
-------------------------------------------
1. Clone or Download the Repository
- Clone the repository to your local machine:
  git clone https://github.com/Momen-Yasser-Ismail/Assigment-1-.git

3. Run the executable "Console.cpp" file and Run the Code 

4. Follow the interactive menu in the console:
   - Option 1: Load Image
   - Option 2: Apply Filters (1 to 18 filters available)
   - Option 3: Save Image
   - Option 4: Exit

B. GUI VERSION (Graphical User Interface)
----------------------------------------
1. Launch Qt Creator.
2. Select "File" -> "Open File or Project..."
3. Navigate into the `GUI` folder and select the `CMakeLists.txt` file.
4. Configure the build kit (e.g., Desktop Qt 6.x MinGW 64-bit).
5. Build the project by pressing `Ctrl + B` (or clicking the hammer icon).
6. Run the project by pressing `Ctrl + R` (or clicking the green Play button).
7. Use the window buttons to load an image, select a filter from the menu/buttons, 
   preview the live effect, and save the output.

--------------------------------------------------------------------------------
5. FILE STRUCTURE SUMMARY FOR ZIP SUBMISSION
--------------------------------------------------------------------------------
Submission File Name: CS213_A1_Part2_SecNum_ID1_ID2_ID3_ID4.zip

Contents:
- Source Files (.cpp, .h, .hpp, Image_Class.h)
- Project Configuration File (.pro or CMakeLists.txt)
- Main C++ File with Header Details
- README.txt (This setup and running instructions file)
- Links.txt / Links.html (Direct links to Video Demo and Shared Document)

Note: Executable (.exe) files and external library binaries (Qt binaries) 
are excluded as per assignment guidelines.
================================================================================
