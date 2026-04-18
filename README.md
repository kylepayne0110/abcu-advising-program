# ABCU Computer Science Advising Assistance Program

A command-line C++ application built for academic advisors in the Computer Science department at ABCU. The program allows advisors to load course data from a CSV file, view an alphanumerically sorted course list, and look up individual course details including prerequisites.

---

## Features

- Load course data from a CSV file into a hash table (unordered_map)
- Print all CS department courses sorted alphanumerically by course number
- Look up any course by number and display its title and prerequisites
- Case-insensitive course number input
- Input validation with error messaging for invalid menu options or bad file data

---

## Data Structure

This program uses an **unordered_map (hash table)** as the primary data structure, with the course number as the key and a `Course` object as the value. This provides O(1) average-case lookup for individual course queries. For the sorted course list, course numbers are extracted into a vector and sorted with `std::sort` — O(n log n).

---

## How to Compile and Run

### Using g++ (MinGW or Linux/Mac)
```bash
g++ ProjectTwo.cpp -o ProjectTwo
./ProjectTwo
```

### Using Visual Studio Developer Command Prompt
```bash
cl ProjectTwo.cpp
ProjectTwo.exe
```

---

## Usage

1. Run the program
2. Select **Option 1** to load the course data file
3. Enter the filename when prompted (e.g. `CS 300 ABCU_Advising_Program_Input.csv`)
4. Use the menu to print the course list or look up a specific course

### Menu Options
```
1. Load Data Structure
2. Print Course List
3. Print Course
9. Exit
```

### Sample Output
```
Welcome to the ABCU Computer Science Advising Assistance Program!
1. Load Data Structure.
2. Print Course List.
3. Print Course.
9. Exit.
What would you like to do? 2

CSCI100, Introduction to Computer Science
CSCI101, Introduction to Programming in C++
CSCI200, Data Structures
CSCI300, Introduction to Algorithms
CSCI301, Advanced Programming in C++
CSCI350, Operating Systems
CSCI400, Large Software Development
MATH201, Discrete Mathematics
```

```
What would you like to do? 3
Please enter the course number to print information for: csci400

CSCI400, Large Software Development
Prerequisites: CSCI301 CSCI350
```

---

## Input File Format

The CSV input file should follow this format:

```
courseNumber,courseName,prerequisite1,prerequisite2,...
```

- Every line must have at least a course number and course name
- Prerequisites are optional and listed by course number
- Lines with fewer than 2 fields are skipped with a warning

### Example (`CS 300 ABCU_Advising_Program_Input.csv`)
```
CSCI100,Introduction to Computer Science
CSCI101,Introduction to Programming in C++,CSCI100
CSCI200,Data Structures,CSCI101
MATH201,Discrete Mathematics
CSCI300,Introduction to Algorithms,CSCI200,MATH201
CSCI301,Advanced Programming in C++,CSCI101
CSCI350,Operating Systems,CSCI300
CSCI400,Large Software Development,CSCI301,CSCI350
```

---

## Runtime & Memory Analysis

| Operation | Complexity | Notes |
|---|---|---|
| Load file (Option 1) | O(n) | One parse + one hash insert per line, both O(1) |
| Print course list (Option 2) | O(n log n) | O(n) key extraction into vector + O(n log n) `std::sort` |
| Look up course (Option 3) | O(1) avg | Direct hash table access by course number key |

Loading is O(n) since we're just reading each line once and dropping it into the hash table. Lookup is where the hash table really earns its keep — O(1) average case means it doesn't matter if the catalog has 8 courses or 800, finding a specific course is effectively instant.

The sorted list is the one spot where the hash table costs us something. Since unordered_map has no concept of order, Option 2 pulls all the keys into a vector and sorts them, which bumps it to O(n log n). If printing the sorted list were the main thing this program did, I'd have used a `std::map` instead — it's a BST so it keeps keys sorted automatically and would make Option 2 just O(n). But advisors are going to be looking up individual courses way more often than printing the full list, so O(1) lookup was the right call.

Memory is O(n) overall — one Course object per entry in the table, each holding a couple strings and a small vector of prereqs. Nothing to worry about at this scale.

---

## Project Context

Built as Project Two for **CS-300: Data Structures and Algorithms** at Southern New Hampshire University (SNHU). The project demonstrates practical application of hash tables, file I/O, sorting, and modular C++ design.

---

## Author

**Kyle Payne**  
CS-300-13159-M01 | SNHU  
April 2026
