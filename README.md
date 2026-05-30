# Home Budget App

A simple C++ console application for tracking personal income and expenses.

The project was created to practice basic C++ programming concepts, including classes, objects, vectors, file handling, user input, and simple data persistence.

## Features

- Add income and expense transactions
- Store transaction data with date, category, type, amount, and description
- Display all saved transactions in a formatted table
- Calculate and display the current balance
- Save transactions to a JSON file
- Load transactions from a JSON file
- Use basic terminal colors to distinguish income and expenses

## Project Structure

The code is planned to be organized into separate header and source files:

```text
HomeBudget/
├── main.cpp
├── transaction.h
├── transaction.cpp
├── budget.h
└── budget.cpp
```

## File Responsibilities

```text
main.cpp
```

Contains the main menu and controls the flow of the program.

```
transaction.h
```

Declares the `Transaction` class. A header file describes what the class looks like and what functions are available.

```
transaction.cpp
```

Defines how the `Transaction` class functions actually work.

```
budget.h
```

Declares the `Budget` class, which stores and manages multiple transactions.

```
budget.cpp
```

Defines the logic for adding transactions, showing the balance, displaying all transactions, saving data, and loading data.

## How To Build

Using CMake:

```bash
cmake -S . -B build
cmake --build build
```

The executable will be created in the `build` directory.

You can also compile manually with `g++`:

```bash
g++ main.cpp budget.cpp transaction.cpp -o main
```

## How To Run

After building with CMake:

```bash
./build/home_budget
```

After compiling manually with `g++`:

```bash
./main
```

## Sample Data

The application saves and loads user data from `budget.json`.

This file is ignored by Git because it may contain private personal finance data. A sample file is included as `sample-budget.json` so the program can be tested quickly with example transactions.

To use the sample data, copy it to `budget.json`:

```bash
cp sample-budget.json budget.json
```

Then run the app and choose:

```
5. Load
3. All
```

## What I Practiced

- Creating and using classes
- Constructor initialization lists
- Getters and encapsulation
- `std::vector`
- Reading user input with `std::cin` and `std::getline`
- File handling with `std::ifstream` and `std::ofstream`
- Basic CSV-like file parsing
- JSON serialization with `nlohmann/json`
- Formatting output with `std::setw`, `std::fixed`, and `std::setprecision`
- Splitting code into `.h` and `.cpp` files
- Avoiding `using namespace std;` in larger projects
- Basic error handling while loading data from a file

## Future Improvements Roadmap

- [x] Refactor monolithic code into proper header (`.h`) and source (`.cpp`) files
- [x] Remove `using namespace std;` to avoid namespace pollution
- [x] Implement basic error handling for safer file parsing, including `std::stod` validation
- [x] Add input validation when adding a new transaction
- [x] Add option to delete a transaction
- [x] Add option to search or filter transactions by category
- [x] Add income and expense summaries
- [x] Prevent semicolons in fields saved to the transaction file
- [x] Add transactions sorting
- [x] Add transactions editing
- [x] Add CMake build configuration
- [x] Replace text file storage with JSON
- [ ] Move storage to SQLite

## Notes

This is a learning project. The goal is not only to build a working budget application, but also to show gradual progress in C++ code organization, readability, and safer data handling.
